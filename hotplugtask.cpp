#include "hotplugtask.h"

HotplugTask::HotplugTask()
{
}

void HotplugTask::doWork()
{
    system("ping www.baidu.com");
}
