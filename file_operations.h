#ifndef FILE_OPERATIONS_H_INCLUDED
#define FILE_OPERATIONS_H_INCLUDED

#include "student.h"
#include <vector>
#include <string>

// Skaitymo funkcija
bool skaitytiDuomenisIsFailo(const std::string& failoPavadinimas, std::vector<Studentas>& studentai);

// Generavimo funkcija
void GeneruotiStudentuFaila(const std::string& failoPavadinimas, int studentuKiekis, int ndKiekis = 5);

// VECTOR STRATEGIJA 3 (OPTIMALI - stable_partition)
void StudentuPadalinimas_Vector(std::vector<Studentas>& studentai, bool pagalVidurki = true);

#endif // FILE_OPERATIONS_H_INCLUDED
