#ifndef BACKUP_H
#define BACKUP_H

class backup
{
public:
    backup();
    static bool is_connect();

private:
    static int do_cmd_return_val(const char *cmd, const char* input_cmd);
};

#endif // BACKUP_H
