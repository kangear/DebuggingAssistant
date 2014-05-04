#include "backup.h"
#include <stdio.h>
#include <string>

backup::backup()
{

}

bool backup::is_connect()
{
    return do_cmd_return_val("adb shell", "exit\r") == 0 ? true : false;
}

int backup::do_cmd_return_val(const char *cmd, const char* input_cmd)
{
    int ret = 0;
    FILE *fp;
    fp = popen(cmd,"w");
    if (fp == NULL) return -1;
    fputs(input_cmd, fp);
    ret = pclose(fp);

    return ret;
}
