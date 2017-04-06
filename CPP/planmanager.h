#ifndef PLANMANAGER_H
#define PLANMANAGER_H

#include <QDebug>
#include <QHash>
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include "viewmodel.h"

class PlanManager : public QObject
{
    Q_OBJECT

    int m_lastid;
    QSqlDatabase m_db;
    QSqlQuery *m_query;
    QHash<int, QString> m_list;
    QStandardItemModel *m_model;

    void createDB();
    void dbToModel();
    void removeIDFromDB(const int &id);
    void removeIDFromModel(const int &id);

public:
    explicit PlanManager(QObject *parent = 0);

    QStandardItemModel *model() const;

public slots:
    void removeItem(const int &index);
    QString nameFromRel(const int &id);
    void editItem(const int &index, const QString &text, const int &rel1,
                  const int &rel2);
    void addItem(const QString &text, const int &rel1Index,
                 const int &rel2Index);
};

#endif  // PLANMANAGER_H
