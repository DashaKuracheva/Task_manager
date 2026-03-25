#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QDateTime>
#include <QJsonObject>

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


inline QJsonObject taskToJS(const Task &t) {
    QJsonObject obj;
    obj["title"] = t.title;
    obj["description"] = t.description;
    obj["deadline"] = t.deadline.toString(Qt::ISODate);
    obj["status"] = statusToString(t.status);
    obj["id"] = t.id;
    return obj;
}

inline Task taskFromJS(const QJsonObject &obj) {
    Task t;
    t.title = obj.value("title").toString();
    t.description = obj.value("description").toString();
    QString dl = obj.value("deadline").toString();
    t.deadline = QDateTime::fromString(dl, Qt::ISODate);
    t.status = stringToStatus(obj.value("status").toString());
    t.id = obj.value("id").toInt(-1);
    return t;
}

#endif // TASK_H
