
n = input("n = ");



% Excercise 1
% normal
% a) 

%P(X<=0) 
n1 = chi2cdf(0, n);

%  P(x>=0) = 1 - P(x<0)
n2 = 1 - chi2cdf(0, n);

% b)
% P(-1<=x <=1) =  P(x<=1) - P(x<-1)
n3 = chi2cdf(1,n) - chi2cdf(-1, n);

% P(x<=-1 or x>=1) = 1 - P( -1<x<1) = 1- P(-1<=x<=1)
n4 = 1-(chi2cdf(1,n) - chi2cdf(-1, n));

% c)
alpha = input("alpha= ");
n5 = chi2inv(alpha, n);

% d)
beta = input("beta= ");
n5 = chi2inv(1-beta, n);












