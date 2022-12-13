#include "readerdisplayer.h"
//#include <QDebug>

ReaderDisplayer::ReaderDisplayer(QObject *parent) : QObject(parent)
{

}

void ReaderDisplayer::setDataModel(const std::vector<ParsedObject> &modelData)
{
    QVariantList _country;
    QVariantList _Mfr_CommonName;
    QVariantList _Mfr_ID;
    QVariantList _Mfr_Name;

    for(const auto &data: modelData){
        _country.append(QString::fromStdString(data.country()));
        _Mfr_CommonName.append(QString::fromStdString(data.getMfr_CommonName()));
        _Mfr_ID.append(data.getMfr_ID());
        _Mfr_Name.append(QString::fromStdString(data.getMfr_Name()));
    }

    setCountry(_country);
    setMfr_CommonName(_Mfr_CommonName);
    setMfr_ID(_Mfr_ID);
    setMfr_Name(_Mfr_Name);
}

const QVariantList &ReaderDisplayer::country() const
{
    return m_country;
}

void ReaderDisplayer::setCountry(const QVariantList &newCountry)
{
    if (m_country == newCountry)
        return;

    m_country = newCountry;
    emit countryChanged();
}

const QVariantList &ReaderDisplayer::Mfr_CommonName() const
{
    return m_Mfr_CommonName;
}

void ReaderDisplayer::setMfr_CommonName(const QVariantList &newMfr_CommonName)
{
    if (m_Mfr_CommonName == newMfr_CommonName)
        return;

    m_Mfr_CommonName = newMfr_CommonName;
    emit Mfr_CommonNameChanged();
}

QVariantList ReaderDisplayer::Mfr_ID() const
{
    return m_Mfr_ID;
}

void ReaderDisplayer::setMfr_ID(QVariantList newMfr_ID)
{
    if (m_Mfr_ID == newMfr_ID)
        return;

    m_Mfr_ID = newMfr_ID;
    emit Mfr_IDChanged();
}

const QVariantList &ReaderDisplayer::Mfr_Name() const
{
    return m_Mfr_Name;
}

void ReaderDisplayer::setMfr_Name(const QVariantList &newMfr_Name)
{
    if (m_Mfr_Name == newMfr_Name)
        return;

    m_Mfr_Name = newMfr_Name;
    emit Mfr_NameChanged();
}
