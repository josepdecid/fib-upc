%% Exemple de fitxer

x = 0 : 0.1 : 1;
y = exp(x);

t = table(x, y)';

%% Save in a file
fid = fopen('prova.txt', 'w');
fprintf(fid, '&s