%% Exercice 2 - Full_lab4.pdf
%  iterative methods for fixed point

f = @(x) x.^6 - x - 1;
t = 1:0.1:1.4;
plot(t, f(t)), grid, title('Eq');

%% FZero Matlab
alpha = fzero(f, 1);

%% Iterative method 1
g1 = @(x) x.^6 - 1;
dg1 = @(x) 6.*(x.^5);
x0 = 1; tol = 0.0005; N = 10;
if abs(dg1(x0)) < 1
    [ root ] = new_fixpt(f, g1, x0, tol, N);
else
   disp('Divergent method');
end

%% Convergence
y = ones(size(t));
plot(t, f(t), t, dg1(t), t, y), grid, title('x^6 - x - 1');
legend('eq', 'method 1', 'location', 'best');

%% Iterative method 2
g2 = @(x) (x + 1).^(1/6);
dg2 = @(x) 1./(x + 1).^(5/6)./6;
x0 = 1; tol = 0.0005; N = 10;
if abs(dg2(x0)) < 1
    [ root ] = new_fixpt(f, g2, x0, tol, N);
else
   disp('Divergent method');
end

%% Convergence
y = ones(size(t));
plot(t, f(t), t, dg2(t), t, y), grid, title('x^6 - x - 1');
legend('eq', 'method 1', 'location', 'best');