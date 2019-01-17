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

bool QJsonExportable::JsonSave(const QUrl& filepath)
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
	saveFile.write(saveDoc.toJson());

	return true;
}

bool QJsonImportable::JsonLoad(const QUrl& filepath)
{
	QFile loadFile(filepath.toLocalFile());

	if (!loadFile.open(QIODevice::ReadOnly))
	{
		qWarning("Couldn't open Json file to load.");
		return false;
	}

	const QByteArray saveData = loadFile.readAll();
	QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
	JsonRead(loadDoc.object());

	return true;
}
