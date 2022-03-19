#pragma once
#include <QAbstractTableModel>
#include "UserService.h"

class WatchListModel: public QAbstractTableModel
{
	Q_OBJECT
private:
    UserService* us = nullptr;
    QTimer* timer;
    void dataChangedSignalEmit();
public:
    WatchListModel(UserService* us, QObject* parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

};

