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
    int identifier;
    QString name;
    Plan const *firstRelation = nullptr;
    Plan const *secondRelation = nullptr;

    int currentColor;
    QList<int> availableColors;

    int temporaryFirstRelation = -1;
    int temprarySecondRelation = -1;

    Plan() {}
    Plan(const int &identifier, const QString &name);

    void addToDatabase(QSqlQuery *query);
    void updateInDatabse(QSqlQuery *query);
    static Plan fromRecord(const QSqlRecord &record);

    QStandardItem *toItem();
};

#endif  // PLAN_H
