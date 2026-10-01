n = 7.^(1:12)';
pi_n = zeros(length(n), 1);
err_abs = zeros(length(n), 1);
err_rel = zeros(length(n), 1);

for k = 1:length(n)
    pi_n(k) = pi_succ(n(k));
    err_abs(k) = abs(pi - pi_n(k));
    err_rel(k) = err_abs(k) / pi;
end

disp(table(n, pi_n, err_abs, err_rel));