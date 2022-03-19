p = input("p = ")

for n = 1:20:500
    values = 1:n;
    bd = binopdf(values, n, p);
    subplot(2, 1, 1)
    plot(values, bd);
    nd = normpdf(values, n * p, sqrt(n * p *(1 - p)));
    subplot(2, 1, 2)
    plot(values, nd);
    pause(1);
    hold off;
end