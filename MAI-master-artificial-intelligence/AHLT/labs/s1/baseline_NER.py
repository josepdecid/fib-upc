import argparse
import os
import string
from glob import glob
from typing import List, Tuple, Dict

from bs4 import BeautifulSoup as Bs
from nltk import word_tokenize
from nltk.corpus import stopwords
from tqdm import tqdm

from labs.s1.extract import extract_grouped_entities, extract_most_common_suffixes

STOPWORDS = set(stopwords.words('english'))

TYPE_WORDS = {}
COMMON_SUFFIXES = {}

EVAL_JAR_DIR = os.path.join('project', 'eval', 'evaluateNER.jar')


def tokenize(sentence: str) -> List[Tuple[str, int, int]]:
    """
    Tokenize a sentence to obtain each token and its start and end position inside the sentence.

    Parameters
    ----------
    sentence : str
        Plain text sentence.

    Returns
    -------
    List[Tuple[str, int, int]]
        List of tokens that constitute the sentence with the associated start and end position.

    """
    tokenized_output = []
    tokenized_words = word_tokenize(sentence)

    i = 0
    for word in tokenized_words:
        word_pos = sentence.find(word, i)
        tokenized_output.append((word, word_pos, word_pos + len(word) - 1))
        i = word_pos + len(word)

    return tokenized_output


def extract_entities(tokenized_sentence: List[Tuple[str, int, int]], sentence: str) -> List[Dict[str, str]]:
    """
    Extract entities applying a list of rules to the tokenized sentence.

    Parameters
    ----------
    tokenized_sentence : List[Tuple[str, int, int]]
         List of tokens that constitute the sentence with the associated start and end position.
    sentence : str
        Plain text sentence.

    Returns
    -------
    List[Dict[str, str]]
        List of entities for the given sentence, where the entity is described with a dictionary with the following
        format: {'name': 'test', 'offset': '0-3', 'type': 'drug'}. Possible types: ['drug', 'drug_n', 'group', 'brand'].
    """
    extracted_entities = []
    marked_iob = []

    def mark_as_(d_type: str = None):
        marked_iob.append(d_type)

    def output_as_(d_type: str, name: str, offset: str):
        drug_info = {'name': name, 'offset': offset, 'type': d_type}
        extracted_entities.append(drug_info)

    def detect_multi(acceptable_tags, tag_to_mark):
        if tag in acceptable_tags:
            idx_g = 1
            if idx + idx_g < len(marked_iob) and marked_iob[idx + idx_g] in acceptable_tags:
                marked_iob[idx] = None
                while idx + idx_g < len(marked_iob) and marked_iob[idx + idx_g] in acceptable_tags:
                    marked_iob[idx + idx_g] = None
                    idx_g += 1

                end = tokenized_sentence[idx + idx_g - 1][2]
                group_sentence = sentence[start:end]
                output_as_(tag_to_mark, group_sentence, f'{start}-{end}')

    for idx, (token, _, _) in enumerate(tokenized_sentence):
        if token.lower() in ['cannabis', 'cocaine', 'amphetamine', 'nitrites', 'cocaine',
                             'ecstasy', 'lsd', 'heroin', 'crack', 'lithium']:
            mark_as_('drug')
        elif token in STOPWORDS or token in string.punctuation or token in ["''", "``", '""']:
            mark_as_(None)
        elif token in TYPE_WORDS['group']:
            mark_as_('group')
        elif token.isupper() and '-' in token:
            mark_as_('drug_n')
        elif any(map(lambda x: x in token, ['PGE2', 'CMC', 'EFG', '(V)', '(-)'])):
            mark_as_('drug_n')
        elif token.lower().startswith(('alpha-', 'beta-')):
            mark_as_('drug_n')
        elif token.isupper():
            mark_as_('brand')

        # Common suffixes
        elif any(map(lambda x: token.endswith(x), COMMON_SUFFIXES['drug'])):
            mark_as_('drug' if '-' not in token else 'drug_n')
        elif any(map(lambda x: token.endswith(x), COMMON_SUFFIXES['group'])):
            mark_as_('group')
        elif any(map(lambda x: token.endswith(x), COMMON_SUFFIXES['brand'])):
            mark_as_('brand')

        # Matching words by type
        elif token in TYPE_WORDS['drug']:
            mark_as_('drug')
        elif token in TYPE_WORDS.get('multi-group', []):
            mark_as_('m-group')
        elif token in TYPE_WORDS.get('multi-drug', []):
            mark_as_('drug_n')
        elif token in TYPE_WORDS.get('multi-brand', []):
            mark_as_('m-brand')

        # By default, mark anything else as `None` to filter them out when parsing together multi-tokens.
        else:
            mark_as_(None)

    # Multi-token

    for idx, (tag, (token, start, end)) in enumerate(zip(marked_iob, tokenized_sentence)):
        detect_multi(['group', 'm-group'], 'group')
        detect_multi(['drug', 'drug_n'], 'drug_n')
        detect_multi(['brand', 'm-brand'], 'brand')

    for tag, (token, start, end) in zip(marked_iob, tokenized_sentence):
        if tag is not None and tag != 'm-group':
            interval = f'{start}-{end}'
            output_as_(tag, token, interval)

    return extracted_entities


