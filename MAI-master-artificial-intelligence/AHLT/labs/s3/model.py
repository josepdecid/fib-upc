from labs.s3.main import evaluate
from project.models.MEmodel import MEmodel


def model_evaluate():

    model = MEmodel('labs/s3/model.dat')
    with open('test_feats.dat', mode='r') as f:
        for line in f.readlines():
            data = line.split('\t')
            meta = data[:3]
            features = data[4:]

            dist = model.prob_dist_z(features)
            best = 'null'
            mx = 0
            for c in dist:
                if dist[c] > mx:
                    mx = dist[c]
                    best = c

            output_ddi(*meta, '0' if best == 'null' else '1', best)


def output_ddi(s_id, id_e1, id_e2, is_ddi, ddi_type, output_file='task9.2_VJ_42.txt'):
    """

    Parameters
    ----------
    s_id
    id_e1
    id_e2
    is_ddi
    ddi_type
    output_file

    Returns
    -------

    """
    with open(output_file, mode='a') as f:
        f.write('|'.join([s_id, id_e1, id_e2, is_ddi, ddi_type]) + '\n')