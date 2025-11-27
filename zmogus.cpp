#include "zmogus.h"

// Default konstruktorius
Zmogus::Zmogus() : vardas_(""), pavarde_("") {
}

// Konstruktorius su parametrais
Zmogus::Zmogus(const std::string& vardas, const std::string& pavarde)
    : vardas_(vardas), pavarde_(pavarde) {
}

// Copy konstruktorius
Zmogus::Zmogus(const Zmogus& other)
    : vardas_(other.vardas_), pavarde_(other.pavarde_) {
}

// Virtualus destruktorius
Zmogus::~Zmogus() {
    vardas_.clear();
    pavarde_.clear();
}

// Copy assignment operatorius
Zmogus& Zmogus::operator=(const Zmogus& other) {
    if (this != &other) {
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;
    }
    return *this;
}

// Virtualus metodas su implementacija
void Zmogus::info() const {
    std::cout << "Zmogus: " << vardas_ << " " << pavarde_ << std::endl;
}
