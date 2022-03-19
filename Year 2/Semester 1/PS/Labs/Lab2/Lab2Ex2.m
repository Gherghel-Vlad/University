
n = 3;
p = 0.5;
x = 0:3;

% (0 1 2 3)

% Xa<x - always for every branch
% x < 0 
c1 = 0;

% 0<=x<1
c2 = binocdf(0, n, p);

% 1<=x<2
c3 = binocdf(0, n, p) + binocdf(1, n, p);

% 2<=x<3
c4 = binocdf(0, n, p) + binocdf(1, n, p) + binocdf(2, n, p);

% x>=3
c4 = binocdf(0, n, p) + binocdf(1, n, p) + binocdf(2, n, p) + binocdf(3, n, p);


% c.
% P(X=0)
p0 = binocdf(0, n, p);
%P(X!=1)
p1 = binocfd(x, n, p) - binocfd(1, n, p);

% d.
% P(X<=2)
p2 = binocfd(0, n, p) + binocfd(1, n, p) + binocfd(2, n, p);

% P(x<2)
p3 = binocfd(0, n, p) + binocfd(1, n, p);

% e.
% P(X>=1)
p4 = binocfd(1, n, p) + binocfd(2, n, p) + binocfd(3, n, p);
% P(x>1)
p5 = binocfd(2, n, p) + binocfd(3, n, p);


% f.

X = binornd(3, 0.5);

















