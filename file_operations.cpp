#include "file_operations.h"
#include "operations.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

bool skaitytiDuomenisIsFailo(const string& failoPavadinimas, list<Studentas>& studentai)
{
    auto start = high_resolution_clock::now();

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

    auto end = high_resolution_clock::now();
    duration<double> diff = end - start;

    cout << "Sekmingai nuskaityta " << studentuSkaicius << " studentu duomenys. " << endl;
    cout << "Duomenu nuskaitymo laikas: " << fixed << setprecision(6) << diff.count() << " s" << endl;
    return true;
}

void GeneruotiStudentuFaila(const string& failoPavadinimas, int studentuKiekis, int ndKiekis)
{
    auto start = high_resolution_clock::now();

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

    auto end = high_resolution_clock::now();
    duration<double> diff = end - start;

    cout << "Failas " << failoPavadinimas
         << " sugeneruotas su " << studentuKiekis << " irasu." << endl;
    cout << "Failo kurimo laikas: " << fixed << setprecision(6) << diff.count() << " s" << endl;
}

void isvestiRezultatusIFaila(const string& failoPavadinimas, const list<Studentas>& studentai, bool pagalVidurki, bool rodytiAbu)
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

void StudentuPadalinimas(const list<Studentas>& studentai, bool pagalVidurki)
{
    if (studentai.empty()) {
        cout << "Nera studentu duomenu padalijimui!" << endl;
        return;
    }

    // Matuojame rusiavimo laika
    auto start_rusiavimas = high_resolution_clock::now();

    list<Studentas> vargsiukai;
    list<Studentas> saunuoliai;

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

    if (pagalVidurki) {
        vargsiukai.sort([](const Studentas& a, const Studentas& b) {
            return a.galutinis_vidurkis < b.galutinis_vidurkis;
        });
        saunuoliai.sort([](const Studentas& a, const Studentas& b) {
            return a.galutinis_vidurkis < b.galutinis_vidurkis;
        });
    } else {
        vargsiukai.sort([](const Studentas& a, const Studentas& b) {
            return a.galutine_mediana < b.galutine_mediana;
        });
        saunuoliai.sort([](const Studentas& a, const Studentas& b) {
            return a.galutine_mediana < b.galutine_mediana;
        });
    }

    auto end_rusiavimas = high_resolution_clock::now();
    duration<double> diff_rusiavimas = end_rusiavimas - start_rusiavimas;

    cout << "\n--- LAIKO MATAVIMAS ---" << endl;
    cout << "Studentu rusiavimo i kategorijas laikas: " << fixed << setprecision(6)
         << diff_rusiavimas.count() << " s" << endl;

    string tipas;
    if (pagalVidurki) {
        tipas = "vidurkis";
    } else {
        tipas = "mediana";
    }

    // Matuojame vargsiuku failo kurimo laika
    auto start_vargsiukai = high_resolution_clock::now();

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
    } else {
        cout << "Klaida kuriant vargsiuku faila!" << endl;
    }

    auto end_vargsiukai = high_resolution_clock::now();
    duration<double> diff_vargsiukai = end_vargsiukai - start_vargsiukai;

    // Matuojame saunuoliu failo kurimo laika
    auto start_saunuoliai = high_resolution_clock::now();

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
    } else {
        cout << "Klaida kuriant saunuoliu faila!" << endl;
    }

    auto end_saunuoliai = high_resolution_clock::now();
    duration<double> diff_saunuoliai = end_saunuoliai - start_saunuoliai;

    double bendras_isvedimas = diff_vargsiukai.count() + diff_saunuoliai.count();

    cout << "Vargsiuku failo kurimo laikas: " << fixed << setprecision(6)
         << diff_vargsiukai.count() << " s" << endl;
    cout << "Saunuoliu failo kurimo laikas: " << fixed << setprecision(6)
         << diff_saunuoliai.count() << " s" << endl;
    cout << "Bendras isvedimo laikas: " << fixed << setprecision(6)
         << bendras_isvedimas << " s" << endl;
    cout << "Bendras laikas (rusiavimas + isvedimas): " << fixed << setprecision(6)
         << (diff_rusiavimas.count() + bendras_isvedimas) << " s" << endl;
    cout << "-----------------------\n" << endl;

    cout << "Vargsiuku failas '" << vargsiukuFailas << "' sukurtas su " << vargsiukai.size() << " irasais." << endl;
    cout << "Saunuoliu failas '" << saunuoliuFailas << "' sukurtas su " << saunuoliai.size() << " irasais." << endl;
}
