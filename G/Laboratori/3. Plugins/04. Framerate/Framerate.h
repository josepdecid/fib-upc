#ifndef _FRAMERATE_H
#define _FRAMERATE_H

#include <QTimer>
#include "plugin.h" 

class Framerate: public QObject, public Plugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "Plugin") 
  Q_INTERFACES(Plugin)

  public:
    void onPluginLoad();
    void postFrame();
  private:
    QTimer* timer;
    int currentFrames;
  private slots:
    void updateFPS();
};

#endif
