%����滻����
function [b_sub,add_sum]=COMB_SUB(b,xi,xj,add_sum)

[m,n] = size(b);
b_sub = b;

for i=1:m
    if b_sub(i,xi)==1
        if b_sub(i,xj)==1
            b_sub(i,xi)=0;
            b_sub(i,xj)=0;
            b_sub(i,n+1)=1;
            add_sum = add_sum - 1;
        else
            b_sub(i,n+1)=0;
        end
    else
        b_sub(i,n+1)=0;
    end 
end

add_sum = add_sum + 1;