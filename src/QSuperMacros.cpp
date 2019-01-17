#include <QString>

#include "QSuperMacros.h"

QSUPERMACROS_USING_NAMESPACE

uint32_t QSuperMacrosVersion::GetMajor()
{
	return QSUPERMACROS_VERSION_MAJOR;
}

uint32_t QSuperMacrosVersion::GetMinor()
{
	return QSUPERMACROS_VERSION_MINOR;
}

uint32_t QSuperMacrosVersion::GetPatch()
{
	return QSUPERMACROS_VERSION_PATCH;
}

uint32_t QSuperMacrosVersion::GetTag()
{
	return QSUPERMACROS_VERSION_TAG_HEX;
}

QString QSuperMacrosVersion::GetVersion()
{
	return QString::number(GetMajor()) + "." +
		QString::number(GetMinor()) + "." +
		QString::number(GetTag()) + "." +
		QString::number(GetTag(),16);
}