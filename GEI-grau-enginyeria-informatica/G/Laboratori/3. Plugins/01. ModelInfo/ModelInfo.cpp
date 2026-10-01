#include "ModelInfo.h"
#include "glwidget.h"

void ModelInfo::onPluginLoad() {
	updateCounters();
}

void ModelInfo::postFrame() {
	cout << "Objects: " << objectCount << endl;
	cout << "|- Polygons: " << polygonCount << endl;
	if (trianglePercent != -1)
		cout << "|   \\- " << trianglePercent << "\% triangles" << endl;
	cout << "\\- Vertices: " << vertexCount << endl << endl;
}

void ModelInfo::onObjectAdd() {
	updateCounters();
}

void ModelInfo::onSceneClear() {
	updateCounters();
}

void ModelInfo::updateCounters() {
	polygonCount = 0;
	vertexCount = 0;
	int triangleCount = 0;
	for (Object obj : scene()->objects()) {
		polygonCount += obj.faces().size();
		for (Face f : obj.faces())
			if (f.numVertices() == 3)
				++triangleCount;
		vertexCount += obj.vertices().size();
	}
	
	objectCount = scene()->objects().size();
	trianglePercent = triangleCount == 0
		? -1 : ((float) triangleCount / (float) polygonCount) * 100;
}