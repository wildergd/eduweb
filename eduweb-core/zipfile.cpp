#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QByteArray>
#include <QStringList>
#include <QProgressBar>
#include <zip.h>
#include "zipfile.h"
#include "filesystemutils.h"

bool ZipFile::unzipFile(const QString fileName, const QString folder, QProgressBar * progress)
{
	QFile sourcefile(fileName);
	QDir dest(folder);

	if (!sourcefile.exists())
		return false;

	dest.mkpath(folder);

	QFileInfo info(sourcefile);

	if (!sourcefile.copy(QDir::temp().absoluteFilePath(info.fileName())))
		return false;

	sourcefile.close();
	sourcefile.setFileName(QDir::temp().absoluteFilePath(info.fileName()));
	if (!sourcefile.exists())
		return false;

	int error;
	struct zip * zipHandle = zip_open(sourcefile.fileName().toUtf8(), ZIP_CHECKCONS, &error);

	if (NULL == zipHandle)
		return false;

	int fileCount = zip_get_num_files(zipHandle);

	if (progress)
	{
		progress->reset();
		progress->setMaximum(fileCount - 1);
	}

	for(int index = 0; index < fileCount; index++)
	{
		struct zip_stat fileStats;
		zip_stat_init(&fileStats);
		if (zip_stat_index(zipHandle, index, ZIP_FL_UNCHANGED, &fileStats) == 0)
		{
			const char* szZippedFileName = fileStats.name;
			QFileInfo fileInfo(QString::fromUtf8(szZippedFileName));

			if (fileInfo.dir().path().compare(".") != 0 &&
			    !dest.exists(fileInfo.dir().path()))
			{
				dest.mkpath(fileInfo.dir().path());
			}

			struct zip_file* fileData = zip_fopen_index(zipHandle, index, ZIP_FL_UNCHANGED);
			if (NULL != fileData)
			{
				char* buffer = new char[fileStats.size];
				int readBytes = zip_fread(fileData, buffer, fileStats.size);

				QFile outFile(dest.absoluteFilePath(QString::fromAscii(szZippedFileName)));
				if (outFile.open(QIODevice::WriteOnly))
				{
					outFile.write(QByteArray::fromRawData(buffer, readBytes));
					outFile.close();
				}

				delete []buffer;
			}
			zip_fclose(fileData);
		}

		if (progress)
		{
			progress->setValue(index);
		}
	}

	zip_close(zipHandle);

	sourcefile.close();
	sourcefile.remove();
	return true;
}

bool ZipFile::compressFolder(const QString sourceFolder, const QString destFile, QProgressBar * progress)
{
	QDir source(sourceFolder);

	if (!source.exists())
		return false;

	int error;
	struct zip * zipHandle = zip_open(destFile.toUtf8(), ZIP_CREATE, &error);

	if (NULL == zipHandle)
		return false;

	QStringList filesInFolder = FileSystemUtils::scanFolder(sourceFolder, sourceFolder);

	if (progress)
	{
		progress->reset();
		progress->setMaximum(filesInFolder.count() - 1);
	}

	foreach(QString fileName, filesInFolder)
	{
		QFileInfo fileInfo(fileName);
		QFileInfo srcFile(source.absoluteFilePath(fileInfo.filePath()));
		if (srcFile.isFile())
		{
			struct zip_source *sourceFile;
			if ((sourceFile = zip_source_file(zipHandle, srcFile.absoluteFilePath().toUtf8(), 0, -1)) == NULL ||
			    zip_add(zipHandle, fileInfo.filePath().toUtf8(), sourceFile) < 0)
			{
				zip_source_free(sourceFile);
			}
		}

		if (progress)
			progress->setValue(progress->value() + 1);
	}

	zip_close(zipHandle);

	return true;
}
