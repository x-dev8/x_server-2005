@echo off

if exist ".\Robot-pdb\" del /f /q ".\Robot-pdb\"
if not exist ".\Robot-pdb" md "Robot-pdb"

xcopy/AEFRSY "..\..\Temp\Robot\Release\Robot.pdb" ".\Robot-pdb\Bin\Release\"

xcopy/AEFRSY "..\..\Temp\Robot\Release\Robot.exe" ".\Robot-pdb\Bin\Release\"

echo 备份完成！