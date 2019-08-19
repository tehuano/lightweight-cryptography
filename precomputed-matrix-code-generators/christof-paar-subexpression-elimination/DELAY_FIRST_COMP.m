%��ʱ�����ʼ��
function [delay_first]=DELAY_FIRST_COMP(b)

[m,n]=size(b);
for i=1:m
    for j=1:n
        if b(i,j)==1
            delay_first(i,j)=0;
        else
            delay_first(i,j)=-1;
        end
    end
end