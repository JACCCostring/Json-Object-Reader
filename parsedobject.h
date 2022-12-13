#ifndef PARSEDOBJECT_H
#define PARSEDOBJECT_H

#include <string>

class ParsedObject
{
public:
    ParsedObject();
//    getters
    const std::string &country() const;

    const std::string &getMfr_CommonName() const;

    const int &getMfr_ID() const;

    const std::string &getMfr_Name() const;
//    setters
    void setCountry(const std::string &newCountry);

    void setMfr_CommonName(const std::string &newMfr_CommonName);

    void setMfr_ID(int newMfr_ID);

    void setMfr_Name(const std::string &newMfr_Name);

private:
    std::string _country;
    std::string Mfr_CommonName;
    int Mfr_ID;
    std::string Mfr_Name;
};

#endif // PARSEDOBJECT_H
