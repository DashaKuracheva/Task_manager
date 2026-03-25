#include "taskList.h"

TaskList::TaskList(QWidget *parent) : QWidget(parent) {

    QVBoxLayout *layout = new QVBoxLayout(this);

    list = new QTreeWidget();
    list->setHeaderLabels({"Задача", "Дедлайн", "Статус", ""});
    list->setSelectionMode(QAbstractItemView::SingleSelection);
    list->setExpandsOnDoubleClick(true);
    list->setColumnCount(4);
    list->setRootIsDecorated(true);
    layout->addWidget(list);
}

TaskList::~TaskList(){}

void TaskList::addTask(const Task &task) {
    Task t = task;
    t.id = nextId++;
    allTasks.append(t);
    appendTaskItem(allTasks.size() - 1);
}

void TaskList::appendTaskItem(int index) {

    const Task &t = allTasks.at(index);

    QString statusStr;
    switch (t.status) {
        case TaskStatus::New: statusStr = "New"; break;
        case TaskStatus::InProgress: statusStr = "In Progress"; break;
        case TaskStatus::Done: statusStr = "Done"; break;
    }
//данные одной задачи
    QTreeWidgetItem *parentItem = new QTreeWidgetItem(list, {
        t.title,
        t.deadline.toString("dd.MM.yyyy"),
        statusStr
    });
    parentItem->setData(0, Qt::UserRole, index);
    parentItem->setExpanded(false); // по умолчанию свернут

// выпадающее окно
    QTreeWidgetItem *child = new QTreeWidgetItem(parentItem);
    child->setFirstColumnSpanned(true);

    info = new QLabel(t.description);
    info->setWordWrap(true);
    info->setTextInteractionFlags(Qt::TextSelectableByMouse);
    list->setItemWidget(child, 0, info); //

// кнопки управления
    actionWidget = new QWidget(list);
    QHBoxLayout *h = new QHBoxLayout(actionWidget);
    h->setContentsMargins(0,0,0,0);
    h->setSpacing(6);

    QPushButton *btnEdit = new QPushButton(actionWidget);
    btnEdit->setIcon(QIcon(":/resourses/icons/edit.png"));
    btnEdit->setToolTip("Редактировать");
    btnEdit->setFixedSize(40,40);

    QPushButton *btnDelete = new QPushButton(actionWidget);
    btnDelete->setIcon(QIcon(":/resourses/icons/delete.png"));
    btnDelete->setToolTip("Удалить");
    btnDelete->setFixedSize(40,40);

    h->addWidget(btnEdit);
    h->addWidget(btnDelete);
    h->addStretch();

    list->setItemWidget(parentItem, 3, actionWidget);

    int taskId = t.id;

    btnEdit->setProperty("taskId", taskId); // Сохраняем ID внутри
    connect(btnEdit, SIGNAL(clicked()), this, SLOT(onEditClicked()));

    btnDelete->setProperty("taskId", taskId); // Сохраняем ID внутри
    connect(btnDelete, SIGNAL(clicked()), this, SLOT(onDeleteClicked()));

    list->resizeColumnToContents(0);
    list->resizeColumnToContents(1);
    list->resizeColumnToContents(2);
    list->setColumnWidth(3, 90);
}


void TaskList::onEditClicked() {}

void TaskList::onDeleteClicked() {}


QJsonArray TaskList::JSArr() {
    QJsonArray arr;
    for (int i = 0; i < allTasks.size(); i++) {
        Task &t = allTasks[i];
        arr.append(taskToJS(t));
    }
    return arr;
}


void TaskList::loadFromJSArr(const QJsonArray &arr) {
    allTasks.clear();
    nextId = 0;
    for (int i = 0; i < arr.size(); i++) {
        QJsonValue v = arr.at(i);
        if (!v.isObject()) continue;
        Task t = taskFromJS(v.toObject());
        if (t.id < 0) {
            t.id = nextId++;
        } else {
            nextId = qMax(nextId, t.id + 1);
        }
        allTasks.append(t);
    }
    refreshList();
}

void TaskList::refreshList() {
    list->clear();
    for (int i = 0; i < allTasks.size(); i++)
        appendTaskItem(i);
}

void TaskList::clearTasks() {
    allTasks.clear();
    list->clear();
    info->setText("Выберите задачу из списка");
    refreshList();
}

