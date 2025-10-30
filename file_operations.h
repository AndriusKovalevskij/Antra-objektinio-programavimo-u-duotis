#ifndef FILE_OPERATIONS_H_INCLUDED
#define FILE_OPERATIONS_H_INCLUDED
#include "student_struct.h"
#include <vector>
#include <list>
#include <string>

// Funkcijos veikiancios su vector
bool skaitytiDuomenisIsFailo_Vector(const std::string& failoPavadinimas, std::vector<Studentas>& studentai);
void StudentuPadalinimas_Vector(const std::vector<Studentas>& studentai, bool pagalVidurki = true);
void isvestiRezultatusIFaila_Vector(const std::string& failoPavadinimas, const std::vector<Studentas>& studentai, bool pagalVidurki = true, bool rodytiAbu = false);

// Funkcijos veikiancios su list
bool skaitytiDuomenisIsFailo_List(const std::string& failoPavadinimas, std::list<Studentas>& studentai);
void StudentuPadalinimas_List(const std::list<Studentas>& studentai, bool pagalVidurki = true);
void isvestiRezultatusIFaila_List(const std::string& failoPavadinimas, const std::list<Studentas>& studentai, bool pagalVidurki = true, bool rodytiAbu = false);

// Bendros funkcijos
void GeneruotiStudentuFaila(const std::string& failoPavadinimas, int studentuKiekis, int ndKiekis = 5);

#endif // FILE_OPERATIONS_H_INCLUDED