def output_entities(s_id: str, entities: List[Dict[str, str]], output_dir: str) -> None:
    """
    Outputs entities of a sentence with the following format: `{s_id}|{offset}|{token}|{category}`

    Parameters
    ----------
    s_id : str
        Sentence identifier.
    entities : List[Dict[str, str]]
        List of entities for the given sentence, where the entity is described with a dictionary with the following
        format: {'name': 'test', 'offset': '0-3', 'type': 'drug'}. Possible types: ['drug', 'drug_n', 'group', 'brand'].
    output_dir : str
        File path to print the output to.
    """
    output_data = []
    for entity in entities:
        output_data.append(f'{s_id}|{entity["offset"]}|{entity["name"]}|{entity["type"]}')

    output_data = '\n'.join(output_data)
    if len(output_data) > 0:
        output_data += '\n'

    with open(output_dir, mode='a') as f:
        f.write(output_data)


def evaluate(input_dir: str, output_dir: str) -> None:
    os.system(f'java -jar {EVAL_JAR_DIR} {input_dir} {output_dir}')


def extract_data_information(input_dir: str, goal: int):
    global TYPE_WORDS
    TYPE_WORDS = extract_grouped_entities(input_dir)
    TYPE_WORDS['multi-group'] = word_tokenize(' '.join(TYPE_WORDS['group']))

    global COMMON_SUFFIXES
    COMMON_SUFFIXES = extract_most_common_suffixes(TYPE_WORDS)

    if goal == 2:
        # For the second goal, we extract information from external knowledge sources such as:
        # - HSDB (Hazardous Substances Data Bank)
        # - Drug Bank
        with open(os.path.join('project', 'resources', 'HSDB.txt'), mode='r') as f:
            TYPE_WORDS['drug'] += f.read().split('\n')

        with open(os.path.join('project', 'resources', 'DrugBank.txt'), mode='r') as f:
            for line in f.readlines():
                sentence, token_type = line.strip().split('|')
                tokenized_sentence = tokenize(sentence)
                if len(tokenized_sentence) > 1:
                    if f'multi-{token_type}' not in TYPE_WORDS.keys():
                        TYPE_WORDS[f'multi-{token_type}'] = []
                    TYPE_WORDS[f'multi-{token_type}'] += tokenized_sentence
                else:
                    TYPE_WORDS[token_type] += sentence

    for k, v in COMMON_SUFFIXES.items():
        COMMON_SUFFIXES[k] = set(v)


def nerc(input_dir: str, input_dir_eval: str, goal: int, output_dir: str) -> None:
    extract_data_information(input_dir, goal)
    for file in tqdm(glob(os.path.join(input_dir_eval, '*')), ncols=100, desc='Detecting NERC'):
        with open(file, mode='r') as f:
            content = f.read().strip()
            bs_content = Bs(content, 'lxml')
            sentences = bs_content.find_all('sentence')
            for sentence in sentences:
                sid, text = sentence['id'], sentence['text']
                token_list = tokenize(text)
                entities = extract_entities(token_list, text)
                output_entities(sid, entities, output_dir)
    evaluate(input_dir_eval, output_dir)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='MAI-AHLT Session 1, - NERC baseline')

    parser.add_argument('goal', type=int, choices=[1, 2],
                        help='Whether to execute deliverable GOAL-2 (using only train dataset information)'
                             'or GOAL-2 (using external knowledge sources)')

    parser.add_argument('input_dir', type=str, help='Training dataset path')
    parser.add_argument('input_dir_eval', type=str, help='Evaluation dataset path')
    parser.add_argument('output_dir', type=str, help='Output path')

    args = parser.parse_args()

    open(args.output_dir, mode='w').close()
    nerc(args.input_dir, args.input_dir_eval, args.goal, args.output_dir)
