#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
<<<<<<< HEAD
#include <QStandardItemModel>
#include <QLabel>
=======
#include "tickettablemodel.h"
>>>>>>> 0bd88b1ea15d28da156bab7c212583a891174f30

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onActionNew();
    void onActionView();
    void onActionEdit();
<<<<<<< HEAD
    void onClearFilters();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QLabel *lblStats;
=======
    void onActionDelete();
    void updateActions();

private:
    Ui::MainWindow *ui;
    TicketTableModel *model;
>>>>>>> 0bd88b1ea15d28da156bab7c212583a891174f30
};
#endif
