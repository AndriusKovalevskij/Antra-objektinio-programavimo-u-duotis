#include "file_operations.h"
#include "operations.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

bool skaitytiDuomenisIsFailo(const string& failoPavadinimas, vector<Studentas>& studentai)
{
    ifstream failas(failoPavadinimas);
    if (!failas.is_open()) {
        cout << "Klaida: nepavyko atidaryti failo " << failoPavadinimas << endl;
        return false;
    }

    string eilute;

    if (!getline(failas, eilute))
    {
        cout << "Klaida: failas tuscias arba pazeistas" << endl;
        failas.close();
        return false;
    }

    int studentuSkaicius = 0;
    while (getline(failas, eilute))
    {
        if (eilute.empty()) continue;

        stringstream ss(eilute);
        Studentas studentas;

        if (!(ss >> studentas.vardas >> studentas.pavarde))
        {
            cout << "Klaida skaitant eilute: " << eilute << endl;
            continue;
        }

        int pazymys;
        vector<int> visi_pazymiai;

        while (ss >> pazymys)
        {
            if (pazymys < 1 || pazymys > 10)
            {
                cout << "Netinkamas pazymys " << pazymys << " studentui "
                     << studentas.vardas << " " << studentas.pavarde << endl;
                continue;
            }
            visi_pazymiai.push_back(pazymys);
        }

        if (visi_pazymiai.empty())
        {
            cout << "Studentas " << studentas.vardas << " " << studentas.pavarde
                 << " neturi pazymiu" << endl;
            continue;
        }

        studentas.egzrezultatas = visi_pazymiai.back();
        visi_pazymiai.pop_back();
        studentas.ndpazymiai = visi_pazymiai;

        if (studentas.ndpazymiai.size() > 0)
        {
            int sum = 0;
            for (int nd_pazymys : studentas.ndpazymiai)
            {
                sum += nd_pazymys;
            }
            studentas.galutinis_vidurkis = double(sum) / double(studentas.ndpazymiai.size()) * 0.4 + studentas.egzrezultatas * 0.6;
            studentas.galutine_mediana = MedianosSkaiciavimas(studentas.ndpazymiai) * 0.4 + studentas.egzrezultatas * 0.6;
        } else {
            studentas.galutinis_vidurkis = studentas.egzrezultatas * 0.6;
            studentas.galutine_mediana = studentas.egzrezultatas * 0.6;
        }

        studentai.push_back(studentas);
        studentuSkaicius++;
    }

    failas.close();
    cout << "Sekmingai nuskaityta " << studentuSkaicius << " studentu duomenys. " << endl;
    return true;
}

void GeneruotiStudentuFaila(const string& failoPavadinimas, int studentuKiekis, int ndKiekis)
{
    ofstream fout(failoPavadinimas);
    if (!fout.is_open()) {
        cout << "Klaida: nepavyko sukurti failo " << failoPavadinimas << endl;
        return;
    }

    fout << left << setw(20) << "Vardas"
         << setw(20) << "Pavarde";
    for (int i = 1; i <= ndKiekis; i++) {
        fout << setw(8) << ("ND" + to_string(i));
    }
    fout << setw(10) << "Egzaminas" << "\n";

    for (int i = 1; i <= studentuKiekis; i++) {
        fout << left << setw(20) << ("Vardas" + to_string(i))
             << setw(20) << ("Pavarde" + to_string(i));

        for (int j = 0; j < ndKiekis; j++) {
            fout << setw(8) << AtsitiktinioPazymioGeneravimas();
        }
        fout << setw(10) << AtsitiktinioPazymioGeneravimas() << "\n";
    }

    fout.close();
    cout << "Failas " << failoPavadinimas
         << " sugeneruotas su " << studentuKiekis << " irasu." << endl;
}

