#include "driver.h"
#include <QAbstractListModel>

Driver::Driver(QObject *parent)
	: QObject{parent}
{
	m_rows = 50;
	m_columns = 90;

	m_model = new gameModel(m_rows, m_columns);

	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, [this] {
		static int iteration = 0;

		qInfo() << "iteration #" << iteration++;
		m_model->goToNextGeneration();
	});
}

Driver::~Driver()
{
	delete m_model;
	delete timer;
}

void Driver::setSideLength(int newLength)
{
	if (m_sideLength != newLength) {
		m_sideLength = newLength;
		emit sideLengthChanged(newLength);
	}
}

void Driver::togglePlayback()
{
	m_playing = !m_playing;
	if (m_playing) {
		timer->start(500);
		qInfo() << "started";
	}
	else {
		timer->stop();
		qInfo() << "stopped";
	}
}

void Driver::goToNextGen()
{
	m_model->goToNextGeneration();
}
