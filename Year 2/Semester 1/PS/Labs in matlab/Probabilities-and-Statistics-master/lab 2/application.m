n = input("Input number of values: ")
p = input("Input probability: ")

v = 0:1:n;
y = binopdf(v, n, p);
subplot(2, 1, 1);
plot(v, y, 'r*');

w = 0: 0.001: n;
z = binocdf(w, n, p);
subplot(2, 1, 2);
plot(w, z);
