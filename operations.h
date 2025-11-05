#ifndef OPERATIONS_H_INCLUDED
#define OPERATIONS_H_INCLUDED

#include "student.h"
#include <vector>
#include <string>

// Ivesties funkcijos
void ivestiesIsvalymas();
int ivestiSkaiciu(const std::string& zinute, int min_pazymys = 1, int max_pazymys = 10);
std::string ivestiVarda(const std::string& zinute);

// Namu darbu pazymiai
void NDpazymiuivestis(std::vector<int>& ndpazymiai);
int AtsitiktinioPazymioGeneravimas();
void NDPazymiuGeneravimas(std::vector<int>& ndpazymiai);

// Studento duomenu ivedimas
Studentas Stud_ivestis(int studentoNr, bool atsitiktinai = false);

#endif // OPERATIONS_H_INCLUDED
