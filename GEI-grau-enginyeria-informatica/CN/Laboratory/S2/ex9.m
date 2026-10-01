function [ suma ] = ex9(x, n, tol)
% Partial sum of exponential series
    suma = 1;
    aux = 1;
    fact = 1;
    era = 1;
    while (fact < n && era > tol)
       aux = aux * x / fact;
       suma = suma + aux;
       era = abs(exp(x) - suma);
       fact = fact + 1;
    end
    
    disp('iteracions '), disp(fact);
    disp('error'), disp(era);
end