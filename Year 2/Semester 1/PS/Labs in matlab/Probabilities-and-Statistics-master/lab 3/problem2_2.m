n = input("n (>=30) = ")
p = input("p (<=0.05) = ")

val = 0:n;
bd = binopdf(val, n, p);
pd = poisspdf(val, n * p);

plot(val, bd);
hold on;
plot(val, pd);