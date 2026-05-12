#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
<<<<<<< HEAD
#include <QLabel>
#include "tickettablemodel.h"
=======
#include <QStandardItemModel>
#include <QLabel>
>>>>>>> 98a108b29e2f13524abc3728ae1e33cd1e9c3d76

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
    void onActionDelete();
    void updateActions();
=======
>>>>>>> 98a108b29e2f13524abc3728ae1e33cd1e9c3d76
    void onClearFilters();

private:
    Ui::MainWindow *ui;
<<<<<<< HEAD
    TicketTableModel *model;
=======
    QStandardItemModel *model;
>>>>>>> 98a108b29e2f13524abc3728ae1e33cd1e9c3d76
    QLabel *lblStats;
};
#endif
