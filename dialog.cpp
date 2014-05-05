#include "dialog.h"
#include "ui_dialog.h"
#include "backup.h"

#include <QtCore>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->textEdit_result->setFont (QFont ("OldEnglish", 8));
    on_pushButton_Refresh_released();
}

Dialog::~Dialog()
{
    delete ui;
}
// reboot device
void Dialog::on_pushButton_reboot_released()
{
    on_pushButton_Refresh_released();
    if(true == is_connect)
    {
        int ret = backup::do_cmd_return_str("adb reboot 2>&1", ui->textEdit_result);
        if(ret != 0)
            update_result(msg_alert, "Reboot failed!");
        else
            update_result(msg_succeed, "Reboot succeed!");

    }
    else
        device_not_connect();
}


// refreash connect state
void Dialog::on_pushButton_Refresh_released()
{
    if(true == backup::is_connect())
    {
        is_connect = true;
        ui->label_connect_state->setText("已连接");
    }
    else
    {
        is_connect = false;
       // ui->label_connect_state->setTextColor(QColor("red"));
        ui->label_connect_state->setText("未连接");
    }
}
// remount /system
void Dialog::on_pushButton_remount_system_released()
{
    on_pushButton_Refresh_released();
    if(true == is_connect)
    {
        int ret = backup::do_cmd_return_str("adb shell mount -o remount,rw /system 2>&1", ui->textEdit_result);
        if(ret != 0)
            update_result(msg_alert, "Remount system Error!\n");
        else
            update_result(msg_succeed, "Remount system ok!\n");
    }
    else
        device_not_connect();
}

// remount /
void Dialog::on_pushButton_remount_root_released()
{
    on_pushButton_Refresh_released();
    if(true == is_connect)
    {
        int ret = backup::do_cmd_return_str("adb shell mount -o remount,rw / 2>&1", ui->textEdit_result);
        if(ret != 0)
            update_result(msg_alert, "Remount root Error!\n");
        else
            update_result(msg_succeed, "Remount root ok!\n");
    }
    else
        device_not_connect();
}

// update framework.jar
void Dialog::on_pushButton_update_framework_released()
{
    on_pushButton_Refresh_released();
    if(true == is_connect)
    {
        int ret = backup::do_cmd_return_str("adb push /home/kangear/ybk-hw/ybkMisc/out/target/product/rk30sdk/system/framework/framework.jar /system/framework/ 2>&1", ui->textEdit_result);
        if(ret != 0)
            update_result(msg_alert, "Update framework Error!\n");
        else
            update_result(msg_succeed, "Update framework ok!\n");
    }
    else
        device_not_connect();
}

// update services.jar
void Dialog::on_pushButton_update_services_released()
{
    on_pushButton_Refresh_released();
    if(true == is_connect)
    {
        int ret = backup::do_cmd_return_str("adb push /home/kangear/ybk-hw/ybkMisc/out/target/product/rk30sdk/system/framework/framework.jar /system/framework/ 2>&1", ui->textEdit_result);
        if(ret != 0)
            update_result(msg_alert, "Update services java Error!\n");
        else
            update_result(msg_succeed, "Update services java ok!\n");
    }
    else
        device_not_connect();
}

void Dialog::on_pushButton_update_apk_released()
{
    on_pushButton_Refresh_released();
    if(true == is_connect)
    {
        if(system("adb") != 0)
            qDebug("Update apk Error!\n");
        else
            qDebug("Update apk ok!\n");
    }
    else
        device_not_connect();
}

void Dialog::on_pushButton_mult_run_released()
{

    on_pushButton_Refresh_released();
    if(true != is_connect)
        return;

    ui->pushButton_mult_run->setEnabled(false);
    if(ui->checkBox_update_services->checkState() == Qt::Checked)
        on_pushButton_update_services_released();

    if(ui->checkBox_update_framework->checkState() == Qt::Checked)
        on_pushButton_update_framework_released();

    if(ui->checkBox_update_apk->checkState() == Qt::Checked)
        on_pushButton_update_apk_released();



    if(ui->checkBox_reboot->checkState() == Qt::Checked)
        on_pushButton_reboot_released();

    ui->pushButton_mult_run->setEnabled(true);
}



void Dialog::on_pushButton_update_hardware_released()
{
    on_pushButton_Refresh_released();
    if(true == is_connect)
    {
        int ret = backup::do_cmd_return_str("adb push /home/kangear/ybk-hw/ybkMisc/out/target/product/rk30sdk/system/lib/hw/print.default.so /system/lib/hw/ 2>&1", ui->textEdit_result);
        if(ret != 0)
            update_result(msg_alert, "Update hardware Error!\n");
        else
            update_result(msg_succeed, "Update hardware ok!\n");
    }
    else
        device_not_connect();
}

void Dialog::on_pushButton_update_services_jni_released()
{
    on_pushButton_Refresh_released();
    if(true == is_connect)
    {
        int ret = backup::do_cmd_return_str("adb push /home/kangear/ybk-hw/ybkMisc/out/target/product/rk30sdk/system/lib/libandroid_servers.so /system/lib/ 2>&1", ui->textEdit_result);
        if(ret != 0)
            update_result(msg_alert, "Update services jni now Error!\n");
        else
            update_result(msg_succeed, "Update services jni now ok!\n");
    }
    else
    {
        device_not_connect();
    }
}

void Dialog::update_result(int level, const QString qstring)
{
    check_tag(ui->textEdit_result);

    QString line = qstring;
    QString alertHtml = "<font color=\"Red\">";
    QString notifyHtml = "<font color=\"Lime\">";
    QString infoHtml = "<font color=\"Black\">";
    QString succeedHtml = "<font color=\"Blue\">";
    QString endHtml = "</font><br>";

    switch(level)
    {
        case msg_alert: line = alertHtml % line % endHtml + "--------------------------------"; break;
        case msg_notify: line = notifyHtml % line; break;
        case msg_info: line = infoHtml % line; break;
        case msg_succeed: line = succeedHtml % line % endHtml + "--------------------------------"; break;
        default: line = infoHtml % line; break;
    }
    line = line % endHtml;
    backup::update_result(ui->textEdit_result, line);
}

void Dialog::device_not_connect()
{
    check_tag(ui->textEdit_result);
    update_result(msg_alert, "Device is not connect!\n");
}

void Dialog::check_tag(QTextEdit* textedit)
{
//    QString endHtml = "</font><br>";
//    QString line = "-------------------------------------" % endHtml;
//    if(textedit->toPlainText() != "")
//        backup::update_result(ui->textEdit_result, line);
}



