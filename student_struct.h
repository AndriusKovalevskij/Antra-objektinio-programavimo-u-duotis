#ifndef STUDENT_STRUCT_H_INCLUDED
#define STUDENT_STRUCT_H_INCLUDED

#include <string>
#include <vector>

struct Studentas
{
    std::string vardas;
    std::string pavarde;
    std::vector<int> ndpazymiai;
    int egzrezultatas{};
    double galutinis_vidurkis{};
    double galutine_mediana{};
};

#endif // STUDENT_STRUCT_H_INCLUDED
