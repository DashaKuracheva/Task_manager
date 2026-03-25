#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "dialogOpen.h"
#include "dialogCreate.h"
#include "taskList.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *widget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *rowLayout;
    QListWidget *taskList;
    QPushButton *btnAdd, *btnSearch;
    QLineEdit *edtSearch;
    QToolBar *toolBar;
    QAction *open, *saveFile, *newFile, *tasksList, *calendar, *deadline, *filter;
    TaskList *myTaskList;
    QString currentFilePath;
    QDialog *calendarDialog= nullptr;

private slots:
    void addTask();
    void search();
    void openFile();//для открытия файла *open
    void saveMyFile();// для сохранения файла *saveFile
    void addNewFile();//для добавления файла *newFile
    void displayCalendar(); //для отображения календаря *calendar
    void showTasks();// для отображения/скрытия задач *tasksList
    void sortDeadline();//сортировка по дедлайну *deadline
    void filterOut();// фильтрация по статусу *filter
    void displayFileContent(const QString &content);
    void onCalendarDestroyed(QObject* obj);

};

#endif // MAINWINDOW_H
