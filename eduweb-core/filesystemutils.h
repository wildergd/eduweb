#ifndef FILESYSTEMUTILS_H
#define FILESYSTEMUTILS_H

#include "eduweb-core.h"
#include <QProgressBar>

class EDUWEB_CORE_EXPORT FileSystemUtils
{
public:
//	static bool unzipFile(const QString fileName, const QString folder, QProgressBar * progress = 0);
//	static bool compressFolder(const QString sourceFolder, const QString destFile, QProgressBar * progress = 0);
	static QStringList scanFolder(const QString directory, QString relativeToPath = QString());
	static bool copyDirectory(const QString source, const QString dest, QProgressBar * progress = 0);
	static bool removeDirectory(const QString path, QProgressBar * progress = 0);
	static QString hashMD5(const QString fileName);
};

#endif // FILESYSTEMUTILS_H
