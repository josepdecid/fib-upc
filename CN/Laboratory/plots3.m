%% Exemple de gràfiques
%  Dos gràfics en una mateixa finestra

RU = rand(10000, 1);
RN = randn(10000, 1);

subplot(2, 1, 1); hist(RU); title('Uniform');
subplot(2, 1, 2); hist(RN); title('Normal');