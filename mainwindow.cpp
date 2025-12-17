#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chronomaitre.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QStandardItemModel(0, 2);
    model->setHeaderData(0, Qt::Horizontal, "Temps");
    model->setHeaderData(1, Qt::Horizontal, "Écart");
    ui->tableau->setModel(model);

    // Chrono → IHM
    connect(ui->timer, &ChronoMaitre::start, this, &MainWindow::start);
    connect(ui->timer, &ChronoMaitre::stop, this, &MainWindow::stop);
    connect(ui->timer, &ChronoMaitre::lap,   this, &MainWindow::lap);

    // IHM → Chrono
    connect(ui->demarrer, &QPushButton::clicked, ui->timer, &ChronoMaitre::startStop);
    connect(ui->retenir,  &QPushButton::clicked, ui->timer, &ChronoMaitre::lapRequest);
    connect(ui->exporter, &QPushButton::clicked, this,       &MainWindow::save);

    ui->retenir->setEnabled(false);
    ui->exporter->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start()
{
    ui->demarrer->setText("Arrêter");
    ui->retenir->setEnabled(true);
}

void MainWindow::stop()
{
    ui->demarrer->setText("Démarrer");
    ui->retenir->setEnabled(false);
}

void MainWindow::lap(QString time, QString gap)
{
    QList<QStandardItem *> row;
    row << new QStandardItem(time)
        << new QStandardItem(gap);

    row[0]->setTextAlignment(Qt::AlignCenter);
    row[1]->setTextAlignment(Qt::AlignCenter);

    model->appendRow(row);
    ui->exporter->setEnabled(true);
}

void MainWindow::save()
{
    QString file = QFileDialog::getSaveFileName(this, "Exporter CSV", "", "CSV (*.csv)");
    if (file.isEmpty()) return;

    QFile f(file);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream out(&f);

    for (int r = 0; r < model->rowCount(); r++)
        out << model->item(r,0)->text() << ";"
            << model->item(r,1)->text() << "\n";
}
