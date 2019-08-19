%重建trace记录表
function [trace_out]=TRACE_RESTRUCT(trace)

[m,n]=size(trace);

if m==1
    trace_out = [0,0];
else
    for i=1:m-1
        for j=1:n
            trace_out(i,j)=trace(i,j);
        end
    end
end