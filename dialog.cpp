#include "dialog.h"
#include "ui_dialog.h"
#include "backup.h"
#include "task.h"

#include <QtCore>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    on_create();

    QThread *thread = new QThread( );
    Task    *task   = new Task();
    task->moveToThread(thread);
    connect( thread, SIGNAL(started()), task, SLOT(doWork()) );
    connect( task, SIGNAL(event_hotplug()), this, SLOT(event_hotplug()) );
    connect( task, SIGNAL(workFinished()), thread, SLOT(quit()) );
    //automatically delete thread and task object when work is done:
    connect( thread, SIGNAL(finished()), task, SLOT(deleteLater()) );
    connect( thread, SIGNAL(finished()), thread, SLOT(deleteLater()) );
    thread->start();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::event_hotplug()
{
    //qDebug() << "hotplug_callback";
    update_ui();
}

// reboot device
void Dialog::on_pushButton_reboot_released()
{
    if(!check_if_can_run(false))
        return;

    int ret = backup::do_cmd_return_str("adb reboot 2>&1", ui->textEdit_result);
    if(ret != 0)
        update_result(msg_alert, "Reboot failed!");
    else
        update_result(msg_succeed, "Reboot succeed!");

    update_ui();
}


// refreash ui
void Dialog::on_pushButton_Refresh_released()
{
    update_ui();
}

bool Dialog::check_if_device_connect()
{
    int ret = false;
    if(true == backup::is_connect())
    {
        is_connect = true;
        ui->label_connect_state->setText("<font color='blue'>已连接!</font>");
        ret = true;
    }
    else
    {
        is_connect = false;
        ui->label_connect_state->setText("<font color='red'>未连接!</font>");
    }
    return ret;
}

// remount /system
void Dialog::on_pushButton_remount_system_released()
{
    if(!check_if_can_run(false))
        return;
    int ret = backup::do_cmd_return_str("adb shell busybox mount -o remount,rw /system 2>&1", ui->textEdit_result);
    //int ret = backup::do_remount_system();
    if(ret != 0)
        update_result(msg_alert, "Remount system Error!\n");
    else
        update_result(msg_succeed, "Remount system ok!\n");

    update_ui();
}

// remount /
void Dialog::on_pushButton_remount_root_released()
{
    if(!check_if_can_run(false))
        return;
    int ret = backup::do_cmd_return_str("adb shell busybox mount -o remount,rw / 2>&1", ui->textEdit_result);
    if(ret != 0)
        update_result(msg_alert, "Remount root Error!\n");
    else
        update_result(msg_succeed, "Remount root ok!\n");
}

// update framework.jar
void Dialog::on_pushButton_update_framework_released()
{
    if(!check_if_can_run(false))
        return;
    int ret = backup::do_cmd_return_str(get_cmd_update_framework_jar(), ui->textEdit_result);
    if(ret != 0)
        update_result(msg_alert, "Update framework Error!\n");
    else
        update_result(msg_succeed, "Update framework ok!\n");
}

// update services.jar
void Dialog::on_pushButton_update_services_released()
{
    if(!check_if_can_run(false))
        return;
    int ret = backup::do_cmd_return_str(get_cmd_update_services_jar(), ui->textEdit_result);
    if(ret != 0)
        update_result(msg_alert, "Update services java Error!\n");
    else
        update_result(msg_succeed, "Update services java ok!\n");
}

void Dialog::on_pushButton_update_apk_released()
{
    if(!check_if_can_run(false))
        return;
    if(system("adb") != 0)
        qDebug("Update apk Error!\n");
    else
        qDebug("Update apk ok!\n");
}

void Dialog::on_pushButton_mult_run_released()
{

    if(!check_if_can_run(false))
        return;

    ui->pushButton_mult_run->setEnabled(false);

    // remount system
    if(ui->checkBox_remount_system->checkState() == Qt::Checked)
        on_pushButton_remount_system_released();

    // remount root
    if(ui->checkBox_remount_root->checkState() == Qt::Checked)
        on_pushButton_remount_root_released();

    // update services framework
    if(ui->checkBox_update_framework->checkState() == Qt::Checked)
        on_pushButton_update_framework_released();

    // update services java
    if(ui->checkBox_update_services->checkState() == Qt::Checked)
        on_pushButton_update_services_released();

    // update services jni
    if(ui->checkBox_update_services_jni->checkState() == Qt::Checked)
        on_pushButton_update_services_jni_released();

    // update apk
    if(ui->checkBox_update_apk->checkState() == Qt::Checked)
        on_pushButton_update_apk_released();

    // update hardware.so
    if(ui->checkBox_update_hardware->checkState() == Qt::Checked)
        on_pushButton_update_hardware_released();

    // reboot device
    if(ui->checkBox_reboot->checkState() == Qt::Checked)
        on_pushButton_reboot_released();

    ui->pushButton_mult_run->setEnabled(true);
}


