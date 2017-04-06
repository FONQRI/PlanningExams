#ifndef PLANMANAGER_H
#define PLANMANAGER_H

#include <QDebug>
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "viewmodel.h"

class PlanManager : public QObject
{
    Q_OBJECT

    int m_lastid;
    QSqlDatabase m_db;
    QSqlQuery *m_query;
    QStandardItemModel *m_model;

    void createDB();
    void dbToModel();

public:
    explicit PlanManager(QObject *parent = 0);

public slots:
    void addItem(const QString &text);
    void removeItem(const int &index);
    QString nameFromRel(const int &index);
    void updateRels(const int &index, const int &rel1, const int &rel2);
};

#endif  // PLANMANAGER_H
