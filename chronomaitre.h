#ifndef CHRONOMAITRE_H
#define CHRONOMAITRE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class ChronoMaitre;
}
QT_END_NAMESPACE

class ChronoMaitre : public QMainWindow
{
    Q_OBJECT

public:
    ChronoMaitre(QWidget *parent = nullptr);
    ~ChronoMaitre();

private:
    Ui::ChronoMaitre *ui;
};
#endif // CHRONOMAITRE_H
