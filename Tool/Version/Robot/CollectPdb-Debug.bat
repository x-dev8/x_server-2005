@echo off

if exist ".\Robot-pdb-debug\" del /f /q ".\Robot-pdb-debug\"
if not exist ".\Robot-pdb-debug" md "Robot-pdb-debug"

xcopy/AEFRSY "..\..\Temp\Robot\Debug\Robot.pdb" ".\Robot-pdb-debug\Bin\Debug\"

xcopy/AEFRSY "..\..\Temp\Robot\Debug\Robot-Debug.exe" ".\Robot-pdb-debug\Bin\Debug\"

echo 备份完成！