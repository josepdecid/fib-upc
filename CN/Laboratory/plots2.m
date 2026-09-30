%% Exemple de gràfiques
%  Tres funcions en un mateix plot

% Hold on afegeix sobre plot existent
% pause(t) para t segons, i pause espera a acció

x = 0 : pi/20 : 2*pi;

y1 = sin(x);
plot(x, y1, '+'); hold on; pause(2);

y2 = sin(x - 0.25);
plot(x, y2, ':'); hold on; pause;

y3 = sin(x - 0.50);
plot(x, y3, '--'); hold off