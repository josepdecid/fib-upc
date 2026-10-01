# Pair of coords (None if unused)
problem_number = 1
spacecrafts = {
    'Red':    (5, 5),
    'Orange': (1, 5),
    'Yellow': (4, 4),
    'Green':  (2, 3),
    #'Blue':   (5, 5),
    'Purple': (3, 2)
}

with open('lunar_lockout_template.pddl', mode='r') as pf:
    lines = pf.readlines()
    lines[0] = f'(define (problem lunar-lockout{problem_number})\n'
    code = ''.join(lines)
    
    codified_at = []
    codified_empty = []

    for i in range(1, 6):
        for j in range(1, 6):
            occupied = False
            for s_name, s_coords in spacecrafts.items():
                if s_coords == (i, j):
                    occupied = True
                    codified_at.append(f'\t\t(at {s_name} C{i} C{j})')
            
            if not occupied:
                codified_empty.append(f'\t\t(empty C{i} C{j})')

    codified_problem = '\n'.join(codified_at) + '\n\n' + '\n'.join(codified_empty)

    code = code.replace(';@ SPECIFIC PROBLEM @;', codified_problem, 1)

    with open(f'lunar_lockout_{problem_number}.pddl', mode='w') as f:
        f.write(code)