// ─────────────────────────────────────────────────────────────
//					INCLUDE
// ─────────────────────────────────────────────────────────────

#include <QJsonImportExport.h>

// ─────────────────────────────────────────────────────────────
//					DECLARATION
// ─────────────────────────────────────────────────────────────

QSUPERMACROS_USING_NAMESPACE;

// ─────────────────────────────────────────────────────────────
//					FUNCTIONS
// ─────────────────────────────────────────────────────────────

bool QJsonExportable::dataSave(const QUrl& filepath, const bool fromJson) const
{
	QFile saveFile(filepath.toLocalFile());

	if (!saveFile.open(QIODevice::WriteOnly))
	{
		qWarning("Couldn't open Json save file.");
		return false;
	}

	QJsonObject jsonObject;
	jsonWrite(jsonObject);
	QJsonDocument saveDoc(jsonObject);
	saveFile.write(fromJson ? saveDoc.toJson() : saveDoc.toBinaryData());

	return true;
}

bool QJsonExportable::jsonSave(const QUrl& filepath) const
{
	return dataSave(filepath, true);
}

bool QJsonExportable::binarySave(const QUrl& filepath) const
{
	return dataSave(filepath, false);
}

bool QJsonImportable::dataLoad(const QUrl& filepath, const bool fromJson)
{
	QFile loadFile(filepath.toLocalFile());

	if (!loadFile.open(QIODevice::ReadOnly))
	{
		qWarning("Couldn't open Json file to load.");
		return false;
	}

	const QByteArray saveData = loadFile.readAll();
	QJsonDocument loadDoc(fromJson ? QJsonDocument::fromJson(saveData) : QJsonDocument::fromBinaryData(saveData));
	jsonRead(loadDoc.object());

	return true;
}

bool QJsonImportable::jsonLoad(const QUrl& filepath)
{
	return dataLoad(filepath, true);
}

bool QJsonImportable::binaryLoad(const QUrl& filepath)
{
	return dataLoad(filepath, false);
}
