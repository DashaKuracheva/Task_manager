#include "dialogOpen.h"

DialogOpen::DialogOpen(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Выбор файла");
    setMinimumWidth(600);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *fileLayout = new QHBoxLayout();

    pathEdit = new QLineEdit(this);
    pathEdit->setPlaceholderText("Путь к файлу");

    QPushButton *btnBrowse = new QPushButton("Обзор", this);
    fileLayout->addWidget(pathEdit);
    fileLayout->addWidget(btnBrowse);

    QPushButton *btnOk = new QPushButton("Открыть", this);
    QPushButton *btnCancel = new QPushButton("Отмена", this);

    QHBoxLayout *actionLayout = new QHBoxLayout();
    actionLayout->addWidget(btnOk);
    actionLayout->addWidget(btnCancel);

    mainLayout->addLayout(fileLayout);
    mainLayout->addLayout(actionLayout);

    connect(btnBrowse, SIGNAL(clicked()), this, SLOT(browseFile()));
    connect(btnOk, SIGNAL(clicked()), this, SLOT(acceptOpening()));
    connect(btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
}

void DialogOpen::browseFile() {
    QString selected = QFileDialog::getOpenFileName(0,"Выберите файл задач", "", "JSON файлы (*.json)");
    if (!selected.isEmpty()) {
        pathEdit->setText(selected);
        filePath = selected;
    }
}

void DialogOpen::acceptOpening() {

}
