@echo off

if exist ".\Server-pdb\" del /f /q ".\Server-pdb\"
if not exist ".\Server-pdb" md "Server-pdb"

xcopy/AEFRSY "..\Temp\CenterServer\Release\CenterServer.pdb" ".\Server-pdb\Bin\Release\"
xcopy/AEFRSY "..\Temp\CharacterServer\Release\CharacterServer.pdb" ".\Server-pdb\Bin\Release\"
xcopy/AEFRSY "..\Temp\GameServer\Release\GameServer.pdb" ".\Server-pdb\Bin\Release\"
xcopy/AEFRSY "..\Temp\GateServer\Release\GateServer.pdb" ".\Server-pdb\Bin\Release\"
xcopy/AEFRSY "..\Temp\DatabaseServer\Release\DatabaseServer.pdb" ".\Server-pdb\Bin\Release\"

xcopy/AEFRSY "..\Temp\CenterServer\Release\CenterServer.exe" ".\Server-pdb\Bin\Release\"
xcopy/AEFRSY "..\Temp\CharacterServer\Release\CharacterServer.exe" ".\Server-pdb\Bin\Release\"
xcopy/AEFRSY "..\Temp\GameServer\Release\GameServer.exe" ".\Server-pdb\Bin\Release\"
xcopy/AEFRSY "..\Temp\GateServer\Release\GateServer.exe" ".\Server-pdb\Bin\Release\"
xcopy/AEFRSY "..\Temp\DatabaseServer\Release\DatabaseServer.exe" ".\Server-pdb\Bin\Release\"

echo 备份完成！