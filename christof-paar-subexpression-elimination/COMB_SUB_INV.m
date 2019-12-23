%��Ϸ��滻
function [b_sub,add_sum]=COMB_SUB_INV(b,yi,yj,add_sum)

[m,n] = size(b);

for i=1:m
    for j=1:n-1
        b_sub(i,j)=b(i,j);
    end
end

for i=1:m
    if b(i,n)==1
        b_sub(i,yi)=1;
        b_sub(i,yj)=1;
        add_sum = add_sum + 1;
    end 
end

add_sum = add_sum - 1;