#ifndef CHRONOMAITRE_H
#define CHRONOMAITRE_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QElapsedTimer>
#include <QLCDNumber>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class ChronoMaitre : public QLCDNumber
{
    Q_OBJECT

public:
    explicit ChronoMaitre(QWidget *parent = nullptr);

signals:
    void start();
    void stop();
    void lap(QString time, QString gap);

public slots:
    void startStop();
    void lapRequest();
    void tic();

private:
    QTimer timer;
    QElapsedTimer elapsed;
    QString currentTime;
    QString lastLap = "00:00:00.000";
    bool running = false;
};
#endif // CHRONOMAITRE_H
