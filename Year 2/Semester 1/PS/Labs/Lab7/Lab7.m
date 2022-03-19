% 1 a
% H0: niu = 9
% H1: niu < 9

% INPUT
% X - the vector that contains your data
% M - test value (theta0 (in our case is niu (9)))
% SIGMA - standard deviation for the population 
% ALPHA - significance level 
% TAIL - indicates the type of the test

% OUTPUT
% H - tells us if we reject H0 or not
% P - P-value of the test (we shall print it at the end)
% CI - confidence interval
% ZVAL - observed value of TS (TS0 - we shall print it)

alpha = input("significance level: ");
x = [7 7 4 5 9 9 ...
4 12 8 1 8 7 ...
3 13 2 1 17 7 ...
12 5 6 2 1 13 ...
14 10 2 4 9 11 ...
3 5 12 6 10 7 ...
];
n = length(x);
sigma = 5;

fprintf('We are using left-tailed test for significance level %g and standard deviation %g\n', alpha, sigma)

m0=9;

%[H,P,CI,ZVAL] = ztest(x,m0,sigma,alpha,1);


%fprintf("H: %g\n", H)
%fprintf("RR: %g\n", rr)
%fprintf("TS0: %g\n", ZVAL)
%fprintf("P-value: %g\n", P)


RR = norminv(alpha);

[h, p, ci, zstat] = ztest(x, m0, sigma, alpha, -1);
 
if h == 1 % result of the test, h = 0, if H0 is NOT rejected, h = 1, if H0 IS rejected
    fprintf('\n So the null hypothesis is rejected,\n')
    fprintf('i.e. the data suggests that the standard IS NOT met.\n')
else
    fprintf('\n So the null hypothesis is not rejected,\n')
    fprintf('i.e. the data suggests that the standard IS  met.\n')
end   

fprintf('the rejection region is (%4.4f, %4.4f)\n', -inf, RR)
fprintf('the value of the test statistic z is %4.4f\n', zstat)
fprintf('the P-value of the test is %4.4f\n\n', p)









