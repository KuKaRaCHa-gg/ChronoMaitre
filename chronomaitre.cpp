#include "chronomaitre.h"

ChronoMaitre::ChronoMaitre(QWidget *parent) : QLCDNumber(parent)
{
    setDigitCount(12);
    display("00:00:00.000");
    connect(&timer, &QTimer::timeout, this, &ChronoMaitre::tic);
}

void ChronoMaitre::startStop()
{
    if (!running) {
        elapsed.restart();
        timer.start(10);
        running = true;
        emit start();
    } else {
        timer.stop();
        running = false;
        emit stop();
    }
}

void ChronoMaitre::tic()
{
    qint64 ms = elapsed.elapsed();
    QTime t = QTime::fromMSecsSinceStartOfDay(ms);

    currentTime = t.toString("hh:mm:ss.zzz");
    display(currentTime);
}

void ChronoMaitre::lapRequest()
{
    if (!running) return;

    // Temps actuel
    QString time = currentTime;

    // Calcule l’écart
    QTime t1 = QTime::fromString(lastLap, "hh:mm:ss.zzz");
    QTime t2 = QTime::fromString(time, "hh:mm:ss.zzz");

    int diff = t1.msecsTo(t2);

    QTime gap = QTime(0,0).addMSecs(diff);
    QString gapStr = gap.toString("hh:mm:ss.zzz");

    lastLap = time;

    emit lap(time, gapStr);
}
