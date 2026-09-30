function [or_fib] = orfib(n)
if n <= 2
    or_fib = 1;
else
    mem_fib = zeros(n);
    mem_fib(1) = 1;
    mem_fib(2) = 1;
    for i = 3:n
        mem_fib(i) = sum(mem_fib(i-2:i-1));
    end
    or_fib = mem_fib(n) / mem_fib(n-1);
end
end