% a
n=3
x=0:3
p=0.5
plot(x,  binopdf(x,n,p), "*r")
hold on

% b
stairs(x, binocdf(x,n,p))
legend('probability', 'trial')

%c
binopdf(0,n,p)
1 - binopdf(1,n,p)

%d
binocdf(2,n,p)
binocdf(1,n,p)

%e
1 - binocdf(0,n,p)
1 - binocdf(1,n,p)