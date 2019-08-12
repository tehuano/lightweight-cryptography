[vsm vsn] = size(add_sum_vector);
j=0;
ADP_min_area_sum = 0;
for i=1:vsn
    if add_sum_vector(i) == min_add_sum
        ADP_min_area = min_add_sum * key_trace_delay_vector(i);
        j=j+1;
    else
        ADP_min_area = 0;
    end
    ADP_min_area_sum  = ADP_min_area_sum + ADP_min_area;
end
ADP_min_area_aver = ADP_min_area_sum/j  
ADP_reduce_percent = (EDP_orig-ADP_min_area_aver)/EDP_orig*100
