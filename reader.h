#ifndef READER_H
#define READER_H

#include <QObject>

#include "restmanager.h" //for REST API handling
#include "parsedobject.h"
#include "readerdisplayer.h" //for data model

class Reader : public QObject
{
    Q_OBJECT
public:
    explicit Reader(QObject *parent = nullptr);
    //method to be invoked from QML
    Q_INVOKABLE void openFile(const QVariant &);
    Q_INVOKABLE int getModelDataSize() const;
    //all getters to get data from the model... since it can not be access from QML
    Q_INVOKABLE QVariantList getCountry();
    Q_INVOKABLE QVariantList getID();
    Q_INVOKABLE QVariantList getName();

private:
    ReaderDisplayer& getDataModel(); //method for recovering model's data
    std::vector<ParsedObject> parseData(const QByteArray &); //method for parsing data

private:
    RESTManager rManager;
    ReaderDisplayer *readerDisplayer;
//    QByteArray JSONdata;
    int modelSize;
};

#endif // READER_H
