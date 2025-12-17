#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chronomaitre.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QStandardItem>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile styleFile(":/style.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = QLatin1String(styleFile.readAll());
        this->setStyleSheet(style);
        styleFile.close();

    }

    model = new QStandardItemModel(0, 2, this);
    model->setHeaderData(0, Qt::Horizontal, "Temps");
    model->setHeaderData(1, Qt::Horizontal, "Écart");

    ui->tableau->setModel(model);
    ui->tableau->horizontalHeader()->setStretchLastSection(true);

    connect(ui->timer, &ChronoMaitre::start, this, &MainWindow::start);
    connect(ui->timer, &ChronoMaitre::stop,  this, &MainWindow::stop);
    connect(ui->timer, &ChronoMaitre::lap,   this, &MainWindow::lap);

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
    model->setRowCount(0);
    ui->exporter->setEnabled(false);
    ui->exporter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
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
    out << "Temps;Ecart\n";

    for (int r = 0; r < model->rowCount(); r++) {
        out << model->item(r,0)->text() << ";"
            << model->item(r,1)->text() << "\n";
    }
}
