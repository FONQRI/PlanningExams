#include "planmanager.h"

QStandardItemModel *PlanManager::model() const { return m_model; }
void PlanManager::createDB()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("DB.SQLITE");
    if (!m_db.open()) qDebug() << "Couldn't open database!";

    m_query = new QSqlQuery(m_db);

    m_query->exec(
        "CREATE TABLE IF NOT EXISTS plans(id INTEGER, name STRING, rel1 "
        "INTEGER, rel2 INTEGER)");

    m_query->exec("SELECT DISTINCT id FROM plans ORDER  BY id ASC");
    m_lastid = m_query->last() ? m_query->value(0).toInt() : -1;
}

void PlanManager::dbToModel()
{
    m_plans.clear();
    m_model->clear();

    m_query->exec("SELECT * FROM plans");
    while (m_query->next()) m_plans << Plan::fromRecord(m_query->record());

    connectPlans();
    for (Plan &P : m_plans) m_model->appendRow(P.toItem());

    m_model->sort(0);
}

int PlanManager::idFromIndex(const int &role)
{
    if (role < 0)
        return role;
    else
        return m_model->item(role)->data(IDRole).toInt();
}

void PlanManager::connectPlans()
{
    for (Plan &P : m_plans)
        for (Plan &PP : m_plans)
            {
                if (PP.tempRel1 == P.id) PP.rel1 = &P;
                if (PP.tempRel2 == P.id) PP.rel2 = &P;
            }
}

Plan *PlanManager::findByID(const int &id)
{
    for (Plan &P : m_plans)
        if (P.id == id) return &P;

    return nullptr;
}

int PlanManager::indexByID(const int &id)
{
    int count = 0;

    for (Plan &P : m_plans)
        {
            if (P.id == id) return count;
            ++count;
        }

    return -1;
}

int PlanManager::indexFromText(const QString &text)
{
    if (text.isEmpty()) return -1;

    QModelIndexList found = m_model->match(m_model->index(0, 0), TextRole, text,
                                           -1, Qt::MatchExactly);

    if (found.count() != 1) return -1;

    return found[0].row();
}

PlanManager::PlanManager(QObject *parent) : QObject(parent)
{
    createDB();
    m_model = new ViewModel(this);
    m_model->setSortRole(TextRole);
    dbToModel();
}

void PlanManager::addItem(const QString &text, const int &rel1, const int &rel2)
{
    Plan P(++m_lastid, text);
    P.rel1 = findByID(idFromIndex(rel1));
    P.rel2 = findByID(idFromIndex(rel2));

    m_plans << P;
    P.addToDB(m_query);
    m_model->appendRow(P.toItem());

    m_model->sort(0);
}

void PlanManager::removeItem(const int &index)
{
    int id = idFromIndex(index);

    m_query->prepare("DELETE FROM plans WHERE id=?");
    m_query->bindValue(0, id);
    m_query->exec();

    m_query->prepare("UPDATE plans SET rel1=-1 WHERE rel1=:id");
    m_query->bindValue(":id", id);
    m_query->exec();

    m_query->prepare("UPDATE plans SET rel2=-1 WHERE rel2=:id");
    m_query->bindValue(":id", id);
    m_query->exec();

    int idx = indexByID(id);
    Plan *DP = &m_plans[idx];

    for (Plan &P : m_plans)
        {
            if (P.rel1 == DP) P.rel1 = nullptr;
            if (P.rel2 == DP) P.rel2 = nullptr;
        }

    if (idx >= 0) m_plans.removeAt(idx);

    m_model->clear();
    for (Plan &P : m_plans) m_model->appendRow(P.toItem());

    if (m_model->rowCount() <= 0) m_lastid = -1;
}

void PlanManager::editItem(const int &index, const QString &text,
                           const int &rel1, const int &rel2)
{
    QStandardItem *item = m_model->item(index);
    Plan *P = findByID(idFromIndex(index));

    bool sort = (text != P->name);

    P->name = text;
    P->rel1 = findByID(idFromIndex(rel1));
    P->rel2 = findByID(idFromIndex(rel2));

    P->updateInDB(m_query);

    item->setData(P->rel1 == nullptr ? "" : P->rel1->name, Rel1Role);
    item->setData(P->rel2 == nullptr ? "" : P->rel2->name, Rel2Role);
    item->setData(text, TextRole);

    if (sort) m_model->sort(0);
}
