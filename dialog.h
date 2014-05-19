#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <qpushbutton.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    volatile bool is_connect;
    volatile bool is_current_thread_run;
    volatile bool is_target_product_path_exist;
    volatile bool is_path_saved;
    volatile bool is_can_run;
    bool debug;
    void update_result(int level, bool is_endline, const QString qstring);
    void update_result(int level, const QString qstring);
    void device_not_connect();
    const static int msg_alert = 0;
    const static int msg_notify = 1;
    const static int msg_info = 2;
    const static int msg_succeed = 3;

private slots:
    void on_pushButton_reboot_released();

    void on_pushButton_Refresh_released();

    void on_pushButton_remount_system_released();

    void on_pushButton_remount_root_released();

    void on_pushButton_update_framework_released();

    void on_pushButton_update_services_released();

    void on_pushButton_mult_run_released();

    void on_pushButton_update_apk_released();

    void on_pushButton_update_hardware_released();

    void on_pushButton_update_services_jni_released();

    void on_pushButton_update_vold_released();

    void on_pushButton_edit_path_released();
    bool check_path();

    void on_lineEdit_android_source_textChanged(const QString &arg1);

    void on_lineEdit_target_product_textChanged(const QString &arg1);

    void on_pushButton_sync_system_released();

    void on_pushButton_sync_data_released();

private:
    Ui::Dialog *ui;

public slots:
    void event_hotplug();

// public func
public:
    void err_log(const QString info);
    bool check_if_can_run(bool is_print_log);
    bool check_if_device_connect();


private:
#define PUSH_BUTTON_MAX_NUMBER 20
    QPushButton *push_button[PUSH_BUTTON_MAX_NUMBER];
    void fill_all_push_button(QPushButton *push_button[10], int length);
    void update_ui(bool is_connect);
    void update_ui();
    void update_button_state(bool is_able, QPushButton *push_button[], int length);
    void update_file_change_light(void);
    void on_create();
    QString target_product_path;
    void update_target_product_path();
    void update_target_file_path();

    QString framework_jar_absolute_path;
    QString services_jar_absolute_path;
    QString servers_so_absolute_path;
    QString vold_bin_absolute_path;

    // const final
    QString framework_jar_relative_path;
    QString services_jar_relative_path;
    QString servers_so_relative_path;
    QString vold_bin_relative_path;

    QString get_cmd_update_framework_jar();
    QString get_cmd_update_services_jar();
    QString get_cmd_update_servers_so();
    QString get_cmd_update_vold_bin();
};

#endif // DIALOG_H
