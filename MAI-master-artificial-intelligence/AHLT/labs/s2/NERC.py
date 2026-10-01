import argparse
import os
import re
import string
from datetime import datetime
from glob import glob
from typing import List, Tuple, Union

import pycrfsuite
from bs4 import BeautifulSoup as Bs
from bs4.element import Tag
from tqdm import tqdm

from labs.s1.baseline_NER import tokenize, evaluate

CRF_MODEL_NAME = os.path.join('labs', 's2', 'crf.model')

HSDB = set()
DRUG_BANK = dict(drug=set(), drug_n=set(), group=set(), brand=set())


def extract_features(tokenized_sentence: List[Tuple[str, int, int]]) -> List[List[str]]:
    """
    Extract features from a tokenized sentence to fit a ML classifier model.

    Parameters
    ----------
    tokenized_sentence : List[Tuple[str, int, int]]
        List of tuples containing each token information formatted as <Token, start_idx, end_idx>

    Returns
    -------
    List[List[str]]
        A list of binary features (represented as strings) for each token of the sentence.
    """
    features = []
    for idx, (token, offset_from, offset_to) in enumerate(tokenized_sentence):
        # Token, suffixes, and previous + next word
        token_features = ['bias',
                          f'form={token.lower()}',
                          f'pre4={token[:4].lower()}',
                          f'suf4={token[-4:].lower()}',
                          f'next={tokenized_sentence[idx + 1][0].lower() if idx + 1 < len(tokenized_sentence) else "_EoS_"}',
                          f'prev={tokenized_sentence[idx - 1][0].lower() if idx - 1 >= 0 else "_BoS_"}']

        # Case (Upper, Capitalized, Lower or Mixed)
        if token.isupper():
            token_features.append('upper')
        elif token[0].isupper():
            token_features.append('capitalized')
        elif token.islower():
            token_features.append('lower')
        elif token.isalnum():
            token_features.append('mixed-case')

        # Type of characters (punctuation, alphanumeric, digit or containing hyphens
        if '-' in token:
            if string.ascii_lowercase in token.lower() and string.punctuation in token:
                token_features.append('mixed-hyphen')
            token_features.append('hyphen')
        elif token in string.punctuation or token in ["''", "``", '""']:
            token_features.append('punctuation')
        elif token.isdigit():
            token_features.append('numeric')
        elif token.isalpha():
            token_features.append('alpha')
        else:
            token_features.append('alphanumeric')

        # Quantized token length into 4 bins (<5, <10, <15, >=15)
        if len(token) < 5:
            token_features.append(f'len=<5')
        elif len(token) < 10:
            token_features.append(f'len=<10')
        elif len(token) < 15:
            token_features.append(f'len=<15')
        else:
            token_features.append(f'len=>=15')

        if token.lower() in HSDB:
            token_features.append('HSDB')

        if token.lower() in DRUG_BANK['drug']:
            token_features.append('DRUG_BANK_DRUG')
        elif token.lower() in DRUG_BANK['drug_n']:
            token_features.append('DRUG_BANK_DRUG_N')
        elif token.lower() in DRUG_BANK['brand']:
            token_features.append('DRUG_BANK_BRAND')
        elif token.lower() in DRUG_BANK['group']:
            token_features.append('DRUG_BANK_GROUP')

        features.append(token_features)

    return features


def output_features(s_id: str, tokenized_sentence: List[Tuple[str, int, int, str]], features: List[List[str]],
                    output_dir: str = None) -> None:
    """
    Print to a file or stdout the features vectors for a sentence.

    Parameters
    ----------
    s_id : str
        Sentence identifier.
    tokenized_sentence : List[Tuple[str, int, int, str]]
        List of tuples containing each token information formatted as <Token, start_idx, end_idx, gold_class>
    features : List[List[str]]
        List of binary features (represented as strings) for each token of the sentence.
    output_dir : str, optional, default=None
        File path to print the output to. If set as `None` (default behavior) it prints to the stdout.
    """
    output_data = []
    for token_info, token_features in zip(tokenized_sentence, features):
        output = [s_id, *[str(x) for x in token_info], *token_features]
        output_data.append('\t'.join(output))

    if output_dir is None:
        print('\n'.join(output_data) + '\n')
    else:
        with open(output_dir, mode='a') as f:
            f.write('\n'.join(output_data) + '\n')


