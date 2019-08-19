%%%%%%%%%%%%%%%%%%%%%%%%%%%%%图形显示%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
x = 1:compute_time;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(1)
%%%%%%%%%%%%%%%%%%%%%%%%%%画时间曲线图1%%%%%%%%%%%%%%%%%%%%%%%%%%%
subplot(3,1,1);
plot(x,add_sum_vector,'-k.','MarkerSize',20);
hold on 
%%%%%%%%%%画标题%%%%%%%
%title('(a) Total Operator Logic (in XOR Gates) VS. Iterative Times');
xlabel('Pattern Groups');
ylabel('Area (in XOR Gates)');
%legend({'多因子CSE计算时间','GreedyCSE计算时间'});
%%%%%%%%%%设置曲线图%%%%%%%
grid on
box off
%H=[0 110 12.5 15.5];
%axis(H)
figure_FontSize=14;
set(get(gca,'XLabel'),'FontSize',figure_FontSize,'Vertical','top');
set(get(gca,'title'),'FontSize',figure_FontSize,'Vertical','bottom');
set(get(gca,'YLabel'),'FontSize',figure_FontSize,'Vertical','bottom');
set(findobj('FontSize',10),'FontSize',figure_FontSize);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%{
%%%%%%%%%%%%%%%%%%%%%%%%%%画时间曲线图2%%%%%%%%%%%%%%%%%%%%%%%%%%%
subplot(3,1,2);
plot(x,key_trace_delay_vector,'-k.','MarkerSize',20);
%%%%%%%%%%画标题%%%%%%%
%title('(b) Logic Depth (in XOR Gates) VS. Iterative Times');
xlabel('Pattern Groups');
ylabel({'Critical Path Delay';'(in XOR Gates)'});
%h1=get(gca,'YLabel')
%legend({'多因子CSE计算时间','GreedyCSE计算时间'});
%%%%%%%%%%设置曲线图%%%%%%%
grid on
box off
%H=[0 110 3.5 6.5];
%axis(H)
figure_FontSize=14;
set(get(gca,'XLabel'),'FontSize',figure_FontSize,'Vertical','top');
set(get(gca,'title'),'FontSize',figure_FontSize,'Vertical','bottom');
set(get(gca,'YLabel'),'FontSize',figure_FontSize,'Vertical','bottom');
set(findobj('FontSize',10),'FontSize',figure_FontSize);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%{
%}
figure(1)
subplot(3,1,3);
%%{
%%%%%%%%%%%%%%%%%%%%%%%%%%画时间曲线图3%%%%%%%%%%%%%%%%%%%%%%%%%%%
plot(x,EDP_vector,'-k.','MarkerSize',20);
%%%%%%%%%%画标题%%%%%%%
%title('(c) EPD VS. Iterative Times');
xlabel('Pattern Groups');
ylabel('Area-Delay-Product');
%legend({'多因子CSE计算时间','GreedyCSE计算时间'});
%%%%%%%%%%设置曲线图%%%%%%%
grid on
box off
%H=[0 110 50 92];
%axis(H)
figure_FontSize=14;
set(get(gca,'XLabel'),'FontSize',figure_FontSize,'Vertical','top');
set(get(gca,'title'),'FontSize',figure_FontSize,'Vertical','bottom');
set(get(gca,'YLabel'),'FontSize',figure_FontSize,'Vertical','bottom');
set(findobj('FontSize',10),'FontSize',figure_FontSize);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%}
