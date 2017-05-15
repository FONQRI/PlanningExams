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

public:
	explicit PlanManager(QObject *parent = 0);
	~PlanManager();

	QStandardItemModel *getModel() const;
	QList<Plan *> *getPlansList();

	QSqlQuery *getQuery() const;

private:
	QSqlQuery *query;
	int lastIDInDatabase;
	QSqlDatabase database;
	QList<Plan *> plansList;
	QStandardItemModel *model;

	void createDatabse();

	void connectPlans();

	Plan *findPlan(const int &id);
	inline int idFromIndex(const int &role);

public slots:
	void clear();
	void updateAllColors();
	void databseToModel();

	int searchPlansIndex(const int &id);
	QVariantList getAvailableColors(const int &id);

	int searchModel(const QString &name);
	void removeItem(const int &index);

	void addItem(const QString &text, const int &relation1,
				 const int &relation2);

	void editItem(const int &index, const QString &text, const int &relation1,
				  const int &relation2);

	void updateItem(const int &index);
};

#endif  // PLANMANAGER_H
