/** 
 * \file QJsonImportExport.h
 * \brief Common define for the library
 */
#ifndef __QJSON_IMPORT_EXPORT_HPP__
#define __QJSON_IMPORT_EXPORT_HPP__

// ─────────────────────────────────────────────────────────────
//					INCLUDE
// ─────────────────────────────────────────────────────────────

// C Header

// C++ Header

// Qt Header
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QUrl>

// Dependancies Header

// Application Header
#include <QSuperMacros.h>

// ─────────────────────────────────────────────────────────────
//					DECLARATION
// ─────────────────────────────────────────────────────────────

#define QJSONIMPORT_ISVALID(jsonName, type) json.contains(jsonName) && json[jsonName].is##type()

// ───────── UINT64 ───────────

#define QJSONIMPORT_ISUINT64VALID(jsonName) QJSONIMPORT_ISVALID(jsonName, String) \

#define QJSONIMPORT_UINT64(jsonName, setter) \
	if (QJSONIMPORT_ISUINT64VALID(jsonName)) \
	{ \
		setter(json[jsonName].toString.toULongLong()); \
	} \
	
#define QJSONIMPORT_UINT64_WLOG(jsonName, setter, logCat) \
{ \
	if (QJSONIMPORT_ISUINT64VALID(jsonName)) \
	{ \
		bool stringValid = false; \
		quint64 value = json[jsonName].toString().toULongLong(&stringValid); \
		if (!stringValid) \
		{ \
			qCWarning(logCat, "Cannot convert String to Unit64"); \
		} \
		setter(value); \
	} \
	else \
	{ \
		qCWarning(logCat, "%s isn't a valid Json String", qPrintable(jsonName)); \
	} \
} \


// ───────── UINT32 ───────────

#define QJSONIMPORT_ISUINT32VALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Double) \

#define QJSONIMPORT_UINT32(jsonName, setter) \
	if (QJSONIMPORT_ISUINT32VALID(jsonName)) \
	{ \
		setter((quint32)(json[jsonName].toDouble())); \
	} \

#define QJSONIMPORT_UINT32_WLOG(jsonName, setter, logCat) \
{ \
	QJSONIMPORT_UINT32(jsonName, setter) \
	else \
	{ \
		qCWarning(logCat, "%s isn't a valid Json Double", qPrintable(jsonName)); \
	} \
} \

// ───────── UINT16 ───────────

#define QJSONIMPORT_ISUINT16VALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Double) \

#define QJSONIMPORT_UINT16(jsonName, setter) \
	if (QJSONIMPORT_ISUINT16VALID(jsonName)) \
	{ \
		setter((quint16)(json[jsonName].toDouble())); \
	} \

#define QJSONIMPORT_UINT16_WLOG(jsonName, setter, logCat) \
{ \
	QJSONIMPORT_UINT16(jsonName, setter) \
	else \
	{ \
		qCWarning(logCat, "%s isn't a valid Json Double", qPrintable(jsonName)); \
	} \
} \

// ───────── UINT8 ───────────

#define QJSONIMPORT_ISUINT8VALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Double) \

#define QJSONIMPORT_UINT8(jsonName, setter) \
	if (QJSONIMPORT_ISUINT8VALID(jsonName)) \
	{ \
		setter((quint8)(json[jsonName].toDouble())); \
	} \

#define QJSONIMPORT_UINT8_WLOG(jsonName, setter, logCat) \
{ \
	QJSONIMPORT_UINT8(jsonName, setter) \
	else \
	{ \
		qCWarning(logCat, "%s isn't a valid Json Double", qPrintable(jsonName)); \
	} \
} \

// ───────── INT ───────────

#define QJSONIMPORT_ISINTVALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Double) \

#define QJSONIMPORT_INT(jsonName, setter) \
	if (QJSONIMPORT_ISINTVALID(jsonName)) \
	{ \
		setter((int)(json[jsonName].toDouble())); \
	} \

