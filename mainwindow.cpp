#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "artist.h"
#include "activespectator.h"
#include "wizardpages.h"

#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    float prob[N][NUM_STARS] = {{0.3, 0.4, 0.3},{0.2, 0.5, 0.3}};

    bool res = ActiveSpectator::setProbability(prob);

    if (!res)
        QMessageBox::warning(this, "Warning", "Set probability failed!", QMessageBox::Ok);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startupWizard()
{
    WizardPages *wizardPages = new WizardPages(this);
    int rc = wizardPages->exec();
    qDebug() << "rc=" << rc;
    wizardPages->deleteLater();
}
