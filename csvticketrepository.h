#ifndef CSVTICKETREPOSITORY_H
#define CSVTICKETREPOSITORY_H

#include <QString>
#include <QList>
#include "tickettablemodel.h"

class CsvTicketRepository {
public:
    explicit CsvTicketRepository(const QString &filePath);

    QList<Ticket> loadAll() const;
    bool saveAll(const QList<Ticket> &tickets) const;

    int findNextId(const QList<Ticket> &tickets) const;

private:
    QString m_filePath;

    Ticket parseRow(const QString &line) const;
    QString toCsvRow(const Ticket &t) const;
};

#endif
