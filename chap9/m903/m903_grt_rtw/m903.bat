set MATLAB=C:\MATLAB701
set MSVCDir=c:\program files\microsoft visual studio .net 2003\vc7
"C:\MATLAB701\rtw\bin\win32\envcheck" INCLUDE "c:\program files\microsoft visual studio .net 2003\vc7\include"
if errorlevel 1 goto vcvars32
"C:\MATLAB701\rtw\bin\win32\envcheck" PATH "c:\program files\microsoft visual studio .net 2003\vc7\bin"
if errorlevel 1 goto vcvars32
goto make
:vcvars32
set VSINSTALLDIR=c:\program files\microsoft visual studio .net 2003\common7\ide
set VCINSTALLDIR=c:\program files\microsoft visual studio .net 2003
set FrameworkSDKDir=c:\program files\microsoft visual studio .net 2003\FrameworkSDK
set FrameworkDir=c:\program files\microsoft visual studio .net 2003\Framework
call "C:\MATLAB701\toolbox\rtw\rtw\private\vcvars32_700.bat"
:make
nmake -f m903.mk ADD_MDL_NAME_TO_GLOBALS=1 VISUAL_VER=7.0
@if not errorlevel 0 echo The make command returned an error of %errorlevel%
