#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

// Studentas - isvestine klase is Zmogus
class Studentas : public Zmogus {
private:
    std::vector<int> ndpazymiai_;
    int egzrezultatas_;
    double galutinis_vidurkis_;
    double galutine_mediana_;


public:
    // Konstruktoriai
    Studentas();  // Default konstruktorius
    Studentas(std::istream& is);  // Konstruktorius skaitymas is srauto
    Studentas(const std::string& vardas, const std::string& pavarde);  // Konstruktorius su parametrais
    Studentas(const Studentas& other);  // Copy konstruktorius

    // Destruktorius (override bazines klases)
    ~Studentas() override;

    // Operatoriai
    Studentas& operator=(const Studentas& other);  // Copy assignment

    // Get'eriai (inline, const)
    inline const std::vector<int>& ndPazymiai() const { return ndpazymiai_; }
    inline int egzRezultatas() const { return egzrezultatas_; }
    inline double galutinisVidurkis() const { return galutinis_vidurkis_; }
    inline double galutineMediana() const { return galutine_mediana_; }

    // Set'eriai
    void setEgzRezultatas(int egz) { egzrezultatas_ = egz; }
    void addNdPazymys(int pazymys) { ndpazymiai_.push_back(pazymys); }
    void setNdPazymiai(const std::vector<int>& pazymiai) { ndpazymiai_ = pazymiai; }

    // Galutinio balo skaiciavimas
    double galBalas(double (*skaiciavimas)(const std::vector<int>&)) const;

    // Implementacija virtualiu metodu is bazines klases
    std::istream& skaityti(std::istream& is) override;
    std::ostream& spausdinti(std::ostream& os) const override;

    // Backward compatibility metodai (naudoja naujus override metodus)
    std::istream& readStudent(std::istream& is);
    std::ostream& writeStudent(std::ostream& os) const;

    // Override info metodas
    void info() const override;

    // Metodas skaiciuoti galutinius balus
    void skaiciuotiGalutini();

    // Friend operatoriai
    friend std::ostream& operator<<(std::ostream& os, const Studentas& s);
    friend std::istream& operator>>(std::istream& is, Studentas& s);
};

// Palyginimo funkcijos
bool compare(const Studentas& a, const Studentas& b);
bool comparePagalVarda(const Studentas& a, const Studentas& b);
bool comparePagalPavarde(const Studentas& a, const Studentas& b);
bool comparePagalVidurki(const Studentas& a, const Studentas& b);
bool comparePagalMediana(const Studentas& a, const Studentas& b);

// Pagalbines funkcijos skaiciavimams
double vidurkis(const std::vector<int>& pazymiai);
double mediana(const std::vector<int>& pazymiai);

#endif // STUDENT_H_INCLUDED
