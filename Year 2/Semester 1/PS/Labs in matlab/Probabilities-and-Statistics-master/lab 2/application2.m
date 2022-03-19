x = 0:3;
% a
p = binopdf(x, 3, 0.5)
subplot(2, 1, 1);
stem(x, p, 'b');
hold on;
% b
cp = binocdf(x, 3, 0.5)
subplot(2, 1, 2);
stairs(x, cp, 'k');
% c
%P(X = 0)
px0 = binopdf(0, 3, 0.5)

%P(x =\= 1)
pxn1 = 1 - binopdf(1, 3, 0.5)

% d
%P(x <= 2)
pxse2 = binocdf(2, 3, 0.5) 
p2 = binopdf(0, 3, 0.5) + binopdf(1, 3, 0.5) + binopdf(2, 3, 0.5)

%P(x<2) = P(x<=2) - P(x = 2)
pxs2 = binocdf(2, 3, 0.5) - binopdf(2, 3, 0.5)

% e
% P(x > 1) = 1 - P(x <= 1)
pxg1 = 1 - binocdf(1, 3, 0.5)

% P(x >= 1) = 1 - P(x < 1) = 1 - P(x <= 1) + P(x = 1)
pxge1 = 1 - binocdf(1, 3, 0.5) + binopdf(1, 3, 0.5)

%f
