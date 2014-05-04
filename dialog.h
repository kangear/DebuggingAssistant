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

private slots:
    void on_pushButton_reboot_released();

    void on_pushButton_Refresh_released();

    void on_pushButton_remount_system_released();

    void on_pushButton_remount_root_released();

    void on_pushButton_update_framework_released();

    void on_pushButton_update_services_released();

    void on_pushButton_mult_run_released();

    void on_pushButton_update_apk_released();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
