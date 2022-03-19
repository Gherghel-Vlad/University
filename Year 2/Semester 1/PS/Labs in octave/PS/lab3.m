pkg load statistics

# a)
miu = input("miu = ")
sigma = input("sigma = ")
p1 = normcdf(0, miu, sigma) # P(X<=0) = cdf(0)
p2 = 1-p1 #  P(X>=0) = 1 - P(X<0) = 1 - P(X<=0)

# b)
p3 = normcdf(0, miu, sigma) - normcdf(-1, miu, sigma)
# P(-1<=X<=1) = P(X<=1) - P(X<-1)
p4 = 1-p3

# c)
alpha = input("alpha = ")
p5 = norminv(alpha, miu, sigma)

# d)
beta = input("beta = ")
p6 = norminv(1-beta, miu, sigma)
