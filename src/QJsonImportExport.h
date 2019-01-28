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

// ───────── GLOBAL ───────────
#define QJSONIMPORT_ISVALID(jsonName, jsonType) json.contains(jsonName) && json[jsonName].is##jsonType() \

#define QJSONIMPORT(jsonName, setter, type, jsonType) \
	if (QJSONIMPORT_ISVALID(jsonName, jsonType)) \
	{ \
		setter((type)(json[jsonName].to##jsonType())); \
	} \

#define QJSONIMPORT_WLOG(jsonName, setter, type, jsonType, logCat) \
{ \
	QJSONIMPORT(jsonName, setter, type, jsonType) \
	else \
	{ \
		qCWarning(logCat, "%s isn't a valid Json " #jsonType, qPrintable(jsonName)); \
	} \
} \

// ───────── OBJECT ───────────
#define QJSONIMPORT_ISOBJECTVALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Object) \

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
			qCWarning(logCat, "Cannot convert String to uint64"); \
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

#define QJSONIMPORT_UINT32(jsonName, setter) QJSONIMPORT(jsonName, setter, quint32, Double) \

#define QJSONIMPORT_UINT32_WLOG(jsonName, setter, logCat) QJSONIMPORT_WLOG(jsonName, setter, quint32, Double, logCat) \

// ───────── UINT16 ───────────
#define QJSONIMPORT_ISUINT16VALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Double) \

#define QJSONIMPORT_UINT16(jsonName, setter) QJSONIMPORT(jsonName, setter, quint16, Double) \

#define QJSONIMPORT_UINT16_WLOG(jsonName, setter, logCat) QJSONIMPORT_WLOG(jsonName, setter, quint16, Double, logCat) \

// ───────── UINT8 ───────────
#define QJSONIMPORT_ISUINT8VALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Double) \

#define QJSONIMPORT_UINT8(jsonName, setter) QJSONIMPORT(jsonName, setter, quint8, Double) \

#define QJSONIMPORT_UINT8_WLOG(jsonName, setter, logCat) QJSONIMPORT_WLOG(jsonName, setter, quint8, Double, logCat) \

// ───────── UINT ───────────
#define QJSONIMPORT_ISUINTVALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Double) \

#define QJSONIMPORT_UINT(jsonName, setter) QJSONIMPORT(jsonName, setter, quint, Double) \

#define QJSONIMPORT_UINT_WLOG(jsonName, setter, logCat) QJSONIMPORT_WLOG(jsonName, setter, quint, Double, logCat) \

// ───────── INT64 ───────────
#define QJSONIMPORT_ISUINT64VALID(jsonName) QJSONIMPORT_ISVALID(jsonName, String) \

#define QJSONIMPORT_UINT64(jsonName, setter) \
	if (QJSONIMPORT_ISUINT64VALID(jsonName)) \
	{ \
		setter(json[jsonName].toString.toLongLong()); \
	} \

#define QJSONIMPORT_UINT64_WLOG(jsonName, setter, logCat) \
{ \
	if (QJSONIMPORT_ISUINT64VALID(jsonName)) \
	{ \
		bool stringValid = false; \
		qint64 value = json[jsonName].toString().toLongLong(&stringValid); \
		if (!stringValid) \
		{ \
			qCWarning(logCat, "Cannot convert String to int64"); \
		} \
		setter(value); \
	} \
	else \
	{ \
		qCWarning(logCat, "%s isn't a valid Json String", qPrintable(jsonName)); \
	} \
} \

// ───────── INT32 ───────────
#define QJSONIMPORT_ISINT32VALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Double) \

#define QJSONIMPORT_INT32(jsonName, setter) QJSONIMPORT(jsonName, setter, qint32, Double) \

#define QJSONIMPORT_INT32_WLOG(jsonName, setter, logCat) QJSONIMPORT_WLOG(jsonName, setter, qint32, Double, logCat) \

// ───────── INT16 ───────────
#define QJSONIMPORT_ISINT16VALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Double) \

#define QJSONIMPORT_INT16(jsonName, setter) QJSONIMPORT(jsonName, setter, qint16, Double) \

#define QJSONIMPORT_INT16_WLOG(jsonName, setter, logCat) QJSONIMPORT_WLOG(jsonName, setter, qint16, Double, logCat) \

// ───────── INT8 ───────────
#define QJSONIMPORT_ISINT8VALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Double) \

#define QJSONIMPORT_INT8(jsonName, setter) QJSONIMPORT(jsonName, setter, qint8, Double) \

#define QJSONIMPORT_INT8_WLOG(jsonName, setter, logCat) QJSONIMPORT_WLOG(jsonName, setter, qint8, Double, logCat) \

// ───────── INT ───────────
#define QJSONIMPORT_ISINTVALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Double) \

#define QJSONIMPORT_INT(jsonName, setter) QJSONIMPORT(jsonName, setter, int, Double) \

#define QJSONIMPORT_INT_WLOG(jsonName, setter, logCat) QJSONIMPORT_WLOG(jsonName, setter, int, Double, logCat) \

// ───────── BOOL ───────────
#define QJSONIMPORT_ISBOOLVALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Bool) \

#define QJSONIMPORT_BOOL(jsonName, setter) QJSONIMPORT(jsonName, setter, bool, Bool) \

#define QJSONIMPORT_BOOL_WLOG(jsonName, setter, logCat) QJSONIMPORT_WLOG(jsonName, setter, bool, Bool, logCat) \

// ───────── STRING ───────────
#define QJSONIMPORT_ISSTRINGVALID(jsonName) QJSONIMPORT_ISVALID(jsonName, String) \

#define QJSONIMPORT_STRING(jsonName, setter) QJSONIMPORT(jsonName, setter, QString, String) \

#define QJSONIMPORT_STRING_WLOG(jsonName, setter, logCat) QJSONIMPORT_WLOG(jsonName, setter, QString, String, logCat) \

// ───────── FLOAT ───────────
#define QJSONIMPORT_ISFLOATVALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Double) \

#define QJSONIMPORT_FLOAT(jsonName, setter) QJSONIMPORT(jsonName, setter, float, Double) \

#define QJSONIMPORT_FLOAT_WLOG(jsonName, setter, logCat) QJSONIMPORT_WLOG(jsonName, setter, float, Double, logCat) \


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
