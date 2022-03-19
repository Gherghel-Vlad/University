A=[1 0 -2; 2 1 3; 0 1 0]
B=[2 1 1; 1 0 -1; 1 1 0]

C=A-B
D=A*B
E=A.*B




x=linspace(-10, 10);
y1=(x.^5)/10;
y2=x.*sin(x);
y3=cos(x);
figure
p=plot(x, y1, 'r--', x, y2,'g-', x, y3, 'b-.');
title('Some title')
xlabel('x')
ylabel('y')
legend("y1", 'y2', 'y3')