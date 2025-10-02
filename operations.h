#ifndef OPERATIONS_H_INCLUDED
#define OPERATIONS_H_INCLUDED

#include "student_struct.h"
#include <vector>
#include <string>

// Ivesties funkcijos
void ivestiesIsvalymas();
int ivestiSkaiciu(const std::string& zinute, int min_pazymys = 1, int max_pazymys = 10);
std::string ivestiVarda(const std::string& zinute);

// Skaiciavimai
double MedianosSkaiciavimas(std::vector<int> pazymiai);

// Namu darbu pazymiai
void NDpazymiuivestis(std::vector<int>& ndpazymiai);
int AtsitiktinioPazymioGeneravimas();
void NDPazymiuGeneravimas(std::vector<int>& ndpazymiai);

// Studento duomenu ivedimas
Studentas Stud_ivestis(int studentoNr, bool atsitiktinai = false);

// Rikiavimas
bool palyginimasPagalVarda(const Studentas& a, const Studentas& b);
bool palyginimasPagalPavarde(const Studentas& a, const Studentas& b);

#endif // OPERATIONS_H_INCLUDED
