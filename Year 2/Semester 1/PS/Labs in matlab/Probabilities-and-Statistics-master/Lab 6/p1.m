alpha = input('Sign level (in (0, 1)) = ');
m0 = input('test value = ');

% teta - target parameter
% null H0: teta = teta0
% alt H1: teta < teta0 left-tailed
%         teta > teta0 right-tailed
%         teta = teta0 two-tailed
% Decision rejection H0
%          to not reject H0

X = [ 7 7 4 5 9 9 ...
      4 12 8 1 8 7 ...
      3 13 2 1 17 7 ...
      12 5 6 2 1 13 ...
      14 10 2 4 9 11 ...
      3 5 12 6 10 7 ...
      ];
sigma = 5;
tail = -1;
[h, p, ci, zval] = ztest(X, "m0", sigma, "alpha", tail);

fprintf('Observed value of the test statistic is %3.5f\n', zval);
fprintf('P value is %1.5f\n', p);
q1 = norminv(alpha, 0, 1)
fprintf('Rejection region RR is (-infinity, %3.5f)\n', q1);