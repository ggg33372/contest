#ifndef WIZARDPAGES_H
#define WIZARDPAGES_H

#include <QWizard>
#include <QWizardPage>
#include <QTreeWidget>

class WizardPages : public QObject
{
    Q_OBJECT
public:
    explicit WizardPages(QWidget *parent = 0);
    ~WizardPages();

    QWizardPage *createStartPage();
    QWizardPage *createActivePage();
    QWizardPage *createCorruptedPage();

    int exec();

private:
    QWizardPage *startupPage;
    QWizardPage *activePage;
    QWizardPage *corruptedPage;
    QWizard     *wizard;
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

    // QWizardPage interface
    void initializePage();
    bool isComplete() const;

protected slots:
    void onItemClicked(QTreeWidgetItem *item, int column);
    void onItemChanged(QTreeWidgetItem *item, int column);

private:
   QTreeWidget *treeWidget;
};

class CorruptedSpectatorPage: public QWizardPage
{
    Q_OBJECT

public:
    CorruptedSpectatorPage(QWidget *parent = NULL);

   // QWizardPage interface
   void initializePage();
   bool isComplete() const;

protected slots:
    void onItemClicked(QTreeWidgetItem *item, int column);
    void onItemChanged(QTreeWidgetItem *item, int column);

private:
   QTreeWidget *treeWidget;
};

#endif // WIZARDPAGES_H
