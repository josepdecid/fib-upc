#include "KeyboardSelect.h"
#include "glwidget.h"

void KeyboardSelect::keyPressEvent(QKeyEvent *event) {
	int key = event->key();
	if (key >= Qt::Key_0 && key <= Qt::Key_9) {
		unsigned long index = key - Qt::Key_0;
		if (index >= scene()->objects().size()) {
			index = -1;
		} scene()->setSelectedObject(index);
	}
}

