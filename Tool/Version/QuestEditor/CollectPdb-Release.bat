@echo off

if exist ".\QuestEditor-pdb\" del /f /q ".\QuestEditor-pdb\"
if not exist ".\QuestEditor-pdb" md "QuestEditor-pdb"

xcopy/AEFRSY "..\..\Temp\QuestEditor\Release\QuestEditor.pdb" ".\QuestEditor-pdb\Bin\Release\"

xcopy/AEFRSY "..\..\Temp\QuestEditor\Release\QuestEditor.exe" ".\QuestEditor-pdb\Bin\Release\"

echo 备份完成！