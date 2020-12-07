clear
clc
% 加载数据
load('../../data/nurbs/N_surface_data.mat');
addpath('../');

% 绘图区间
xspain=[min(P(1,:))-1,max(P(1,:))+1];
yspain=[min(P(2,:))-1,max(P(2,:))+1];
zspain=[min(P(3,:))-0.5,max(P(3,:))+0.5];

% 节点
figure
view(3);
hold on;grid on;axis equal;
P1=reshape(P(1,:),nx,ny);
P2=reshape(P(2,:),nx,ny);
P3=reshape(P(3,:),nx,ny);
surf(P1,P2,P3,'FaceColor','none','LineWidth',1.0);
plot3(P1,P2,P3,'r*');
set(gca,'Xtick',0:nx,'Ytick',0:ny);
xlabel('\it x'); ylabel('\it y'); zlabel('\it z');
xlim(xspain);ylim(yspain);zlim(zspain);
% text(P(1,2*nx+2)-0.1,P(2,2*nx+2)+0.1,P(3,2*nx+2)+0.4,'P_{32}');
styleset(8,6,10.5,'S_plot2_p');

% 节点与曲面
figure
view(3);
hold on;grid on;axis equal;
P1=reshape(P(1,:),nx,ny);
P2=reshape(P(2,:),nx,ny);
P3=reshape(P(3,:),nx,ny);
surf(P1,P2,P3,'FaceColor','none','LineWidth',1.0);
plot3(P1,P2,P3,'r*');
surf(sx,sy,sz,'LineWidth',0.3);
colormap(jet);
set(gca,'Xtick',0:nx,'Ytick',0:ny);
xlabel('\it x'); ylabel('\it y'); zlabel('\it z');
xlim(xspain); ylim(yspain); zlim(zspain);
styleset(8,6,10.5,'S_plot2');

