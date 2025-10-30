#include "menu.h"
#include "operations.h"
#include "file_operations.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

int rodytiMeniu()
{
    cout << "\n==================================" << endl;
    cout << "    PROGRAMOS MENIU (v0.3)" << endl;
    cout << "==================================" << endl;
    cout << "1 - Ivesti duomenis rankiniu budu (VECTOR)" << endl;
    cout << "2 - Generuoti duomenis atsitiktinai (VECTOR)" << endl;
    cout << "3 - Nuskaityti duomenis is failo (VECTOR)" << endl;
    cout << "4 - Nuskaityti duomenis is failo (LIST)" << endl;
    cout << "5 - Ivesti duomenis rankiniu budu (LIST)" << endl;
    cout << "6 - Sugeneruoti testinius failus" << endl;
    cout << "7 - Baigti programa" << endl;
    cout << "==================================" << endl;
    return ivestiSkaiciu("Pasirinkite buda (1-7): ", 1, 7);
}

void rodytiRezultatus_Vector(const vector<Studentas>& Grupe)
{
    if (Grupe.empty()) {
        cout << "Nera ivestos informacijos apie studentus!" << endl;
        return;
    }

    cout << "\n=== Naudojamas VECTOR konteineris ===" << endl;

    int rusiuotiPagal = ivestiSkaiciu("\nKaip norite rusiuoti studentus?\n1 - Pagal varda\n2 - Pagal pavarde\nPasirinkimas: ", 1, 2);
    vector<Studentas> surusiuotiStudentai = Grupe;

    if (rusiuotiPagal == 1)
    {
        sort(surusiuotiStudentai.begin(), surusiuotiStudentai.end(), palyginimasPagalVarda);
    } else {
        sort(surusiuotiStudentai.begin(), surusiuotiStudentai.end(), palyginimasPagalPavarde);
    }

    int pasirinkimas;
    cout << "\nPasirinkite galutinio ivertinimo tipa:" << endl;
    cout << "1 - Pagal vidurki" << endl;
    cout << "2 - Pagal mediana" << endl;
    cout << "3 - Rodyti abu" << endl;
    pasirinkimas = ivestiSkaiciu("Jusu pasirinkimas: ", 1, 3);

    cout << "\nStudento informacija:" << endl;
    cout << left << setw(20) << "Vardas" << "|"
         << left << setw(20) << "Pavarde";

    if (pasirinkimas == 1)
    {
        cout << "|" << left << setw(20) << "Galutinis (vid.)";
    } else if (pasirinkimas == 2) {
        cout << "|" << left << setw(20) << "Galutinis (Med.)";
    } else {
        cout << "|" << left << setw(20) << "Galutinis (Vid.)"
             << "|" << left << setw(20) << "Galutinis (Med.)";
    }
    cout << "|" << left << setw(20) << "Objektas atmintyje";
    cout << endl;

    if (pasirinkimas == 3)
    {
        cout << string(105, '-') << endl;
    } else {
        cout << string(80, '-') << endl;
    }

    for (const auto& studentas : surusiuotiStudentai)
    {
        cout << setw(20) << left << studentas.vardas << "|"
             << setw(20) << left << studentas.pavarde;

        if (pasirinkimas == 1)
        {
            cout << "|" << fixed << setprecision(2) << setw(20) << left << studentas.galutinis_vidurkis;
        } else if (pasirinkimas == 2){
            cout << "|" << fixed << setprecision(2) << setw(20) << left << studentas.galutine_mediana;
        } else {
            cout << "|" << fixed << setprecision(2) << setw(20) << left << studentas.galutinis_vidurkis
                 << "|" << fixed << setprecision(2) << setw(20) << left << studentas.galutine_mediana;
        }
        cout << "|" << setw(20) << left << &studentas;
        cout << endl;
    }

    cout << "\nAr norite padalinti studentus i kategorijas ir issaugoti i failus? (1 - taip, 2 - ne): ";
    int padalinti = ivestiSkaiciu("", 1, 2);

    if (padalinti == 1) {
        if (pasirinkimas == 1) {
            StudentuPadalinimas_Vector(surusiuotiStudentai, true);
        } else {
            if (pasirinkimas == 2) {
                StudentuPadalinimas_Vector(surusiuotiStudentai, false);
            } else {
                int tipas = ivestiSkaiciu("\nPagal kuri bala padalinti?\n1 - Pagal vidurki\n2 - Pagal mediana\nPasirinkimas: ", 1, 2);
                if (tipas == 1) {
                    StudentuPadalinimas_Vector(surusiuotiStudentai, true);
                } else {
                    StudentuPadalinimas_Vector(surusiuotiStudentai, false);
                }
            }
        }
    }
}

