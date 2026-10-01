import difflib

from labs.s1.baseline_NER import tokenize, extract_entities

with open('goldNER.txt', 'r') as f:
    gold_lines = f.read().strip().split('\n')
    gold_lines.sort()

with open('labs/s1/task9.1_VJ_42.txt', 'r') as f:
    out_lines = f.read().strip().split('\n')
    out_lines.sort()

for line in difflib.unified_diff(gold_lines, out_lines):
    # if (line.endswith('drug') or line.endswith('drug_n')) and line[0] != ' ':
    if (line.endswith('drug_n')) and line[0] == '-':
        print(line)

        tokenized = tokenize(line.split('|')[-2])
        print(tokenized)
        # entities = extract_entities(tokenized)
        # print(line, '\n', tokenized, '\n', entities, '\n')
