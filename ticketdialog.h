#ifndef TICKETDIALOG_H
#define TICKETDIALOG_H

#include <QDialog>
#include "tickettablemodel.h"

namespace Ui { class TicketDialog; }

class TicketDialog : public QDialog {
    Q_OBJECT
public:
    enum class Mode { View, Edit, New };
    explicit TicketDialog(Mode mode, const Ticket &ticket = {}, QWidget *parent = nullptr);
    ~TicketDialog();

    Ticket getTicket() const;

private slots:
    void onEditClicked();
    void validate();

private:
    Ui::TicketDialog *ui;
    Mode currentMode;
    void applyMode();
    int m_id;
};
#endif
