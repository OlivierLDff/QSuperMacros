#include <QString>

#include "QSuperMacros.h"

QSUPER_MACROS_USING_NAMESPACE

uint32_t QSuperMacrosVersion::GetMajor()
{
	return QSUPER_MACROS_VERSION_MAJOR;
}

uint32_t QSuperMacrosVersion::GetMinor()
{
	return QSUPER_MACROS_VERSION_MINOR;
}

uint32_t QSuperMacrosVersion::GetPatch()
{
	return QSUPER_MACROS_VERSION_PATCH;
}

uint32_t QSuperMacrosVersion::GetTag()
{
	return QSUPER_MACROS_VERSION_TAG_HEX;
}

QString QSuperMacrosVersion::GetVersion()
{
	return QString::number(GetMajor()) + "." +
		QString::number(GetMinor()) + "." +
		QString::number(GetTag()) + "." +
		QString::number(GetTag(),16);
}