def parse_gold_sentence_entities(tokenized_sentence: List[Tuple[str, int, int]],
                                 sentence: Tag, is_eval: bool = False) -> List[Tuple[str, int, int, Union[str, None]]]:
    """
    Parse gold class from the training XML data in IOB format.

    Parameters
    ----------
    tokenized_sentence : List[Tuple[str, int, int]]
        List of tuples containing each token information formatted as <Token, start_idx, end_idx>
    sentence : bs4.element.Tag
        XML formatted sentence data.
    is_eval : bool, optional, default=False

    Returns
    -------
    List[Tuple[str, int, int, str]]
        Extended tokenized_sentence containing the gold class tag in IOB format as the last element in the tuple.
    """
    # In evaluation mode we don't have access to real entities tags.
    # Hence, we just set them as `O` tags.
    if is_eval:
        return [(token, start, end, None) for token, start, end in tokenized_sentence]

    entities = sentence.find_all('entity')

    if len(entities) == 0:
        return [(token, start, end, 'O') for token, start, end in tokenized_sentence]

    def parse_entity(entity) -> Tuple[str, int, int]:
        offsets = list(map(int, re.split(r'[-;]', entity['charoffset'])))
        return entity['type'], int(offsets[0]), int(offsets[-1])

    def generate_iob(tag: str, type: str = None):
        return token, start, end, 'O' if tag == 'O' else f'{tag}-{type}'

    entities: List[Tuple[str, int, int]] = [parse_entity(e) for e in entities]

    idx_e = 0
    e_type, e_start, e_end = entities[idx_e]

    is_inside = False
    end_entities = False

    output_token_list = []
    for token, start, end in tokenized_sentence:
        # Evaluate the following obtained entity.
        if not end_entities and start > e_end:
            is_inside = False
            idx_e += 1
            if idx_e >= len(entities):
                end_entities = True
            else:
                e_type, e_start, e_end = entities[idx_e]

        # If last sentence has been already added, mark all the following tokens as `O`.
        if end_entities:
            output_token_list.append(generate_iob('O'))

        # If the entity start corresponds to the token start mark it as `B`.
        elif start == e_start:
            output_token_list.append(generate_iob('B', e_type))
            is_inside = True

        # If the token is between the entity start and end mark it as `B` or `I` depending on there is a previous `B`.
        elif start >= e_start and end <= e_end:
            iob_tag = 'I' if is_inside else 'B'
            output_token_list.append(generate_iob(iob_tag, e_type))

        # Otherwise, mark it as `O` and discard any possible immediate `I`.
        else:
            output_token_list.append(generate_iob('O'))
            is_inside = False

    return output_token_list


def output_entities(s_id: str, tokenized_sentence: List[Tuple[str, int, int, Union[str, None]]], predictions: List[str],
                    output_dir: str) -> None:
    """
    Outputs entities of a sentence with the following format: `{s_id}|{offset}|{token}|{category}`

    Parameters
    ----------
    s_id : str
        Sentence identifier.
    tokenized_sentence : List[str, int, int, Union[str, None]]
        List of tuples containing each token information formatted as <Token, start_idx, end_idx, gold_class>
        `gold_class` is None when dealing with evaluation dataset.
    predictions : List[str]
        List of predictions for the sentence in IOB format.
    output_dir : str
        File path to print the output to.
    """
    output_data = []
    c_entity = None

    for (token, start, end, _), prediction in zip(tokenized_sentence, predictions):
        if c_entity is not None:
            if prediction.startswith('I-'):
                c_entity = (f'{c_entity[0]} {token}', c_entity[1], end, c_entity[3])
            else:
                offset = f'{c_entity[1]}-{c_entity[2]}'
                output_data.append(f'{s_id}|{offset}|{c_entity[0]}|{c_entity[3]}')
                c_entity = None

        if prediction.startswith('B-'):
            c_entity = (token, start, end, prediction[2:])

    if c_entity is not None:
        offset = f'{c_entity[1]}-{c_entity[2]}'
        output_data.append(f'{s_id}|{offset}|{c_entity[0]}|{c_entity[3]}')

    output_data = '\n'.join(output_data)
    if len(output_data) > 0:
        output_data += '\n'

    with open(output_dir, mode='a') as f:
        f.write(output_data)


