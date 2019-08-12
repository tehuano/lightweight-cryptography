%求最大频率的组合
function [MF]=MAX_FREQ_COMB(F,Fmax)
[m,n]=size(F);
a=1;
for i=1:n
    for j=i:n
        if F(i,j)==Fmax
            MF(a,1)=i;
            MF(a,2)=j;
            a=a+1;
        end
    end 
end