#include "plan.h"

Plan::Plan(const int &id, const QString &name)
{
    this->identifier = id;
    this->name = name;
}

void Plan::addToDatabase(QSqlQuery *query)
{
    query->prepare("INSERT INTO plans VALUES(?, ?, ?, ?)");

    query->bindValue(0, identifier);
    query->bindValue(1, name);
    query->bindValue(2,
                     firstRelation == nullptr ? -1 : firstRelation->identifier);
    query->bindValue(
        3, secondRelation == nullptr ? -1 : secondRelation->identifier);

    query->exec();
}

void Plan::updateInDatabse(QSqlQuery *query)
{
    QString ps = "UPDATE plans SET rel1=?, rel2=?, name=? WHERE id=?";
    query->prepare(ps);

    query->bindValue(0,
                     firstRelation == nullptr ? -1 : firstRelation->identifier);
    query->bindValue(
        1, secondRelation == nullptr ? -1 : secondRelation->identifier);
    query->bindValue(2, name);
    query->bindValue(3, identifier);

    query->exec();
}

Plan Plan::fromRecord(const QSqlRecord &record)
{
    Plan P;

    P.identifier = record.value(0).toInt();
    P.name = record.value(1).toString();
    P.temporaryFirstRelation = record.value(2).toInt();
    P.temprarySecondRelation = record.value(3).toInt();

    return P;
}

QStandardItem *Plan::toItem()
{
    QStandardItem *item = new QStandardItem;

    item->setData(identifier, IDRole);
    item->setData(name, TextRole);
    item->setData(firstRelation == nullptr ? "" : firstRelation->name,
                  Rel1Role);
    item->setData(secondRelation == nullptr ? "" : secondRelation->name,
                  Rel2Role);

    return item;
}
