#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QAbstractTableModel>

struct cell {
	bool alive = false;
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

private:
	virtual QHash<int, QByteArray> roleNames() const override;

	QVector<QVector<cell>> m_grid;
	int m_numRows, m_numColumns;
};

#endif // GAMEMODEL_H
