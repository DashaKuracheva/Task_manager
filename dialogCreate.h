#ifndef DIALOGCREATE_H
#define DIALOGCREATE_H

#include <QtWidgets>

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
    QLabel *name, *description, *deadline;
    QTextEdit *edtDescription;
    QDateEdit *data;

private slots:
    void create();

};

#endif // DIALOGCREATE_H
