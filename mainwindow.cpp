#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ticketdialog.h"
#include <QMessageBox>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    model = new TicketTableModel(this);
    repository = new CsvTicketRepository("tickets.csv");

    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->horizontalHeader()->setSectionResizeMode(TicketTableModel::TitleCol, QHeaderView::Stretch);

    connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::updateActions);
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::onActionNew);
    connect(ui->actionView, &QAction::triggered, this, &MainWindow::onActionView);
    connect(ui->actionEdit, &QAction::triggered, this, &MainWindow::onActionEdit);
    connect(ui->actionDelete, &QAction::triggered, this, &MainWindow::onActionDelete);

    loadData();
    updateActions();
}

void MainWindow::loadData() {
    QList<Ticket> tickets = repository->loadAll();
    model->setItems(QVector<Ticket>::fromList(tickets));
    m_nextId = repository->findNextId(tickets);
}

void MainWindow::saveData() {
    repository->saveAll(model->items().toList());
}

void MainWindow::updateActions() {
    bool hasSelection = ui->tableView->selectionModel()->hasSelection();
    ui->actionView->setEnabled(hasSelection);
    ui->actionEdit->setEnabled(hasSelection);
    ui->actionDelete->setEnabled(hasSelection);
}

void MainWindow::onActionNew() {
    TicketDialog dlg(TicketDialog::Mode::New, {}, this);
    if (dlg.exec() == QDialog::Accepted) {
        Ticket t = dlg.getTicket();
        t.id = m_nextId++;
        model->addTicket(t);
        saveData();
    }
}

void MainWindow::onActionEdit() {
    QModelIndex current = ui->tableView->currentIndex();
    if (!current.isValid()) return;

    TicketDialog dlg(TicketDialog::Mode::Edit, model->getTicket(current.row()), this);
    if (dlg.exec() == QDialog::Accepted) {
        model->updateTicket(current.row(), dlg.getTicket());
        saveData();
    }
}

void MainWindow::onActionView() {
    QModelIndex current = ui->tableView->currentIndex();
    if (!current.isValid()) return;

    TicketDialog dlg(TicketDialog::Mode::View, model->getTicket(current.row()), this);
    dlg.exec();
}

void MainWindow::onActionDelete() {
    QModelIndex current = ui->tableView->currentIndex();
    if (!current.isValid()) return;

    auto res = QMessageBox::question(this, "Видалення", "Ви впевнені, що хочете видалити заявку?");
    if (res == QMessageBox::Yes) {
        model->removeTicket(current.row());
        saveData();
    }
}

MainWindow::~MainWindow() { delete ui; }
