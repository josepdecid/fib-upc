from glob import glob

from bs4 import BeautifulSoup as bs
from collections import Counter
from tqdm import tqdm

from labs.s1.baseline_NER import tokenize

options = ['drug', 'drug_n', 'brand', 'group']
grouped_entities = {k: [] for k in options}

for file in tqdm(glob('project/data/Train/*'), desc='Reading files', ncols=100):
    with open(file, mode='r') as f:
        content = f.read().strip()
        bs_content = bs(content, 'lxml')
        entities = bs_content.find_all('entity')

        for entity in entities:
            if entity['type'] in options:
                grouped_entities[entity['type']].append(entity['text'])


def extract_multi_token_length(s: str):
    tokenized_sentence = tokenize(s)
    return len(tokenized_sentence)


def most_common_suffixes_of_length(a: int, d_type: str, n: int = None):
    filtered_entities = filter(lambda x: ' ' not in x, set(grouped_entities[d_type]))
    suffixes = list(map(lambda x: x[-a:], set(filtered_entities)))
    counter = Counter(suffixes)
    return counter.most_common(n)


# for d_type, suf_len in [('drug', 5), ('drug_n', 4), ('group', 4), ('brand', 5)]:
#     with open(f'labs/s1/{d_type}_suffixes.csv', 'w', newline='') as f:
#         writer = csv.writer(f)
#         writer.writerow(['Suffix', 'Count'])
#         for w, c in most_common_suffixes_of_length(suf_len, d_type):
#             writer.writerow([w, c])

for d_type in ['drug', 'drug_n', 'group', 'brand']:
    token_length_counter = Counter(map(lambda x: extract_multi_token_length(x), grouped_entities[d_type]))
    print(d_type, token_length_counter.most_common())

with open('labs/s1/group_words.txt', mode='w') as f:
    f.write('\n'.join(set(grouped_entities['group'])))
