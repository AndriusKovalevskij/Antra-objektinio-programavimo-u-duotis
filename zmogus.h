#ifndef ZMOGUS_H_INCLUDED
#define ZMOGUS_H_INCLUDED

#include <string>
#include <iostream>

// Abstrakti bazine klase
class Zmogus {
protected:
    std::string vardas_;
    std::string pavarde_;

    public:
    // Konstruktoriai
    Zmogus();  // Default konstruktorius
    Zmogus(const std::string& vardas, const std::string& pavarde);  // Konstruktorius su parametrais
    Zmogus(const Zmogus& other);  // Copy konstruktorius

    // Virtualus destruktorius
    virtual ~Zmogus();

#endif // ZMOGUS_H_INCLUDED
