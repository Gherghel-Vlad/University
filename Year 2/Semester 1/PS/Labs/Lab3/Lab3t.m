
n = input("n = ");



% Excercise 1
% normal
% a) 

%P(X<=0) 
n1 = tcdf(0, n);

%  P(x>=0) = 1 - P(x<0)
n2 = 1 - tcdf(0, n);

% b)
% P(-1<=x <=1) =  P(x<=1) - P(x<-1)
n3 = tcdf(1,n) - tcdf(-1, n);

% P(x<=-1 or x>=1) = 1 - P( -1<x<1) = 1- P(-1<=x<=1)
n4 = 1-(tcdf(1,n) - tcdf(-1, n));

% c)
alpha = input("alpha= ");
n5 = tinv(alpha, n);

% d)
beta = input("beta= ");
n5 = tinv(1-beta, n);












