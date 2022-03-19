#include "BuildingsTableModel.h"
#include <qbrush.h>
#include <qfont.h>
#include <algorithm>

int BuildingsTableModel::rowCount(const QModelIndex& parent) const
{
	return this->bService->getBuildingsVector().size();
}

int BuildingsTableModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant BuildingsTableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();

	Ethnologist e = this->eth;
	// get the events
	std::vector<Building> baseList = this->bService->getBuildingsVector();
	std::vector<Building> list;

	if (row == baseList.size())
	{
		return QVariant();
	}

	for (int i = 0; i < baseList.size(); i++) {
		if (baseList[i].getThematicArea() == e.getThematicArea()) {
			list.push_back(baseList[i]);
		}
	}
	
	for (int i = 0; i < baseList.size(); i++) {
		if (baseList[i].getThematicArea() != e.getThematicArea() && baseList[i].getThematicArea() != "office") {
			list.push_back(baseList[i]);
		}
	}

	for (int i = 0; i < baseList.size(); i++) {
		if (baseList[i].getThematicArea() == "office") {
			list.push_back(baseList[i]);
		}
	}


	// get the event from the current row
	Building b = list[row];
	std::string aux;
	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(b.getId());
		case 1:
			return QString::fromStdString(b.getDescription());
		case 2:
			return QString::fromStdString(b.getThematicArea());
		case 3:
			return QString::fromStdString(b.getLocation());
		default:
			break;
		}
	}
	
	if (role == Qt::BackgroundRole) {
		if(e.getThematicArea() == b.getThematicArea())
			return QBrush(Qt::blue);
		/*if (strcmp(b.getThematicArea().c_str(), this->eth->getThematicArea().c_str()) == 0) {
			return QBrush(Qt::blue);
		}*/
	}
	return QVariant();
}

QVariant BuildingsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QString{ "Id" };
			case 1:
				return QString{ "Description" };
			case 2:
				return QString{ "Thematic sector" };
			case 3:
				return QString{ "Location" };
			default:
				break;
			}
		}
	}

	return QVariant();
}

Qt::ItemFlags BuildingsTableModel::flags(const QModelIndex& index) const
{
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}


