x = 0:0.1:3
f1 = x.^5 / 10
f2 = x .* sin(x)
f3 = cos(x)

hold on;
subplot (3, 1, 1)
plot(x, f1, 'm-', 'linewidth', 1.5);
legend('x.^5 / 10', 'location', 'northwest')
grid on;
hold off;
title('Function 1');
set(gca, 'fontsize', 16);

hold on;
subplot (3, 1, 2)
plot(x, f2, 'c-', 'linewidth', 1.5)
legend('x * sin(x)', 'location', 'northwest')
grid on;
hold off;
title('Function 2');
set(gca, 'fontsize', 16);

hold on;
subplot (3, 1, 3)
plot(x, f3, 'b-', 'linewidth', 1.5)
legend('cos(x)', 'location', 'northwest')
grid on;
hold off;
title('Function 3');
set(gca, 'fontsize', 16);