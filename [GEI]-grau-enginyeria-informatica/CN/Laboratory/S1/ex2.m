function [] = ex2(n)
% Generate size n sample of r.v.
% Display histogram and calculate mean and std

samples = rand(n, 1);

mu = mean(samples);
sigma = std(samples);
hist(samples);

disp(['Mean is ', num2str(mu)]);
disp(['Standard deviation is ', num2str(sigma)]);
end

