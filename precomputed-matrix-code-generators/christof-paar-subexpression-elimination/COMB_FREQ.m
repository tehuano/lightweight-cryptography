%�����Ƶ�ʾ�����
function [F]=COMB_FREQ(b)

[m,n] = size(b);

F=zeros(n,n);
for i=1:m
    for j=1:n-1
        if b(i,j)==1
            for k=j+1:n
            	if b(i,k)==1
                	F(j,k)=F(j,k)+1;
             	end
             end 
        end
    end 
end
