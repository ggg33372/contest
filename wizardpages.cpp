#include <QDebug>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QVBoxLayout>
#include "wizardpages.h"

WizardPages::WizardPages(QWidget *parent): QWizard(parent)
{
    setWindowTitle("Enter startup conditions");

    setPage(IdStartupPage, new StartupPage());
    setPage(IdActiveSpectatorPage, new ActiveSpectatorPage());
    setPage(IdCorruptedSpectatorPage, new CorruptedSpectatorPage());
    setPage(IdActorsPage, new ActorsPage());
}

double WizardPages::winProfit() const
{
    return field("winProfit").toDouble();
}

QList<ActorData> WizardPages::probabilities() const
{
    ActiveSpectatorPage *asp = qobject_cast<ActiveSpectatorPage *>(page(IdActiveSpectatorPage));
    if (asp)
        return asp->probabilities();
    return QList<ActorData>();
}

QList<ActorData> WizardPages::prices() const
{
    CorruptedSpectatorPage *csp = qobject_cast<CorruptedSpectatorPage *>(page(IdCorruptedSpectatorPage));
    if (csp)
        return csp->prices();
    return QList<ActorData>();
}

ActorData WizardPages::earning() const
{
    ActorsPage *acp = qobject_cast<ActorsPage *>(page(IdActorsPage));
    if (acp)
        return acp->earning();
    return ActorData();
}

StartupPage::StartupPage(QWidget *parent):
    QWizardPage(parent)
{
    setTitle("Startup");

    QFormLayout *layout = new QFormLayout;

    QLabel *label = new QLabel("Number of active spectators");
    label->setWordWrap(true);
    QSpinBox *spbValue = new QSpinBox();
    spbValue->setMinimum(1);
    spbValue->setMaximum(1000);
    registerField("activeSpectators", spbValue);
    layout->addRow(label, spbValue);

    label = new QLabel("Number of corrupted spectators");
    label->setWordWrap(true);
    spbValue = new QSpinBox();
    spbValue->setMinimum(1);
    spbValue->setMaximum(1000);
    registerField("corruptedSpectators", spbValue);
    layout->addRow(label, spbValue);

    label = new QLabel("Win profit");
    label->setWordWrap(true);
    QDoubleSpinBox *dspbValue = new QDoubleSpinBox();
    dspbValue->setMinimum(1);
    dspbValue->setMaximum(1000);
    dspbValue->setPrefix("$");
    registerField("winProfit", dspbValue, "value", SIGNAL(valueChanged(double)));
    layout->addRow(label, dspbValue);

    setLayout(layout);
}

ActiveSpectatorPage::ActiveSpectatorPage(QWidget *parent):
    QWizardPage(parent), treeWidget(new QTreeWidget()), iconTrue(":/icons/true.png"), iconFalse(":/icons/false.png")
{
    setTitle("Active spectators");

    treeWidget->setColumnCount(4);
    QStringList labels;
    labels << "Order" << "Masyanya" << "GlukOza" << "Quartet dvorovykh koshek" << "Ok";
    treeWidget->setHeaderLabels(labels);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(treeWidget);
    setLayout(layout);

    connect(treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), SLOT(onItemClicked(QTreeWidgetItem*,int)));
    connect(treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*,int)), SLOT(onItemChanged(QTreeWidgetItem*,int)));
}

QList<ActorData> ActiveSpectatorPage::probabilities() const
{
    QList<ActorData> list;
    int count = treeWidget->topLevelItemCount();
    for (int i=0; i<count; ++i)
    {
        QTreeWidgetItem *item = treeWidget->topLevelItem(i);
        ActorData prob;
        prob.actor1 = item->text(1).toDouble();
        prob.actor2 = item->text(2).toDouble();
        prob.actor3 = item->text(3).toDouble();
        list.append(prob);
    }
    return list;
}

void ActiveSpectatorPage::initializePage()
{
    int active = field("activeSpectators").toInt();
    double winProfit = field("winProfit").toDouble();

    qDebug() << "active=" << active << "; winProfit=" << winProfit;

    QStringList columns;
    columns << QString() << QString("0") << QString("0") << QString("0") << QString();
    for (int i=0; i<active; ++i)
    {
        columns[0]=QString::number(i+1);
        QTreeWidgetItem *item = new QTreeWidgetItem(columns);
        item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        treeWidget->addTopLevelItem(item);
    }
}

bool ActiveSpectatorPage::isComplete() const
{
    bool ok(true);
    int itemCount = treeWidget->topLevelItemCount();
    for (int row = 0; row < itemCount; ++row)
    {
        QTreeWidgetItem *item = treeWidget->topLevelItem(row);
        double sum = 0;
        for (int column=1; column < treeWidget->columnCount(); ++column)
            sum+=item->text(column).toDouble();

        if (1 - sum)
        {
            item->setIcon(4, iconFalse);
            ok = false;
        }
        else
            item->setIcon(4, iconTrue);
    }
    return ok;
}

