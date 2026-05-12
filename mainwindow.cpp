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

    // Налаштування проксі-моделі для пошуку та сортування
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    proxyModel->setFilterKeyColumn(TicketTableModel::TitleCol); // Пошук за темою
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    ui->tableView->setModel(proxyModel);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(TicketTableModel::TitleCol, QHeaderView::Stretch);

    // З'єднання зі слотами (Використовуємо назви з вашого XML: editSearch, btnClear)
    connect(ui->editSearch, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);
    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::onBtnClearClicked);
    connect(ui->tableView, &QAbstractItemView::doubleClicked, this, &MainWindow::onTableDoubleClicked);

    connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::updateActions);
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::onActionNew);
    connect(ui->actionView, &QAction::triggered, this, &MainWindow::onActionView);
    connect(ui->actionEdit, &QAction::triggered, this, &MainWindow::onActionEdit);
    connect(ui->actionDelete, &QAction::triggered, this, &MainWindow::onActionDelete);

    loadData();
    updateActions();
}

// Реалізація пошуку
void MainWindow::onSearchTextChanged(const QString &text) {
    proxyModel->setFilterFixedString(text);
}

// Реалізація кнопки очищення
void MainWindow::onBtnClearClicked() {
    ui->editSearch->clear();
}

void MainWindow::onTableDoubleClicked(const QModelIndex &index) {
    onActionView();
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
    QModelIndex proxyIndex = ui->tableView->currentIndex();
    if (!proxyIndex.isValid()) return;

    QModelIndex sourceIndex = proxyModel->mapToSource(proxyIndex);
    TicketDialog dlg(TicketDialog::Mode::Edit, model->getTicket(sourceIndex.row()), this);
    if (dlg.exec() == QDialog::Accepted) {
        model->updateTicket(sourceIndex.row(), dlg.getTicket());
        saveData();
    }
}

void MainWindow::onActionView() {
    QModelIndex proxyIndex = ui->tableView->currentIndex();
    if (!proxyIndex.isValid()) return;
    QModelIndex sourceIndex = proxyModel->mapToSource(proxyIndex);
    TicketDialog dlg(TicketDialog::Mode::View, model->getTicket(sourceIndex.row()), this);
    dlg.exec();
}

void MainWindow::onActionDelete() {
    QModelIndex proxyIndex = ui->tableView->currentIndex();
    if (!proxyIndex.isValid()) return;

    if (QMessageBox::question(this, "Видалення", "Ви впевнені, що хочете видалити заявку?") == QMessageBox::Yes) {
        QModelIndex sourceIndex = proxyModel->mapToSource(proxyIndex);
        model->removeTicket(sourceIndex.row());
        saveData();
    }
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

MainWindow::~MainWindow() { delete ui; }
