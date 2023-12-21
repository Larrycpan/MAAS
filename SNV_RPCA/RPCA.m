function [A1 E1 iter] = RPCA(D, omega, lambda, tol, maxIter)

[m n] = size(D);

if nargin < 3
    lambda = 1 /sqrt(max(m,n));
end

if nargin < 4
    tol = 1e-7;
elseif tol == -1
    tol = 1e-7;
end

if nargin < 5
    maxIter = 1000;
elseif maxIter == -1
    maxIter = 1000;
end

% initialize
Y = D;
norm_two = svds(Y, 1);
norm_inf = norm( Y(:), inf) / lambda;
dual_norm = max(norm_two, norm_inf);
Y = Y / dual_norm;

A1 = zeros( m, n);
E1 = zeros( m, n);
mu = 1.25/norm_two;
mu_bar = mu * 1e7;
r = 1.1;
d_norm = norm(D, 'fro');

iter = 0;
total_svd = 0;
converged = false;
stopCon = 1;
sv = 10;
while ~converged       
    iter = iter + 1;
    
    temp_T = D - A1 + (1/mu)*Y;
    E1 = temp_T;
    EE = max(temp_T - lambda/mu, 0);
    EE = EE+min(temp_T + lambda/mu, 0);
    E1(omega) = EE(omega);

    if choosvd(n, sv) == 1
        [U S V] = svds(D - E1 + (1/mu)*Y, sv);
    else
        [U S V] = svd(D - E1 + (1/mu)*Y, 'econ');
    end
    diagS = diag(S);
    lenS = length(find(diagS > 1/mu));
    if lenS < sv
        sv = min(lenS + 1, n);
    else
        sv = min(lenS + round(0.05*n), n);
    end
    
    A1 = U(:, 1:lenS) * diag(diagS(1:lenS) - 1/mu) * V(:, 1:lenS)';    

    total_svd = total_svd + 1;
    
    Z = D - A1 - E1;  
    Y = Y + mu*Z;
    mu = min(mu*r, mu_bar);
        
    %% stop condition  
    stopCon = norm(Z, 'fro') / d_norm;
    if stopCon < tol
        converged = true;
    end         
    
    if ~converged && iter >= maxIter
        disp('Reach maximum iterations') ;
        converged = 1 ;       
    end
end


