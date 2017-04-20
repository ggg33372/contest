/*В конкурсе "Золотой граммофон" участвуют Глюк'оза,
 Масяня и квартет дворовых кошек "Чарующие звуки". Победа в конкурсе
 обеспечит дополнитльные доходы от концертов в размере $S.
 Имеется N добросовестных активных зрителей.
 Каждый из них проголосует за участников конкурса
 с вероятностью pi,j(i = 1,...,N, j=1,2,3). Здесь i-
номер активиста, j-номер конкурсанта. Кроме того, имеется M
недобросовестных активистов, согласных проголосовать за деньги.
Каждый из них за сумму $q(j=1,2,3) проголосует за исполнителя номер j.
Составить модель функционирования системы.*/
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startupWizard()
{
    WizardPages *wizardPages = new WizardPages(this);
    int rc = wizardPages->exec();

    if (rc==WizardPages::Accepted)
    {
        qDebug() << "winProfit=" << wizardPages->winProfit();
        ui->textBrowser->insertPlainText(QString("Win profit: %1\n").arg(wizardPages->winProfit()));

        QList<ActorData> prob = wizardPages->probabilities();
        for (QList<ActorData>::ConstIterator it=prob.constBegin(); it!=prob.constEnd(); ++it)
        {
//            qDebug() << "Probabilities:" << (*it).actor1 << ";" << (*it).actor2 << ";" << (*it).actor3;
            ui->textBrowser->insertPlainText(QString("Probabilities: %1; %2; %3\n").arg((*it).actor1).arg((*it).actor2).arg((*it).actor3));
            QList<double> prob;
            prob << (*it).actor1 << (*it).actor2 << (*it).actor3;
            activeSpectators.append(ActiveSpectator(prob));
        }

        QList<ActorData> pices = wizardPages->prices();
        for (QList<ActorData>::ConstIterator it=pices.constBegin(); it!=pices.constEnd(); ++it)
//            qDebug() << "Prices:" << (*it).actor1 << ";" << (*it).actor2 << ";" << (*it).actor3;
            ui->textBrowser->insertPlainText(QString("Prices: %1; %2; %3\n").arg((*it).actor1).arg((*it).actor2).arg((*it).actor3));

        ActorData earning = wizardPages->earning();
//        qDebug() << "Earning:" << earning.actor1 << ";" << earning.actor2 << ";" << earning.actor3;
        ui->textBrowser->insertPlainText(QString("Earning: %1; %2; %3\n").arg(earning.actor1).arg(earning.actor2).arg(earning.actor3));

        int index = 0;
        for (QList<ActiveSpectator>::ConstIterator it=activeSpectators.constBegin(); it!=activeSpectators.constEnd(); ++it, ++index)
        {
//            qDebug() << "Probabilities:" << (*it).actor1 << ";" << (*it).actor2 << ";" << (*it).actor3;
            int result = (*it).vote();
            ui->textBrowser->insertPlainText(QString("Active spectator #%1 vote for artist %2\n").arg(index).arg(result));
        }

    }
    wizardPages->deleteLater();
}
