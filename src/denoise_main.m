clear
 
D=csvread('./CRC.mut.csv',1,1);
D=D'

[m,n]=size(D); 
ms=0; % value represents missing.
omega=find(D~=ms); 
omegaC=find(D==ms);
lambda=1/sqrt(max(m,n))*(1+20*length(omegaC)/(m*n));
[A1,E1]= RPCA(D,omega,lambda);

%% Integralization
AA1=int8(A1);
AA1=table(AA1)
writetable(AA1, './CRC.mut1.csv');