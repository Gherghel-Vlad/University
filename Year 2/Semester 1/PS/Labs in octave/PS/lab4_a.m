p = input("p = ");
N = input("N = ");
U = rand(1, N);

X = (U<p);

U_X = unique(X);
n_X = hist(X, length(U_X));
rel_freq=n_X/N;
disp(rel_freq);

bino = binopdf(X, n, p);
figure
