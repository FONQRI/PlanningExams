#ifndef PLANMANAGER_H
#define PLANMANAGER_H

#include <QDebug>
#include <QHash>
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <vector>
#include "plan.h"
#include "viewmodel.h"

class PlanManager : public QObject
{
    Q_OBJECT

    Plan *nullPlan = nullptr;

    int m_lastid;
    QSqlDatabase m_db;
    QSqlQuery *m_query;
    QList<Plan> m_plans;
    QStandardItemModel *m_model;

    void createDB();
    void dbToModel();
    void removeIDFromModel(const int &id);

    inline int idFromIndex(const int &role);

    void connectPlans();
    Plan *findByID(const int &id);
    int indexByID(const int &id);

public:
    explicit PlanManager(QObject *parent = 0);

    QStandardItemModel *model() const;

public slots:
    int indexFromText(const QString &text);
    void removeItem(const int &index);
    void addItem(const QString &text, const int &rel1, const int &rel2);
    void editItem(const int &index, const QString &text, const int &rel1,
                  const int &rel2);
};

#endif  // PLANMANAGER_H
