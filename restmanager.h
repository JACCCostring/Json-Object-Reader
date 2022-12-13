#ifndef RESTMANAGER_H
#define RESTMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class RESTManager : public QObject
{
    Q_OBJECT
public:
    explicit RESTManager(QObject *parent = nullptr);
    //methods
    void setURL(const QString &);
    void downloadData();

    friend void operator >> (const RESTManager &, QByteArray &);

private slots:
    void onDataDownloaded(QNetworkReply *);

private:
    QString RESTUrl;

    QByteArray parsedData; //for parsed data
};

#endif // RESTMANAGER_H
