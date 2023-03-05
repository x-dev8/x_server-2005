@echo off

if exist ".\Server-pdb-debug\" del /f /q ".\Server-pdb-debug\"
if not exist ".\Server-pdb-debug" md "Server-pdb-debug"

xcopy/AEFRSY "..\Temp\CenterServer\Debug\CenterServer.pdb" ".\Server-pdb-debug\Bin\Debug\"
xcopy/AEFRSY "..\Temp\CharacterServer\Debug\CharacterServer.pdb" ".\Server-pdb-debug\Bin\Debug\"
xcopy/AEFRSY "..\Temp\GameServer\Debug\GameServer.pdb" ".\Server-pdb-debug\Bin\Debug\"
xcopy/AEFRSY "..\Temp\GateServer\Debug\GateServer.pdb" ".\Server-pdb-debug\Bin\Debug\"
xcopy/AEFRSY "..\Temp\DatabaseServer\Debug\DatabaseServer.pdb" ".\Server-pdb-debug\Bin\Debug\"

xcopy/AEFRSY "..\Temp\CenterServer\Debug\CenterServer-Debug.exe" ".\Server-pdb-debug\Bin\Debug\"
xcopy/AEFRSY "..\Temp\GameServer\Debug\GameServer-Debug.exe" ".\Server-pdb-debug\Bin\Debug\"
xcopy/AEFRSY "..\Temp\CharacterServer\Debug\CharacterServer-Debug.exe" ".\Server-pdb-debug\Bin\Debug\"
xcopy/AEFRSY "..\Temp\GateServer\Debug\GateServer-Debug.exe" ".\Server-pdb-debug\Bin\Debug\"
xcopy/AEFRSY "..\Temp\DatabaseServer\Debug\DatabaseServer-Debug.exe" ".\Server-pdb-debug\Bin\Debug\"

echo 备份完成！