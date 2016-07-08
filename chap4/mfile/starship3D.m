function starship3D()
%
%
s=4;
d=[12 12 12];
k=5;
n=2^k-1;
theta=pi*(-n:2:n)/n;
phi=(pi/2)*(-n:2:n)'/n;
X=s*cos(phi)*cos(theta)+d(1);
Y=s*cos(phi)*sin(theta)+d(2);
Z=s*sin(phi)*ones(size(theta))+d(3);
colormap([0 0 0;1 1 1]);
C=hadamard(2^k);
surf(X,Y,Z,C);
axis([-2 15 -2 15 -2 15]);
hold on;
T=eye(3);
h=[0 0 0];
a=[-1 0 0];
b=[0 2 0];
c=[1 0 0];
d=[0 0 0.8];
a=a*T+h;
b=b*T+h;
c=c*T+h;
d=d*T+h;
x=[a(1) b(1) c(1) a(1);d(1) d(1) d(1) d(1)];
y=[a(2) b(2) c(2) a(2);d(2) d(2) d(2) d(2)];
z=[a(3) b(3) c(3) a(3);d(3) d(3) d(3) d(3)];
colormap([0 0 0;1 1 0;1 1 1;1 0 0;0 1 0;1 0 1]);
c=[0 -0.5 0.5];
surf(x,y,z,c);
hold off;