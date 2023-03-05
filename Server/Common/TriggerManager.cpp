#include "TriggerManager.h"

TriggerMananger& GetTriggerManager()
{
    static TriggerMananger instance;
    return instance;
}

void TriggerMananger::Update()
{
}
