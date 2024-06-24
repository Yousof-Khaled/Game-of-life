#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QAbstractTableModel>

struct cell {
	bool alive = false;
	int row, column;
};

class gameModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	explicit gameModel(int rows, int columns, QObject *parent = nullptr);

	enum {
		aliveRole = Qt::UserRole
	};

	// Basic functionality:
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

	// Editable:
	bool setData(const QModelIndex &index, const QVariant &value,
				 int role = Qt::EditRole) override;

	Qt::ItemFlags flags(const QModelIndex& index) const override;

	void updateEntity(bool alive, int row, int column);

	void goToNextGeneration();

	bool isValid (int r, int c);

	bool findNextGenStatus (cell* entity);

	QVector<cell*> getNeighbors (cell* entity);

	int countAliveNeighbors (cell* entity);

private:
	virtual QHash<int, QByteArray> roleNames() const override;

	QVector<QVector<cell>> m_grid;

	QSet<cell*> aliveEntities;

	int m_numRows, m_numColumns;
};

#endif // GAMEMODEL_H
