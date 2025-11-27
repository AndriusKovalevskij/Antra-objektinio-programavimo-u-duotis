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

    // Copy assignment operatorius
    Zmogus& operator=(const Zmogus& other);

    // Get'eriai (inline, const)
    inline std::string vardas() const { return vardas_; }
    inline std::string pavarde() const { return pavarde_; }

    // Set'eriai
    void setVardas(const std::string& vardas) { vardas_ = vardas; }
    void setPavarde(const std::string& pavarde) { pavarde_ = pavarde; }

    // Virtualus metodai (daro klase abstrakcia)
    virtual std::istream& skaityti(std::istream& is) = 0;
    virtual std::ostream& spausdinti(std::ostream& os) const = 0;

    // Virtualus metodas su implementacija
    virtual void info() const;
};

#endif // ZMOGUS_H_INCLUDED
