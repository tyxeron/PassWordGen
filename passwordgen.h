#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class PassWordGen;
}

class PassWordGen : public QMainWindow
{
    Q_OBJECT

public:
    explicit PassWordGen(QWidget *parent = nullptr);
    ~PassWordGen();

public slots:
    void generate();
    void copyclip();

signals:
    void passwordGenerated(QString newValue);

private:
    Ui::PassWordGen *ui;
};

#endif // MAINWINDOW_H
