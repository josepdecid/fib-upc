% MAI-CI Fuzzy Systems
% Authors: Josep de Cid | Gonzalo Recio

L = 0.495;      % L Bar length              0.495 m
d = 0.023;      % d Pivot to CG distance    0.023 m
m = 0.43;       % m Mass of pendulum        0.43 kg
J = 0.0090;     % J Moment of Inertia       0.0090 kgm2
c = 0.00035;    % c Viscous damping         0.00035 Nms / rad
g = 9.80665;    % g Earth’s Gravity         9.80665 m/s2

fismat = readfis('fismat');
fismat_3_trimf = readfis('fismat_3_trimf');
fismat_3_gauss = readfis('fismat_3_gauss');