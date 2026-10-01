problem_number = 3
config = {
    'N': 4,
    'R': (0, 0),
    'G': (3, 3),
    'sequence': [
        (3, 3),
        (2, 3),
        (3, 3),
        (3, 2),
        (3, 3),
        (2, 3)
    ],
    'costs': [
        [1, 1, 1, 1],
        [1, 1, 1, 1],
        [1, 1, 1, 1],
        [1, 1, 1, 1]
    ]
}

with open('moving_target_template.pddl', mode='r') as pf:
    lines = pf.readlines()
    lines[0] = f'(define (problem moving-target{problem_number})\n'
    code = ''.join(lines)

    coords = '\t\t' + ' '.join(['C' + str(i) for i in range(config['N'])]) + ' - coord'
    code = code.replace('{% COORDS %}', coords, 1)

    timesteps = '\t\t' + ' '.join(['T' + str(i) for i in range(len(config['sequence']))]) + ' - time'
    code = code.replace('{% TIMESTEPS %}', timesteps, 1)

    next_coords = ''
    for i in range(config['N'] - 1):
        next_coords += f'\t\t(next C{i} C{i + 1}) (next C{i + 1} C{i})\n'
    code = code.replace('{% NEXT_COORDS %}', next_coords[:-1], 1)

    next_timesteps = ''
    for i in range(len(config['sequence']) - 1):
        next_timesteps += f'\t\t(next T{i} T{i + 1})\n'
    code = code.replace('{% NEXT_TIMESTEPS %}', next_timesteps[:-1], 1)

    costs = ''
    for i in range(config['N']):
        costs += '\t\t'
        for j in range(config['N']):
            costs += f'(= (cost C{i} C{j}) {config["costs"][i][j]}) '
        costs = costs[:-1] + '\n'
    code = code.replace('{% COSTS %}', costs[:-1], 1)

    robot = f'\t\t(at R C{config["R"][0]} C{config["R"][1]} T0)'
    code = code.replace('{% ROBOT %}', robot, 1)

    ghost = f'\t\t(at G C{config["G"][0]} C{config["G"][1]} T0)'
    code = code.replace('{% GHOST %}', ghost, 1)

    sequence = ''
    for t, step in enumerate(config['sequence']):
        sequence += f'\t\t(scheduled C{step[0]} C{step[1]} T{t})\n'
    code = code.replace('{% SCHEDULE %}', sequence[:-1], 1)

    with open(f'moving_target_problem_{problem_number}.pddl', mode='w') as f:
        f.write(code)