n = input("Degrees of freedom = ");
alpa = input("Alpha = ");
beta = input("Beta = ");

# a) P(X <= 0)
pa1 = chi2cdf(0, n)
# P(X >= 0) = 1 - P(X <= 0)
pa2 = 1 - chi2cdf(0, n)

# b) P(-1 <= X <= 1) = P(x <= 1) - P(X < -1) = P(X <= 1) - P(x < -1) 
pb1 = chi2cdf(1, n) - chi2cdf(-1, n)

# P(X<= -1 or x >= 1) = 1 - P(-1 <= X <= 1)
pb2 = 1 - pb1

# c) P(X < x_alpha) = alpha
ansc = chi2inv(alpha, n)

# d) P(X > x_beta) = beta
ansd = chi2inv(1 - beta, n)