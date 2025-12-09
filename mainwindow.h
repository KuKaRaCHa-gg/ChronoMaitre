#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void start();
    void stop();
    void lap(QString time, QString gap);
    void save();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
};

#endif // MAINWINDOW_H
