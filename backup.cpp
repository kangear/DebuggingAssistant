#include "backup.h"
#include <stdio.h>
#include <string>
#include "ui_dialog.h"
#include <QtCore>
#include "dialog.h"

backup::backup()
{

}

bool backup::is_connect()
{
    return do_cmd_return_val("adb shell > /dev/null 2>&1", "exit\r") == 0 ? true : false;
}

int backup::do_cmd_return_val(const char *cmd, const char* input_cmd)
{
    int ret = 0;
    FILE *fp;
    fp = popen(cmd,"w");
    if (fp == NULL) return -1;
    fputs(input_cmd, fp);
    ret = pclose(fp);

    return ret/256;
}

int backup::do_cmd_return_str(const char* cmd, QTextEdit* textedit)
{
    int ret = 0;
    FILE *fp;
    char buf[1024];
    fp = popen(cmd,"r");
    if (fp==NULL) return -1;
    while(fgets(buf,1024,fp)!=NULL)
    {
        backup::update_result(textedit, QString(QLatin1String(buf)) % "</font><br>");
    }

    ret = pclose(fp);
    return ret/256;
}

void backup::update_result(QTextEdit* textedit, const QString qstring)
{
    textedit->moveCursor(QTextCursor::End);
    textedit->textCursor().insertHtml(qstring);
    textedit->moveCursor(QTextCursor::End);
}
