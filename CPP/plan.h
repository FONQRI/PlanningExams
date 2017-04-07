#ifndef PLAN_H
#define PLAN_H

#include <QDebug>
#include <QStandardItem>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>

enum DataRoles
{
    IDRole = Qt::UserRole + 1,
    TextRole = Qt::UserRole + 2,
    Rel1Role = Qt::UserRole + 3,
    Rel2Role = Qt::UserRole + 4
};

class Plan
{
public:
    QString name;
    Plan *rel1 = nullptr;
    Plan *rel2 = nullptr;
    int id;

    int tempRel1;
    int tempRel2;

    Plan() {}
    Plan(const int &id, const QString &name);

    void addToDB(QSqlQuery *Q);
    void updateInDB(QSqlQuery *Q);
    static Plan fromRecord(const QSqlRecord &R);

    QStandardItem *toItem();
};

#endif  // PLAN_H
