p = input("Probaility = ")
N = input("Number of simulations = ")

for i = 1:N
    X(i) = 0;
    while rand >= p
        X(i) = X(i) + 1;
    end
end


UX = unique(X);
nX = hist(X, length(UX));
relativeFrequency = nX / N

plot(UX, relativeFrequency, '*')