#define QJSONIMPORT_INT_WLOG(jsonName, setter, logCat) \
{ \
	QJSONIMPORT_INT(jsonName, setter) \
	else \
	{ \
		qCWarning(logCat, "%s isn't a valid Json Double", qPrintable(jsonName)); \
	} \
} \

// ───────── BOOL ───────────

#define QJSONIMPORT_ISBOOLVALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Bool) \

#define QJSONIMPORT_BOOL(jsonName, setter) \
	if (QJSONIMPORT_ISBOOLVALID(jsonName)) \
	{ \
		setter(json[jsonName].toBool()); \
	} \

#define QJSONIMPORT_BOOL_WLOG(jsonName, setter, logCat) \
{ \
	QJSONIMPORT_BOOL(jsonName, setter) \
	else \
	{ \
		qCWarning(logCat, "%s isn't a valid Json Bool", qPrintable(jsonName)); \
	} \
} \

// ───────── STRING ───────────

#define QJSONIMPORT_ISSTRINGVALID(jsonName) QJSONIMPORT_ISVALID(jsonName, String) \

#define QJSONIMPORT_STRING(jsonName, setter) \
	if (QJSONIMPORT_ISSTRINGVALID(jsonName)) \
	{ \
		setter(json[jsonName].toString()); \
	} \

#define QJSONIMPORT_STRING_WLOG(jsonName, setter, logCat) \
{ \
	QJSONIMPORT_STRING(jsonName, setter) \
	else \
	{ \
		qCWarning(logCat, "%s isn't a valid Json String", qPrintable(jsonName)); \
	} \
} \

// ───────── FLOAT ───────────

#define QJSONIMPORT_ISFLOATVALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Double) \

#define QJSONIMPORT_FLOAT(jsonName, setter) \
	if (QJSONIMPORT_ISFLOATVALID(jsonName)) \
	{ \
		setter((float)(json[jsonName].toDouble())); \
	} \

#define QJSONIMPORT_FLOAT_WLOG(jsonName, setter, logCat) \
{ \
	QJSONIMPORT_FLOAT(jsonName, setter) \
	else \
	{ \
		qCWarning(logCat, "%s isn't a valid Json Double", qPrintable(jsonName)); \
	} \
} \

// ───────── OBJECT ───────────

#define QJSONIMPORT_ISOBJECTVALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Object)

#define QJSONIMPORT_OBJECT(jsonName, objectDest) \
	if (QJSONIMPORT_ISOBJECTVALID(jsonName)) \
	{ \
		objectDest->JsonRead(json[jsonName].toObject()); \
	} \

#define QJSONIMPORT_OBJECT_WLOG(jsonName, objectDest, logCat) \
{ \
	QJSONIMPORT_OBJECT(jsonName, objectDest) \
	else \
	{ \
		qCWarning(logCat, "%s isn't a valid Json Object", qPrintable(jsonName)); \
	} \
} \


// ───────── ARRAY ───────────

#define QJSONIMPORT_ISARRAYVALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Array) \

QSUPERMACROS_NAMESPACE_START

// ─────────────────────────────────────────────────────────────
//					CLASS
// ─────────────────────────────────────────────────────────────

/** An object that can be export to a json document */
class QSUPERMACROS_API_ QJsonExportable
{
public:
	/** Public virtual Destructor */
	virtual ~QJsonExportable() = default;
	/** Save the object in the filepath.
	 * \return If the save succeed
	 */
	virtual bool JsonSave(const QUrl& filepath);
	/** Dump the object in the json object */
	virtual void JsonWrite(QJsonObject &json) const {};
};

/** An object that can be import from a json document */
class QSUPERMACROS_API_ QJsonImportable
{
public:
	/** Public virtual Destructor */
	virtual ~QJsonImportable() = default;
	/** Load from a Json file. \return If the load was a success */
	virtual bool JsonLoad(const QUrl& filepath);
	/** Inflate from the json object */
	virtual void JsonRead(const QJsonObject &json) {};
};

/** An object that can be import and export to and from json format */
class QSUPERMACROS_API_ QJsonImportExport : public QJsonExportable, public QJsonImportable
{
};

QSUPERMACROS_NAMESPACE_END

#endif
