function spaceship3D(T,h)
%�X�y�[�X�E�V�b�v�̃��f��
%���̓f�[�^
%��]�}�g���b�N�X
%���s�ړ��x�N�g��
%
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
colormap([1 0 0;0 1 0;0 0 1]);
c=[0 -1 1];
surf(x,y,z,c);
axis([-2 10 0 10 0 10]);
