#ifndef _MODELINFO_H
#define _MODELINFO_H

#include "plugin.h" 

class ModelInfo: public QObject, public Plugin {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	void onPluginLoad();
	void postFrame();

	void onObjectAdd();
	void onSceneClear();
  private:
    int objectCount;
	int polygonCount;	
	int vertexCount;
    float trianglePercent;	

	void updateCounters();
};

#endif
