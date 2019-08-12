%���ӷ�������
function [add_sum]=ADDER_SUM(b)
    
[m,n]=size(b);
sumh = zeros(m);
add_sum = 0;
for i=1:m
    for j=1:n
        if b(i,j)==1
            sumh(i)=sumh(i)+1;
        end
    end
    if sumh(i) > 0 
        add_sum = add_sum + sumh(i) - 1;
    end 
end