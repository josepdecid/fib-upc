function [ root ] = new_fixpt(inputArg1,inputArg2)
     k = 0;
     tols = 1; tolf = abs(f(x)); err = max(tols, tolf);
     x_sol = x;
     while (err > tol && k < 0)
         xprev = x;
         x = g(x);
         k = k + 1;
         tols = abs(x - xprev);
         tolf = abs(f(x));
         err = max(tols, tolf);
         x_sol = [x_sol, x];
     end
     root = x;
end

