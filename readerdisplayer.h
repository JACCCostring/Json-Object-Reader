#ifndef READERDISPLAYER_H
#define READERDISPLAYER_H

#include <QObject>
#include <QVariantList>

#include "parsedobject.h"

class ReaderDisplayer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantList country READ country WRITE setCountry NOTIFY countryChanged)
    Q_PROPERTY(QVariantList Mfr_CommonName READ Mfr_CommonName WRITE setMfr_CommonName NOTIFY Mfr_CommonNameChanged)
    Q_PROPERTY(QVariantList Mfr_ID READ Mfr_ID WRITE setMfr_ID NOTIFY Mfr_IDChanged)
    Q_PROPERTY(QVariantList Mfr_Name READ Mfr_Name WRITE setMfr_Name NOTIFY Mfr_NameChanged)

public:
    explicit ReaderDisplayer(QObject *parent = nullptr);
    //method for setting data for the model in QML
    void setDataModel(const std::vector<ParsedObject> &);

//    getters and setters
    const QVariantList &country() const;

    const QVariantList &Mfr_CommonName() const;

    QVariantList Mfr_ID() const;

    const QVariantList &Mfr_Name() const;

private:

    void setCountry(const QVariantList &newCountry);

    void setMfr_CommonName(const QVariantList &newMfr_CommonName);

    void setMfr_ID(QVariantList newMfr_ID);

    void setMfr_Name(const QVariantList &newMfr_Name);

private:
signals:
    void countryChanged();
    void Mfr_CommonNameChanged();
    void Mfr_IDChanged();
    void Mfr_NameChanged();

private:
    QVariantList m_country;
    QVariantList m_Mfr_CommonName;
    QVariantList m_Mfr_ID;
    QVariantList m_Mfr_Name;
};

#endif // READERDISPLAYER_H
