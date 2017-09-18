
#include "tasks.h"
#include "HardwareReset.h"

void InitTasks(void)
{
    HardwareResetMEF_ini();
}

void MainTasks(void)
{
    HardwareResetMEF_act( 30, 60 );
}