void ActiveSpectatorPage::onItemClicked(QTreeWidgetItem *item, int column)
{
    if (column>0)
        treeWidget->editItem(item, column);
}

void ActiveSpectatorPage::onItemChanged(QTreeWidgetItem *item, int column)
{
    if (column>3)
        return;
    double value = item->text(column).toDouble();
    if (value>1)
        value = 1;
    else if (value<0)
        value = 0;
    treeWidget->blockSignals(true);
    item->setText(column, QString::number(value));
    treeWidget->blockSignals(false);
    completeChanged();
}
// =========================================================================
CorruptedSpectatorPage::CorruptedSpectatorPage(QWidget *parent):
    QWizardPage(parent), treeWidget(new QTreeWidget()), iconTrue(":/icons/true.png"), iconFalse(":/icons/false.png")
{
    setTitle("Corrupted spectators");

    treeWidget->setColumnCount(5);
    QStringList labels;
    labels << "Order" << "Masyanya" << "GlukOza" << "Quartet dvorovykh koshek";
    treeWidget->setHeaderLabels(labels);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(treeWidget);
    setLayout(layout);

    connect(treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), SLOT(onItemClicked(QTreeWidgetItem*,int)));
    connect(treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*,int)), SLOT(onItemChanged(QTreeWidgetItem*,int)));
}

QList<ActorData> CorruptedSpectatorPage::prices() const
{
    QList<ActorData> list;
    int count = treeWidget->topLevelItemCount();
    for (int i=0; i<count; ++i)
    {
        QTreeWidgetItem *item = treeWidget->topLevelItem(i);
        ActorData prob;
        prob.actor1 = item->text(1).mid(1).toDouble();
        prob.actor2 = item->text(2).mid(1).toDouble();
        prob.actor3 = item->text(3).mid(1).toDouble();
        list.append(prob);
    }
    return list;
}

void CorruptedSpectatorPage::initializePage()
{
    int active = field("corruptedSpectators").toInt();

    QStringList columns;
    columns << QString() << QString("$1") << QString("$1") << QString("$1");
    for (int i=0; i<active; ++i)
    {
        columns[0]=QString::number(i+1);
        QTreeWidgetItem *item = new QTreeWidgetItem(columns);
        item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        treeWidget->addTopLevelItem(item);
    }
}

void CorruptedSpectatorPage::onItemClicked(QTreeWidgetItem *item, int column)
{
    if (column>0)
    {
//        QString txt = item->text(column);
//        qDebug() << "txt=" << txt;
//        treeWidget->blockSignals(true);
//        item->setText(column, txt.mid(1));
//        treeWidget->blockSignals(false);
//        qDebug() << "item text:" << item->text(column);
        treeWidget->editItem(item, column);
//        treeWidget->blockSignals(true);
//        item->setText(column, txt);
//        treeWidget->blockSignals(false);
    }
}

void CorruptedSpectatorPage::onItemChanged(QTreeWidgetItem *item, int column)
{
    QString txt = item->text(column);
    double value = (txt.startsWith("$")?txt.mid(1):txt).toDouble();

    if (value>1000000)
        value = 1000000;
    else if (value < 1)
        value = 1;

    treeWidget->blockSignals(true);
    item->setText(column, QString("$%1").arg(value));
    treeWidget->blockSignals(false);
    completeChanged();
}

// =========================================================================
ActorsPage::ActorsPage(QWidget *parent):QWizardPage(parent)
{
    setTitle("Actors");

    QFormLayout *layout = new QFormLayout;

    QLabel *label = new QLabel("Masyanya");
    label->setWordWrap(true);
    QDoubleSpinBox *dspbValue = new QDoubleSpinBox();
    dspbValue->setMinimum(1000);
    dspbValue->setMaximum(100000);
    dspbValue->setPrefix("$");
    registerField("money1", dspbValue, "value", SIGNAL(valueChanged(double)));
    layout->addRow(label, dspbValue);

    label = new QLabel("GlukOza");
    label->setWordWrap(true);
    dspbValue = new QDoubleSpinBox();
    dspbValue->setMinimum(1000);
    dspbValue->setMaximum(100000);
    dspbValue->setPrefix("$");
    registerField("money2", dspbValue, "value", SIGNAL(valueChanged(double)));
    layout->addRow(label, dspbValue);

    label = new QLabel("Quartet dvorovykh koshek");
    label->setWordWrap(true);
    dspbValue = new QDoubleSpinBox();
    dspbValue->setMinimum(1000);
    dspbValue->setMaximum(100000);
    dspbValue->setPrefix("$");
    registerField("money3", dspbValue, "value", SIGNAL(valueChanged(double)));
    layout->addRow(label, dspbValue);

    setLayout(layout);
}

ActorData ActorsPage::earning() const
{
    ActorData earn;
    earn.actor1 = field("money1").toDouble();
    earn.actor2 = field("money2").toDouble();
    earn.actor3 = field("money3").toDouble();
    return earn;
}
