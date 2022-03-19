p = input('p (in (0, 1)) = ');

% U = rand;
% X = (U < p);
% success U < p, failure U >= p
N = input('Number of simulations = ');
for j = 1:19
    for i = 1:N
        U = rand;
        X(i) = (U < p);
    end

    UX = unique(X);
    nX = hist(X, length(UX));
    relativeFrequency = nX / N
end