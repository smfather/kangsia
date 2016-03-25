#ifndef MODELER_H
#define MODELER_H

#include <QString>

class modeler
{
public:
	modeler() {}
	~modeler() {}

	static void setModelName(QString& mn) { model_name = mn; }
	static void setModelPath(QString& mp) { model_path = mp; }

	static QString& modelName() { return model_name; }
	static QString& modelPath() { return model_path; }

private:
	static QString model_name;
	static QString model_path;
};

#endif