void rodytiRezultatus_List(const list<Studentas>& Grupe)
{
    if (Grupe.empty()) {
        cout << "Nera ivestos informacijos apie studentus!" << endl;
        return;
    }

    cout << "\n=== Naudojamas LIST konteineris ===" << endl;

    int rusiuotiPagal = ivestiSkaiciu("\nKaip norite rusiuoti studentus?\n1 - Pagal varda\n2 - Pagal pavarde\nPasirinkimas: ", 1, 2);
    list<Studentas> surusiuotiStudentai = Grupe;

    if (rusiuotiPagal == 1)
    {
        surusiuotiStudentai.sort(palyginimasPagalVarda);
    } else {
        surusiuotiStudentai.sort(palyginimasPagalPavarde);
    }

    int pasirinkimas;
    cout << "\nPasirinkite galutinio ivertinimo tipa:" << endl;
    cout << "1 - Pagal vidurki" << endl;
    cout << "2 - Pagal mediana" << endl;
    cout << "3 - Rodyti abu" << endl;
    pasirinkimas = ivestiSkaiciu("Jusu pasirinkimas: ", 1, 3);

    cout << "\nStudento informacija:" << endl;
    cout << left << setw(20) << "Vardas" << "|"
         << left << setw(20) << "Pavarde";

    if (pasirinkimas == 1)
    {
        cout << "|" << left << setw(20) << "Galutinis (vid.)";
    } else if (pasirinkimas == 2) {
        cout << "|" << left << setw(20) << "Galutinis (Med.)";
    } else {
        cout << "|" << left << setw(20) << "Galutinis (Vid.)"
             << "|" << left << setw(20) << "Galutinis (Med.)";
    }
    cout << "|" << left << setw(20) << "Objektas atmintyje";
    cout << endl;

    if (pasirinkimas == 3)
    {
        cout << string(105, '-') << endl;
    } else {
        cout << string(80, '-') << endl;
    }

    for (const auto& studentas : surusiuotiStudentai)
    {
        cout << setw(20) << left << studentas.vardas << "|"
             << setw(20) << left << studentas.pavarde;

        if (pasirinkimas == 1)
        {
            cout << "|" << fixed << setprecision(2) << setw(20) << left << studentas.galutinis_vidurkis;
        } else if (pasirinkimas == 2){
            cout << "|" << fixed << setprecision(2) << setw(20) << left << studentas.galutine_mediana;
        } else {
            cout << "|" << fixed << setprecision(2) << setw(20) << left << studentas.galutinis_vidurkis
                 << "|" << fixed << setprecision(2) << setw(20) << left << studentas.galutine_mediana;
        }
        cout << "|" << setw(20) << left << &studentas;
        cout << endl;
    }

    cout << "\nAr norite padalinti studentus i kategorijas ir issaugoti i failus? (1 - taip, 2 - ne): ";
    int padalinti = ivestiSkaiciu("", 1, 2);

    if (padalinti == 1) {
        if (pasirinkimas == 1) {
            StudentuPadalinimas_List(surusiuotiStudentai, true);
        } else {
            if (pasirinkimas == 2) {
                StudentuPadalinimas_List(surusiuotiStudentai, false);
            } else {
                int tipas = ivestiSkaiciu("\nPagal kuri bala padalinti?\n1 - Pagal vidurki\n2 - Pagal mediana\nPasirinkimas: ", 1, 2);
                if (tipas == 1) {
                    StudentuPadalinimas_List(surusiuotiStudentai, true);
                } else {
                    StudentuPadalinimas_List(surusiuotiStudentai, false);
                }
            }
        }
    }
}
