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
