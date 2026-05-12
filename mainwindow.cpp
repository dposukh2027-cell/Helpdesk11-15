#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ticketdialog.h"
<<<<<<< HEAD
#include <QHeaderView>
=======
>>>>>>> 98a108b29e2f13524abc3728ae1e33cd1e9c3d76

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

<<<<<<< HEAD
    model = new TicketTableModel(this);
    ui->tableView->setModel(model);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->horizontalHeader()->setSectionResizeMode(TicketTableModel::TitleCol, QHeaderView::Stretch);

    connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::updateActions);

    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::onActionNew);
    connect(ui->actionView, &QAction::triggered, this, &MainWindow::onActionView);
    connect(ui->actionEdit, &QAction::triggered, this, &MainWindow::onActionEdit);
    connect(ui->actionDelete, &QAction::triggered, this, &MainWindow::onActionDelete);
    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::onClearFilters);

    updateActions();
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
        model->addTicket(dlg.getTicket());
    }
}

void MainWindow::onActionEdit() {
    QModelIndex current = ui->tableView->currentIndex();
    if (!current.isValid()) return;

    TicketDialog dlg(TicketDialog::Mode::Edit, model->getTicket(current.row()), this);
    if (dlg.exec() == QDialog::Accepted) {
        model->updateTicket(current.row(), dlg.getTicket());
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
    if (current.isValid()) model->removeTicket(current.row());
}

void MainWindow::onClearFilters() {
=======
    // Ініціалізація моделі та таблиці [cite: 34, 105]
    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"ID", "Title", "Priority", "Status", "Created At"});
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true); // Адаптивність [cite: 128]

    // Налаштування StatusBar [cite: 18, 147]
    ui->statusbar->showMessage("Ready");
    lblStats = new QLabel("Total: 0  Filtered: 0", this);
    ui->statusbar->addPermanentWidget(lblStats);

    // Коннекти для команд [cite: 24, 95]
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::onActionNew);
    connect(ui->actionView, &QAction::triggered, this, &MainWindow::onActionView);
    connect(ui->actionEdit, &QAction::triggered, this, &MainWindow::onActionEdit);
    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::onClearFilters);
}

void MainWindow::onActionNew() {
    // Відкриття немодального діалогу в режимі New [cite: 112, 123]
    TicketDialog *dlg = new TicketDialog(TicketDialog::Mode::New, this);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show();
}

void MainWindow::onActionView() {
    TicketDialog *dlg = new TicketDialog(TicketDialog::Mode::View, this);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show(); // [cite: 124]
}

void MainWindow::onActionEdit() {
    TicketDialog *dlg = new TicketDialog(TicketDialog::Mode::Edit, this);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show(); // [cite: 125]
}

void MainWindow::onClearFilters() {
    ui->comboFilterStatus->setCurrentIndex(0);
    ui->comboFilterPriority->setCurrentIndex(0);
>>>>>>> 98a108b29e2f13524abc3728ae1e33cd1e9c3d76
    ui->editSearch->clear();
}

MainWindow::~MainWindow() { delete ui; }
