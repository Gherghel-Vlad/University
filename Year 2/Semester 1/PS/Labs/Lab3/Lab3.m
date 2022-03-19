
miu = input("miu = ");
sig = input("sig = ");


% Excercise 1
% normal
% a) 

%P(X<=0) 
n1 = normcdf(0, miu, sig);

%  P(x>=0) = 1 - P(x<0)
n2 = 1 - normcdf(0, miu, sig);

% b)
% P(-1<=x <=1) =  P(x<=1) - P(x<-1)
n3 = normcdf(1,miu, sig) - normcdf(-1, miu,sig);

% P(x<=-1 or x>=1) = 1 - P( -1<x<1) = 1- P(-1<=x<=1)
n4 = 1-(normcdf(1,miu, sig) - normcdf(-1, miu,sig));

% c)
alpha = input("alpha= ");
n5 = norminv(alpha, miu, sig);

% d)
beta = input("beta= ");
n5 = norminv(1-beta, miu, sig);












