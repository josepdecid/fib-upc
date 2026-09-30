f = @(x, e) 1.01*e^(4*x) - 4.62*e^(3*x) - 3.11*e^(2*x) + 12.2*e^x - 1.99;
eabs = fx - fxt; erel = eabs / fx;
disp(erel);

F = @(x, z) (((1.01*z - 4.62)*z - 3.11)*z + 12.2)*z - 1.99;
Fx = F(x); eabs = Fx - Fxt; erel = eabs / Fx;
disp(erel);