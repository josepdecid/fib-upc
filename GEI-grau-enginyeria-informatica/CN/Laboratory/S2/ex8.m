%% Exercice 8 - list Lab2
%  Wednesday 7th March 2018

%% Plots
F = @(x, n) x.^n .* exp(x - 1);
t = 0:0.01:1;

for i = 1:9
   subplot(3, 3, i);
   plot(t, F(t, i*5));
   title(strcat('n=', num2str(i)));
end

IF(1) = 1/exp(1);
for k = 2:50
   IF(k) = 1 - k * IF(k - 1); 
end

%% Back

IB(50) = 0;
for k = 50:-1:2
    IB(k-1) = (1 - IB(k)) / k;
end

disp([IF ; IB]');

%% Exact value
F = @(x, n) x.^n .* exp(x-1);
for k = 1:50
   IE(k) = integral(@(x) F(x, k), 0, 1);
end

disp([IF  IB IE]);