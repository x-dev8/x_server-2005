@echo off

if exist ".\QuestEditor-pdb-debug\" del /f /q ".\QuestEditor-pdb-debug\"
if not exist ".\QuestEditor-pdb-debug" md "QuestEditor-pdb-debug"

xcopy/AEFRSY "..\..\Temp\QuestEditor\Debug\QuestEditor.pdb" ".\QuestEditor-pdb-debug\Bin\Debug\"

xcopy/AEFRSY "..\..\Temp\QuestEditor\Debug\QuestEditor-Debug.exe" ".\QuestEditor-pdb-debug\Bin\Debug\"

echo 备份完成！