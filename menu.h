#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "student_struct.h"
#include <vector>
#include <list>

int rodytiMeniu();
void rodytiRezultatus_Vector(const std::vector<Studentas>& Grupe);
void rodytiRezultatus_List(const std::list<Studentas>& Grupe);

#endif // MENU_H_INCLUDED
