%���������ӳ�
function [delay_last]=DELAY_LAST_COMP(delay)

[m,n]=size(delay);
a=zeros(1,n);
%    delay computing;
for i=1:m
    a(:)=delay(i,:); 
    p=1;
    while p<n    
        %��С��������
        for j=p:n
            for k=j+1:n
                if a(j)>a(k)
                    b=a(j);
                    a(j)=a(k);
                    a(k)=b;
                end
            end
        end
        
        a;i;
        
        %�ϲ���С����
        q=p;
        while a(q)<0
            q=q+1;
        end
        if q<n
           a(q) = -1;
           a(q+1) = a(q+1) + 1;
        end
        
        p=q+1;
    end
    delay_last(i) = a(n);
end             

        
        
        
        
            
            