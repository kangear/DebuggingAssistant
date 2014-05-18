#include "backup.h"
#include <stdio.h>
#include <string>

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>
#include <QtCore>

backup::backup()
{

}

bool backup::is_connect()
{
    return do_cmd_return_val("adb shell > /dev/null 2>&1", "exit\r") == 0 ? true : false;
}

bool backup::do_remount_system()
{
    return do_cmd_return_val("adb shell", "su && busybox mount -o remount,rw /system && exit && exit\r") == 0 ? true : false;
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



int backup::do_cmd_return_str(QString cmd_str, QTextEdit* textedit)
{
    qDebug() << cmd_str;
    char*  cmd_char = NULL;
    QByteArray ba = cmd_str.toLatin1();
    cmd_char=ba.data();
    do_cmd_return_str(cmd_char ,textedit);
}

int backup::do_cmd_return_str(const char* cmd, QTextEdit* textedit)
{
    int ret = 0;
    FILE *fp;
    char buf[1024];
    fp = popen(cmd,"r");
    if (fp==NULL) return -1;
    QString endHtml = "</font><br>";
    QString line;
    while(fgets(buf,1024,fp)!=NULL)
    {
        backup::update_result(textedit, QString(QLatin1String(buf)) % endHtml);
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
