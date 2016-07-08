function dydt=myfunc(t,y)
%function dydt=myfunc(t,y)
%常微分方程式の例題
%tは時間軸ベクトル
%出力はモーターの回転速度
%
dydt=[-y(1)+1];