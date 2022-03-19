
2;

x = 0:0.01:3;

y1 = x .^ 5 / 10;
y2 = x .* sin(x);
y3 = cos(x);

plot(x, y1);
hold on;
plot(x, y2, 'r--');
hold on;
plot(x, y3, 'y-.');
legend('x^5/10', 'xsinx', 'cosx');
legend('show');

