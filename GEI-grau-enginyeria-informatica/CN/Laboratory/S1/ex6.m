%% Plot random 2D sample
n = 100;
samples = rand(n, 2);
scatter(samples(:, 1), samples(:, 2));

%% Plot sin(x), sin(2x), cos(x), cos(2x), between -pi and pi
x = -pi:0.1:pi;

figure();

y = sin(x);
subplot(221), plot(x, y), title('sin(x)'), pause;

y = sin(2*x);
subplot(222), plot(x, y), title('sin(2x)'), pause;

y = cos(x);
subplot(223), plot(x, y), title('cos(x)'), pause;

y = cos(2*x);
subplot(224), plot(x, y), title('cos(2x)'), pause;