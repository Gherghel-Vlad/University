n = input("Degrees of freedom = ");
alpa = input("Alpha = ");
beta = input("Beta = ");

# a) P(X <= 0)
pa1 = tcdf(0, n)
# P(X >= 0) = 1 - P(X <= 0)
pa2 = 1 - tcdf(0, n)

# b) P(-1 <= X <= 1) = P(x <= 1) - P(X < -1) = P(X <= 1) - P(x < -1) 
pb1 = tcdf(1, n) - tcdf(-1, n)

# P(X<= -1 or x >= 1) = 1 - P(-1 <= X <= 1)
pb2 = 1 - pb1

# c) P(X < x_alpha) = alpha
ansc = tinv(alpha, n)

# d) P(X > x_beta) = beta
ansd = tinv(1 - beta, n)