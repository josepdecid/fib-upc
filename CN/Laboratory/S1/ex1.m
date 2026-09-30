syms k
sumFirst = @(n) symsum(k, k, 1, n);
sumFirstPowered = @(n, p) symsum(k^p, k, 1, n);