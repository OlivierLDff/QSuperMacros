#include <QString>

#include "QSuperMacros.h"

QSUPERMACROS_USING_NAMESPACE

uint32_t QSuperMacrosVersion::getMajor()
{
	return QSUPERMACROS_VERSION_MAJOR;
}

uint32_t QSuperMacrosVersion::getMinor()
{
	return QSUPERMACROS_VERSION_MINOR;
}

uint32_t QSuperMacrosVersion::getPatch()
{
	return QSUPERMACROS_VERSION_PATCH;
}

uint32_t QSuperMacrosVersion::getTag()
{
	return QSUPERMACROS_VERSION_TAG_HEX;
}

QString QSuperMacrosVersion::getVersion()
{
	return QString::number(getMajor()) + "." +
		QString::number(getMinor()) + "." +
		QString::number(getTag()) + "." +
		QString::number(getTag(),16);
}
