 p = input("p = ");
 N = input("N = ");
 U = [];
 for c = 1:N
    U(c) = rand;
 end
 X= (U<p);
 
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
 fprintf('\n ');