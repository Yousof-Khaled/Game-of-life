#include "driver.h"
#include <QAbstractListModel>

Driver::Driver(QObject *parent)
	: QObject{parent}
{
	m_rows = 200;
	m_columns = 350;

	m_model = new gameModel(m_rows, m_columns);

	// for (int i = 0; i < m_rows ; ++i) {
	// 	for (int j = 0 ; j < m_columns ; ++j) {
	// 		// auto index = createIndex(i, j);
	// 		qInfo() << i << ", " << j << " : " << m_model->index(i, j).data(gameModel::aliveRole);
	// 	}
	// }
}

Driver::~Driver()
{
	delete m_model;
}
