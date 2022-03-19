n = input("Degrees of freedom numerator = ");
m = input("Degrees of freedom denumerator = ");
alpa = input("Alpha = ");
beta = input("Beta = ");

# a) P(X <= 0)
pa1 = fcdf(0, n, m)
# P(X >= 0) = 1 - P(X <= 0)
pa2 = 1 - fcdf(0, n, m)

# b) P(-1 <= X <= 1) = P(x <= 1) - P(X < -1) = P(X <= 1) - P(x < -1) 
pb1 = fcdf(1, n, m) - fcdf(-1, n, m)

# P(X<= -1 or x >= 1) = 1 - P(-1 <= X <= 1)
pb2 = 1 - pb1

# c) P(X < x_alpha) = alpha
ansc = finv(alpha, n, m)

# d) P(X > x_beta) = beta
ansd = finv(1 - beta, n, m)