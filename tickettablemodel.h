#ifndef TICKETTABLEMODEL_H
#define TICKETTABLEMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include <QDateTime>

struct Ticket {
    int id;
    QString title;
    QString priority;
    QString status;
    QString createdAt;
    QString description;
};

class TicketTableModel : public QAbstractTableModel {
    Q_OBJECT
public:
    enum Column { IdCol, TitleCol, PriorityCol, StatusCol, CreatedAtCol, ColCount };

    explicit TicketTableModel(QObject *parent = nullptr) : QAbstractTableModel(parent) {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return parent.isValid() ? 0 : tickets.size();
    }
    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return parent.isValid() ? 0 : ColCount;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void addTicket(const Ticket &ticket);
    void updateTicket(int row, const Ticket &ticket);
    void removeTicket(int row);
    Ticket getTicket(int row) const { return tickets.value(row); }

private:
    QVector<Ticket> tickets;
};

#endif
