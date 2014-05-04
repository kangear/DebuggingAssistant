#include "dialog.h"
#include "ui_dialog.h"
#include "backup.h"

#include <QtCore>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
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
        system("adb reboot");
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
        ui->label_connect_state->setText("未连接");
    }
}
// remount /system
void Dialog::on_pushButton_remount_system_released()
{
    on_pushButton_Refresh_released();
    if(true == is_connect)
    {
        if(system("adb shell mount -o remount,rw /system") != 0)
            qDebug("Remount system Error!");
        else
            qDebug("Remount system ok!");
    }
}

// remount /
void Dialog::on_pushButton_remount_root_released()
{
    on_pushButton_Refresh_released();
    if(true == is_connect)
    {
        if(system("adb shell mount -o remount,rw /") != 0)
            qDebug("Remount root Error!");
        else
            qDebug("Remount root ok!");
    }
}

// update framework.jar
void Dialog::on_pushButton_update_framework_released()
{
    on_pushButton_Refresh_released();
    if(true == is_connect)
    {
        if(system("adb push /home/kangear/ybk-hw/ybkMisc/out/target/product/rk30sdk/system/framework/framework.jar /system/framework/") != 0)
            qDebug("Update framework Error!");
        else
            qDebug("Update framework ok!");
    }
}

// update services.jar
void Dialog::on_pushButton_update_services_released()
{
    on_pushButton_Refresh_released();
    if(true == is_connect)
    {
        if(system("adb push /home/kangear/ybk-hw/ybkMisc/out/target/product/rk30sdk/system/framework/framework.jar /system/framework/") != 0)
            qDebug("Update framework Error!");
        else
            qDebug("Update framework ok!");
    }
}

void Dialog::on_pushButton_update_apk_released()
{
    on_pushButton_Refresh_released();
    if(true == is_connect)
    {
        if(system("adb") != 0)
            qDebug("Update apk Error!");
        else
            qDebug("Update apk ok!");
    }
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


