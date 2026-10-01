import argparse
import os
import subprocess
from glob import glob
from typing import Dict, List, Tuple

from bs4 import BeautifulSoup as Bs
from nltk.parse.corenlp import CoreNLPDependencyParser
from tqdm import tqdm

from labs.s3.main import entity_to_indices, analyse, extract_head, least_common_parent, extract_parents, evaluate
from labs.s3.model import model_evaluate

MAP_SPECIAL_SYMBOLS = {
    '-LRB-': '(',
    '-RRB-': ')',
    '-LSB-': '[',
    '-RSB-': ']',
    '-LCB-': '{',
    '-RCB-': '}',
}

DEPENDENCY_PARSER = CoreNLPDependencyParser(url="http://localhost:9000")

EVAL_JAR_DIR = os.path.join('project', 'eval', 'evaluateDDI.jar')


def extract_features(analysis, entities: Dict[str, Tuple[int, int]], e1: str, e2: str) -> List[str]:
    feat_vector = ['bias']

    try:
        range_e1 = entity_to_indices(analysis, entities[e1])
        range_e2 = entity_to_indices(analysis, entities[e2])
    except AssertionError:
        # Error in some multi-part entities (a-b;c-d)
        return feat_vector

    e1_text = indices_to_text(analysis, range_e1)
    e2_text = indices_to_text(analysis, range_e2)

    feat_vector += [
        f'entity1={e1_text}',
        f'entity2={e2_text}'
    ]

    feat_vector += [
        f'entity1_suf4={e1_text[-4:]}',
        f'entity2_suf4={e2_text[-4:]}'
    ]

    head_e1 = extract_head(analysis, range_e1)
    parent_head_e1 = analysis[head_e1]['head']
    head_e2 = extract_head(analysis, range_e2)
    parent_head_e2 = analysis[head_e2]['head']

    if parent_head_e1 is not None:
        feat_vector += [
            f'entity1_rel={analysis[head_e1]["rel"]}',
            f'entity1_parent_lemma={analysis[parent_head_e1]["lemma"]}'
        ]

    if parent_head_e2 is not None:
        feat_vector += [
            f'entity2_rel={analysis[head_e2]["rel"]}',
            f'entity2_parent_lemma={analysis[parent_head_e2]["lemma"]}',
        ]

    lcp = least_common_parent(analysis, head_e1, head_e2)
    cp = extract_parents(analysis, lcp)
    feat_vector += [f'parent={analysis[i]["lemma"]}' for i in cp]
    if head_e1 in cp or head_e2 in cp:
        feat_vector += ['one_parent_of_other']

    if lcp == head_e1:
        feat_vector += [f'direct_parenthood={analysis[head_e2]["rel"]}']
    if lcp == head_e2:
        feat_vector += [f'direct_parenthood={analysis[head_e1]["rel"]}']

    for p in cp:
        if analysis[p]['tag'] == 'VB':
            feat_vector += [f'verb={analysis[p]["lemma"]}']

    return feat_vector


def indices_to_text(analysis, index_range):
    text = [analysis[i]['lemma'] for i in index_range]
    return '_'.join(text)


def output_features(s_id, e1, e2, e_type, features, mode) -> None:
    with open(f'{mode}_feats.dat', mode='a') as f:
        f.write('\t'.join([s_id, e1, e2, e_type, *features]) + '\n')

    with open(f'{mode}_feats_megam.dat', mode='a') as f:
        f.write('\t'.join([e_type, *features]) + '\n')


def parse_documents(input_dir: str, mode: str):
    output_data = ''
    for file in tqdm(glob(os.path.join(input_dir, '*')), ncols=100, desc='Detecting DDI'):
        # parse XML file, obtaining a DOM tree
        with open(file, mode='r') as f:
            content = f.read().strip()
            tree = Bs(content, 'lxml')
            # process each sentence in the file
            sentences = tree.find_all("sentence")
            for s in sentences:
                sid = s["id"]  # get sentence id
                s_text = s["text"]  # get sentence text
                if s_text == '':
                    continue
                # load sentence entities into a dictionary
                entities = {}
                ents = s.find_all('entity')
                for e in ents:
                    id_ = e['id']
                    if ';' in e['charoffset']:
                        parts = e['charoffset'].split(';')
                        offs = [parts[0].split('-')[0], parts[-1].split('-')[1]]
                    else:
                        offs = e['charoffset'].split("-")
                    entities[id_] = int(offs[0]), int(offs[1])
                # Tokenize, tag, and parse sentence
                analysis = analyse(s_text)
                # for each pair in the sentence, decide whether it is DDI and its type
                pairs = s.find_all('pair')
                for p in pairs:
                    id_e1 = p['e1']
                    id_e2 = p['e2']
                    try:
                        ground = p['type'] if p['ddi'] == 'true' else 'null'
                    except KeyError:
                        ground = 'null'
                    features = extract_features(analysis, entities, id_e1, id_e2)
                    output_features(sid, id_e1, id_e2, ground, features, mode)

    return output_data


def interact_recognitor(input_dir_train: str, input_dir_eval: str, output_file: str) -> None:
    # process each file in directory
    parse_documents(input_dir_train, 'train')
    output_data = parse_documents(input_dir_eval, 'test')

    with open(output_file, mode='w') as f:
        f.write(output_data)

    model_weight = subprocess.run(args=['./project/models/megam_osx.opt',
                                        '-quiet', '-nc', '-nobias', 'multiclass', 'train_feats_megam.dat'],
                                  stdout=subprocess.PIPE)

    with open('labs/s3/model.dat', mode='w') as f:
        f.write(model_weight.stdout.decode('utf-8'))

    model_evaluate()

    # get performance score
    evaluate(input_dir_eval, output_file)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='MAI-AHLT Session 3, - DDI baseline')

    parser.add_argument('input_dir_train', type=str, help='Training dataset path')
    parser.add_argument('input_dir_eval', type=str, help='Evaluation dataset path')
    parser.add_argument('output_dir', type=str, help='Output path')

    args = parser.parse_args()

    open('train_feats.dat', mode='w').close()
    open('test_feats.dat', mode='w').close()
    open('train_feats_megam.dat', mode='w').close()
    open('test_feats_megam.dat', mode='w').close()
    open(args.output_dir, mode='w').close()

    interact_recognitor(args.input_dir_train, args.input_dir_eval, args.output_dir)
