#include "gamemodel.h"

gameModel::gameModel(int rows, int columns, QObject *parent)
	: QAbstractTableModel(parent)
{
	m_numRows = rows;
	m_numColumns = columns;

	m_grid = QVector<QVector<cell>> (m_numRows, QVector<cell>(m_numColumns));

	for (int i = 0 ; i < m_numRows ; ++i) {
		for (int j = 0 ; j < m_numColumns ; ++j) {
			if (i & 1) {
				m_grid[i][j].alive = bool(j & 1);
			}
			else {
				m_grid[i][j].alive = !bool(j & 1);
			}
		}
	}

	// qInfo() << QString::asprintf("creating model: (%d, %d)\n", m_numRows, m_numColumns);
	// qInfo() << QString::asprintf("Double check: (%d, %d)\n", m_grid.count(), m_grid[49].count());
}

int gameModel::rowCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;

	// FIXME: Implement me!
	return m_numRows;
}

int gameModel::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;

	// FIXME: Implement me!
	return m_numColumns;
}

QVariant gameModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	// qInfo() << index.row() << " " << index.column();

	// FIXME: Implement me!
	switch (role) {
	case aliveRole:
		return QVariant(m_grid[index.row()][index.column()].alive);
	default:
		qWarning("Unknown Role");
		break;
	}
	return QVariant();
}

bool gameModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (data(index, role) != value) {
		// FIXME: Implement me!

		switch (role) {
		case aliveRole:
			m_grid[index.row()][index.column()].alive = value.toBool();
			break;
		default:
			break;
		}

		emit dataChanged(index, index, {role});
		return true;
	}
	return false;
}

Qt::ItemFlags gameModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> gameModel::roleNames() const
{
	QHash<int, QByteArray> names;

	names[aliveRole] = "isAlive";

	return names;
}
