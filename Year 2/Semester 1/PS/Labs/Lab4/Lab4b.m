 %n = input("n = ");
 %p = input("p = ");
 %N = input("N = ");
 n=10;
 p=0.5;
 N=20;
 U= [];
 X=[];
  for i = 1:N
    U = rand(1, N);
    X(i)=sum(U<p);
  end
 
 U_X = unique(X);
 n_X = hist(X,length(U_X));
 
 rel_freq = n_X/N;
 
 fprintf('U: ');
 fprintf('%g ', U);
 fprintf('\nX: ');
 fprintf('%g ', X);
 fprintf('\nU_X: ');
 fprintf('%g ', U_X);
 fprintf('\nn_X: ');
 fprintf('%g ', n_X);
 fprintf('\nrel_freq: ');
 fprintf('%g ', rel_freq);
 fprintf('\nBinopdf(X, n, p) ');
 fprintf('%g ', binopdf(X, n, p));
 fprintf('\n ');
 
 
y1=U_X;
y2=binopdf(X, n, p);
figure
p=plot(U_X, rel_freq, '*', X, binopdf(X, n, p), 'g-');

 