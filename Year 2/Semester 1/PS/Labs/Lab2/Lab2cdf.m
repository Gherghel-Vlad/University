
prompt1 = "n= ";
prompt2 = "p= ";
n = input(prompt1);
p = input(prompt2);

if (p < 0 || p > 1)
    fprintf('p is not a good value (p needs to be between 0 and 1)');
    return;
end

figure
defects=0:10;
z = binocdf(defects, n, p);

stairs(defects, z);
grid on;