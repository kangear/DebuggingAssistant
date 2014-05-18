#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    bool is_connect;
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

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
