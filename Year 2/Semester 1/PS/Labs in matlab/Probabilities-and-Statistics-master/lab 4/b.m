p = input('Probability = ');
n = input('Number of trials = ');
N = input('Number of simulations = ');

binornd(1:1:n, p, 3, 4)

for i = 1:N
    U = rand(n, 1);
    X(i) = sum(U < p);
end


k = 0:n;
bpdfk = binopdf(k, n, p);
plot(k, bpdfk, '*')
hold on;


UX = unique(X);
nX = hist(X, length(UX));
relativeFrequency = nX / N

plot(UX, relativeFrequency, "*")