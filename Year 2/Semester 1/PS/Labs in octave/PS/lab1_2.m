x = 0:0.1:3
f1 = x.^5 / 10
f2 = x .* sin(x)
f3 = cos(x)
hold on;
plot(x, f1, 'm-', 'linewidth', 1.5)
hold on;
plot(x, f2, 'c-', 'linewidth', 1.5)
hold on;
plot(x, f3, 'b-', 'linewidth', 1.5)
hold off;
grid on;
title('Plot Functions');
set(gca, 'fontsize', 16);
legend('x.^5 / 10', 'x * sin(x)', 'cos(x)')