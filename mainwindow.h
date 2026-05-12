#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tickettablemodel.h"
#include "csvticketrepository.h"

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
    void onActionDelete();
    void updateActions();

private:
    void loadData();
    void saveData();

    Ui::MainWindow *ui;
    TicketTableModel *model;
    CsvTicketRepository *repository;
    int m_nextId;
};
#endif
