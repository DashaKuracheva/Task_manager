#include "dialogCreate.h"

DialogCreate::DialogCreate(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Создание задачи");
    setMinimumWidth(800);
    QVBoxLayout *mnLayout = new QVBoxLayout(this);
    QHBoxLayout *rowLayout = new QHBoxLayout();

    name = new QLabel("Название задачи:", this);
    mnLayout->addWidget(name);
    edtName = new QLineEdit(this);
    btnCreate = new QPushButton("Создать", this);
    rowLayout->addWidget(edtName);
    rowLayout->addWidget(btnCreate);

    description = new QLabel("Детальное описание:", this);
    edtDescription = new QTextEdit(this);

    dline = new QLabel("Срок выполнения:", this);
    data = new QDateTimeEdit(QDateTime::currentDateTime(), this);
    data->setCalendarPopup(true);
    data->setDisplayFormat("dd.MM.yyyy");

    statusCombo = new QComboBox(this);
    statusCombo->addItem("New");
    statusCombo->addItem("In Progress");
    statusCombo->addItem("Done");

    btnCancel = new QPushButton("Отмена", this);

    mnLayout->addLayout(rowLayout);
    mnLayout->addWidget(description);
    mnLayout->addWidget(edtDescription);

    mnLayout->addWidget(dline);
    mnLayout->addWidget(data);

    mnLayout->addWidget(new QLabel("Статус:", this));
    mnLayout->addWidget(statusCombo);

    mnLayout->addSpacing(10);
    mnLayout->addWidget(btnCancel);

    connect(btnCreate, SIGNAL(clicked()), this, SLOT(create()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(reject()));

}

DialogCreate::~DialogCreate() {}

void DialogCreate::create() {
    QString title = edtName->text().trimmed();
    if (title.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Название задачи не может быть пустым");
        return;
    }

    Task t;
    t.title = title;
    t.description = edtDescription->toPlainText().trimmed();
    t.deadline = data->dateTime();

    switch (statusCombo->currentIndex()) {
        case 0: t.status = TaskStatus::New; break;
        case 1: t.status = TaskStatus::InProgress; break;
        case 2: t.status = TaskStatus::Done; break;
        default: t.status = TaskStatus::New; break;
    }
    emit taskCreated(t);
    accept();
}








