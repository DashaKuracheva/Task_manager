#include "mainwindow.h"
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

    /* ЗАМЕНЯЕМ НА QTreeWidget
    taskList = new QListWidget();
    taskList->setEnabled(false);//заблокирован до открытия файла*/


    //myTaskView = new TaskTreeWidget(this);


    //формирование вертикального слоя
    mainLayout->addLayout(rowLayout);
    mainLayout->setAlignment(rowLayout, Qt::AlignTop);
    //mainLayout->addWidget(myTaskView);

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

    toolBar->addAction(QIcon(":/resourses/icons/calendar1.png"), "Календарь", this, &MainWindow::displayCalendar); //toolBar->addAction(QIcon(":/resourses/calendar.png"), "Календарь", this, SLOT(displayCalendar()));
    toolBar->addSeparator();
    toolBar->addAction(QIcon(":/resourses/icons/tasks1.png"), "Список задач", this, &MainWindow::showTasks);//отобразить скрыть список задач
    toolBar->addSeparator();
    toolBar->addAction(QIcon(":/resourses/icons/deadline.png"), "Дедлайн", this, &MainWindow::sortDeadline);//блжайшие дедлайны
    toolBar->addSeparator();
    toolBar->addAction(QIcon(":/resourses/icons/filter.png"), "Фильтр", this, &MainWindow::filterOut);//фильтрация задач по статусу

    /*dialogOpen = nullptr;
    dialogSave = nullptr;
    dialogCreate = nullptr;
    dialogEdit = nullptr;*/

}


MainWindow::~MainWindow()
{
}

void MainWindow::addTask() {
    // код
}

void MainWindow::search() {
    // код
}

void MainWindow::openFile() {
    // код
}

void MainWindow::addNewFile() {
    // код
}

void MainWindow::saveMyFile() {
    // код
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


