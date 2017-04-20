#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "activespectator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void startupWizard();

private:
    Ui::MainWindow *ui;
    QList<ActiveSpectator> activeSpectators;

};

#endif // MAINWINDOW_H
