%延时矩阵重建函数
function [delay_out,dr_num_out]=DELAY_RESTRUCT(delay,delay_reserve,yi,yj,n_orig,dr_num)

[m,n]=size(delay);
for i=1:m
    for j=1:n-1
        delay_out(i,j)=delay(i,j);
    end
end
if yj>n_orig
    if yi>n_orig
        delay_out(:,yi) = delay_reserve(dr_num-2,:);
        delay_out(:,yj) = delay_reserve(dr_num-1,:);
        dr_num_out = dr_num - 2;
    else
        for i=1:m
            if delay(i,n)>0
                delay_out(i,yi) = 0;
                delay_out(i,yj) = delay(i,n) - 1;
                dr_num_out = dr_num;
            end
        end
    end
else
    for i=1:m
        if delay(i,n)==1
            delay_out(i,yi) = 0;
            delay_out(i,yj) = 0;
        end
    end
    dr_num_out = dr_num;
end
        
        