#ifndef DIALOGCREATE_H
#define DIALOGCREATE_H

#include <QtWidgets>
#include "task.h"

class DialogCreate : public QDialog {
    Q_OBJECT

public:
    DialogCreate (QWidget *parent = nullptr);
    ~DialogCreate();

private:
    QVBoxLayout *mnLayout;
    QHBoxLayout *rowLayout;
    QPushButton *btnCreate, *btnCancel;
    QLineEdit *edtName;
    QLabel *name, *description, *dline;
    QTextEdit *edtDescription;
    QDateTimeEdit *data;
    QComboBox *statusCombo;

signals:
    void taskCreated(const Task &task);

private slots:
    void create();

};

#endif // DIALOGCREATE_H
