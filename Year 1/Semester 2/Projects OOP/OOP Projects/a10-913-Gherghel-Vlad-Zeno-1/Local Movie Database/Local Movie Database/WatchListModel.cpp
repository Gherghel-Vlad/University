#include "WatchListModel.h"
#include <QTimer>

WatchListModel::WatchListModel(UserService* us, QObject* parent):  QAbstractTableModel(parent)
{
	this->us = us;
	this->timer = new QTimer(this);
	this->timer->setInterval(1000);
	connect(timer, &QTimer::timeout, this, &WatchListModel::dataChangedSignalEmit);
	timer->start();	
}

void WatchListModel::dataChangedSignalEmit() {
	QModelIndex topLeft = createIndex(0, 0);
	QModelIndex bottomRight = createIndex(this->us->getWatchListAsVector().size(), 4);
	emit dataChanged(topLeft, bottomRight, { Qt::DisplayRole });
	emit layoutChanged();
}

int WatchListModel::rowCount(const QModelIndex& parent) const
{
	return this->us->getWatchListAsVector().size();
}

int WatchListModel::columnCount(const QModelIndex& parent) const
{
	return 5;
}

QVariant WatchListModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	if (role == Qt::DisplayRole) {
		Movie m = this->us->getWatchListAsVector()[row];
		switch (index.column()) {
		case 0:
			return QString::fromStdString(m.getTitle());
		case 1:
			return QString::fromStdString(m.getGenre());
		case 2:
			return QString::number(m.getYearOfRelease());
		case 3:
			return QString::number(m.getNumberOfLikes());
		case 4:
			return QString::fromStdString(m.getTrailer());
		default:
			break;
		}

	}


	return QVariant();
}
