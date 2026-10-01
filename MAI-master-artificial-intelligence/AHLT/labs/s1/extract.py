import os
from collections import Counter, defaultdict
from glob import glob
from typing import List, Dict, Tuple, Set

from bs4 import BeautifulSoup as Bs
from tqdm import tqdm


def extract_grouped_entities(input_dir: str) -> Dict[str, List[str]]:
    options = ['drug', 'drug_n', 'brand', 'group']
    grouped_entities = {k: [] for k in options}

    for file in tqdm(glob(os.path.join(input_dir, '*')), desc='Reading files', ncols=100):
        with open(file, mode='r') as f:
            content = f.read().strip()
            bs_content = Bs(content, 'lxml')
            entities = bs_content.find_all('entity')

            for entity in entities:
                if entity['type'] in options:
                    grouped_entities[entity['type']].append(entity['text'])

    return grouped_entities


def extract_most_common_suffixes(grouped_entities: Dict[str, List[str]]) -> Dict[str, Set[str]]:
    """
    Extract most common suffixes from the given grouped entities.

    Parameters
    ----------
    grouped_entities : Dict[str, List[str]]
        Entities grouped by type (`drug`, `drug_n`, `brand` or `group`).

    Returns
    -------
    Dict[str, Set[str]]
        Most common suffixes grouped by type analogously to the input format.
    """

    def most_common_suffixes_of_length(n: int) -> List[Tuple[str, int]]:
        filtered_entities = filter(lambda x: ' ' not in x, set(grouped_entities[d_type]))
        suffixes = list(map(lambda x: x[-n:], set(filtered_entities)))
        counter = Counter(suffixes)
        return counter.most_common()

    most_common_suffixes = defaultdict(set)
    for d_type, suf_len in [('drug', 5), ('drug_n', 4), ('group', 4), ('brand', 5)]:
        # Extract most common suffixes of the given length for the corresponding type.
        for w, _ in most_common_suffixes_of_length(suf_len):
            most_common_suffixes[d_type].add(w)

    return most_common_suffixes
