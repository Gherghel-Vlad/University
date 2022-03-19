
2.2;

x = 0:0.01:3;
y1 = x .^ 5 / 10;
subplot(3, 1, 1);
plot(x, y1);
legend('x^5/10');
y2 = x .* sin(x);
subplot(3, 1, 2);
plot(x, y2);
legend('xsinx');
y3 = cos(x);
subplot(3, 1, 3);
plot(x, y3);
legend('cosx');