def run_phase(mode: str, input_dir: str, output_dir: str) -> None:
    if mode == 'train':
        model = pycrfsuite.Trainer(verbose=False)
        model.set_params({
            'c1': 0.1,  # L1 penalty
            'c2': 0.01,  # L2 penalty
            'max_iterations': 200,  # maximum number of iterations
            'feature.possible_transitions': True  # whether to include transitions that are possible, but not observed
        })
    else:
        model = pycrfsuite.Tagger()
        model.open(CRF_MODEL_NAME)

    pb_desc = 'Parsing training data' if mode == 'train' else 'Predicting entities'
    for file in tqdm(glob(os.path.join(input_dir, '*')), ncols=100, desc=pb_desc):
        output_features_path = os.path.sep.join(output_dir.split(os.path.sep)[:-1])

        with open(file, mode='r') as f:
            content = f.read().strip()
            bs_content = Bs(content, 'lxml')
            sentences = bs_content.find_all('sentence')
            for sentence in sentences:
                sid, text = sentence['id'], sentence['text']
                tokens_list = tokenize(text)

                features = extract_features(tokens_list)

                tokens_list = parse_gold_sentence_entities(tokens_list, sentence, is_eval=mode != 'train')
                output_features(sid, tokens_list, features, os.path.join(output_features_path, f'features_{mode}.txt'))

                if mode == 'train':
                    model.append(features, list(map(lambda x: x[3], tokens_list)))
                else:
                    prediction = model.tag(features)
                    output_entities(sid, tokens_list, prediction, output_dir)

    if mode == 'train':
        print('Training CRF model...')
        start_time = datetime.now()
        model.train(CRF_MODEL_NAME)
        print(f'Model trained in {(datetime.now() - start_time).seconds}s')


def extract_external_information():
    global HSDB
    with open(os.path.join('project', 'resources', 'HSDB.txt'), mode='r') as f:
        lines = f.read().strip().split('\n')
        for entry in lines:
            tokens = tokenize(entry)
            for token, _, _ in tokens:
                HSDB.add(token.lower())

    global DRUG_BANK
    with open(os.path.join('project', 'resources', 'DrugBank.txt'), mode='r') as f:
        lines = f.read().strip().split('\n')
        for line in lines:
            entry, entry_type = line.strip().split('|')
            tokens = tokenize(entry)
            for token, _, _ in tokens:
                DRUG_BANK[entry_type].add(token.lower())


def nerc(input_dir: str, input_dir_eval: str, output_dir: str, goal: int) -> None:
    if goal == 5:
        extract_external_information()
    run_phase('train', input_dir, output_dir)
    run_phase('eval', input_dir_eval, output_dir)
    evaluate(input_dir_eval, output_dir)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='MAI-AHLT Session 2 - NERC using machine learning')

    parser.add_argument('goal', type=int, choices=[4, 5],
                        help='Whether to execute deliverable GOAL-4 (using only train dataset information)'
                             'or GOAL-5 (using external knowledge sources)')
    parser.add_argument('input_dir', type=str, help='Training dataset path')
    parser.add_argument('input_dir_eval', type=str, help='Evaluation dataset path')
    parser.add_argument('output_dir', type=str, help='Output path')

    args = parser.parse_args()

    open(args.output_dir, mode='w').close()  # Nuke outputs
    nerc(args.input_dir, args.input_dir_eval, args.output_dir, args.goal)
