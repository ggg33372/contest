#include <QDebug>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QVBoxLayout>
#include "wizardpages.h"

WizardPages::WizardPages(QWidget *parent):
    QObject(parent), startupPage(NULL), activePage(NULL), wizard(NULL)
{
    wizard = new QWizard(parent);
    wizard->setWindowTitle("Enter startup conditions");

    startupPage = createStartPage();
    wizard->addPage(startupPage);
    activePage = createActivePage();
    wizard->addPage(activePage);
    corruptedPage = createCorruptedPage();
    wizard->addPage(corruptedPage);
}

WizardPages::~WizardPages()
{
    delete wizard;
}

QWizardPage *WizardPages::createStartPage()
{
    return new StartupPage();
}

QWizardPage *WizardPages::createActivePage()
{
    return new ActiveSpectatorPage;
}

QWizardPage *WizardPages::createCorruptedPage()
{
    return new CorruptedSpectatorPage;
}

int WizardPages::exec()
{
    return wizard->exec();
}

StartupPage::StartupPage(QWidget *parent):
    QWizardPage(parent)
{
    setTitle("Startup");

    QLabel *lblActive = new QLabel("Number of active spectators");
    lblActive->setWordWrap(true);

    QSpinBox *spbActive = new QSpinBox();
    spbActive->setMinimum(1);
    spbActive->setMaximum(1000);

    registerField("activeSpectators", spbActive);

    QFormLayout *layout = new QFormLayout;
    layout->addRow(lblActive, spbActive);

    QLabel *lblCorrupted = new QLabel("Number of corrupted spectators");
    lblCorrupted->setWordWrap(true);

    QSpinBox *spbCorrupted = new QSpinBox();
    spbCorrupted->setMinimum(1);
    spbCorrupted->setMaximum(1000);
    registerField("corruptedSpectators", spbCorrupted);

    layout->addRow(lblCorrupted, spbCorrupted);
    setLayout(layout);
}

ActiveSpectatorPage::ActiveSpectatorPage(QWidget *parent):
    QWizardPage(parent), treeWidget(new QTreeWidget())
{
    setTitle("Active spectators");

    treeWidget->setColumnCount(4);
    QStringList labels;
    labels << "Order" << "Masyanya" << "GlukOza" << "Quartet dvorovykh koshek";
    treeWidget->setHeaderLabels(labels);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(treeWidget);
    setLayout(layout);

    connect(treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), SLOT(onItemClicked(QTreeWidgetItem*,int)));
    connect(treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*,int)), SLOT(onItemChanged(QTreeWidgetItem*,int)));
}

void ActiveSpectatorPage::initializePage()
{
    int active = field("activeSpectators").toInt();

    QStringList columns;
    columns << QString() << QString("0") << QString("0") << QString("0");
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
    int itemCount = treeWidget->topLevelItemCount();
    for (int row = 0; row < itemCount; ++row)
    {
        QTreeWidgetItem *item = treeWidget->topLevelItem(row);
        double sum = 0;
        for (int column=1; column < treeWidget->columnCount(); ++column)
            sum+=item->text(column).toDouble();
        if (1 - sum)
            return false;
    }
    return true;
}

void ActiveSpectatorPage::onItemClicked(QTreeWidgetItem *item, int column)
{
    if (column>0)
        treeWidget->editItem(item, column);
}

void ActiveSpectatorPage::onItemChanged(QTreeWidgetItem *item, int column)
{
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
    QWizardPage(parent), treeWidget(new QTreeWidget())
{
    setTitle("Corrupted spectators");

    treeWidget->setColumnCount(5);
    QStringList labels;
    labels << "Order" << "Price" << "Masyanya" << "GlukOza" << "Quartet dvorovykh koshek";
    treeWidget->setHeaderLabels(labels);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(treeWidget);
    setLayout(layout);

    connect(treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), SLOT(onItemClicked(QTreeWidgetItem*,int)));
    connect(treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*,int)), SLOT(onItemChanged(QTreeWidgetItem*,int)));
}

void CorruptedSpectatorPage::initializePage()
{
    int active = field("corruptedSpectators").toInt();

    QStringList columns;
    columns << QString() << QString("0") << QString("0") << QString("0") << QString("0");
    for (int i=0; i<active; ++i)
    {
        columns[0]=QString::number(i+1);
        QTreeWidgetItem *item = new QTreeWidgetItem(columns);
        item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        treeWidget->addTopLevelItem(item);
    }
}

bool CorruptedSpectatorPage::isComplete() const
{
    int itemCount = treeWidget->topLevelItemCount();
    for (int row = 0; row < itemCount; ++row)
    {
        QTreeWidgetItem *item = treeWidget->topLevelItem(row);
        double sum = 0;
        for (int column=2; column < treeWidget->columnCount(); ++column)
            sum+=item->text(column).toDouble();
        if (1 - sum)
            return false;
    }
    return true;
}

void CorruptedSpectatorPage::onItemClicked(QTreeWidgetItem *item, int column)
{
    if (column>0)
        treeWidget->editItem(item, column);
}

void CorruptedSpectatorPage::onItemChanged(QTreeWidgetItem *item, int column)
{
    double value = item->text(column).toDouble();
    if (column==1)
    {
        if (value>1000000)
            value = 1000000;
        else if (value < 1)
            value = 1;
    }
    else
    {
        if (value>1)
            value = 1;
        else if (value<0)
            value = 0;
    }
    treeWidget->blockSignals(true);
    item->setText(column, QString::number(value));
    treeWidget->blockSignals(false);
    completeChanged();
}
