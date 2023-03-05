@echo off
xcopy/AEFRSY ".\AccountServer\Output\*.*" ".\log\AccountServer\"
del /f /q ".\AccountServer\Output"
xcopy/AEFRSY ".\DatabaseServer\Output\*.*" ".\log\DatabaseServer\"
del /f /q ".\DatabaseServer\Output"
xcopy/AEFRSY ".\AccountServer\Log\*.*" ".\log\AccountServer\Log\"
del /f /q ".\AccountServer\log"
xcopy/AEFRSY ".\DatabaseServer\Log\*.*" ".\log\DatabaseServer\Log\"
del /f /q ".\DatabaseServer\log"

xcopy/AEFRSY ".\CenterServer\Output\*.*" ".\log\CenterServer\"
del /f /q ".\CenterServer\Output"
xcopy/AEFRSY ".\GameServerGroup\GameServerA\Output\*.*" ".\log\GameServerGroup\GameServerA\"
del /f /q ".\GameServerGroup\GameServerA\Output"
xcopy/AEFRSY ".\GameServerGroup\GameServerB\Output\*.*" ".\log\GameServerGroup\GameServerB\"
del /f /q ".\GameServerGroup\GameServerB\Output"

xcopy/AEFRSY ".\GateServerGroup\GameServerA\GateServer1\Output\*.*" ".\log\GateServerGroup\GameServerA\GateServer1\"
del /f /q ".\GateServerGroup\GameServerA\GateServer1\Output"
xcopy/AEFRSY ".\GateServerGroup\GameServerA\GateServer2\Output\*.*" ".\log\GateServerGroup\GameServerA\GateServer2\"
del /f /q ".\GateServerGroup\GameServerA\GateServer2\Output"
xcopy/AEFRSY ".\GateServerGroup\GameServerB\GateServer1\Output\*.*" ".\log\GateServerGroup\GameServerB\GateServer1\"
del /f /q ".\GateServerGroup\GameServerB\GateServer1\Output"
xcopy/AEFRSY ".\GateServerGroup\GameServerB\GateServer2\Output\*.*" ".\log\GateServerGroup\GameServerB\GateServer2\"
del /f /q ".\GateServerGroup\GameServerB\GateServer2\Output"
xcopy/AEFRSY ".\LoginServer\Output\*.*" ".\log\LoginServer\Output\"
del /f /q ".\LoginServer\Output"


echo move over!
pause
