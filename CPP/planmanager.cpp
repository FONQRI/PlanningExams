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
        "INTEGER, rel2 INEGER)");

    m_query->exec("SELECT DISTINCT id FROM plans ORDER BY ASC");
    m_lastid = m_query->last() ? m_query->value(0).toInt() : 0;
}

void PlanManager::dbToModel()
{
    m_model->clear();

    m_query->exec("SELECT * FROM plans");

    while (m_query->next())
        {
            QStandardItem *item = new QStandardItem;

            item->setData(m_query->value(0).toInt(), IDRole);
            item->setData(m_query->value(1).toString(), TextRole);
            item->setData(m_query->value(2).toInt(), Rel1Role);
            item->setData(m_query->value(3).toInt(), Rel2Role);

            m_model->appendRow(item);
        }
}

PlanManager::PlanManager(QObject *parent) : QObject(parent)
{
    createDB();
    m_model = new ViewModel(this);
    dbToModel();
}

void PlanManager::addItem(const QString &text, const int &rel1Index,
                          const int &rel2Index)
{
    qDebug() << text << rel1Index << rel2Index;

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

    m_query->exec();

    QStandardItem *item = new QStandardItem;

    item->setData(m_lastid, IDRole);
    item->setData(text, TextRole);
    item->setData(rel1id, Rel1Role);
    item->setData(rel2id, Rel2Role);

    m_model->appendRow(item);
    // TODO sort the model?
}

void PlanManager::removeItem(const int &index)
{
    m_query->prepare("DELETE FROM plans WHERE id=:id");
    m_query->bindValue(":id", m_model->item(index)->data(IDRole).toInt());
    m_model->removeRow(index);
}

QString PlanManager::nameFromRel(const int &index)
{
    if (index < 0) return "";
    return m_model->item(index)->data(TextRole).toString();
}

void PlanManager::updateRels(const int &index, const int &rel1, const int &rel2)
{
    QStandardItem *item = m_model->item(index);
    int id = item->data(IDRole).toInt();

    m_query->prepare("UPDATE plans SET rel1=:rel WHERE id=:id");
    m_query->bindValue(":rel", rel1);
    m_query->bindValue(":id", id);
    m_query->exec();

    m_query->prepare("UPDATE plans SET rel2=:rel WHERE id=:id");
    m_query->bindValue(":rel", rel2);
    m_query->bindValue(":id", id);
    m_query->exec();

    item->setData(rel1, Rel1Role);
    item->setData(rel2, Rel2Role);
}