// update hardware
void Dialog::on_pushButton_update_hardware_released()
{
    if(!check_if_can_run(false))
        return;
    int ret = backup::do_cmd_return_str("adb push /home/kangear/ybk-hw/ybkMisc/out/target/product/rk30sdk/system/lib/hw/print.default.so /system/lib/hw/ 2>&1", ui->textEdit_result);
    if(ret != 0)
        update_result(msg_alert, "Update hardware Error!\n");
    else
        update_result(msg_succeed, "Update hardware ok!\n");
}

// update services jni
void Dialog::on_pushButton_update_services_jni_released()
{
    if(!check_if_can_run(false))
        return;
    int ret = backup::do_cmd_return_str(get_cmd_update_servers_so(), ui->textEdit_result);
    if(ret != 0)
        update_result(msg_alert, "Update services jni now Error!\n");
    else
        update_result(msg_succeed, "Update services jni now ok!\n");

}

void Dialog::update_result(int level, const QString qstring)
{
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

void Dialog::err_log(const QString info)
{
    update_result(msg_alert, info);
}

// update vold.bin
void Dialog::on_pushButton_update_vold_released()
{
    if(!check_if_can_run(true))
        return;

    if(QFile(framework_jar_absolute_path).exists())
    {
        int ret = backup::do_cmd_return_str(get_cmd_update_vold_bin(), ui->textEdit_result);
        if(ret != 0)
            update_result(msg_alert, "Update vold Failed!\n");
        else
        {
            // restart vold
            backup::do_cmd_return_str("adb shell setprop ctl.stop vold && adb shell setprop ctl.start vold 2>&1", ui->textEdit_result);
            update_result(msg_succeed, "Update vold Succeed!\n");
        }
    }
    else
    {
        update_result(msg_alert, "No such file or directory!\n");
    }
}

void Dialog::fill_all_push_button(QPushButton *push_button[10], int length)
{
    for(int i=0; i<length; i++)
        push_button[i] = NULL;

    push_button[1] = ui->pushButton_remount_system;
    push_button[2] = ui->pushButton_remount_root;
    push_button[3] = ui->pushButton_update_framework;
    push_button[4] = ui->pushButton_update_services;
    push_button[5] = ui->pushButton_update_services_jni;
    push_button[6] = ui->pushButton_update_hardware;
    push_button[7] = ui->pushButton_update_apk;
    push_button[8] = ui->pushButton_reboot;
    push_button[9] = ui->pushButton_mult_run;
    push_button[10] = ui->pushButton_update_vold;
}

void Dialog::update_ui()
{
    check_if_can_run(false);
    update_button_state(is_can_run, push_button, PUSH_BUTTON_MAX_NUMBER);
    update_target_product_path();
}

void Dialog::update_button_state(bool is_able, QPushButton *push_button[], int length)
{
    for(int i=0; i< length ; i++)
        if(push_button[i] != NULL)
            push_button[i]->setDisabled(!is_able);

}

void Dialog::on_create()
{
    // if debug
    debug = false;

    fill_all_push_button(push_button, PUSH_BUTTON_MAX_NUMBER);

    // init sth.
    is_path_saved = true;
    is_current_thread_run = false;
    is_can_run = true;

    // update ui
    update_ui();

    ui->textEdit_result->setFont (QFont ("OldEnglish", 8));

}

void Dialog::update_target_product_path()
{
    target_product_path = ui->lineEdit_android_source->text() + "/out/target/product/" + ui->lineEdit_target_product->text();
    if(false)qDebug() << target_product_path;
}

void Dialog::update_target_file_path()
{

    framework_jar_relative_path = "system/framework/framework.jar";
    services_jar_relative_path  = "system/framework/services.jar";
    servers_so_relative_path    = "system/lib/libandroid_servers.so";
    vold_bin_relative_path      = "system/bin/vold";

    // framework_jar_absolute_path = target_product_path + "/" + framework_jar_relative_path;
    //        framework.jar system/framework/framework.jar
    //         services.jar system/framework/services.jar
    //libandroid_servers.so system/lib/libandroid_servers.so
    //                 vold system/bin/vold
    framework_jar_absolute_path = target_product_path + "/" + framework_jar_relative_path;
    services_jar_absolute_path  = target_product_path + "/" + services_jar_relative_path;
    servers_so_absolute_path    = target_product_path + "/" + servers_so_relative_path;
    vold_bin_absolute_path      = target_product_path + "/" + vold_bin_relative_path;


}

QString Dialog::get_cmd_update_framework_jar()
{
    return  "adb push "
            + framework_jar_absolute_path + " "
            + framework_jar_relative_path + " 2>&1";
}

QString Dialog::get_cmd_update_services_jar()
{
    return "adb push "
            + services_jar_absolute_path + " "
            + services_jar_relative_path + " 2>&1";
}

QString Dialog::get_cmd_update_servers_so()
{
    return "adb push "
            + servers_so_absolute_path + " "
            + servers_so_relative_path + " 2>&1";
}

QString Dialog::get_cmd_update_vold_bin()
{
    return "adb push "
            + vold_bin_absolute_path + " "
            + vold_bin_relative_path + " 2>&1";
}

void Dialog::on_pushButton_edit_path_released()
{
    if(ui->lineEdit_android_source->isEnabled())
    {
        ui->lineEdit_android_source->setDisabled(true);
        ui->lineEdit_target_product->setDisabled(true);
        ui->pushButton_edit_path->setText("Edit");
        is_path_saved = true;
    }
    else
    {
        ui->lineEdit_android_source->setDisabled(false);
        ui->lineEdit_target_product->setDisabled(false);
        ui->pushButton_edit_path->setText("Save");

        // if path is not exist when app start.
        if(check_path() == false)
            ui->pushButton_edit_path->setDisabled(true);

        is_path_saved = false;
    }
    update_ui();
}


bool Dialog::check_path()
{
    bool ret = false;
    ui->label_path_title->setText("");
    update_target_product_path();
    update_target_file_path();
    QDir *dir = new QDir(ui->lineEdit_android_source->text());
    if(!dir->exists())
    {
        ui->label_path_title->setText("<font color='red'>Android source path is not exists!</font>");
    }
    else
    {
        QDir *dir = new QDir(target_product_path);
        if(!dir->exists())
        {
            ui->label_path_title->setText("<font color='red'>target_product_path is not exists!</font>");
        }
        else
        {
            ret = true;
        }
    }

    return ret;
}

void Dialog::on_lineEdit_android_source_textChanged(const QString &arg1)
{
    if(check_path() == false)
        ui->pushButton_edit_path->setDisabled(true);
    else
        ui->pushButton_edit_path->setDisabled(false);
}

void Dialog::on_lineEdit_target_product_textChanged(const QString &arg1)
{
    if(check_path() == false)
        ui->pushButton_edit_path->setDisabled(true);
    else
        ui->pushButton_edit_path->setDisabled(false);
}


bool Dialog::check_if_can_run(bool is_print_log)
{
    is_can_run = true;
    if(!is_path_saved)
    {
        if(is_print_log)
            err_log("Please save path first!");
        is_can_run = false;
    }
    if(!check_path())
    {
        if(is_print_log)
            err_log("Path is not exist!");
        is_can_run = false;
    }
    if(!check_if_device_connect())
    {
        if(is_print_log)
            err_log("Device is not connected!");
        is_can_run = false;
    }

    return is_can_run;
}

void Dialog::on_pushButton_sync_system_released()
{
    if(!check_if_can_run(false))
        return;

    QString android_product_out = target_product_path;
    if(QDir(android_product_out).exists())
    {
        int ret = backup::do_cmd_return_str("adb -p " + android_product_out + " sync system 2>&1", ui->textEdit_result);
        if(ret != 0)
            update_result(msg_alert, "Sync system Failed!\n");
        else
            update_result(msg_succeed, "Sync system Succeed!\n");
    }
    else
        update_result(msg_alert, "No such file or directory!\n");
}

void Dialog::on_pushButton_sync_data_released()
{
    if(!check_if_can_run(false))
        return;

    QString android_product_out = target_product_path;
    if(QDir(android_product_out).exists())
    {
        int ret = backup::do_cmd_return_str("adb -p " + android_product_out + " sync data 2>&1", ui->textEdit_result);
        if(ret != 0)
            update_result(msg_alert, "Sync data Failed!\n");
        else
            update_result(msg_succeed, "Sync data Succeed!\n");
    }
    else
        update_result(msg_alert, "No such file or directory!\n");
}
