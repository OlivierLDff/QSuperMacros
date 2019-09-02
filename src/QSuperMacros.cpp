#include <QString>

#include "QSuperMacros.h"

QSUPERMACROS_USING_NAMESPACE

uint32_t Version::getMajor()
{
	return QSUPERMACROS_VERSION_MAJOR;
}

uint32_t Version::getMinor()
{
	return QSUPERMACROS_VERSION_MINOR;
}

uint32_t Version::getPatch()
{
	return QSUPERMACROS_VERSION_PATCH;
}

uint32_t Version::getTag()
{
	return QSUPERMACROS_VERSION_TAG_HEX;
}

QString Version::getVersion()
{
	return QString::number(getMajor()) + "." +
		QString::number(getMinor()) + "." +
		QString::number(getTag()) + "." +
		QString::number(getTag(),16);
}
