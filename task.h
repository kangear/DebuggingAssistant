#ifndef TASK_H
#define TASK_H

#include <QObject>

class Task : public QObject
{
    Q_OBJECT
public:
    explicit Task(QObject *parent = 0);

public slots:
    void doWork();
signals:
    void workFinished();
    void event_hotplug();

public:
    void MonitorNetlinkUevent();


    
};

#endif // TASK_H
