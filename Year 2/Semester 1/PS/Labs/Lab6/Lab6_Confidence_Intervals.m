x = [7, 7, 4, 5, 9, 9, 4, 12, 8, 1, 8, 7, 3, 13, 2, 1, 17, 7, 12, 5, 6, 2, 1, 13, 14, 10, 2, 4, 9, 11, 3, 5, 12, 6, 10, 7];
n = length(x);

one_minus_alpha = input("confience level: ");
alpha = 1-one_minus_alpha; % significance level

% Ex 1 a)
sigma = 5;

m1 = mean(x) - sigma/sqrt(n) * norminv(1-alpha/2);
m2 = mean(x) + sigma/sqrt(n) * norminv(1-alpha/2);

m1
m2

% Ex 1 b)
% s = standard divation of the sample
s = std(x);

m3 = mean(x) - s/sqrt(n) * tinv(1-alpha/2, n-1);
m4 = mean(x) + s/sqrt(n) * tinv(1-alpha/2, n-1);

m3
m4

% Ex 1 c
sSquare = var(x);
c1 = ((n-1)*sSquare)/chi2inv(1-Alpha/2, n-1);
c2 = ((n-1)*sSquare)/chi2inv(Alpha/2, n-1);
C1 = sqrt(c1);
C2 = sqrt(c2);

%var(x) usually computes s^2
%s^2 - variance of the sample
%sigma^2 - variance of the population
%var(x,1) usually computes sigma^2
%[20 20 20 20 11 11 11]
%[20 11 / 4 3]
%x = [20*ones(1,4),11*ones(1,3)]
%cov, corrcoef



%fprintf("%g", x);