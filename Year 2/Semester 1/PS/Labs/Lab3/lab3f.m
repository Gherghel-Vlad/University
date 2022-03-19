
m = input("m = ");
n = input("n = ");



% Excercise 1
% normal
% a) 

%P(X<=0) 
n1 = fcdf(0, m, n);

%  P(x>=0) = 1 - P(x<0)
n2 = 1 - fcdf(0, m, n);

% b)
% P(-1<=x <=1) =  P(x<=1) - P(x<-1)
n3 = fcdf(1,m, n) - fcdf(-1, m, n);

% P(x<=-1 or x>=1) = 1 - P( -1<x<1) = 1- P(-1<=x<=1)
n4 = 1-(fcdf(1,m, n) - fcdf(-1, m, n));

% c)
alpha = input("alpha= ");
n5 = fcdf(alpha, m, n);

% d)
beta = input("beta= ");
n5 = fcdf(1-beta, m, n);












