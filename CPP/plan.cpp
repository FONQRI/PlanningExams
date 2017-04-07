#include "plan.h"

Plan::Plan(const int &id, const QString &name)
{
    this->id = id;
    this->name = name;
}

void Plan::addToDB(QSqlQuery *Q)
{
    Q->prepare("INSERT INTO plans VALUES(?, ?, ?, ?)");

    Q->bindValue(0, id);
    Q->bindValue(1, name);
    Q->bindValue(2, rel1 == nullptr ? -1 : rel1->id);
    Q->bindValue(3, rel2 == nullptr ? -1 : rel2->id);

    Q->exec();
}

void Plan::updateInDB(QSqlQuery *Q)
{
    QString ps = "UPDATE plans SET rel1=?, rel2=?, name=? WHERE id=?";
    Q->prepare(ps);

    Q->bindValue(0, rel1 == nullptr ? -1 : rel1->id);
    Q->bindValue(1, rel2 == nullptr ? -1 : rel2->id);
    Q->bindValue(2, name);
    Q->bindValue(3, id);

    Q->exec();
}

Plan Plan::fromRecord(const QSqlRecord &R)
{
    Plan P;

    P.id = R.value(0).toInt();
    P.name = R.value(1).toString();
    P.tempRel1 = R.value(2).toInt();
    P.tempRel2 = R.value(3).toInt();

    return P;
}

QStandardItem *Plan::toItem()
{
    QStandardItem *item = new QStandardItem;

    item->setData(id, IDRole);
    item->setData(name, TextRole);
    item->setData(rel1 == nullptr ? "" : rel1->name, Rel1Role);
    item->setData(rel2 == nullptr ? "" : rel2->name, Rel2Role);

    return item;
}
