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

bool QJsonExportable::DataSave(const QUrl& filepath, const bool fromJson) const
{
	QFile saveFile(filepath.toLocalFile());

	if (!saveFile.open(QIODevice::WriteOnly))
	{
		qWarning("Couldn't open Json save file.");
		return false;
	}

	QJsonObject jsonObject;
	JsonWrite(jsonObject);
	QJsonDocument saveDoc(jsonObject);
	saveFile.write(fromJson ? saveDoc.toJson() : saveDoc.toBinaryData());

	return true;
}

bool QJsonExportable::JsonSave(const QUrl& filepath)
{
	return DataSave(filepath, true);
}

bool QJsonExportable::BinarySave(const QUrl& filepath)
{
	return DataSave(filepath, false);
}

bool QJsonImportable::DataLoad(const QUrl& filepath, const bool fromJson)
{
	QFile loadFile(filepath.toLocalFile());

	if (!loadFile.open(QIODevice::ReadOnly))
	{
		qWarning("Couldn't open Json file to load.");
		return false;
	}

	const QByteArray saveData = loadFile.readAll();
	QJsonDocument loadDoc(fromJson ? QJsonDocument::fromJson(saveData) : QJsonDocument::fromBinaryData(saveData));
	JsonRead(loadDoc.object());

	return true;
}

bool QJsonImportable::JsonLoad(const QUrl& filepath)
{
	return DataLoad(filepath, true);
}

bool QJsonImportable::BinaryLoad(const QUrl& filepath)
{
	return DataLoad(filepath, false);
}
