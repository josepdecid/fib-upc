n = [5 ; 10 ; 25 ; 50 ; 100 ; 1000];
its = length(n);
or = (1 + sqrt(5))/2;

or_fract = zeros(its, 1);
or_fract_eabs = zeros(its, 1);
or_fract_erel = zeros(its, 1);
or_fib = zeros(its, 1);
or_fib_eabs = zeros(its, 1);
or_fib_erel = zeros(its, 1);

for i = 1:its
    or_fract(i) = orfract(n(i));
    or_fract_eabs(i) = or - or_fract(i);
    or_fract_erel(i) = or_fract_eabs(i) / or;
    
    or_fib(i) = orfib(n(i));
    or_fib_eabs(i) = or - or_fib(i);
    or_fib_erel(i) = or_fib_eabs(i) / or;
end

disp(table( ...
    n, or_fract, or_fract_eabs, or_fract_erel, ...
    or_fib, or_fib_eabs, or_fib_erel ...
));