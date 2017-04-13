#include "plan.h"

Plan::Plan(const int &id, const QString &name)
{
    this->identifier = id;
    this->name = name;
}

QString Plan::colorsListToString()
{
    QString text;
    for (const int &I : availableColors) text += QString::number(I) + ",";
    return text;
}

void Plan::colorListFromString(const QString &text)
{
    availableColors.clear();
    QStringList list = text.split(",", QString::SkipEmptyParts);
    for (const QString &S : list) availableColors << S.toInt();
}

void Plan::addToDatabase(QSqlQuery *query)
{
    query->prepare("INSERT INTO plans VALUES(?, ?, ?, ?, ?, ?)");

    query->bindValue(0, identifier);
    query->bindValue(1, name);
    query->bindValue(2,
                     firstRelation == nullptr ? -1 : firstRelation->identifier);
    query->bindValue(
        3, secondRelation == nullptr ? -1 : secondRelation->identifier);
    query->bindValue(4, currentColor);
    query->bindValue(5, colorsListToString());

    query->exec();
}

void Plan::updateInDatabse(QSqlQuery *query)
{
    QString ps =
        "UPDATE plans SET rel1=?, rel2=?, name=? WHERE id=?, color=?, "
        "colorlist=?";
    query->prepare(ps);

    query->bindValue(0,
                     firstRelation == nullptr ? -1 : firstRelation->identifier);
    query->bindValue(
        1, secondRelation == nullptr ? -1 : secondRelation->identifier);
    query->bindValue(2, name);
    query->bindValue(3, identifier);
    query->bindValue(4, currentColor);
    query->bindValue(5, colorsListToString());

    query->exec();
}

Plan *Plan::fromRecord(const QSqlRecord &record)
{
    Plan *P = new Plan();

    P->identifier = record.value(0).toInt();
    P->name = record.value(1).toString();
    P->temporaryFirstRelation = record.value(2).toInt();
    P->temprarySecondRelation = record.value(3).toInt();
    P->currentColor = record.value(4).toInt();
    P->colorListFromString(record.value(5).toString());

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
    item->setData(currentColor, ColorRole);

    return item;
}
