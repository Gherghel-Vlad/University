% Exercise 2 Normal
p = input("p= ");
n = 10000;


x=[];
e=1;
for i= 0:10000
    x(e) = i;
    e=e+1;
end

y1=binocdf(x, n, p);
y2=normcdf(x, n*p, sqrt(n*p*(1-p)));


figure
p=plot(x, y1, 'r--', x, y2,'g');