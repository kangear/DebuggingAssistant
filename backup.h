#ifndef BACKUP_H
#define BACKUP_H

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

class backup
{
public:
    backup();
    static bool is_connect();
    static bool do_remount_system();
    static int do_cmd_return_str(const char *cmd, QTextEdit* textedit);
    static void update_result(QTextEdit* textedit, const QString qstring);

private:
    static int do_cmd_return_val(const char *cmd, const char* input_cmd);
};

#endif // BACKUP_H
