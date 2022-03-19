miu = input("miu = ");
sigma = input("sigma = ");
alpha = input("alpha = ");
beta = input("beta = ");

# a) P(X <= 0) = cdf(0)
pa1 = normcdf(0, miu, sigma)

# P(X >= 0) = 1 - P(X < 0) = 1 - P(X <= 0)
pa2 = 1 - normcdf(0, miu, sigma)

# b) P(-1 <= X <= 1) = P(x <= 1) - P(X < -1) = P(X <= 1) - P(x < -1) 
pb1 = normcdf(1, miu, sigma) - normcdf(-1, miu, sigma) 

# P(X<= -1 or x >= 1) = 1 - P(-1 <= X <= 1)
pb2 = 1 - pb1

# c) P(X < x_alpha) = alpha
ansc = norminv(alpha, miu, sigma)

# d) P(X > x_beta) = beta
ansd = norminv(1 - beta, miu, sigma)