pkg load statistics

x = [7 7 4 5 9 9 4 12 8 1 8 7 3 13 2 1 17 7 12 5 6 2 1 13 14 10 2 4 9 11 3 5 12 6 10 7];
n = length(x);
confLevel = input('Please input the confidence level (in (0.95,0.99)) = '); %1 - alpha
alpha = 1 - confLevel;

%a) 
% Assuming that past experience indicates that sgima = 5, find a 100(1-alfa)% confidence interval for the average number of files stored.
% average = mean. xbar = the mean value of x(x = the data).

sigma = 5;
xbar = mean(x);

% q = quantile
% in pdf-ul confidence intervals -> primul interval dupa egal.(large sample and sigma known)
q1 = norminv(1 - alpha/2);

a1 = xbar - (sigma/sqrt(n)) * q1;
a2 = xbar + (sigma/sqrt(n)) * q1;
fprintf('Confidence interval for the population mean, miu, where sigma = %d is (%3.5f, %3.5f)\n', sigma, a1, a2);

%b)

s = std(x);  % standard deviation of the sample
q2 = tinv(1 - alpha/2, n - 1);
b1 = xbar - (s/sqrt(n)) * q2;
b2 = xbar + (s/sqrt(n)) * q2;
fprintf('Confidence interval for population mean, miu, where sigma is unknown is (%3.5f, %3.5f)\n', b1, b2)

%c)

varOfX = var(x); % s^2
q3 = chi2inv(1 - alpha/2, n - 1);
q4 = chi2inv(alpha/2, n - 1);
c1 = ((n - 1) * varOfX) / q3 ;
c2 = ((n - 1) * varOfX) / q4;
C1 = sqrt(c1);
C2 = sqrt(c2);

fprintf('Confidence Interval for the population variance sigma^2 is (% 3.5f, %3.5f)\n',c1,c2)

% problem gives u the details! 
% to be able to use comments
% knowing how to explain the code in the comments (what is s^2, what is chi2inv)

% var(x) usually computes s^2
% s^2 - variance of the sample
% sigma^2 - variance of the population
% var(x,1) usually computes sigma^2

% type help var

% set of data: [20 20 20 20 11 11 11] <=> [20 11 / 4 3] - vector
% write that vector as: x = [20*ones(1,4),11*ones(1,3)]

% Find how the functions cov, corrcoef work!

% RULES PRACTICAL:
% - after holidays.
% - problems are just aplications. VERY similar to what we've done 
% - we have to bring ALL the laboratories
% - we dont have to start a program from scrach
% - just to use the material that we have. to mix the data and to solve it
% - the practical exam aprox 20-25 minutes
% 70% final exam
% 30% seminar + lab (matched somehow idk)