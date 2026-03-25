#include"dialogEdit.h"

DialogEdit::DialogEdit(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Редактирование задачи");
    setMinimumWidth(800);
    QVBoxLayout *vmainLayout = new QVBoxLayout(this);
    QHBoxLayout *hmainLayout = new QHBoxLayout();

    title = new QLabel("Название задачи(новое):", this);
    vmainLayout->addWidget(title);
    edtTitle= new QLineEdit(this);
    vmainLayout->addWidget(edtTitle);

    descript=new QLabel("Детальное описание(новое):", this);
    vmainLayout->addWidget(descript);
    edtDescript= new QTextEdit(this);
    vmainLayout->addWidget(edtDescript);

    datatime=new QLabel("Срок выполнения(новый):", this);
    vmainLayout->addWidget(datatime);
    edtTime = new QDateTimeEdit(QDateTime::currentDateTime(), this);
    edtTime->setCalendarPopup(true);
    edtTime->setDisplayFormat("dd.MM.yyyy HH:mm");
    edtTime->setTimeSpec(Qt::LocalTime);
    vmainLayout->addWidget(edtTime);

    lblStatus= new QLabel("Статус задачи(новый):", this);
    vmainLayout->addWidget(lblStatus);
    status = new QComboBox(this);
    status->addItem("New");
    status->addItem("In Progress");
    status->addItem("Done");
    vmainLayout->addWidget(status);

    save = new QPushButton("Сохранить", this);
    cancel = new QPushButton("Отменить", this);
    hmainLayout->addWidget(save);
    hmainLayout->addWidget(cancel);

    vmainLayout->addLayout(hmainLayout);

    connect(save, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));

}

void DialogEdit::setTask(const Task &task) {
    edtTitle->setText(task.title);
    edtDescript->setPlainText(task.description);
    edtTime->setDateTime(task.deadline);

    // Устанавливаем статус в комбобоксе
    if (task.status == TaskStatus::New) status->setCurrentIndex(0);
    else if (task.status == TaskStatus::InProgress) status->setCurrentIndex(1);
    else if (task.status == TaskStatus::Done) status->setCurrentIndex(2);
}

// Формируем новую задачу на основе того, что ввел пользователь
Task DialogEdit::getTask() const {
    Task t;
    t.title = edtTitle->text();
    t.description = edtDescript->toPlainText();
    t.deadline = edtTime->dateTime();

    int idx = status->currentIndex();
    if (idx == 0) t.status = TaskStatus::New;
    else if (idx == 1) t.status = TaskStatus::InProgress;
    else t.status = TaskStatus::Done;

    return t;
}
