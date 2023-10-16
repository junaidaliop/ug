clear all; 
clc; 
close all
h=0.8;
b=0.6; 
a=0.4; 
m = 80.; 
g = 9.81; 
Me = 100.; 
fprintf('Given dimensions of the shaft are as follows:\n\t a = 0.4m, b = 0.6m, h = 0.8m, \n\t Mass of shaft = 80kg')
fprintf('\n\t Moment about point E in the vertical direction is Me = 100Nm\n')

Ax=0; Ay=0; Az=0; % m
Bx=0; By=0; Bz=h; % m
Dx=0; Dy=b; Dz=0; % m
Ex=0; Ey=b; Ez=h; % m
Cx=0; Cy=b/2;Cz=h/2; % m
Px=a; Py=0; Pz=0; % m
fprintf('\t Let us assume point A of the shaft is at origin (0,0,0).\n\t Now we calculate the position vectors of');
fprintf(' each point')
fprintf('\n\t rA = 0i + 0j + 0k');
fprintf('\n\t rB = 0i + 0j + 0.8k');
fprintf('\n\t rC = 0i + 0.3j + 0.4k');
fprintf('\n\t rD = 0i + 0.6j + 0k');
fprintf('\n\t rE = 0i + 0.6j + 0.4k');
fprintf('\n\t rP = 0.4i + 0j + 0k');
fprintf('\n\t rG = 0i + 0j + -784.8k\n\t ');
rA=[Ax Ay Az];
rB=[Bx By Bz];
rD=[Dx Dy Dz];
rE=[Ex Ey Ez];
rC=[Cx Cy Cz];
rP=[Px Py Pz];
G = [0 0 -m*g];

fprintf('Now we find the unit vector in direction of the tension in cable PD.\n\t ');
fprintf('u = rPD / ||rPD||\n\t ');
fprintf('Next, we find the tension as\n\t T = ||T||.u\n\t ');
fprintf('The reaction forces at the bearings FA and FB are given as \n\t ');
fprintf('\n\t FA = FAxi + FAyj + Fzk');
fprintf('\n\t FB = FAxi + FAyj + 0k\n\t ');
syms FAx FAy FAz
FA = [FAx,FAy,FAz];
syms FBx FBy
FB = [FBx,FBy,0];

fprintf('\nEvaluating the equations of equilibrium of the system as follows\n\t ');
fprintf('\nSum of Forces = 0 \n\t ');
fprintf('\nFA + FB + G + T = 0 \n\t ');
fprintf('\nNow we can resolve the equations of equilibrium into their respective axial components\n and solve for Fx, Fy, and Fz');

u=(rP-rD)/norm(rP-rD);
syms T
T = T*u;
SF = FA + FB + G + T;
Me=[0,0,Me];
SMA = cross(rC, G) + cross(rD, T) + cross(rB, FB)+ Me;
Fx=vpa(SF(1),3); %this function rounds the figure off to 3 decimal places
fprintf('\n\nSum of forces in x-direction = Fx : %s = 0 \n\t ',char(Fx))
Fy=vpa(SF(2),3);
fprintf('\nSum of forces in y-direction = Fy : %s = 0 \n\t ',char(Fy))
Fz=vpa(SF(3),3);
fprintf('\nSum of forces in z-direction = Fz : %s = 0 \n\t ',char(Fz))
fprintf('\nSimilarly, we find the moments about each axis as well.\n\t ');

