function squareroot2(block)
  setup(block);
function setup(block)
  block.NumInputPorts  = 1;
  block.NumOutputPorts = 1;
  block.SetPreCompInpPortInfoToDynamic;
  block.SetPreCompOutPortInfoToDynamic;
  block.InputPort(1).DirectFeedthrough = true;
  block.SampleTimes = [-1 0];
  block.SetAccelRunOnTLC(true);
  block.RegBlockMethod('Outputs',    @Output);  

  function Output(block)
  block.OutputPort(1).Data = sqrt(block.InputPort(1).Data);
