#include "restmanager.h"
#include "./curlProject/FileManager.h" //when data done then storage it in a file

RESTManager::RESTManager(QObject *parent) : QObject(parent)
{

}

void RESTManager::setURL(const QString &newUrl)
{
    RESTUrl = newUrl;
}

void RESTManager::downloadData()
{
    QNetworkAccessManager *m = new QNetworkAccessManager(this);
    m->get(QNetworkRequest(QUrl(RESTUrl)));

    connect(m, &QNetworkAccessManager::finished, this, &RESTManager::onDataDownloaded);
}

void RESTManager::onDataDownloaded(QNetworkReply *replyDone)
{
    parsedData = replyDone->readAll();

    FileManager fManager("/Users/f1r3544/MyProject/QT Test/Object-Reader/example.txt", FileType::WRITE);
    fManager << parsedData.toStdString(); //storage parsed data into the file
}

void operator >> (const RESTManager &ownClass, QByteArray &o){
    o = ownClass.parsedData;
}
