function graphShip(block)
  setup(block);
function setup(block)
  block.NumInputPorts  = 4;
  block.InputPort(1).Dimensions  = 3;
  block.InputPort(2).Dimensions  = 3;
  block.InputPort(3).Dimensions  = 3;
  block.InputPort(4).Dimensions  = 3;
  block.NumOutputPorts = 0;
  block.SetPreCompInpPortInfoToDynamic;
  block.SetPreCompOutPortInfoToDynamic;
  block.InputPort(1).DirectFeedthrough = false;
  block.InputPort(2).DirectFeedthrough = false;
  block.InputPort(3).DirectFeedthrough = false;
  block.InputPort(4).DirectFeedthrough = false;
  block.SampleTimes = [-1 0];
  block.SetAccelRunOnTLC(true);
  block.RegBlockMethod('Outputs',    @Output);  

function Output(block)
      
  s=4;
  d=[6 12 5];
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
      
  a=[-1; 0; 0];
  b=[0; 2; 0];
  c=[1; 0; 0];
  d=[0; 0; 0.8];
  h=[block.InputPort(1).Data(1);block.InputPort(1).Data(2);block.InputPort(1).Data(3)];
  T=[1,0,0;0,1,0;0,0,1];

  T(1,1)=block.InputPort(2).Data(1);
  T(2,1)=block.InputPort(2).Data(2);
  T(3,1)=block.InputPort(2).Data(3);
  T(1,2)=block.InputPort(3).Data(1);
  T(2,2)=block.InputPort(3).Data(2);
  T(3,2)=block.InputPort(3).Data(3);
  T(1,3)=block.InputPort(4).Data(1);
  T(2,3)=block.InputPort(4).Data(2);
  T(3,3)=block.InputPort(4).Data(3);
  a=T*a+h;
  b=T*b+h;
  c=T*c+h;
  d=T*d+h;
  x=[a(1) b(1) c(1) a(1);d(1) d(1) d(1) d(1)];
  y=[a(2) b(2) c(2) a(2);d(2) d(2) d(2) d(2)];
  z=[a(3) b(3) c(3) a(3);d(3) d(3) d(3) d(3)];
  colormap([1 0 0;0 1 0;0 0 1]);
  col=[0 -1 1];
  surf(x,y,z,col);
  axis([-2 10 0 10 0 10]);
  hold off;

