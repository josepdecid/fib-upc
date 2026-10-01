import argparse
import os
import re
from glob import glob
from typing import Dict, Union, List, Tuple

from bs4 import BeautifulSoup as Bs
from nltk.parse.corenlp import CoreNLPDependencyParser
from tqdm import tqdm

MAP_SPECIAL_SYMBOLS = {
    '-LRB-': '(',
    '-RRB-': ')',
    '-LSB-': '[',
    '-RSB-': ']',
    '-LCB-': '{',
    '-RCB-': '}',
}

DEPENDENCY_PARSER = CoreNLPDependencyParser(url='http://localhost:9000')

EVAL_JAR_DIR = os.path.join('project', 'eval', 'evaluateDDI.jar')


def check_interaction(analysis, entities: Dict[str, Tuple[int, int]], e1: str, e2: str) -> Tuple[str, str]:
    try:
        range_e1 = entity_to_indices(analysis, entities[e1])
        range_e2 = entity_to_indices(analysis, entities[e2])
    except AssertionError:
        # Error in some multi-part entities (a-b;c-d)
        return '0', 'null'

    head_e1 = extract_head(analysis, range_e1)
    head_e2 = extract_head(analysis, range_e2)

    lcp = least_common_parent(analysis, head_e1, head_e2)

    keywords_by_type = {
        'effect': ['administer', 'potentiate', 'prevent'],
        'mechanism': ['reduce', 'increase', 'decrease'],
        'advise': ['should', 'recommend', 'avoid'],
        'int': ['interact', 'interaction']
    }

    for y_type, keywords in keywords_by_type.items():
        if any(map(lambda key: analysis[key]['lemma'] in keywords, extract_parents(analysis, lcp))):
            return '1', y_type

    return '0', 'null'


def entity_to_indices(analysis, entity_offset: Tuple[int, int]) -> Tuple[int, int]:
    start, end = None, None
    for key, value in analysis.items():
        if key == 0:
            continue
        if value['start'] <= entity_offset[0] <= value['end']:
            start = key
        if value['start'] <= entity_offset[1] <= value['end']:
            end = key
        if start is not None and end is not None:
            break
    assert start is not None and end is not None, f'{analysis} ||| {entity_offset}'
    return start, end


def extract_head(analysis, indices):
    for i in range(indices[0], indices[1] + 1):
        head = analysis[i]['head']
        if head < indices[0] or head > indices[1]:
            return head


def extract_parents(analysis, head: int) -> List[int]:
    parent = head
    parents = []
    while parent is not None:
        parents.append(parent)
        parent = analysis[parent]['head']
    return parents


def least_common_parent(analysis, head1: int, head2: int) -> int:
    parents1 = extract_parents(analysis, head1)
    parents2 = extract_parents(analysis, head2)

    for parent in parents1:
        if parent in parents2:
            return parent


def analyse(s: str) -> Dict[int, Dict[str, Union[str, int]]]:
    # HTML symbols
    s = re.sub(r'&#..;', '|', s)
    s = s.replace('\n', '|')
    s = s.replace('\r', '|')
    tree, = DEPENDENCY_PARSER.raw_parse(s)
    nodes = tree.nodes
    result = dict()
    for key, content in nodes.items():
        result[key] = {k: content[k] for k in ['head', 'word', 'rel', 'tag', 'lemma']}

    i = 0
    for key in range(len(result)):
        word = result[key]['word']
        if word is not None:
            if word in MAP_SPECIAL_SYMBOLS.keys():
                word = MAP_SPECIAL_SYMBOLS[word]

            word_pos = s.find(word, i)

            result[key]['start'] = word_pos
            result[key]['end'] = word_pos + len(word) - 1

            i = word_pos + len(word)

    return result


def evaluate(input_dir: str, output_dir: str) -> None:
    os.system(f'java -jar {EVAL_JAR_DIR} {input_dir} {output_dir}')


def interact_recognitor(input_dir_eval: str, output_file: str) -> None:
    # process each file in directory
    output_data = ''
    for file in tqdm(glob(os.path.join(input_dir_eval, '*')), ncols=100, desc='Detecting DDI'):
        # parse XML file, obtaining a DOM tree
        with open(file, mode='r') as f:
            content = f.read().strip()
            tree = Bs(content, 'lxml')
            # process each sentence in the file
            sentences = tree.find_all('sentence')
            for s in sentences:
                s_id = s['id']
                s_text = s['text']

                # Skip sentences with empty text
                if s_text == '':
                    continue

                # Load sentence entities into a dictionary
                entities = {}
                text_entities = s.find_all('entity')
                for e in text_entities:
                    e_id = e['id']
                    # Multi-token entities formatted as [a-b;c-d]
                    # Take range as [a-d]
                    if ';' in e['charoffset']:
                        parts = e['charoffset'].split(';')
                        offs = [parts[0].split('-')[0], parts[-1].split('-')[1]]
                    else:
                        offs = e['charoffset'].split('-')
                    entities[e_id] = int(offs[0]), int(offs[1])

                # Tokenize, tag, and parse the sentence
                analysis = analyse(s_text)

                # For each pair in the sentence, decide whether it is DDI and its type
                pairs = s.find_all('pair')
                for p in pairs:
                    id_e1 = p['e1']
                    id_e2 = p['e2']
                    (is_ddi, ddi_type) = check_interaction(analysis, entities, id_e1, id_e2)
                    output_data += '|'.join([s_id, id_e1, id_e2, is_ddi, ddi_type]) + '\n'

    # Store output data into the corresponding file
    with open(output_file, mode='w') as f:
        f.write(output_data)

    # Get performance score
    evaluate(input_dir_eval, output_file)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='MAI-AHLT Session 3, - DDI baseline')

    parser.add_argument('input_dir_eval', type=str, help='Evaluation dataset path')
    parser.add_argument('output_dir', type=str, help='Output path')

    args = parser.parse_args()
    interact_recognitor(args.input_dir_eval, args.output_dir)
