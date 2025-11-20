#include "student.h"
#include <sstream>

// Default konstruktorius
Studentas::Studentas()
    : vardas_(""), pavarde_(""), egzrezultatas_(0),
      galutinis_vidurkis_(0.0), galutine_mediana_(0.0) {
}

// Konstruktorius su srauto skaitymu
Studentas::Studentas(std::istream& is)
    : egzrezultatas_(0), galutinis_vidurkis_(0.0), galutine_mediana_(0.0) {
    readStudent(is);
}

// Konstruktorius su parametrais
Studentas::Studentas(const std::string& vardas, const std::string& pavarde)
    : vardas_(vardas), pavarde_(pavarde), egzrezultatas_(0),
      galutinis_vidurkis_(0.0), galutine_mediana_(0.0) {
}

// Copy konstruktorius
Studentas::Studentas(const Studentas& other)
    : vardas_(other.vardas_), pavarde_(other.pavarde_),
      ndpazymiai_(other.ndpazymiai_), egzrezultatas_(other.egzrezultatas_),
      galutinis_vidurkis_(other.galutinis_vidurkis_),
      galutine_mediana_(other.galutine_mediana_) {
}

Studentas::~Studentas() {
    vardas_.clear();
    pavarde_.clear();
    egzrezultatas_ = 0;
    galutinis_vidurkis_ = 0;
    galutine_mediana_ = 0;
}


// Copy assignment
Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) {
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;
        ndpazymiai_ = other.ndpazymiai_;
        egzrezultatas_ = other.egzrezultatas_;
        galutinis_vidurkis_ = other.galutinis_vidurkis_;
        galutine_mediana_ = other.galutine_mediana_;
    }
    return *this;
}


// Galutinio balo skaiciavimas
double Studentas::galBalas(double (*skaiciavimas)(const std::vector<int>&)) const {
    if (ndpazymiai_.empty()) {
        return egzrezultatas_ * 0.6;
    }

    double nd_balas = skaiciavimas(ndpazymiai_);
    return nd_balas * 0.4 + egzrezultatas_ * 0.6;
}

// Skaitymas is srauto (readStudent)
std::istream& Studentas::readStudent(std::istream& is) {
    is >> vardas_ >> pavarde_;

    int pazymys;
    std::vector<int> visi_pazymiai;

    while (is >> pazymys) {
        if (pazymys >= 1 && pazymys <= 10) {
            visi_pazymiai.push_back(pazymys);
        }
    }

    // Paskutinis - egzaminas
    if (!visi_pazymiai.empty()) {
        egzrezultatas_ = visi_pazymiai.back();
        visi_pazymiai.pop_back();
        ndpazymiai_ = visi_pazymiai;
    }

    skaiciuotiGalutini();

    return is;
}

// Isvedimas i srauta (writeStudent)
std::ostream& Studentas::writeStudent(std::ostream& os) const {
    os << vardas_ << " " << pavarde_ << " (Vid: "
       << galutinis_vidurkis_ << ", Med: " << galutine_mediana_ << ")";
    return os;
}

// Galutiniu balu skaiciavimas
void Studentas::skaiciuotiGalutini() {
    if (ndpazymiai_.empty()) {
        galutinis_vidurkis_ = egzrezultatas_ * 0.6;
        galutine_mediana_ = egzrezultatas_ * 0.6;
        return;
    }

    double suma = std::accumulate(ndpazymiai_.begin(), ndpazymiai_.end(), 0.0);
    galutinis_vidurkis_ = (suma / ndpazymiai_.size()) * 0.4 + egzrezultatas_ * 0.6;

    galutine_mediana_ = galBalas(mediana);
}

// Isvedimo operatorius
std::ostream& operator<<(std::ostream& os, const Studentas& s) {
    return s.writeStudent(os);
}

// Ivedimo operatorius
std::istream& operator>>(std::istream& is, Studentas& s) {
    return s.readStudent(is);
}


bool compare(const Studentas& a, const Studentas& b) {
    return a.vardas() < b.vardas();
}

bool comparePagalVarda(const Studentas& a, const Studentas& b) {
    return a.vardas() < b.vardas();
}

bool comparePagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde() < b.pavarde();
}

bool comparePagalVidurki(const Studentas& a, const Studentas& b) {
    return a.galutinisVidurkis() < b.galutinisVidurkis();
}

bool comparePagalMediana(const Studentas& a, const Studentas& b) {
    return a.galutineMediana() < b.galutineMediana();
}

// Vidurkio skaiciavimas
double vidurkis(const std::vector<int>& pazymiai) {
    if (pazymiai.empty()) return 0.0;
    double suma = std::accumulate(pazymiai.begin(), pazymiai.end(), 0.0);
    return suma / pazymiai.size();
}

// Medianos skaiciavimas
double mediana(const std::vector<int>& pazymiai) {
    if (pazymiai.empty()) return 0.0;

    std::vector<int> temp = pazymiai;
    std::sort(temp.begin(), temp.end());

    size_t dydis = temp.size();
    if (dydis % 2 == 0) {
        return (temp[dydis/2 - 1] + temp[dydis/2]) / 2.0;
    } else {
        return temp[dydis/2];
    }
}
