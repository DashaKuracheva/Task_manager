#ifndef DIALOGOPEN_H
#define DIALOGOPEN_H

#include <QtWidgets>

class DialogOpen : public QDialog {
    Q_OBJECT

public:
    DialogOpen(QWidget *parent = nullptr);
    QString getFilePath() const { return filePath; }

signals:
    void fileOpened(const QString &content);

private slots:
    void browseFile();
    void acceptOpening();

private:
    QLineEdit *pathEdit;
    QString filePath;

};

#endif // DIALOGOPEN_H
