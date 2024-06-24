#ifndef DRIVER_H
#define DRIVER_H

#include <QObject>
#include <QQmlEngine>

#include "gamemodel.h"
#include <QTimer>

class Driver : public QObject
{
	Q_OBJECT
	QML_ELEMENT
	QML_SINGLETON

	Q_PROPERTY(gameModel* model READ model CONSTANT FINAL);
	Q_PROPERTY(int numRows READ numRows CONSTANT FINAL);
	Q_PROPERTY(int numColumns READ numColumns CONSTANT FINAL);

public:
	explicit Driver(QObject *parent = nullptr);
	~Driver();

	gameModel* model() {
		return m_model;
	}

	int numRows () {
		return m_rows;
	}

	int numColumns () {
		return m_columns;
	}

	Q_INVOKABLE void togglePlayback();

signals:

private:

	int m_rows, m_columns;
	gameModel *m_model;

	QTimer *timer;
	bool m_playing = false;
};

#endif // DRIVER_H
