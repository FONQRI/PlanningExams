#ifndef PLANMANAGER_H
#define PLANMANAGER_H

#include <QDebug>
#include <QHash>
#include <QObject>
#include <QTime>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <vector>
#include "plan.h"
#include "viewmodel.h"

class PlanManager : public QObject
{
    Q_OBJECT

    int lastIDInDatabase;
    QSqlDatabase database;
    QSqlQuery *query;
    QList<Plan> plansList;
    QStandardItemModel *model;

    void createDatabse();
    void databseToModel();

    void connectPlans();

    int indexByID(const int &id);   // searh in plans list
    Plan *findByID(const int &id);  // searh in plans list
    inline int idFromIndex(const int &role);

public:
    explicit PlanManager(QObject *parent = 0);

    QStandardItemModel *getModel() const;

public slots:
    int indexFromText(const QString &text);  // search in model
    void removeItem(const int &index);

    void addItem(const QString &text, const int &relation1,
                 const int &relation2);

    void editItem(const int &index, const QString &text, const int &relation1,
                  const int &relation2);
};

#endif  // PLANMANAGER_H
