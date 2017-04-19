#include "planmanager.h"

PlanManager::PlanManager(QObject *parent) : QObject(parent)
{
    createDatabse();
    model = new ViewModel(this);
    model->setSortRole(TextRole);
    databseToModel();
}

PlanManager::~PlanManager()
{
    for (Plan *P : plansList)
    {
        delete P;
        P = nullptr;
    }
}

QStandardItemModel *PlanManager::getModel() const { return model; }
QList<Plan *> *PlanManager::getPlansList() { return &plansList; }
QSqlQuery *PlanManager::getQuery() const { return query; }
void PlanManager::createDatabse()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("DB.SQLITE");
    if (!database.open()) qDebug() << "Couldn't open database!";

    query = new QSqlQuery(database);

    query->exec(
        "CREATE TABLE IF NOT EXISTS plans(id INTEGER, name STRING, rel1 "
        "INTEGER, rel2 INTEGER, color INTEGER, colorlist STRING)");

    query->exec("SELECT DISTINCT id FROM plans ORDER  BY id ASC");
    lastIDInDatabase = query->last() ? query->value(0).toInt() : -1;
}

void PlanManager::databseToModel()
{
    plansList.clear();
    model->clear();

    query->exec("SELECT * FROM plans");
    while (query->next()) plansList << Plan::fromRecord(query->record());

    connectPlans();
    for (Plan *P : plansList) model->appendRow(P->toItem());

    model->sort(0);
}

int PlanManager::idFromIndex(const int &role)
{
    if (role < 0)
        return role;
    else
        return model->item(role)->data(IDRole).toInt();
}

void PlanManager::clear()
{
    for (Plan *P : plansList)
    {
        delete P;
        P = nullptr;
    }

    plansList.clear();
    query->exec("DELETE FROM plans");
    model->clear();
    lastIDInDatabase = 0;
}

QVariantList PlanManager::getAvailableColors(const int &id)
{
    QVariantList list;
    QList<int> ac = findPlan(id)->availableColors;

    for (int &I : ac) list << I;
    return list;
}

void PlanManager::connectPlans()
{
    for (Plan *P : plansList)
        for (Plan *PP : plansList)
        {
            if (PP->temporaryFirstRelation == P->identifier)
                PP->firstRelation = P;
            if (PP->temprarySecondRelation == P->identifier)
                PP->secondRelation = P;
        }
}

Plan *PlanManager::findPlan(const int &id)
{
    for (Plan *P : plansList)
        if (P->identifier == id) return P;

    return nullptr;
}

int PlanManager::searchPlansIndex(const int &id)
{
    int count = 0;

    for (Plan *P : plansList)
    {
        if (P->identifier == id) return count;
        ++count;
    }

    return -1;
}

int PlanManager::searchModel(const QString &name)
{
    if (name.isEmpty()) return -1;

    QModelIndexList found =
        model->match(model->index(0, 0), TextRole, name, -1, Qt::MatchExactly);

    if (found.count() != 1) return -1;

    return found[0].row();
}

void PlanManager::addItem(const QString &text, const int &relation1,
                          const int &relation2)
{
    Plan *P = new Plan(++lastIDInDatabase, text);
    P->firstRelation = findPlan(idFromIndex(relation1));
    P->secondRelation = findPlan(idFromIndex(relation2));

    plansList << P;
    P->addToDatabase(query);
    model->appendRow(P->toItem());

    model->sort(0);
}

void PlanManager::removeItem(const int &index)
{
    int id = idFromIndex(index);

    query->prepare("DELETE FROM plans WHERE id=?");
    query->bindValue(0, id);
    query->exec();

    query->prepare("UPDATE plans SET rel1=-1 WHERE rel1=:id");
    query->bindValue(":id", id);
    query->exec();

    query->prepare("UPDATE plans SET rel2=-1 WHERE rel2=:id");
    query->bindValue(":id", id);
    query->exec();

    int idx = searchPlansIndex(id);
    Plan *DP = plansList[idx];

    for (Plan *P : plansList)
    {
        if (P->firstRelation == DP) P->firstRelation = nullptr;
        if (P->secondRelation == DP) P->secondRelation = nullptr;
    }

    if (idx >= 0) plansList.removeAt(idx);

    model->clear();
    for (Plan *P : plansList) model->appendRow(P->toItem());

    if (model->rowCount() <= 0) lastIDInDatabase = -1;
}

void PlanManager::editItem(const int &index, const QString &text,
                           const int &relation1, const int &relation2)
{
    QStandardItem *item = model->item(index);
    Plan *P = findPlan(idFromIndex(index));

    bool sort = (text != P->name);

    P->name = text;
    P->firstRelation = findPlan(idFromIndex(relation1));
    P->secondRelation = findPlan(idFromIndex(relation2));

    P->updateInDatabse(query);

    item->setData(P->firstRelation == nullptr ? "" : P->firstRelation->name,
                  Rel1Role);
    item->setData(P->secondRelation == nullptr ? "" : P->secondRelation->name,
                  Rel2Role);
    item->setData(text, TextRole);

    if (sort) model->sort(0);
}
