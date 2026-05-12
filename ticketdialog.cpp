#include "ticketdialog.h"
#include "ui_ticketdialog.h"
#include <QDateTime>
#include <QRandomGenerator>

TicketDialog::TicketDialog(Mode mode, const Ticket &ticket, QWidget *parent)
    : QDialog(parent), ui(new Ui::TicketDialog), currentMode(mode) {
    ui->setupUi(this);

    if (mode == Mode::New) {
        m_id = QRandomGenerator::global()->bounded(1000, 9999);
        ui->valID->setText("NEW");
    } else {
        m_id = ticket.id;
        ui->valID->setText(QString::number(m_id));
        ui->editTitle->setText(ticket.title);
        ui->comboPriority->setCurrentText(ticket.priority);
        ui->comboStatus->setCurrentText(ticket.status);
        ui->editDescription->setPlainText(ticket.description);
    }

    applyMode();

    // ПР №13: Реакція на зміну тексту для валідації
    connect(ui->editTitle, &QLineEdit::textChanged, this, &TicketDialog::validate);

    connect(ui->btnEdit, &QPushButton::clicked, this, &TicketDialog::onEditClicked);
    connect(ui->btnSave, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->btnCancel, &QPushButton::clicked, this, &QDialog::reject);
    connect(ui->btnClose, &QPushButton::clicked, this, &QDialog::reject);

    validate();
}

void TicketDialog::validate() {
    // Кнопка Save активна тільки якщо Title не порожній
    bool isValid = !ui->editTitle->text().trimmed().isEmpty();
    ui->btnSave->setEnabled(isValid);

    // Візуальна індикація
    if (!isValid && currentMode != Mode::View) {
        ui->editTitle->setStyleSheet("border: 1px solid red;");
    } else {
        ui->editTitle->setStyleSheet("");
    }
}

Ticket TicketDialog::getTicket() const {
    Ticket t;
    t.id = m_id;
    t.title = ui->editTitle->text().trimmed();
    t.priority = ui->comboPriority->currentText();
    t.status = ui->comboStatus->currentText();
    t.description = ui->editDescription->toPlainText().trimmed();
    t.createdAt = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm");
    return t;
}

void TicketDialog::applyMode() {
    bool isReadOnly = (currentMode == Mode::View);
    ui->editTitle->setReadOnly(isReadOnly);
    ui->editDescription->setReadOnly(isReadOnly);
    ui->comboPriority->setEnabled(!isReadOnly);
    ui->comboStatus->setEnabled(!isReadOnly);

    ui->btnEdit->setVisible(isReadOnly);
    ui->btnSave->setVisible(!isReadOnly);
    ui->btnCancel->setVisible(!isReadOnly);
    ui->btnClose->setVisible(isReadOnly);

    setWindowTitle(currentMode == Mode::View ? "Перегляд" :
                       (currentMode == Mode::Edit ? "Редагування" : "Нова заявка"));
    validate();
}

void TicketDialog::onEditClicked() {
    currentMode = Mode::Edit;
    applyMode();
}

TicketDialog::~TicketDialog() { delete ui; }
