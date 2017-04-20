#ifndef WIZARDPAGES_H
#define WIZARDPAGES_H

#include <QWizard>
#include <QWizardPage>
#include <QTreeWidget>
#include <QList>

struct ActorData
{
    double actor1;
    double actor2;
    double actor3;
};

class WizardPages : public QWizard
{
    Q_OBJECT

    enum Pages
    {
        IdStartupPage = 1000,
        IdActiveSpectatorPage,
        IdCorruptedSpectatorPage,
        IdActorsPage
    };

public:
    explicit WizardPages(QWidget *parent = 0);

    double winProfit() const;
    QList<ActorData> probabilities() const;
    QList<ActorData> prices() const;
    ActorData        earning() const;
};

class StartupPage: public QWizardPage
{
    Q_OBJECT

public:
    StartupPage(QWidget *parent = NULL);
};

class ActiveSpectatorPage: public QWizardPage
{
    Q_OBJECT

public:
    ActiveSpectatorPage(QWidget *parent = NULL);
    QList<ActorData> probabilities() const;

    // QWizardPage interface
    void initializePage();
    bool isComplete() const;

protected slots:
    void onItemClicked(QTreeWidgetItem *item, int column);
    void onItemChanged(QTreeWidgetItem *item, int column);

private:
   QTreeWidget *treeWidget;
   QIcon iconTrue;
   QIcon iconFalse;
};

class CorruptedSpectatorPage: public QWizardPage
{
    Q_OBJECT

public:
    CorruptedSpectatorPage(QWidget *parent = NULL);
    QList<ActorData> prices() const;

   // QWizardPage interface
   void initializePage();

protected slots:
    void onItemClicked(QTreeWidgetItem *item, int column);
    void onItemChanged(QTreeWidgetItem *item, int column);

private:
   QTreeWidget *treeWidget;
   QIcon iconTrue;
   QIcon iconFalse;
};

class ActorsPage: public QWizardPage
{
    Q_OBJECT

public:
    ActorsPage(QWidget *parent = NULL);
    ActorData        earning() const;
};

#endif // WIZARDPAGES_H
