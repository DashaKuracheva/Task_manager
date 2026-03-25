#include "mainwindow.h"
#include "dialogOpen.h"
#include "dialogCreate.h"
//#include "taskTree.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // формрование ЦЕНТРАЛЬНОГО ВИДЖЕТА
    widget = new QWidget(this);

    mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(20, 20, 20, 20);

    rowLayout = new QHBoxLayout();

    //формирование горизонтального слоя
    btnAdd = new QPushButton("Создать");
    btnAdd->setFixedWidth(300);
    btnAdd->setFixedHeight(60);
    connect(btnAdd, SIGNAL(clicked()), this, SLOT(addTask()));

    btnSearch = new QPushButton("Поиск");
    btnSearch->setFixedWidth(170);
    btnSearch->setFixedHeight(60);
    connect(btnSearch, SIGNAL(clicked()), this, SLOT(search()));

    edtSearch=new QLineEdit();
    edtSearch->setPlaceholderText("Поиск задач");
    edtSearch->setFixedHeight(60);

    rowLayout->setContentsMargins(200, 10, 200, 10);
    rowLayout->addWidget(edtSearch);
    rowLayout->addWidget(btnSearch);
    rowLayout->addSpacing(300);
    rowLayout->addWidget(btnAdd);

    myTaskList = new TaskList(this);

    //формирование вертикального слоя
    mainLayout->addLayout(rowLayout);
    mainLayout->setAlignment(rowLayout, Qt::AlignTop);
    mainLayout->addWidget(myTaskList);

    widget->setLayout(mainLayout);
    setCentralWidget(widget);

    //Формирование МЕНЮ
    QMenu *menu = menuBar()->addMenu("&Файл");

    open = new QAction("Открыть", this);
    open->setShortcut(QKeySequence("Ctrl+O"));
    menu->addAction(open);
    connect(open, SIGNAL(triggered()), this, SLOT(openFile()));

    newFile = new QAction("Новый файл", this);
    newFile->setShortcut(QKeySequence("Ctrl+N"));
    menu->addAction(newFile);
    connect(newFile, SIGNAL(triggered()), this, SLOT(addNewFile()));

    saveFile = new QAction("Сохранить", this);
    saveFile->setShortcut(QKeySequence("Ctrl+S"));
    menu->addAction(saveFile);
    connect(saveFile, SIGNAL(triggered()), this, SLOT(saveMyFile()));

    /*ДОБАВЛЕНИЕ СПРАВКИ
    menu = menuBar()->addMenu("Справка");
    about = new QAction("Справка");
    menu->addAction(about);*/

     //Формирование ПАНЕЛИ ИНСТРУМЕНТОВ
    toolBar = new QToolBar(this);

    toolBar->setIconSize(QSize(80, 80));
    addToolBar(toolBar);

    toolBar->addAction(QIcon(":/resourses/icons/open.png"), "Открыть", this, SLOT(openFile()));
    toolBar->addSeparator();
    toolBar->addAction(QIcon(":/resourses/icons/save.png"), "Сохранить", this, SLOT(saveMyFile()));
    toolBar->addSeparator();
    toolBar->addAction(QIcon(":/resourses/icons/calendar1.png"), "Календарь", this, SLOT(displayCalendar())); //toolBar->addAction(QIcon(":/resourses/calendar.png"), "Календарь", this, SLOT(displayCalendar()));
    toolBar->addSeparator();
    toolBar->addAction(QIcon(":/resourses/icons/tasks1.png"), "Список задач", this, SLOT(showTasks()));//отобразить скрыть список задач
    toolBar->addSeparator();
    toolBar->addAction(QIcon(":/resourses/icons/deadline.png"), "Дедлайн", this, SLOT(sortDeadline()));//блжайшие дедлайны
    toolBar->addSeparator();
    toolBar->addAction(QIcon(":/resourses/icons/filter.png"), "Фильтр", this, SLOT(filterOut()));//фильтрация задач по статусу

}

MainWindow::~MainWindow(){}

void MainWindow::addTask() {
    DialogCreate dialog(this);
    connect(&dialog, SIGNAL(taskCreated(Task)), myTaskList, SLOT(addTask(Task)));
    dialog.exec();
}

void MainWindow::search() {
    // код
}

void MainWindow::openFile() {
    DialogOpen dialogOpen(this);
    connect(&dialogOpen, SIGNAL(fileOpened(QString)), this, SLOT(displayFileContent(QString)));
    dialogOpen.exec();
}

void MainWindow::addNewFile() {
        if (myTaskList) {
            myTaskList->clearTasks();
        }
        currentFilePath.clear();
        statusBar()->showMessage("Новый проект создан (не сохранён)" , 3000);
}

void MainWindow::saveMyFile() {
        QString path = currentFilePath;
        if (path.isEmpty()) {
            path = QFileDialog::getSaveFileName(this, "Сохранить как", QString(), "JSON файлы (*.json)");
            if (path.isEmpty()) return;
            if (!path.endsWith(".json", Qt::CaseInsensitive)) path += ".json";
            currentFilePath = path;
        }

        QJsonArray arr = myTaskList->JSArr();
        QJsonObject root;
        root["tasks"] = arr;
        QJsonDocument doc(root);

        QFile file(path);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи: " + path);
            return;
        }
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();

        statusBar()->showMessage("Файл сохранён: " + path, 3000);
    }

void MainWindow::displayCalendar() {
    // код
}

void MainWindow::showTasks() {
    //myTaskView->setVisible(!myTaskView->isVisible());
}

void MainWindow::sortDeadline() {
    // код
}

void MainWindow::filterOut() {
    //код
}


void MainWindow::displayFileContent(const QString &content) {
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(content.toUtf8(), &err);
    if (err.error != QJsonParseError::NoError) {
        QMessageBox::warning(this, "Ошибка", "Неверный JSON: " + err.errorString());
        return;
    }
    QJsonArray arr;
    if (doc.isObject()) {
        QJsonObject root = doc.object();
        if (root.contains("tasks") && root.value("tasks").isArray()) {
            arr = root.value("tasks").toArray();
        } else {
            QMessageBox::warning(this, "Ошибка", "JSON не содержит массив tasks");
            return;
        }
    } else if (doc.isArray()) {
        arr = doc.array();
    } else {
        QMessageBox::warning(this, "Ошибка", "Ожидался JSON объект или массив");
        return;
    }
    myTaskList->loadFromJSArr(arr);
}
