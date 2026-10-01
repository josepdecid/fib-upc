import os
import time
import subprocess

algorithms = ['J48', 'AdaBoostM1', 'NaiveBayes', 'MLP', 'IBk']

for algorithm in algorithms:
    instances = ','.join(['1200'] + ['100' for _ in range(24)])
    file_name = f'ALG_{algorithm}_5_A'
    template =\
f"""<?xml version="1.0" encoding="utf-8" standalone="yes"?>
<SimulationSettings>
    <title>IMAS_{file_name}_simulation</title>
    <algorithm>{algorithm}</algorithm>
    <classifiers>25</classifiers>
    <trainingSettings>{instances}</trainingSettings>
    <classifyInstances>1200</classifyInstances>
    <file>segment-challenge.arff</file>
    <testFile>segment-test.arff</testFile>
</SimulationSettings>"""

    with open(os.path.join('src', 'main', 'resources', 'settings', f'{file_name}.xml'), mode='w') as f:
        f.write(template)

    # subprocess.run(['java', '-jar', 'target/A-DSS-1.0.0-jar-with-dependencies.jar', '--gui',
    #     f'USER:edu.urv.mai.imas.agents.UserAgent({file_name});MANAGER:edu.urv.mai.imas.agents.ManagerAgent;'])

    # time.sleep(100)