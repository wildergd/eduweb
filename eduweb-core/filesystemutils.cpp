#include <QtDebug>
#include <QFileInfo>
#include <QProgressBar>
#include <QCryptographicHash>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QByteArray>
#include <QStringList>
#include "filesystemutils.h"

QStringList FileSystemUtils::scanFolder(const QString directory, QString relativeToPath)
{
	QFileInfo info(directory);

	if (!info.exists() || !info.isDir())
		return QStringList();

	QStringList entries;
	QDir srcDir(directory);

	srcDir.setFilter(QDir::Files|QDir::Dirs|QDir::Readable|QDir::NoDotAndDotDot|QDir::Hidden);
	srcDir.setSorting(QDir::DirsFirst);
	QList<QFileInfo> srcList = srcDir.entryInfoList();
	QStringList archiveList;

	foreach(QFileInfo di, srcList)
	{
		if(di.isDir())
			entries << FileSystemUtils::scanFolder(di.absoluteFilePath(), relativeToPath);
		else
		{
			if (relativeToPath.isEmpty() || relativeToPath.isNull())
				entries << di.absoluteFilePath();
			else
			{
				entries << QDir(relativeToPath).relativeFilePath(di.absoluteFilePath());
			}
		}
	}

	if (relativeToPath.isEmpty() || relativeToPath.isNull())
		entries << srcDir.absolutePath();
	else if(!QDir(relativeToPath).relativeFilePath(srcDir.absolutePath()).isEmpty())
	{
		entries << QDir(relativeToPath).relativeFilePath(srcDir.absolutePath());
	}

	return entries;
}

bool FileSystemUtils::copyDirectory(const QString source, const QString dest, QProgressBar * progress)
{
	QDir srcDir(source);
	QDir dstDir(dest);

	if (!dstDir.exists())
		dstDir.mkpath(dstDir.absolutePath());

	QStringList filesList = FileSystemUtils::scanFolder(srcDir.absolutePath(), source);
	filesList.sort();

	if (progress)
	{
		progress->reset();
		progress->setMaximum(filesList.count() - 1);
	}

	foreach(QString fileName, filesList)
	{
		QFileInfo fileInfo(fileName);
		QFileInfo srcFile(srcDir.absoluteFilePath(fileInfo.filePath()));
		QFileInfo dstFile(dstDir.absoluteFilePath(fileInfo.filePath()));

		if (!dstDir.exists(fileInfo.path()))
			dstDir.mkpath(fileInfo.path());

		if (srcFile.isFile())
		{
			if (dstFile.exists())
				QFile::remove(dstFile.absoluteFilePath());

			QFile::copy(srcFile.absoluteFilePath(), dstFile.absoluteFilePath());
		}
		else if (srcFile.isDir() && !dstFile.exists())
			dstDir.mkpath(fileInfo.filePath());

		if (progress)
			progress->setValue(progress->value() + 1);
	}

	return true;
}

bool FileSystemUtils::removeDirectory(const QString path, QProgressBar * progress)
{
	QDir srcDir(path);
	QStringList entries = FileSystemUtils::scanFolder(srcDir.absolutePath());

	if (progress)
	{
		progress->reset();
		progress->setMaximum(entries.count() - 1);
	}

	for(int index = 0; index < entries.count(); index++)
	{
		QString fileName = entries.at(index);
		QFileInfo fileInfo(fileName);

		if(fileInfo.exists() && fileInfo.isFile())
			QFile(fileName).remove();
		else if(fileInfo.isDir())
			srcDir.rmdir(fileName);

		if (progress)
		{
			progress->setValue(index);
		}
	}

	return true;
}

QString FileSystemUtils::hashMD5(const QString fileName)
{
	QCryptographicHash hash(QCryptographicHash::Md5);

	if (!QFile(fileName).exists())
		return QString();

	QFile file(fileName);
	if (!file.open(QFile::ReadOnly))
		return QString();

	hash.addData(file.readAll());
	return QString(hash.result().toHex());
}
