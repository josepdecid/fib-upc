%% Exemple de gràfiques
%  Tres funcions en un mateix plot

x = 0 : pi/20 : 2*pi;

y1 = sin(x);
y2 = sin(x - 0.25);
y3 = sin(x - 0.50);

plot(x, y1, '+', ...
     x, y2, ':', ...
     x, y3, '--');