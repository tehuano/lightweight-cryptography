function ChristofPaarFunction(fname)
%Christof Paar�㷨
%�汾V3.1

%{
add_sum_vector, the area after each cycle optimization.
key_trace_delay_vector, the delay after each cycle optimization.
EDP_vector, the area*delay after each cycle optimization.
min_add_sum, the minimal area among  optimizations.
min_trace_delay, the minimal delay among optimizations.
min_EDP, the minimal area*delay among optimizations.
%}

%��ձ�����
%clear
%�������ڣ�
clc
tic
%load zxqb;
m_rand=163;
n_rand=163;
%{
a = rand(m_rand,n_ra
for i=1:m_rand
    for j=1:n_rand
        if a(i,j)<=0.8;
            b(i,j)='0';
        else
            b(i,j)='1';
        end
    end
end
%}

b=importdata(strcat(fname,'.dat'),',');

b_orig=b;

%{
q = quantizer([5 0]);
%delta = ['8e';'47';'ad';'d8';'e2';'71';'38';'1c';];
delta = ['ff';'ff';];
b = hex2bin(q,delta)
%}

[m_orig,n_orig]=size(b);

%ͳ�Ƽӷ�������
add_sum = ADDER_SUM(b);
%%{
%��ʱ�����ʼ����
delay = DELAY_FIRST_COMP(b);
%ԭʼ����Ĺؼ�·�����㣻
delay_orig = DELAY_LAST_COMP(delay);

%%{
%ԭʼ�������
add_sum_orig = add_sum;
key_trace_delay_orig = max(delay_orig);
EDP_orig = add_sum * key_trace_delay_orig;
%}
%{
save zxqb b;
%}

cyc_num = 1; %�滻ѭ������
MF_all_num = 1; %���Ƶ������б�MF_all�е���ϸ���
dr_num = 1; %�ӳٱ����б����ӳ���������
delay_reserve = zeros(1,m_orig); %��ʼ���ӳٱ����б?

MF_steer_clear = 0; %�Ƿ��ƿ�
comb_or_ascend = 1; %����ϻ���׷��
Zu_He_Ke_Neng_Xing_Xu_Hao = 0;      %��Ͽ��������
min_EDP_sum = 0; %��СEDP���������
cyc_num_sum=0;
%ͳ�����Ƶ�ʣ�
F = COMB_FREQ(b);
%��������Ƶ��ֵ
Fmax = max(max(F));

if Fmax>1
    all_end = 0;        %����ѭ��
else
    all_end = 1;        %������ѭ��
end

%while all_end==0 
while all_end==0 && Zu_He_Ke_Neng_Xing_Xu_Hao < 1000
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%�ϲ����%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%    
   	if comb_or_ascend == 1
        if MF_steer_clear==0
            %���������Ƶ�ʵ����
            MF = MAX_FREQ_COMB(F,Fmax);
            %����ϱ������б���
            [MFm,MFn] = size(MF);
            for i=1:MFm
                MF_all(MF_all_num,1) = MF(i,1);
                MF_all(MF_all_num,2) = MF(i,2);
                MF_all(MF_all_num,3) = cyc_num;
                MF_all_num = MF_all_num + 1;
            end
        end
        MF_steer_clear = 0;
        MF_all;
        %ȡ���
        MF_all_num = MF_all_num - 1;
        xi = MF_all(MF_all_num,1);
        xj = MF_all(MF_all_num,2);
        %����¼
            MF_all(MF_all_num,1) = 0;
            MF_all(MF_all_num,2) = 0;
            MF_all(MF_all_num,3) = 0;   
        %�滻���
        [b,add_sum] = COMB_SUB(b,xi,xj,add_sum);
        %׷���滻���
        trace(cyc_num,1)=xi-1;
        trace(cyc_num,2)=xj-1;

        %���xi��xj����n_orig�򣬱����ϴ��ӳ���ݣ������Ժ�ָ���
        if xj>n_orig 
            if xi>n_orig 
                delay_reserve(dr_num,:)=delay(:,xi);
                delay_reserve(dr_num+1,:)=delay(:,xj);
                dr_num = dr_num + 2;
            end
        end
        %�����ӳ�
        delay = DELAY_MID_COMP(b,delay,xi,xj);

        %%%׼���´��滻%%%%
        %ͳ�����Ƶ�ʣ�
        F = COMB_FREQ(b);
        %��������Ƶ��ֵ
        Fmax = max(max(F));
        cyc_num=cyc_num+1;
        if Fmax>1 
           comb_or_ascend = 1;
        else
            if MF_all(1,1)==0
            	comb_or_ascend = 1;
                all_end = 1;
            else
            	comb_or_ascend = 0;
                all_end = 0;
            end
            %�����ܵ��ӳ�          
            delay_last = DELAY_LAST_COMP(delay);
            
           %%%%%%%%%%%%%%<<<<<<<��ʾ���1>>>>>>>%%%%%%%%%%
            Zu_He_Ke_Neng_Xing_Xu_Hao = Zu_He_Ke_Neng_Xing_Xu_Hao + 1
            trace;
            b;
            add_sum;
 
            key_trace_delay = max(delay_last);
            EDP = add_sum * key_trace_delay;
            delay;
           
            %%{
         	%%%%%%%%%%%%%%<<<<<<<��ʾ���2>>>>>>>%%%%%%%%%%
            add_sum_vector(Zu_He_Ke_Neng_Xing_Xu_Hao) = add_sum;
            key_trace_delay_vector(Zu_He_Ke_Neng_Xing_Xu_Hao) = key_trace_delay;
            EDP_vector(Zu_He_Ke_Neng_Xing_Xu_Hao) = EDP;
            cyc_num_vector(Zu_He_Ke_Neng_Xing_Xu_Hao) = cyc_num-1;
            cyc_num_sum = cyc_num_sum+cyc_num-1;
            %{
 %->->->->->%%%%%%%%%%%%%%<<<<<<<��ʾ���3>>>>>>>%%%%%%%%%
           if key_trace_delay == 7
                min_EDP_sum = min_EDP_sum + 1;
                Zu_He_Ke_Neng_Xing_Xu_Hao
                trace
                add_sum;
                key_trace_delay;
            end
            %}
        end
    end
        
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%׷�ݹ��%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  
	if comb_or_ascend == 0

        cyc_num = cyc_num - 1;
        yi = trace(cyc_num,1) + 1;
        yj = trace(cyc_num,2) + 1;
        %����¼
        trace=TRACE_RESTRUCT(trace);
        %ȡ���滻
        [b,add_sum] = COMB_SUB_INV(b,yi,yj,add_sum);
        %�ؽ��ӳپ���
       [delay,dr_num] = DELAY_RESTRUCT(delay,delay_reserve,yi,yj,n_orig,dr_num);
        
        %�Ƿ�ص��ϲ����
        MF_reserve_num = MF_all(MF_all_num-1,3);
        if MF_reserve_num < cyc_num
        	comb_or_ascend = 0;
        else
            comb_or_ascend = 1;
            MF_steer_clear = 1;
        end
            
    end
   
end

%%{
    %%%%%%%%%%%%%%<<<<<<<��ʾ���2>>>>>>>%%%%%%%%%%
	add_sum_vector;
	key_trace_delay_vector;
	EDP_vector;
    
b_orig;
add_sum_orig;
key_trace_delay_orig;
EDP_orig;
n_rand ;

%save zxq_result_orig add_sum_orig key_trace_delay_orig EDP_orig n_rand;
    
    min_add_sum = min(add_sum_vector);
    add_sum_reduce_percent = (add_sum_orig-min_add_sum)/add_sum_orig*100;
    
	min_trace_delay = min(key_trace_delay_vector);
       
  % z_paper_ADP_min_area_aver;
    
    min_EDP = min(EDP_vector);
	EDP_reduce_percent = (EDP_orig-min_EDP)/EDP_orig*100;
    
    %���ٰٷֱȼ���
% save zxq_result min_add_sum add_sum_reduce_percent min_trace_delay ADP_min_area_aver ADP_reduce_percent min_EDP EDP_reduce_percent;
    
 %%{   
    %%%%%%%%%%%%%%<<<<<<<��ʾ���3>>>>>>>%%%%%%%%%% 
   % cyc_num_vector
    cyc_num_aver = cyc_num_sum/Zu_He_Ke_Neng_Xing_Xu_Hao;
    cyc_num_max = max(cyc_num_vector)
    compute_time = Zu_He_Ke_Neng_Xing_Xu_Hao;
	min_EDP_sum;
%}
time=toc;
 %z_paper_picture_show;
% b_orig;
s1 = size(b)
s2 = size(trace)
opt_fname = [fname '_opt_' num2str(s1(1)) 'x' num2str(s1(2)) '.dat']
trace_fname = [fname '_trace_' num2str(s2(1)) 'x' num2str(s2(2)) '.dat']
csvwrite(opt_fname,b)
csvwrite(trace_fname,trace)

end

