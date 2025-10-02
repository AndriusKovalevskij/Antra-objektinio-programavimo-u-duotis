#include "menu.h"
#include "operations.h"
#include "file_operations.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

int rodytiMeniu()
{
    cout << "\n PROGRAMOS MENIU" << endl;
    cout << "1 - Ivesti duomenis rankiniu budu" << endl;
    cout << "2 - Generuoti duomenis atsitiktinai" << endl;
    cout << "3 - Nuskaityti duomenis is failo" << endl;
    cout << "4 - Baigti programa" << endl;
    cout << "5 - Sugeneruoti testinius failus (1k, 10k, 100k, 1M, 10M)" << endl;

    return ivestiSkaiciu("Pasirinkite buda (1-5): ", 1, 5);
}

void rodytiRezultatus(const vector<Studentas>& Grupe)
{
    if (Grupe.empty()) {
        cout << "Nera ivestos informacijos apie studentus!" << endl;
        return;
    }

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
    cout << endl;

    if (pasirinkimas == 3)
    {
        cout << string(80, '-') << endl;
    } else {
        cout << string(60, '-') << endl;
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
        cout << endl;
    }

    cout << "\nAr norite padalinti studentus i kategorijas ir issaugoti i failus? (1 - taip, 2 - ne): ";
    int padalinti = ivestiSkaiciu("", 1, 2);

    if (padalinti == 1) {
        if (pasirinkimas == 1) {
            StudentuPadalinimas(surusiuotiStudentai, true);
        } else {
            if (pasirinkimas == 2) {
                StudentuPadalinimas(surusiuotiStudentai, false);
            } else {
                int tipas = ivestiSkaiciu("\nPagal kuri bala padalinti?\n1 - Pagal vidurki\n2 - Pagal mediana\nPasirinkimas: ", 1, 2);
                if (tipas == 1) {
                    StudentuPadalinimas(surusiuotiStudentai, true);
                } else {
                    StudentuPadalinimas(surusiuotiStudentai, false);
                }
            }
        }
    }
}