void isvestiRezultatusIFaila(const string& failoPavadinimas, const vector<Studentas>& studentai, bool pagalVidurki, bool rodytiAbu)
{
    ofstream fout(failoPavadinimas);
    if (!fout.is_open()) {
        cout << "Klaida: nepavyko sukurti failo " << failoPavadinimas << endl;
        return;
    }

    fout << left << setw(20) << "Vardas" << "|"
         << left << setw(20) << "Pavarde";

    if (rodytiAbu)
    {
        fout << "|" << left << setw(20) << "Galutinis (Vid.)"
             << "|" << left << setw(20) << "Galutinis (Med.)";
        fout << endl;
        fout << string(80, '-') << endl;
    } else if (pagalVidurki) {
        fout << "|" << left << setw(20) << "Galutinis (vid.)";
        fout << endl;
        fout << string(60, '-') << endl;
    } else {
        fout << "|" << left << setw(20) << "Galutinis (Med.)";
        fout << endl;
        fout << string(60, '-') << endl;
    }

    for (const auto& studentas : studentai)
    {
        fout << setw(20) << left << studentas.vardas << "|"
             << setw(20) << left << studentas.pavarde;

        if (rodytiAbu)
        {
            fout << "|" << fixed << setprecision(2) << setw(20) << left << studentas.galutinis_vidurkis
                 << "|" << fixed << setprecision(2) << setw(20) << left << studentas.galutine_mediana;
        } else if (pagalVidurki) {
            fout << "|" << fixed << setprecision(2) << setw(20) << left << studentas.galutinis_vidurkis;
        } else {
            fout << "|" << fixed << setprecision(2) << setw(20) << left << studentas.galutine_mediana;
        }
        fout << endl;
    }

    fout.close();
    cout << "Rezultatai issaugoti i faila: " << failoPavadinimas << endl;
}

void StudentuPadalinimas(const vector<Studentas>& studentai, bool pagalVidurki)
{
    if (studentai.empty()) {
        cout << "Nera studentu duomenu padalijimui!" << endl;
        return;
    }

    vector<Studentas> vargsiukai;
    vector<Studentas> saunuoliai;

    for (const auto& studentas : studentai) {
        double galutinisBalas;
        if (pagalVidurki) {
            galutinisBalas = studentas.galutinis_vidurkis;
        } else {
            galutinisBalas = studentas.galutine_mediana;
        }

        if (galutinisBalas < 5.0) {
            vargsiukai.push_back(studentas);
        } else {
            saunuoliai.push_back(studentas);
        }
    }

    sort(vargsiukai.begin(), vargsiukai.end(), palyginimasPagalVarda);
    sort(saunuoliai.begin(), saunuoliai.end(), palyginimasPagalVarda);

    string tipas;
    if (pagalVidurki) {
        tipas = "vidurkis";
    } else {
        tipas = "mediana";
    }

    string vargsiukuFailas = "vargsiuku_" + tipas + ".txt";
    ofstream fout1(vargsiukuFailas);
    if (fout1.is_open()) {
        fout1 << left << setw(20) << "Vardas"
              << setw(20) << "Pavarde"
              << setw(25) << ("Galutinis (" + tipas + ")") << endl;
        fout1 << string(65, '-') << endl;

        for (const auto& studentas : vargsiukai) {
            double balas;
            if (pagalVidurki) {
                balas = studentas.galutinis_vidurkis;
            } else {
                balas = studentas.galutine_mediana;
            }
            fout1 << left << setw(20) << studentas.vardas
                  << setw(20) << studentas.pavarde
                  << fixed << setprecision(2) << balas << endl;
        }
        fout1.close();
        cout << "Vargsiuku failas '" << vargsiukuFailas << "' sukurtas su " << vargsiukai.size() << " irasais." << endl;
    } else {
        cout << "Klaida kuriant vargsiuku faila!" << endl;
    }

    string saunuoliuFailas = "saunuoliu_" + tipas + ".txt";
    ofstream fout2(saunuoliuFailas);
    if (fout2.is_open()) {
        fout2 << left << setw(20) << "Vardas"
              << setw(20) << "Pavarde"
              << setw(25) << ("Galutinis (" + tipas + ")") << endl;
        fout2 << string(65, '-') << endl;

        for (const auto& studentas : saunuoliai) {
            double balas;
            if (pagalVidurki) {
                balas = studentas.galutinis_vidurkis;
            } else {
                balas = studentas.galutine_mediana;
            }
            fout2 << left << setw(20) << studentas.vardas
                  << setw(20) << studentas.pavarde
                  << fixed << setprecision(2) << balas << endl;
        }
        fout2.close();
        cout << "Saunuoliu failas '" << saunuoliuFailas << "' sukurtas su " << saunuoliai.size() << " irasais." << endl;
    } else {
        cout << "Klaida kuriant saunuoliu faila!" << endl;
    }
}
