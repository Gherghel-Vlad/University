p = input("p = ")
for n=100:200
  x = 0:n;
  b = binopdf(x,n,p);
  plot(x,b);
  title("Binomial")
  pause(0.5);
 end