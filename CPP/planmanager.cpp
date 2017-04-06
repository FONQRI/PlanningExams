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
    m_lastid = m_query->last() ? m_query->value(0).toInt() : 0;
}

void PlanManager::dbToModel()
{
    m_model->clear();
    m_list.clear();

    m_query->exec("SELECT * FROM plans");

    while (m_query->next())
        {
            int id = m_query->value(0).toInt();
            QString name = m_query->value(1).toString();

            m_list[id] = name;

            QStandardItem *item = new QStandardItem;

            item->setData(id, IDRole);
            item->setData(name, TextRole);
            item->setData(m_query->value(2).toInt(), Rel1Role);
            item->setData(m_query->value(3).toInt(), Rel2Role);

            m_model->appendRow(item);
        }

    m_model->sort(0);
}

void PlanManager::removeIDFromDB(const int &id)
{
    m_query->prepare("UPDATE plans SET rel1=-1 WHERE rel1=:id");
    m_query->bindValue(":id", id);
    m_query->exec();

    m_query->prepare("UPDATE plans SET rel1=-1 WHERE rel2=:id");
    m_query->bindValue(":id", id);
    m_query->exec();
}

void PlanManager::removeIDFromModel(const int &id)
{
    QList<DataRoles> roles;
    roles << Rel1Role << Rel2Role;

    for (const DataRoles &R : roles)
        {
            QModelIndexList found = m_model->match(m_model->index(0, 0), R, id,
                                                   -1, Qt::MatchExactly);

            for (const QModelIndex &I : found)
                {
                    QStandardItem *item = m_model->itemFromIndex(I);
                    item->setData(-1, R);
                }
        }
}

PlanManager::PlanManager(QObject *parent) : QObject(parent)
{
    createDB();
    m_model = new ViewModel(this);
    m_model->setSortRole(TextRole);
    dbToModel();
}

void PlanManager::addItem(const QString &text, const int &rel1Index,
                          const int &rel2Index)
{
    int rel1id =
        rel1Index >= 0 ? m_model->item(rel1Index)->data(IDRole).toInt() : -1;
    int rel2id =
        rel2Index >= 0 ? m_model->item(rel2Index)->data(IDRole).toInt() : -1;

    ++m_lastid;
    m_query->prepare("INSERT INTO plans VALUES(?, ?, ?, ?)");

    m_query->bindValue(0, m_lastid);
    m_query->bindValue(1, text);
    m_query->bindValue(2, rel1id);
    m_query->bindValue(3, rel2id);

    m_list[m_lastid] = text;

    m_query->exec();

    QStandardItem *item = new QStandardItem;

    item->setData(m_lastid, IDRole);
    item->setData(text, TextRole);
    item->setData(rel1id, Rel1Role);
    item->setData(rel2id, Rel2Role);

    m_model->appendRow(item);
    //    m_model->sort(0); // TODO does not work
}

void PlanManager::removeItem(const int &index)
{
    int id = m_model->item(index)->data(IDRole).toInt();
    m_query->prepare("DELETE FROM plans WHERE id=:id");
    m_query->bindValue(":id", id);
    m_query->exec();

    m_model->removeRow(index);
    m_list.remove(id);
    removeIDFromDB(id);
    removeIDFromModel(id);

    if (m_model->rowCount() <= 0) m_lastid = 0;
}

QString PlanManager::nameFromRel(const int &id) { return m_list.value(id, ""); }
void PlanManager::editItem(const int &index, const QString &text,
                           const int &rel1, const int &rel2)
{
    QStandardItem *item = m_model->item(index);
    int id = item->data(IDRole).toInt();

    QString ps = "UPDATE plans SET rel1=:r1, rel2=:r2, name=:name WHERE id=:id";
    m_query->prepare(ps);
    m_query->bindValue(":r1", rel1);
    m_query->bindValue(":r2", rel2);
    m_query->bindValue(":name", text);
    m_query->bindValue(":id", id);
    m_list[id] = text;

    item->setData(rel1, Rel1Role);
    item->setData(rel2, Rel2Role);
    item->setData(text, TextRole);
}
