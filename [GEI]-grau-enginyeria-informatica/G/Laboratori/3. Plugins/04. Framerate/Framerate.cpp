#include "Framerate.h"
#include "glwidget.h"

void Framerate::onPluginLoad() {
	currentFrames = 0;
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateFPS()));
	timer->setInterval(1000);
    timer->start();
}

void Framerate::postFrame() {
	++currentFrames;
}

void Framerate::updateFPS() {
	cout << "FPS: " << currentFrames << endl;
	currentFrames = 0;
}
