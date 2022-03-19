#pragma once
#include <QtCore/qabstractitemmodel.h>
#include "Ethnologist.h"
#include "BuildingsService.h"
class BuildingsTableModel : public QAbstractTableModel
{
private:
	BuildingsService* bService;
	Ethnologist eth;

public:
	BuildingsTableModel(BuildingsService* _bService, Ethnologist e, QObject* parent = NULL) : QAbstractTableModel{ parent } {
		this->eth = e;
		this->bService = _bService;
	}

	// number of rows
	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;

	// number of columns
	int columnCount(const QModelIndex& parent = QModelIndex{}) const override;

	// Value at a given position
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	// add header data
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	void update() { 
		beginResetModel(); 
		endResetModel(); 
		/*QModelIndex topLeft = createIndex(0, 0);
		QModelIndex bottomRight = createIndex(this->bService->getBuildingsVector().size(), 4);
		emit dataChanged(topLeft, bottomRight, { Qt::DisplayRole });
		emit layoutChanged();*/
	}

	// used to set certain properties of a cell
	Qt::ItemFlags flags(const QModelIndex& index) const override;
};
