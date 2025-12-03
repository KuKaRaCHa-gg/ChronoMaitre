#include "chronomaitre.h"
#include "ui_chronomaitre.h"

ChronoMaitre::ChronoMaitre(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChronoMaitre)
{
    ui->setupUi(this);
}

ChronoMaitre::~ChronoMaitre()
{
    delete ui;
}
