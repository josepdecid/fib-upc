#ifndef _KEYBOARDSELECT_H
#define _KEYBOARDSELECT_H

#include "plugin.h" 

class KeyboardSelect: public QObject, public Plugin {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

	public:
		void keyPressEvent(QKeyEvent *);
};

#endif
