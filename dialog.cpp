#include "dialog.h"
#include "ui_dialog.h"
#include "backup.h"

#include <QtCore>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    on_create();

    ui->textEdit_result->setFont (QFont ("OldEnglish", 8));
    on_pushButton_Refresh_released();

    update_ui();
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

    update_ui();
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
    update_ui(is_connect);
}
// remount /system
void Dialog::on_pushButton_remount_system_released()
{
    on_pushButton_Refresh_released();
    if(true == is_connect)
    {
        int ret = backup::do_cmd_return_str("adb shell busybox mount -o remount,rw /system 2>&1", ui->textEdit_result);
        //int ret = backup::do_remount_system();
        if(ret != 0)
            update_result(msg_alert, "Remount system Error!\n");
        else
            update_result(msg_succeed, "Remount system ok!\n");
    }
    else
        device_not_connect();
    update_ui();
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
    {
        device_not_connect();
        return;
    }

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

void Dialog::device_not_connect()
{
    check_tag(ui->textEdit_result);
    update_result(msg_alert, "Device is not connect!\n");
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



void Dialog::check_tag(QTextEdit* textedit)
{
//    QString endHtml = "</font><br>";
//    QString line = "-------------------------------------" % endHtml;
//    if(textedit->toPlainText() != "")
//        backup::update_result(ui->textEdit_result, line);
}

void Dialog::fill_all_push_button(QPushButton *push_button[10], int length)
{
    for(int i=0; i<length; i++)
        push_button[i] = NULL;

    push_button[0] = ui->pushButton_Settings;
    push_button[1] = ui->pushButton_remount_system;
    push_button[2] = ui->pushButton_remount_root;
    push_button[3] = ui->pushButton_update_framework;
    push_button[4] = ui->pushButton_update_services;
    push_button[5] = ui->pushButton_update_services_jni;
    push_button[6] = ui->pushButton_update_hardware;
    push_button[7] = ui->pushButton_update_apk;
    push_button[8] = ui->pushButton_reboot;
    push_button[9] = ui->pushButton_mult_run;
}
#define PUSH_BUTTON_MAX_NUMBER 10

void Dialog::on_pushButton_released()
{
    is_connect = !is_connect;
    update_ui();
}


void Dialog::update_ui(bool disable)
{
    update_button_state(disable, push_button, PUSH_BUTTON_MAX_NUMBER);
}

void Dialog::update_ui()
{
    update_button_state(is_connect && !is_current_thread_run, push_button, PUSH_BUTTON_MAX_NUMBER);
}

void Dialog::update_button_state(bool is_able, QPushButton *push_button[], int length)
{
    for(int i=0; i< length ; i++)
        if(push_button[i] != NULL)
            push_button[i]->setDisabled(!is_able);

}

void Dialog::on_create()
{
    fill_all_push_button(push_button, PUSH_BUTTON_MAX_NUMBER);
}
