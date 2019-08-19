%�м���·���ӳټ��㺯��
function [delay_mid]=DELAY_MID_COMP(b_sub,delay,xi,xj)

[m,n]=size(b_sub);
delay_mid = delay;

    for i=1:m
        if b_sub(i,n)==1
                max_delay = max(delay(i,xi),delay(i,xj));
                delay_mid(i,n)= max_delay + 1;
                delay_mid(i,xi) = -1;
                delay_mid(i,xj) = -1;
        else
            delay_mid(i,n)=-1;
        end
    end


