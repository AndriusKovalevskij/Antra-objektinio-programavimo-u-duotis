#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
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

    // Destruktorius
    ~Studentas();

    // Operatoriai
    Studentas& operator=(const Studentas& other);  // Copy assignment

    // Get'eriai (inline, const)
    inline std::string vardas() const { return vardas_; }
    inline std::string pavarde() const { return pavarde_; }
    inline const std::vector<int>& ndPazymiai() const { return ndpazymiai_; }
    inline int egzRezultatas() const { return egzrezultatas_; }
    inline double galutinisVidurkis() const { return galutinis_vidurkis_; }
    inline double galutineMediana() const { return galutine_mediana_; }

    // Set'eriai
    void setVardas(const std::string& vardas) { vardas_ = vardas; }
    void setPavarde(const std::string& pavarde) { pavarde_ = pavarde; }
    void setEgzRezultatas(int egz) { egzrezultatas_ = egz; }
    void addNdPazymys(int pazymys) { ndpazymiai_.push_back(pazymys); }
    void setNdPazymiai(const std::vector<int>& pazymiai) { ndpazymiai_ = pazymiai; }

    // Galutinio balo skaiciavimas
    double galBalas(double (*skaiciavimas)(const std::vector<int>&)) const;

    // Skaitymas is srauto
    std::istream& readStudent(std::istream& is);

    // Isvedimas i srauta
    std::ostream& writeStudent(std::ostream& os) const;

    // Metodas skaiciuoti galutinius balus (vidurki ir mediana)
    void skaiciuotiGalutini();


    friend std::ostream& operator<<(std::ostream& os, const Studentas& s);
    friend std::istream& operator>>(std::istream& is, Studentas& s);
};

bool compare(const Studentas& a, const Studentas& b);
bool comparePagalVarda(const Studentas& a, const Studentas& b);
bool comparePagalPavarde(const Studentas& a, const Studentas& b);
bool comparePagalVidurki(const Studentas& a, const Studentas& b);
bool comparePagalMediana(const Studentas& a, const Studentas& b);

// Pagalbines funkcijos skaiciavimams
double vidurkis(const std::vector<int>& pazymiai);
double mediana(const std::vector<int>& pazymiai);

#endif // STUDENT_H_INCLUDED
