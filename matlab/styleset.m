%图片放大两倍以提高图片质量
%w:图片的宽度，h:图片的高度，fs：图片中字体大小（六号:7.5,小五:9, 五号:10.5, 小四:12, 四号:14）
%pn：图片的名字，用于保存图片
function styleset(w,h,fs,pn)
% set(gca,'Position',[.14 .14 .80 .74]); %设置边界
if w~=0&&h~=0
    set(gcf,'units','centimeters','Position',[1 2 w*2 h*2]); %设置大小  28.346*2*
end    
box on;
figure_FontSize=fs*2; %此处放大两倍提高图片质量
set(get(gca,'XLabel'),...
    'FontSize',figure_FontSize,...
    'FontName','Times New Roman',...
    'FontAngle','normal',...%normal,italic
    'FontWeight','normal',...%light,normal,demi,bold
    'Vertical','top'); 
set(get(gca,'YLabel'),...
    'FontSize',figure_FontSize,...
    'FontName','Times New Roman',...
    'FontAngle','normal',...
    'FontWeight','normal'); 
set(get(gca,'ZLabel'),...
    'FontSize',figure_FontSize,...
    'FontName','Times New Roman',...
    'FontAngle','normal',...
    'FontWeight','normal'); 
set(get(gca,'Legend'),...
    'FontSize',figure_FontSize,...
    'FontName','Times New Roman',...
    'FontAngle','normal',...
    'FontWeight','normal'); 
set(get(gca,'Title'),...
    'FontSize',figure_FontSize,...
    'FontName','Times New Roman',...
    'FontAngle','normal',...
    'FontWeight','normal'); 
set(gca,'FontSize',figure_FontSize)
set(findobj('FontSize',10),'FontSize',figure_FontSize); 
set(findobj(get(gca,'Children'),'LineWidth',0.5),'LineWidth',1);%将0.5线宽的线改为1

if nargin == 4
    saveas(gcf,pn,'png');%保存图片
end

end