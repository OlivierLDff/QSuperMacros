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

QSUPERMACROS_NAMESPACE_START

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
