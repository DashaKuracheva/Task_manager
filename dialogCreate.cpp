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

    deadline = new QLabel("Срок выполнения:", this);
    data = new QDateEdit(QDate::currentDate(), this);
    data->setCalendarPopup(true);
    data->setDisplayFormat("dd.MM.yyyy");

    btnCancel = new QPushButton("Отмена", this);

    mnLayout->addLayout(rowLayout);
    mnLayout->addWidget(description);
    mnLayout->addWidget(edtDescription);

    mnLayout->addWidget(deadline);
    mnLayout->addWidget(data);

    mnLayout->addSpacing(10);
    mnLayout->addWidget(btnCancel);

    connect(btnCreate, SIGNAL(clicked()), this, SLOT(accept()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(reject()));

}


DialogCreate::~DialogCreate(){}

void DialogCreate::create() {

}
