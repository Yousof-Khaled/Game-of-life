#include "driver.h"
#include <QAbstractListModel>

Driver::Driver(QObject *parent)
	: QObject{parent}
{
	m_rows = 200;
	m_columns = 350;

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
}

void Driver::togglePlayback()
{
	m_playing = !m_playing;
	if (m_playing) {
		timer->start(1000);
		qInfo() << "started";
	}
	else {
		timer->stop();
		qInfo() << "stopped";
	}
}
