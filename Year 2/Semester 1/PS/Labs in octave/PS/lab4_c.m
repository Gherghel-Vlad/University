pkg load statistics

p = input("p = ");
N = input("N = ");

for i = 1:N
  X(i)=0;
  while rand >= p
    X(i) = X(i)+1;
  endwhile
endfor

U_X = unique(X);
n_X = hist(X, length(U_X));

rel_freq=n_X/N;

plot(U_X, rel_freq, '*b');
hold on
x = 0:30
plot(x, geopdf(x,p), '*m');
