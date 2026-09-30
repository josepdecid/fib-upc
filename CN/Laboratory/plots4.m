%% Exemple de gràfiques
%  Dos gràfics en una mateixa finestra

RU = rand(10000, 1);
RN = randn(10000, 1);

subplot(2, 2, 1); plot(RU); title('Uniform Plot');
subplot(2, 2, 2); hist(RU); title('Uniform Hist');
subplot(2, 2, 3); plot(RN); title('Normal Plot');
subplot(2, 2, 4); hist(RN); title('Normal Hist');