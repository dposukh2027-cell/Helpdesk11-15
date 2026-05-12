#ifndef TICKETDIALOG_H
#define TICKETDIALOG_H

#include <QDialog>
<<<<<<< HEAD
=======
#include "tickettablemodel.h"
>>>>>>> 0bd88b1ea15d28da156bab7c212583a891174f30

namespace Ui { class TicketDialog; }

class TicketDialog : public QDialog {
    Q_OBJECT
public:
    enum class Mode { View, Edit, New };
<<<<<<< HEAD
    explicit TicketDialog(Mode mode, QWidget *parent = nullptr);
    ~TicketDialog();

private slots:
    void onEditClicked();
=======
    explicit TicketDialog(Mode mode, const Ticket &ticket = {}, QWidget *parent = nullptr);
    ~TicketDialog();

    Ticket getTicket() const;

private slots:
    void onEditClicked();
    void validate();
>>>>>>> 0bd88b1ea15d28da156bab7c212583a891174f30

private:
    Ui::TicketDialog *ui;
    Mode currentMode;
    void applyMode();
<<<<<<< HEAD
=======
    int m_id;
>>>>>>> 0bd88b1ea15d28da156bab7c212583a891174f30
};
#endif
