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
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QUrl>

// Dependencies Header

// Application Header
#include <QSuperMacros.h>

// ─────────────────────────────────────────────────────────────
//					DECLARATION
// ─────────────────────────────────────────────────────────────

// ───────── GLOBAL ───────────
#define QJSONIMPORT_ISVALID(jsonName, jsonType) \
	json.contains(jsonName) && json[jsonName].is##jsonType() \

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
		qCDebug(logCat, "%s isn't a valid Json " #jsonType, qPrintable(jsonName)); \
	} \
}

#define QJSONEXPORT(jsonName, value) \
	json[jsonName] = value; \

// ───────── OBJECT ───────────
#define QJSONIMPORT_ISOBJECTVALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Object) \

#define QJSONIMPORT_OBJECT(jsonName, objectDest) \
	if (QJSONIMPORT_ISOBJECTVALID(jsonName)) \
	{ \
		objectDest->jsonRead(json[jsonName].toObject()); \
	} \

#define QJSONIMPORT_OBJECT_WLOG(jsonName, objectDest, logCat) \
{ \
	QJSONIMPORT_OBJECT(jsonName, objectDest) \
	else \
	{ \
		qCDebug(logCat, "%s isn't a valid Json Object", qPrintable(jsonName)); \
	} \
}

#define QJSONIMPORT_OBJECT_FROMARRAY(object) \
	object->jsonRead(it.toObject());

#define QJSONEXPORT_OBJECT(jsonName, objectSrc) \
{ \
	QJsonObject jsonObj; \
	objectSrc->jsonWrite(jsonObj); \
	json[jsonName] = jsonObj; \
}

// ───────── ARRAY ───────────
#define QJSONIMPORT_ISARRAYVALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Array) \

#define QJSONIMPORT_ARRAY_OBJECT_WLOG(jsonName, logCat, instructions) \
{ \
	if (QJSONIMPORT_ISARRAYVALID(jsonName)) \
	{ \
		QJsonArray arrayObject = json[jsonName].toArray(); \
		for (auto it : arrayObject) \
		{ \
			if (it.isObject()) \
			{ \
				instructions; \
			} \
			else \
			{ \
				qCDebug(logCat, "%s contains a non valid Json Object", qPrintable(jsonName)); \
			} \
		} \
	} \
	else \
	{ \
		qCDebug(logCat, "%s isn't a valid Json Array", qPrintable(jsonName)); \
	} \
}

#define QJSONEXPORT_ARRAY_OBJECT(jsonName, list) \
{ \
	QJsonArray arrayObject; \
	for (auto it : list) \
	{ \
		QJsonObject jsonObject; \
		it->jsonWrite(jsonObject); \
		arrayObject.append(jsonObject); \
	} \
	QJSONEXPORT(jsonName, arrayObject); \
}

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
			qCDebug(logCat, "Cannot convert String to uint64"); \
		} \
		setter(value); \
	} \
	else \
	{ \
		qCDebug(logCat, "%s isn't a valid Json String", qPrintable(jsonName)); \
	} \
}

#define QJSONEXPORT_UINT64(jsonName, value) QJSONEXPORT(jsonName, QString::number(value)) \

// ───────── UINT32 ───────────
#define QJSONIMPORT_ISUINT32VALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Double) \

#define QJSONIMPORT_UINT32(jsonName, setter) QJSONIMPORT(jsonName, setter, quint32, Double) \

#define QJSONIMPORT_UINT32_WLOG(jsonName, setter, logCat) QJSONIMPORT_WLOG(jsonName, setter, quint32, Double, logCat) \

#define QJSONEXPORT_UINT32(jsonName, value) QJSONEXPORT(jsonName, (double) value) \

// ───────── UINT16 ───────────
#define QJSONIMPORT_ISUINT16VALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Double) \

#define QJSONIMPORT_UINT16(jsonName, setter) QJSONIMPORT(jsonName, setter, quint16, Double) \

#define QJSONIMPORT_UINT16_WLOG(jsonName, setter, logCat) QJSONIMPORT_WLOG(jsonName, setter, quint16, Double, logCat) \

#define QJSONEXPORT_UINT16(jsonName, value) QJSONEXPORT(jsonName, (quint16) value) \

// ───────── UINT8 ───────────
#define QJSONIMPORT_ISUINT8VALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Double) \

#define QJSONIMPORT_UINT8(jsonName, setter) QJSONIMPORT(jsonName, setter, quint8, Double) \

#define QJSONIMPORT_UINT8_WLOG(jsonName, setter, logCat) QJSONIMPORT_WLOG(jsonName, setter, quint8, Double, logCat) \

#define QJSONEXPORT_UINT8(jsonName, value) QJSONEXPORT(jsonName, (quint8) value) \

// ───────── UINT ───────────
#define QJSONIMPORT_ISUINTVALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Double) \

#define QJSONIMPORT_UINT(jsonName, setter) QJSONIMPORT(jsonName, setter, quint, Double) \

#define QJSONIMPORT_UINT_WLOG(jsonName, setter, logCat) QJSONIMPORT_WLOG(jsonName, setter, quint, Double, logCat) \

#define QJSONEXPORT_UINT(jsonName, value) QJSONEXPORT(jsonName, (quint) value) \

// ───────── INT64 ───────────
#define QJSONIMPORT_ISINT64VALID(jsonName) QJSONIMPORT_ISVALID(jsonName, String) \

#define QJSONIMPORT_INT64(jsonName, setter) \
	if (QJSONIMPORT_ISINT64VALID(jsonName)) \
	{ \
		setter(json[jsonName].toString.toLongLong()); \
	} \

