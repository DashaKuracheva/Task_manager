#ifndef DIALOGEDIT_H
#define DIALOGEDIT_H

#include <QtWidgets>
#include "task.h"

class DialogEdit : public QDialog {
    Q_OBJECT
public:
    DialogEdit(QWidget *parent = nullptr);

    void setTask(const Task &task); // Заполнить поля данными перед показом
    Task getTask() const;           // Забрать новые данные после нажатия "Сохранить"

private:
    QLineEdit *edtTitle;
    QVBoxLayout * vmainLayout;
    QHBoxLayout *hmainLayout;
    QTextEdit *edtDescript;
    QLabel *title,*descript,*datatime,*lblStatus;
    QDateTimeEdit *edtTime;
    QComboBox *status;
    QDialogButtonBox *buttonBox;
    QPushButton *save,*cancel;

};

#endif // DIALOGEDIT_H

