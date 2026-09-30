function [pi_n] = pi_succ(n)
m = 0;
for k = 1:n
    rx = rand(); ry = rand();
    if rx*rx + ry*ry <= 1
        m = m + 1;
    end
end
pi_n = 4*m / n;
end

