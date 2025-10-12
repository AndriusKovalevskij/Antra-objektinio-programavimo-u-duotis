#ifndef FILE_OPERATIONS_H_INCLUDED
#define FILE_OPERATIONS_H_INCLUDED

#include "student_struct.h"
#include <vector>
#include <string>
#include <list>

bool skaitytiDuomenisIsFailo(const std::string& failoPavadinimas, std::list<Studentas>& studentai);
void GeneruotiStudentuFaila(const std::string& failoPavadinimas, int studentuKiekis, int ndKiekis = 5);
void StudentuPadalinimas(const std::list<Studentas>& studentai, bool pagalVidurki = true);
void isvestiRezultatusIFaila(const std::string& failoPavadinimas, const std::list<Studentas>& studentai, bool pagalVidurki = true, bool rodytiAbu = false);

#endif // FILE_OPERATIONS_H_INCLUDED
