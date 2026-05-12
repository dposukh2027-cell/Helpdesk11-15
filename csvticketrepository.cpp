#include "csvticketrepository.h"
#include <QFile>
#include <QSaveFile>
#include <QTextStream>
#include <QDateTime>

CsvTicketRepository::CsvTicketRepository(const QString &filePath) : m_filePath(filePath) {}

QList<Ticket> CsvTicketRepository::loadAll() const {
    QList<Ticket> tickets;
    QFile file(m_filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return tickets;
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);

    if (!in.atEnd()) in.readLine();

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (!line.isEmpty()) {
            tickets.append(parseRow(line));
        }
    }
    return tickets;
}

bool CsvTicketRepository::saveAll(const QList<Ticket> &tickets) const {
    QSaveFile file(m_filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);


    out << "ID,Title,Priority,Status,CreatedAt,Description\n";

    for (const auto &t : tickets) {
        out << toCsvRow(t) << "\n";
    }

    return file.commit();
}

int CsvTicketRepository::findNextId(const QList<Ticket> &tickets) const {
    int maxId = 0;
    for (const auto &t : tickets) {
        if (t.id > maxId) maxId = t.id;
    }
    return maxId + 1; // [cite: 189, 199]
}

Ticket CsvTicketRepository::parseRow(const QString &line) const {
    QStringList parts = line.split(',');
    Ticket t;
    t.id = parts.value(0).toInt();
    t.title = parts.value(1);
    t.priority = parts.value(2);
    t.status = parts.value(3);
    t.createdAt = parts.value(4);
    t.description = parts.value(5);
    return t;
}

QString CsvTicketRepository::toCsvRow(const Ticket &t) const {
    return QString("%1,%2,%3,%4,%5,%6")
        .arg(t.id).arg(t.title).arg(t.priority)
        .arg(t.status).arg(t.createdAt).arg(t.description);
}
