#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QDateTime>

enum class TaskStatus {
    New,
    InProgress,
    Done
};

struct Task {
    QString title;
    QString description;
    QDateTime deadline;
    TaskStatus status;
    int id = -1;
};


inline QString statusToString(TaskStatus s) {
    switch (s) {
        case TaskStatus::New: return QStringLiteral("New");
        case TaskStatus::InProgress: return QStringLiteral("InProgress");
        case TaskStatus::Done: return QStringLiteral("Done");
    }
    return QStringLiteral("New");
}

inline TaskStatus stringToStatus(const QString &str) {
    if (str == "InProgress") return TaskStatus::InProgress;
    if (str == "Done") return TaskStatus::Done;
    return TaskStatus::New;
}

#endif // TASK_H