Mx=vpa(SMA(1),3);
fprintf('\n\t Moment about x-axis = Mx : %s = 0 \n\t ',char(Mx))
My=vpa(SMA(2),3);
fprintf('Moment about y-axis = My : %s = 0 \n\t ',char(My))
Mz=vpa(SMA(3),3);
fprintf('Moment about z-axis = Mz : %s = 0 \n\t ',char(Mz))
sol=solve(...
SF(1) , SF(2), SF(3),...
SMA(1),SMA(2),SMA(3));
FAxs=eval(sol.FAx);
FAys=eval(sol.FAy);
FAzs=eval(sol.FAz);
FBxs=eval(sol.FBx);
FBys=eval(sol.FBy);
Ts=eval(sol.T);
fprintf('\n\t\t\t\t\t\t From the above equations of equilibrium we obtained the following results.\n')
fprintf('\t FAx= %5.3f N \n',FAxs)
fprintf('\t FAy= %5.3f N \n',FAys)
fprintf('\t FAz= %5.3f N \n',FAzs)
fprintf('\t FBx= %5.3f N \n',FBxs)
fprintf('\t FBy= %5.3f N \n',FBys)
fprintf('\t T= %5.3f   N \n',Ts)
FAs = [FAxs FAys FAzs];
FBs = [FBxs FBys 0];
Ts = Ts*u;
axis_value=1;
hold on
axis([-axis_value axis_value -axis_value axis_value -axis_value axis_value])
grid on
view(140,20);
quiver3(0,0,0,axis_value+0.1,0,0,...
'Color','b','LineWidth',1.0);
text(axis_value+0.1,0,0,' x',...
'fontsize',12,'fontweight','b');
quiver3(0,0,0,0,axis_value+0.1,0,...
'Color','b','LineWidth',1.0);
text(0,axis_value+0.1,0,' y',...
'fontsize',12,'fontweight','b');
quiver3(0,0,0,0,0,axis_value+0.1,'Color','b','LineWidth',1.0);
text(0,0,axis_value+0.1,' z',...
'fontsize',12,'fontweight','b');

scatter3(Ax,Ay,Az,60,'k','filled')
scatter3(Bx,By,Bz,60,'k','filled')
scatter3(Dx,Dy,Dz,30,'b','filled')
scatter3(Ex,Ey,Ez,30,'b','filled')
scatter3(Cx,Cy,Cz,30,'r','filled')
scatter3(Px,Py,Pz,30,'b','filled')
text(Ax,Ay,Az,' A','fontsize',12);
text(Bx,By,Bz+0.05,' B','fontsize',12);
text(Dx,Dy,Dz,' D','fontsize',12);
text(Ex,Ey,Ez,' E','fontsize',12);
text(Cx,Cy,Cz,' C','fontsize',12);
text(Px,Py,Pz+0.05,' P','fontsize',12);

vert = [Ax Ay Az; Bx By Bz; Ex Ey Ez; Dx Dy Dz];

fac = [1 2 3 4];

prism=patch('Faces',fac,'Vertices',vert,'FaceColor','g');
line([Px Dx],[Py Dy],[Pz Dz],'LineStyle','--','Color','k','LineWidth',1)
fs = 1000;
quiver3(Dx,Dy,Dz,Ts(1)/fs,Ts(2)/fs,Ts(3)/fs,'Color','k','LineWidth',2);
text(Dx+Ts(1)/fs,Dy+Ts(2)/fs,Dz+0.03+Ts(3)/fs,'T');
quiver3(Ax,Ay,Az,FAs(1)/fs,FAs(2)/fs,FAs(3)/fs,'Color','k','LineWidth',2);
text(Ax+FAs(1)/fs,Ay+FAs(2)/fs,Az-0.1+FAs(3)/fs,'F_A');
quiver3(Bx,By,Bz,FBs(1)/fs,FBs(2)/fs,FBs(3)/fs,'Color','k','LineWidth',2);
text(Bx+FBs(1)/fs,By+FBs(2)/fs,Bz+0.05+FBs(3)/fs,'F_B');
quiver3(Cx,Cy,Cz,G(1)/fs,G(2)/fs,G(3)/fs,'Color','k','LineWidth',2);
text(Cx+G(1)/fs,Cy+G(2)/fs,Cz+G(3)/fs,'G');
quiver3(Bx,By,Bz,Me(1)/fs,Me(2)/fs,Me(3)/fs,'Color','k','LineWidth',2);
text(Bx+Me(1)/fs,By+0.05+Me(2)/fs,Bz+0.05+Me(3)/fs,'M_e');
alpha(prism,0.3);
xlabel('x(m)'); ylabel('y(m)');zlabel('z(m)');
%THE END%