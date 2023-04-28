#ifndef ZIPFILE_H
#define ZIPFILE_H

#include "eduweb-core.h"
#include <QProgressBar>

class EDUWEB_CORE_EXPORT ZipFile
{
public:
	static bool unzipFile(const QString fileName, const QString folder, QProgressBar * progress = 0);
	static bool compressFolder(const QString sourceFolder, const QString destFile, QProgressBar * progress = 0);
};

#endif // ZIPFILE_H
