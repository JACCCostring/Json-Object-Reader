#include "parsedobject.h"

ParsedObject::ParsedObject()
{

}

const std::string &ParsedObject::country() const
{
    return _country;
}

const std::string &ParsedObject::getMfr_CommonName() const
{
    return Mfr_CommonName;
}

const int &ParsedObject::getMfr_ID() const
{
    return Mfr_ID;
}

const std::string &ParsedObject::getMfr_Name() const
{
    return Mfr_Name;
}

void ParsedObject::setCountry(const std::string &newCountry)
{
    _country = newCountry;
}

void ParsedObject::setMfr_CommonName(const std::string &newMfr_CommonName)
{
    Mfr_CommonName = newMfr_CommonName;
}

void ParsedObject::setMfr_ID(int newMfr_ID)
{
    Mfr_ID = newMfr_ID;
}

void ParsedObject::setMfr_Name(const std::string &newMfr_Name)
{
    Mfr_Name = newMfr_Name;
}
