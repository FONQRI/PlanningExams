#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QStandardItemModel>

enum DataRoles
{
    IDRole = Qt::UserRole + 1,
    TextRole = Qt::UserRole + 2,
    Rel1Role = Qt::UserRole + 3,
    Rel2Role = Qt::UserRole + 4
};

class ViewModel : public QStandardItemModel
{
    Q_OBJECT

public:
    ViewModel(QObject *parent = 0) : QStandardItemModel(parent) {}
protected:
    QHash<int, QByteArray> roleNames() const
    {
        QHash<int, QByteArray> m_roles;

        m_roles[IDRole] = "idRole";
        m_roles[TextRole] = "textRole";
        m_roles[Rel1Role] = "rel1Role";
        m_roles[Rel2Role] = "rel2Role";

        return m_roles;
    }
};

#endif  // VIEWMODEL_H
