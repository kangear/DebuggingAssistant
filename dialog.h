#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "ui_dialog.h"
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
    void update_result(int level, const QString qstring);
    void device_not_connect();
    void check_tag(QTextEdit* textedit);
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

    void on_pushButton_released();

private:
    Ui::Dialog *ui;


private:
    QPushButton *push_button[10];
    void fill_all_push_button(QPushButton *push_button[10], int length);
    void update_ui(bool is_connect);
    void update_ui();
    void update_button_state(bool is_able, QPushButton *push_button[], int length);
    void update_file_change_light(void);
    void on_create();
};

#endif // DIALOG_H
