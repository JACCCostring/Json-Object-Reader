#include "./curlProject/FileManager.h" //for file handling
#include "reader.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


Reader::Reader(QObject *parent) : QObject(parent)
{
    rManager.setURL("https://vpic.nhtsa.dot.gov/api/vehicles/getallmanufacturers?format=json");
    rManager.downloadData(); //downloading at start so data its ready when need it

    readerDisplayer = new ReaderDisplayer(this); //init... displayer
}

void Reader::openFile(const QVariant &file)
{
    QString filePath = QUrl(file.toString()).toLocalFile();

    FileManager fManager(filePath.toStdString(), FileType::READ);

    std::string standardString;

    fManager >> standardString;

    std::vector<ParsedObject> cObjects = parseData(QString::fromStdString(standardString).toUtf8());
    readerDisplayer->setDataModel(cObjects); //it can apply to model subclassing AbstractModel and so
    modelSize = cObjects.size(); //getting size of container
}

std::vector<ParsedObject> Reader::parseData(const QByteArray &JSONdata)
{
    std::vector<ParsedObject> containerParsedObjects;

    QJsonDocument JSONDoc = QJsonDocument::fromJson(JSONdata);

    QJsonObject JSONObject = JSONDoc.object();

    QJsonValue JSONValue = JSONObject.value("Results");

    QJsonArray JSSONArray = JSONValue.toArray();

    for(const auto &values: qAsConst(JSSONArray)){
        ParsedObject object;

        object.setCountry(values.toObject().value("Country").toString().toStdString());
        object.setMfr_CommonName(values.toObject().value("Mfr_CommonName").toString().toStdString());
        object.setMfr_ID(values.toObject().value("Mfr_ID").toInt());
        object.setMfr_CommonName(values.toObject().value("Mfr_Name").toString().toStdString());

        containerParsedObjects.push_back(object);
    }

    return containerParsedObjects;
}

ReaderDisplayer &Reader::getDataModel()
{
    return *readerDisplayer;
}

int Reader::getModelDataSize() const
{
    return modelSize;
}

QVariantList Reader::getCountry()
{
    return getDataModel().country();
}

QVariantList Reader::getID()
{
    return getDataModel().Mfr_ID();
}

QVariantList Reader::getName()
{
    return getDataModel().Mfr_CommonName();
}
