#ifndef FILE_OPERATIONS_H_INCLUDED
#define FILE_OPERATIONS_H_INCLUDED

#include "student_struct.h"
#include <vector>
#include <string>

bool skaitytiDuomenisIsFailo(const std::string& failoPavadinimas, std::vector<Studentas>& studentai);
void GeneruotiStudentuFaila(const std::string& failoPavadinimas, int studentuKiekis, int ndKiekis = 5);
void StudentuPadalinimas(const std::vector<Studentas>& studentai, bool pagalVidurki = true);
void isvestiRezultatusIFaila(const std::string& failoPavadinimas, const std::vector<Studentas>& studentai, bool pagalVidurki = true, bool rodytiAbu = false);

#endif // FILE_OPERATIONS_H_INCLUDED
