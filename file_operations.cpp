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


bool skaitytiDuomenisIsFailo(const string& failoPavadinimas, vector<Studentas>& studentai)
{
    auto start = high_resolution_clock::now();

    ifstream failas(failoPavadinimas);
    if (!failas.is_open()) {
        cout << "Klaida: nepavyko atidaryti failo " << failoPavadinimas << endl;
        return false;
    }

    string eilute;
    if (!getline(failas, eilute)) {
        cout << "Klaida: failas tuscias arba pazeistas" << endl;
        failas.close();
        return false;
    }

    int studentuSkaicius = 0;
    while (getline(failas, eilute)) {
        if (eilute.empty()) continue;

        stringstream ss(eilute);
        Studentas studentas;

        string vardas, pavarde;
        if (!(ss >> vardas >> pavarde)) {
            cout << "Klaida skaitant eilute: " << eilute << endl;
            continue;
        }

        studentas.setVardas(vardas);
        studentas.setPavarde(pavarde);

        int pazymys;
        vector<int> visi_pazymiai;

        while (ss >> pazymys) {
            if (pazymys < 1 || pazymys > 10) {
                cout << "Netinkamas pazymys " << pazymys << " studentui "
                     << vardas << " " << pavarde << endl;
                continue;
            }
            visi_pazymiai.push_back(pazymys);
        }

        if (visi_pazymiai.empty()) {
            cout << "Studentas " << vardas << " " << pavarde
                 << " neturi pazymiu" << endl;
            continue;
        }

        studentas.setEgzRezultatas(visi_pazymiai.back());
        visi_pazymiai.pop_back();
        studentas.setNdPazymiai(visi_pazymiai);

        studentas.skaiciuotiGalutini();

        studentai.push_back(studentas);
        studentuSkaicius++;
    }

    failas.close();

    auto end = high_resolution_clock::now();
    duration<double> diff = end - start;

    cout << "Sekmingai nuskaityta " << studentuSkaicius << " studentu duomenys." << endl;
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

    fout << left << setw(20) << "Vardas" << setw(20) << "Pavarde";
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


void StudentuPadalinimas_Vector(vector<Studentas>& studentai, bool pagalVidurki)
{
    if (studentai.empty()) {
        cout << "Nera studentu duomenu padalijimui!" << endl;
        return;
    }

    cout << "\n=== VECTOR - OPTIMALI STRATEGIJA (stable_partition) ===" << endl;
    auto start_total = high_resolution_clock::now();

    auto start_partition = high_resolution_clock::now();

    auto partition_point = std::stable_partition(studentai.begin(), studentai.end(),
        [pagalVidurki](const Studentas& s) {
            double balas = pagalVidurki ? s.galutinisVidurkis() : s.galutineMediana();
            return balas < 5.0;
        });

    auto end_partition = high_resolution_clock::now();
    duration<double> diff_partition = end_partition - start_partition;

    auto start_copy = high_resolution_clock::now();

    vector<Studentas> vargsiukai(studentai.begin(), partition_point);
    vector<Studentas> saunuoliai(partition_point, studentai.end());

    auto end_copy = high_resolution_clock::now();
    duration<double> diff_copy = end_copy - start_copy;

    // Rusiavimas
    auto start_sort = high_resolution_clock::now();

    if (pagalVidurki) {
        sort(vargsiukai.begin(), vargsiukai.end(), comparePagalVidurki);
        sort(saunuoliai.begin(), saunuoliai.end(), comparePagalVidurki);
    } else {
        sort(vargsiukai.begin(), vargsiukai.end(), comparePagalMediana);
        sort(saunuoliai.begin(), saunuoliai.end(), comparePagalMediana);
    }

    auto end_sort = high_resolution_clock::now();
    duration<double> diff_sort = end_sort - start_sort;

    string tipas = pagalVidurki ? "vidurkis" : "mediana";

    // Isvedimas i failus
    auto start_output = high_resolution_clock::now();

    string vargsiukuFailas = "vargsiuku_" + tipas + ".txt";
    ofstream fout1(vargsiukuFailas);
    if (fout1.is_open()) {
        fout1 << left << setw(20) << "Vardas" << setw(20) << "Pavarde"
              << setw(25) << ("Galutinis (" + tipas + ")") << endl;
        fout1 << string(65, '-') << endl;
        for (const auto& s : vargsiukai) {
            double balas = pagalVidurki ? s.galutinisVidurkis() : s.galutineMediana();
            fout1 << left << setw(20) << s.vardas() << setw(20) << s.pavarde()
                  << fixed << setprecision(2) << balas << endl;
        }
        fout1.close();
    }

    string saunuoliuFailas = "saunuoliu_" + tipas + ".txt";
    ofstream fout2(saunuoliuFailas);
    if (fout2.is_open()) {
        fout2 << left << setw(20) << "Vardas" << setw(20) << "Pavarde"
              << setw(25) << ("Galutinis (" + tipas + ")") << endl;
        fout2 << string(65, '-') << endl;
        for (const auto& s : saunuoliai) {
            double balas = pagalVidurki ? s.galutinisVidurkis() : s.galutineMediana();
            fout2 << left << setw(20) << s.vardas() << setw(20) << s.pavarde()
                  << fixed << setprecision(2) << balas << endl;
        }
        fout2.close();
    }

    auto end_output = high_resolution_clock::now();
    duration<double> diff_output = end_output - start_output;

    auto end_total = high_resolution_clock::now();
    duration<double> diff_total = end_total - start_total;

    cout << "\n--- LAIKO MATAVIMAS ---" << endl;
    cout << "Partition laikas:            " << fixed << setprecision(6) << diff_partition.count() << " s" << endl;
    cout << "Kopijavimo laikas:           " << fixed << setprecision(6) << diff_copy.count() << " s" << endl;
    cout << "Rusiavimo laikas:            " << fixed << setprecision(6) << diff_sort.count() << " s" << endl;
    cout << "Isvedimo laikas:             " << fixed << setprecision(6) << diff_output.count() << " s" << endl;
    cout << "BENDRAS laikas:              " << fixed << setprecision(6) << diff_total.count() << " s" << endl;
    cout << "------------------------------------" << endl;
    cout << "Vargsiuku: " << vargsiukai.size() << " | Saunuoliu: " << saunuoliai.size() << endl;
    cout << "Failai: " << vargsiukuFailas << ", " << saunuoliuFailas << endl;
    cout << "------------------------------------\n" << endl;
}
