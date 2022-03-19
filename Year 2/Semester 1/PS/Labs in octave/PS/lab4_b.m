pkg load statistics

p = input("p = ");
n = input("n = ");
N = input("N = ");

for i = 1:N
  U = rand(1, n);
  X(i) = sum(U<p);
endfor

U_X = unique(X);
n_X = hist(X, length(U_X));

rel_freq=n_X/N;

plot(U_X, rel_freq, '*b');
hold on
x = 0:n
plot(x, binopdf(x,n,p), '*r');