#define QJSONIMPORT_INT64_WLOG(jsonName, setter, logCat) \
{ \
	if (QJSONIMPORT_ISINT64VALID(jsonName)) \
	{ \
		bool stringValid = false; \
		qint64 value = json[jsonName].toString().toLongLong(&stringValid); \
		if (!stringValid) \
		{ \
			qCDebug(logCat, "Cannot convert String to int64"); \
		} \
		setter(value); \
	} \
	else \
	{ \
		qCDebug(logCat, "%s isn't a valid Json String", qPrintable(jsonName)); \
	} \
}

#define QJSONEXPORT_INT64(jsonName, value) QJSONEXPORT(jsonName, QString::number(value)) \

// ───────── INT32 ───────────
#define QJSONIMPORT_ISINT32VALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Double) \

#define QJSONIMPORT_INT32(jsonName, setter) QJSONIMPORT(jsonName, setter, qint32, Double) \

#define QJSONIMPORT_INT32_WLOG(jsonName, setter, logCat) QJSONIMPORT_WLOG(jsonName, setter, qint32, Double, logCat) \

#define QJSONEXPORT_INT32(jsonName, value) QJSONEXPORT(jsonName, (qint32) value) \

// ───────── INT16 ───────────
#define QJSONIMPORT_ISINT16VALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Double) \

#define QJSONIMPORT_INT16(jsonName, setter) QJSONIMPORT(jsonName, setter, qint16, Double) \

#define QJSONIMPORT_INT16_WLOG(jsonName, setter, logCat) QJSONIMPORT_WLOG(jsonName, setter, qint16, Double, logCat) \

#define QJSONEXPORT_INT16(jsonName, value) QJSONEXPORT(jsonName, (qint16) value) \

// ───────── INT8 ───────────
#define QJSONIMPORT_ISINT8VALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Double) \

#define QJSONIMPORT_INT8(jsonName, setter) QJSONIMPORT(jsonName, setter, qint8, Double) \

#define QJSONIMPORT_INT8_WLOG(jsonName, setter, logCat) QJSONIMPORT_WLOG(jsonName, setter, qint8, Double, logCat) \

#define QJSONEXPORT_INT8(jsonName, value) QJSONEXPORT(jsonName, (qint8) value) \

// ───────── INT ───────────
#define QJSONIMPORT_ISINTVALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Double) \

#define QJSONIMPORT_INT(jsonName, setter) QJSONIMPORT(jsonName, setter, int, Double) \

#define QJSONIMPORT_INT_WLOG(jsonName, setter, logCat) QJSONIMPORT_WLOG(jsonName, setter, int, Double, logCat) \

#define QJSONEXPORT_INT(jsonName, value) QJSONEXPORT(jsonName, (int) value) \

// ───────── BOOL ───────────
#define QJSONIMPORT_ISBOOLVALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Bool) \

#define QJSONIMPORT_BOOL(jsonName, setter) QJSONIMPORT(jsonName, setter, bool, Bool) \

#define QJSONIMPORT_BOOL_WLOG(jsonName, setter, logCat) QJSONIMPORT_WLOG(jsonName, setter, bool, Bool, logCat) \

#define QJSONEXPORT_BOOL(jsonName, value) QJSONEXPORT(jsonName, (bool) value) \

// ───────── STRING ───────────
#define QJSONIMPORT_ISSTRINGVALID(jsonName) QJSONIMPORT_ISVALID(jsonName, String) \

#define QJSONIMPORT_STRING(jsonName, setter) QJSONIMPORT(jsonName, setter, QString, String) \

#define QJSONIMPORT_STRING_WLOG(jsonName, setter, logCat) QJSONIMPORT_WLOG(jsonName, setter, QString, String, logCat) \

#define QJSONEXPORT_STRING(jsonName, value) QJSONEXPORT(jsonName, (QString) value) \

// ───────── FLOAT ───────────
#define QJSONIMPORT_ISFLOATVALID(jsonName) QJSONIMPORT_ISVALID(jsonName, Double) \

#define QJSONIMPORT_FLOAT(jsonName, setter) QJSONIMPORT(jsonName, setter, float, Double) \

#define QJSONIMPORT_FLOAT_WLOG(jsonName, setter, logCat) QJSONIMPORT_WLOG(jsonName, setter, float, Double, logCat) \

#define QJSONEXPORT_FLOAT(jsonName, value) QJSONEXPORT(jsonName, (float) value) \


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
protected:
	bool dataSave(const QUrl& filepath, const bool fromJson = true) const;
public:
	/** Save the object in the filepath.
	 * \return If the save succeed
	 */
	virtual bool jsonSave(const QUrl& filepath) const;
	/** Save the object in the filepath. \return If the save succeed */
	virtual bool binarySave(const QUrl& filepath) const;
	/** Dump the object in the json object */
	virtual void jsonWrite(QJsonObject &json) const {};
};

/** An object that can be import from a json document */
class QSUPERMACROS_API_ QJsonImportable
{
public:
	/** Public virtual Destructor */
	virtual ~QJsonImportable() = default;
protected:
	/** Real loader function */
	bool dataLoad(const QUrl& filepath, const bool fromJson = true);
public:
	/** Load from a Json file. \return If the load was a success */
	virtual bool jsonLoad(const QUrl& filepath);
	/** Load from a json binary file (very fast) \return if the load was a success */
	virtual bool binaryLoad(const QUrl& filepath);
	/** Inflate from the json object */
	virtual void jsonRead(const QJsonObject &json) {};
};

/** An object that can be import and export to and from json format */
class QSUPERMACROS_API_ QJsonImportExport : public QJsonExportable, public QJsonImportable
{
};

QSUPERMACROS_NAMESPACE_END

#endif
