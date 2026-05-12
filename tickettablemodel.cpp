#include "tickettablemodel.h"

QVariant TicketTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) return QVariant();

    const Ticket &t = tickets[index.row()];
    switch (index.column()) {
    case IdCol: return t.id;
    case TitleCol: return t.title;
    case PriorityCol: return t.priority;
    case StatusCol: return t.status;
    case CreatedAtCol: return t.createdAt;
    default: return QVariant();
    }
}

QVariant TicketTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case IdCol: return "ID";
        case TitleCol: return "Тема";
        case PriorityCol: return "Пріоритет";
        case StatusCol: return "Статус";
        case CreatedAtCol: return "Створено";
        }
    }
    return QVariant();
}

void TicketTableModel::addTicket(const Ticket &ticket) {
    int row = tickets.size();
    beginInsertRows(QModelIndex(), row, row);
    tickets.append(ticket);
    endInsertRows();
}

void TicketTableModel::updateTicket(int row, const Ticket &ticket) {
    if (row < 0 || row >= tickets.size()) return;
    tickets[row] = ticket;
    emit dataChanged(index(row, 0), index(row, ColCount - 1));
}

void TicketTableModel::removeTicket(int row) {
    if (row < 0 || row >= tickets.size()) return;
    beginRemoveRows(QModelIndex(), row, row);
    tickets.removeAt(row);
    endRemoveRows();
}
