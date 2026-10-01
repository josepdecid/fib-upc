function [or_fract] = orfract(n)
if n <= 1
    or_fract = 1;
else
    or_fract = 1 + 1/orfract(n-1);
end
end

