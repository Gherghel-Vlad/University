# Created by Octave 6.3.0, Mon Oct 25 18:46:13 2021 GMT <unknown@ASUS-ROG>
pkg load statistics
n = input("n: ")
p = input("p: ")

#x = randi([0,3])
x = 0:n
#p = 0.50

plot(x, binopdf(x,n,p), '*r')
hold on
stairs(x, binocdf(x,n,p))
hold off