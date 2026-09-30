it = 20;
memFact = ones(it, 1);

if it > 0
    e = 2;
else
    e = 1;
end

for k = 2:it
   memFact(k) = k * memFact(k-1);
   e = e + 1/memFact(k);
end

disp(e);