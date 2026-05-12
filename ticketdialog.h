#ifndef TICKETDIALOG_H
#define TICKETDIALOG_H

#include <QDialog>
<<<<<<< HEAD
#include "tickettablemodel.h"
=======
>>>>>>> 98a108b29e2f13524abc3728ae1e33cd1e9c3d76

namespace Ui { class TicketDialog; }

class TicketDialog : public QDialog {
    Q_OBJECT
<<<<<<< HEAD

public:
    enum class Mode { View, Edit, New };

    explicit TicketDialog(Mode mode, const Ticket &ticket = {}, QWidget *parent = nullptr);
    ~TicketDialog();


    Ticket getTicket() const;

=======
public:
    enum class Mode { View, Edit, New };
    explicit TicketDialog(Mode mode, QWidget *parent = nullptr);
    ~TicketDialog();

>>>>>>> 98a108b29e2f13524abc3728ae1e33cd1e9c3d76
private slots:
    void onEditClicked();

private:
    Ui::TicketDialog *ui;
    Mode currentMode;
    void applyMode();
<<<<<<< HEAD
    int m_id;
};

=======
};
>>>>>>> 98a108b29e2f13524abc3728ae1e33cd1e9c3d76
#endif
