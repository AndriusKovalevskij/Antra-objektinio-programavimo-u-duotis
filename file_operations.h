#ifndef FILE_OPERATIONS_H_INCLUDED
#define FILE_OPERATIONS_H_INCLUDED
#include "student_struct.h"
#include <vector>
#include <list>
#include <string>

bool skaitytiDuomenisIsFailo_Vector(const std::string& failoPavadinimas, std::vector<Studentas>& studentai);
bool skaitytiDuomenisIsFailo_List(const std::string& failoPavadinimas, std::list<Studentas>& studentai);
void GeneruotiStudentuFaila(const std::string& failoPavadinimas, int studentuKiekis, int ndKiekis = 5);

// VECTOR STRATEGIJOS
// Strategija 1: Kopijavimas i du naujus konteinerius
void StudentuPadalinimas_Vector_S1(const std::vector<Studentas>& studentai, bool pagalVidurki = true);

// Strategija 2: Vienas konteineris + trynimas
void StudentuPadalinimas_Vector_S2(std::vector<Studentas>& studentai, bool pagalVidurki = true);

// Strategija 3: STL stable_partition
void StudentuPadalinimas_Vector_S3(std::vector<Studentas>& studentai, bool pagalVidurki = true);

// LIST STRATEGIJOS
// Strategija 1: Kopijavimas i du naujus konteinerius
void StudentuPadalinimas_List_S1(const std::list<Studentas>& studentai, bool pagalVidurki = true);

// Strategija 2: Trynimas
void StudentuPadalinimas_List_S2(std::list<Studentas>& studentai, bool pagalVidurki = true);

// Strategija 3: Splice
void StudentuPadalinimas_List_S3(std::list<Studentas>& studentai, bool pagalVidurki = true);

#endif // FILE_OPERATIONS_H_INCLUDED
