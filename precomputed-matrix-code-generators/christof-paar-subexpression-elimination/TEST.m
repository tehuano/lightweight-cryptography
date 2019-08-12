clc
clear
n=4;
A=rand(n,n)
for i=1:n
    for j=1:n
        if A(i,j)<=0.5;
            B(i,j)=0;
        else
            B(i,j)=1;
        end
    end
end
B