#include "gamemodel.h"

gameModel::gameModel(int rows, int columns, QObject *parent)
	: QAbstractTableModel(parent)
{
	m_numRows = rows;
	m_numColumns = columns;

	m_grid = QVector<QVector<cell>> (m_numRows, QVector<cell>(m_numColumns));
	for (int i = 0 ; i < m_numRows ; ++i) {
		for (int j = 0 ; j < m_numColumns ; ++j) {
			m_grid[i][j].row  = i;
			m_grid[i][j].column = j;
		}
	}
}

int gameModel::rowCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;

	return m_numRows;
}

int gameModel::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;

	return m_numColumns;
}

QVariant gameModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	// qInfo() << index.row() << " " << index.column();

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
			updateEntity(value.toBool(), index.row(), index.column());
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

void gameModel::updateEntity(bool alive, int row, int column)
{
	if (alive) {
		aliveEntities.insert(&m_grid[row][column]);
	}
	else {
		aliveEntities.remove(&m_grid[row][column]);
	}
	m_grid[row][column].alive = alive;
}



void gameModel::goToNextGeneration()
{
	QSet<cell*> nextGenEntities, removedEnities, processed;
	foreach (cell* entity, aliveEntities) {

		bool isEntityAlive = findNextGenStatus(entity);
		if (isEntityAlive) {
			nextGenEntities.insert(entity);
		}
		else {
			removedEnities.insert(entity);
		}
		processed.insert(entity);

		auto neighbors = getNeighbors(entity);
		foreach (cell* cuzz, neighbors) {
			if (processed.contains(cuzz)) continue;

			processed.insert(cuzz);

			bool isCuzzAlive = findNextGenStatus(cuzz);
			if (isCuzzAlive) {
				nextGenEntities.insert(cuzz);
			}
		}
	}

	foreach (cell* aliveEntity, nextGenEntities) {
		setData(index(aliveEntity->row, aliveEntity->column), QVariant(true), aliveRole);
	}
	foreach (cell* entity, removedEnities) {
		setData(index(entity->row, entity->column), QVariant(false), aliveRole);
	}
}

bool gameModel::isValid(int r, int c)
{
	return 0 <= r && r < m_numRows && 0 <= c && c < m_numColumns;
}

bool gameModel::findNextGenStatus(cell *entity)
{
	int numAliveNeighbors = countAliveNeighbors(entity);

	if (entity->alive) {
		return 2 <= numAliveNeighbors && numAliveNeighbors <= 3;
	}
	else {
		return numAliveNeighbors == 3;
	}
}

QVector<cell *> gameModel::getNeighbors(cell *entity)
{
	QVector<cell*> neighbors;

	int mx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
	int my[] = {0, 1, 1, 1, 0, -1, -1, -1};

	for (int i = 0 ; i < 8 ; ++i){
		int newRow = entity->row + my[i];
		int newColumn = entity->column + mx[i];

		if (!isValid(newRow, newColumn)) continue;

		neighbors.push_back(&m_grid[newRow][newColumn]);
	}

	return neighbors;
}

int gameModel::countAliveNeighbors(cell *entity)
{
	int aliveCount = 0;
	auto neighbors = getNeighbors(entity);
	foreach (cell* cuzz, neighbors) {
		aliveCount += cuzz->alive;
	}
	return aliveCount;
}

QHash<int, QByteArray> gameModel::roleNames() const
{
	QHash<int, QByteArray> names;

	names[aliveRole] = "isAlive";

	return names;
}
