#ifndef TASKLIST_H
#define TASKLIST_H

#include <QtWidgets>
#include "task.h"

class TaskList : public QWidget {
    Q_OBJECT
public:
    TaskList(QWidget *parent = nullptr);
    ~TaskList();
    QJsonArray JSArr();
    void loadFromJSArr(const QJsonArray &arr);
    void clearTasks();


public slots:
    void addTask(const Task &task);

private:
    int nextId = 0; // уникальные id
    QLabel *info;
    QTreeWidget *list;
    QVector<Task> allTasks;
    QWidget *actionWidget;
    void appendTaskItem(int index);
    void refreshList();

private slots:
    void onEditClicked();
    void onDeleteClicked();
};


#endif // TASKLIST_H










