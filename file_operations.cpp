#include "file_operations.h"
#include "operations.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <list>

using namespace std;
using namespace std::chrono;

bool skaitytiDuomenisIsFailo_Vector(const string& failoPavadinimas, vector<Studentas>& studentai)
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

        if (!(ss >> studentas.vardas >> studentas.pavarde)) {
            cout << "Klaida skaitant eilute: " << eilute << endl;
            continue;
        }

        int pazymys;
        vector<int> visi_pazymiai;

        while (ss >> pazymys) {
            if (pazymys < 1 || pazymys > 10) {
                cout << "Netinkamas pazymys " << pazymys << " studentui "
                     << studentas.vardas << " " << studentas.pavarde << endl;
                continue;
            }
            visi_pazymiai.push_back(pazymys);
        }

        if (visi_pazymiai.empty()) {
            cout << "Studentas " << studentas.vardas << " " << studentas.pavarde
                 << " neturi pazymiu" << endl;
            continue;
        }

        studentas.egzrezultatas = visi_pazymiai.back();
        visi_pazymiai.pop_back();
        studentas.ndpazymiai = visi_pazymiai;

        if (studentas.ndpazymiai.size() > 0) {
            int sum = 0;
            for (int nd_pazymys : studentas.ndpazymiai) {
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

    cout << "Sekmingai nuskaityta " << studentuSkaicius << " studentu duomenys (VECTOR). " << endl;
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

// ============================================
// STRATEGIJA 1: KOPIJAVIMAS Į DU KONTEINERIUS
// ============================================

void StudentuPadalinimas_Vector_S1(const vector<Studentas>& studentai, bool pagalVidurki)
{
    if (studentai.empty()) {
        cout << "Nera studentu duomenu padalijimui!" << endl;
        return;
    }

    cout << "\n=== VECTOR - STRATEGIJA 1 (Kopijavimas) ===" << endl;
    auto start_total = high_resolution_clock::now();

    vector<Studentas> vargsiukai;
    vector<Studentas> saunuoliai;

    // Rezervuojame atminti optimizacijai
    vargsiukai.reserve(studentai.size() / 2);
    saunuoliai.reserve(studentai.size() / 2);

    auto start_split = high_resolution_clock::now();

    // Padalijimas i du konteinerius
    for (const auto& studentas : studentai) {
        double galutinisBalas = pagalVidurki ? studentas.galutinis_vidurkis : studentas.galutine_mediana;

        if (galutinisBalas < 5.0) {
            vargsiukai.push_back(studentas);
        } else {
            saunuoliai.push_back(studentas);
        }
    }

    auto end_split = high_resolution_clock::now();
    duration<double> diff_split = end_split - start_split;

    // Rusiuojame pagal pasirinkta kriteriju
    auto start_sort = high_resolution_clock::now();

    if (pagalVidurki) {
        sort(vargsiukai.begin(), vargsiukai.end(), [](const Studentas& a, const Studentas& b) {
            return a.galutinis_vidurkis < b.galutinis_vidurkis;
        });
        sort(saunuoliai.begin(), saunuoliai.end(), [](const Studentas& a, const Studentas& b) {
            return a.galutinis_vidurkis < b.galutinis_vidurkis;
        });
    } else {
        sort(vargsiukai.begin(), vargsiukai.end(), [](const Studentas& a, const Studentas& b) {
            return a.galutine_mediana < b.galutine_mediana;
        });
        sort(saunuoliai.begin(), saunuoliai.end(), [](const Studentas& a, const Studentas& b) {
            return a.galutine_mediana < b.galutine_mediana;
        });
    }

    auto end_sort = high_resolution_clock::now();
    duration<double> diff_sort = end_sort - start_sort;

    string tipas = pagalVidurki ? "vidurkis" : "mediana";

    // Matuojame vargsiuku failo kurimo laika
    auto start_vargsiukai = high_resolution_clock::now();

    string vargsiukuFailas = "vargsiuku_" + tipas + "_vector_s1.txt";
    ofstream fout1(vargsiukuFailas);
    if (fout1.is_open()) {
        fout1 << left << setw(20) << "Vardas"
              << setw(20) << "Pavarde"
              << setw(25) << ("Galutinis (" + tipas + ")") << endl;
        fout1 << string(65, '-') << endl;

        for (const auto& studentas : vargsiukai) {
            double balas = pagalVidurki ? studentas.galutinis_vidurkis : studentas.galutine_mediana;
            fout1 << left << setw(20) << studentas.vardas
                  << setw(20) << studentas.pavarde
                  << fixed << setprecision(2) << balas << endl;
        }
        fout1.close();
    }

    auto end_vargsiukai = high_resolution_clock::now();
    duration<double> diff_vargsiukai = end_vargsiukai - start_vargsiukai;

    // Matuojame saunuoliu failo kurimo laika
    auto start_saunuoliai = high_resolution_clock::now();

    string saunuoliuFailas = "saunuoliu_" + tipas + "_vector_s1.txt";
    ofstream fout2(saunuoliuFailas);
    if (fout2.is_open()) {
        fout2 << left << setw(20) << "Vardas"
              << setw(20) << "Pavarde"
              << setw(25) << ("Galutinis (" + tipas + ")") << endl;
        fout2 << string(65, '-') << endl;

        for (const auto& studentas : saunuoliai) {
            double balas = pagalVidurki ? studentas.galutinis_vidurkis : studentas.galutine_mediana;
            fout2 << left << setw(20) << studentas.vardas
                  << setw(20) << studentas.pavarde
                  << fixed << setprecision(2) << balas << endl;
        }
        fout2.close();
    }

    auto end_saunuoliai = high_resolution_clock::now();
    duration<double> diff_saunuoliai = end_saunuoliai - start_saunuoliai;

    double bendras_isvedimas = diff_vargsiukai.count() + diff_saunuoliai.count();

    auto end_total = high_resolution_clock::now();
    duration<double> diff_total = end_total - start_total;

    cout << "\n--- LAIKO MATAVIMAS (STRATEGIJA 1) ---" << endl;
    cout << "Studentu padalijimo laikas:  " << fixed << setprecision(6) << diff_split.count() << " s" << endl;
    cout << "Rusiavimo laikas:            " << fixed << setprecision(6) << diff_sort.count() << " s" << endl;
    cout << "Vargsiuku failo kurimas:     " << fixed << setprecision(6) << diff_vargsiukai.count() << " s" << endl;
    cout << "Saunuoliu failo kurimas:     " << fixed << setprecision(6) << diff_saunuoliai.count() << " s" << endl;
    cout << "Bendras isvedimo laikas:     " << fixed << setprecision(6) << bendras_isvedimas << " s" << endl;
    cout << "BENDRAS laikas:              " << fixed << setprecision(6) << diff_total.count() << " s" << endl;
    cout << "------------------------------------" << endl;
    cout << "Vargsiuku: " << vargsiukai.size() << " | Saunuoliu: " << saunuoliai.size() << endl;
    cout << "Failai: " << vargsiukuFailas << ", " << saunuoliuFailas << endl;
    cout << "------------------------------------\n" << endl;
}

// STRATEGIJA 2: VIENAS KONTEINERIS + TRYNIMAS
// Pridėti šią funkciją į file_operations.cpp
// ============================================

void StudentuPadalinimas_Vector_S2(vector<Studentas>& studentai, bool pagalVidurki)
{
    if (studentai.empty()) {
        cout << "Nera studentu duomenu padalijimui!" << endl;
        return;
    }

    cout << "\n=== VECTOR - STRATEGIJA 2 (Trynimas) ===" << endl;
    auto start_total = high_resolution_clock::now();

    vector<Studentas> vargsiukai;
    vargsiukai.reserve(studentai.size() / 2);

    auto start_split = high_resolution_clock::now();

    // Perkelimas ir trynimas (neefektyvu dėl dažnų erase operacijų)
    for (auto it = studentai.begin(); it != studentai.end(); ) {
        double galutinisBalas = pagalVidurki ? it->galutinis_vidurkis : it->galutine_mediana;

        if (galutinisBalas < 5.0) {
            vargsiukai.push_back(*it);
            it = studentai.erase(it);  // Lėta operacija vektoriuje O(n)!
        } else {
            ++it;
        }
    }

    auto end_split = high_resolution_clock::now();
    duration<double> diff_split = end_split - start_split;

    // Rusiuojame
    auto start_sort = high_resolution_clock::now();

    if (pagalVidurki) {
        sort(vargsiukai.begin(), vargsiukai.end(), [](const Studentas& a, const Studentas& b) {
            return a.galutinis_vidurkis < b.galutinis_vidurkis;
        });
        sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
            return a.galutinis_vidurkis < b.galutinis_vidurkis;
        });
    } else {
        sort(vargsiukai.begin(), vargsiukai.end(), [](const Studentas& a, const Studentas& b) {
            return a.galutine_mediana < b.galutine_mediana;
        });
        sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
            return a.galutine_mediana < b.galutine_mediana;
        });
    }

    auto end_sort = high_resolution_clock::now();
    duration<double> diff_sort = end_sort - start_sort;

    string tipas = pagalVidurki ? "vidurkis" : "mediana";

    // Irasymas i failus
    auto start_output = high_resolution_clock::now();

    string vargsiukuFailas = "vargsiuku_" + tipas + "_vector_s2.txt";
    ofstream fout1(vargsiukuFailas);
    if (fout1.is_open()) {
        fout1 << left << setw(20) << "Vardas" << setw(20) << "Pavarde"
              << setw(25) << ("Galutinis (" + tipas + ")") << endl;
        fout1 << string(65, '-') << endl;
        for (const auto& s : vargsiukai) {
            double balas = pagalVidurki ? s.galutinis_vidurkis : s.galutine_mediana;
            fout1 << left << setw(20) << s.vardas << setw(20) << s.pavarde
                  << fixed << setprecision(2) << balas << endl;
        }
        fout1.close();
    }

    string saunuoliuFailas = "saunuoliu_" + tipas + "_vector_s2.txt";
    ofstream fout2(saunuoliuFailas);
    if (fout2.is_open()) {
        fout2 << left << setw(20) << "Vardas" << setw(20) << "Pavarde"
              << setw(25) << ("Galutinis (" + tipas + ")") << endl;
        fout2 << string(65, '-') << endl;
        for (const auto& s : studentai) {
            double balas = pagalVidurki ? s.galutinis_vidurkis : s.galutine_mediana;
            fout2 << left << setw(20) << s.vardas << setw(20) << s.pavarde
                  << fixed << setprecision(2) << balas << endl;
        }
        fout2.close();
    }

    auto end_output = high_resolution_clock::now();
    duration<double> diff_output = end_output - start_output;

    auto end_total = high_resolution_clock::now();
    duration<double> diff_total = end_total - start_total;

    cout << "\n--- LAIKO MATAVIMAS (STRATEGIJA 2) ---" << endl;
    cout << "Padalij.+Trynimo laikas:     " << fixed << setprecision(6) << diff_split.count() << " s" << endl;
    cout << "Rusiavimo laikas:            " << fixed << setprecision(6) << diff_sort.count() << " s" << endl;
    cout << "Isvedimo laikas:             " << fixed << setprecision(6) << diff_output.count() << " s" << endl;
    cout << "BENDRAS laikas:              " << fixed << setprecision(6) << diff_total.count() << " s" << endl;
    cout << "------------------------------------" << endl;
    cout << "Vargsiuku: " << vargsiukai.size() << " | Saunuoliu: " << studentai.size() << endl;
    cout << "------------------------------------\n" << endl;
}

// STRATEGIJA 3: STL STABLE_PARTITION

void StudentuPadalinimas_Vector_S3(vector<Studentas>& studentai, bool pagalVidurki)
{
    if (studentai.empty()) {
        cout << "Nera studentu duomenu padalijimui!" << endl;
        return;
    }

    cout << "\n=== VECTOR - STRATEGIJA 3 (STL partition) ===" << endl;
    auto start_total = high_resolution_clock::now();

    auto start_partition = high_resolution_clock::now();

    // std::stable_partition
    auto partition_point = std::stable_partition(studentai.begin(), studentai.end(),
        [pagalVidurki](const Studentas& s) {
            double balas = pagalVidurki ? s.galutinis_vidurkis : s.galutine_mediana;
            return balas < 5.0;
        });

    auto end_partition = high_resolution_clock::now();
    duration<double> diff_partition = end_partition - start_partition;

    // Sukuriame du vektorius is suskaidyto vektoriaus
    auto start_copy = high_resolution_clock::now();

    vector<Studentas> vargsiukai(studentai.begin(), partition_point);
    vector<Studentas> saunuoliai(partition_point, studentai.end());

    auto end_copy = high_resolution_clock::now();
    duration<double> diff_copy = end_copy - start_copy;

    // Rusiavimas
    auto start_sort = high_resolution_clock::now();

    if (pagalVidurki) {
        sort(vargsiukai.begin(), vargsiukai.end(), [](const Studentas& a, const Studentas& b) {
            return a.galutinis_vidurkis < b.galutinis_vidurkis;
        });
        sort(saunuoliai.begin(), saunuoliai.end(), [](const Studentas& a, const Studentas& b) {
            return a.galutinis_vidurkis < b.galutinis_vidurkis;
        });
    } else {
        sort(vargsiukai.begin(), vargsiukai.end(), [](const Studentas& a, const Studentas& b) {
            return a.galutine_mediana < b.galutine_mediana;
        });
        sort(saunuoliai.begin(), saunuoliai.end(), [](const Studentas& a, const Studentas& b) {
            return a.galutine_mediana < b.galutine_mediana;
        });
    }

    auto end_sort = high_resolution_clock::now();
    duration<double> diff_sort = end_sort - start_sort;

    string tipas = pagalVidurki ? "vidurkis" : "mediana";

    // Irasymas i failus
    auto start_output = high_resolution_clock::now();

    string vargsiukuFailas = "vargsiuku_" + tipas + "_vector_s3.txt";
    ofstream fout1(vargsiukuFailas);
    if (fout1.is_open()) {
        fout1 << left << setw(20) << "Vardas" << setw(20) << "Pavarde"
              << setw(25) << ("Galutinis (" + tipas + ")") << endl;
        fout1 << string(65, '-') << endl;
        for (const auto& s : vargsiukai) {
            double balas = pagalVidurki ? s.galutinis_vidurkis : s.galutine_mediana;
            fout1 << left << setw(20) << s.vardas << setw(20) << s.pavarde
                  << fixed << setprecision(2) << balas << endl;
        }
        fout1.close();
    }

    string saunuoliuFailas = "saunuoliu_" + tipas + "_vector_s3.txt";
    ofstream fout2(saunuoliuFailas);
    if (fout2.is_open()) {
        fout2 << left << setw(20) << "Vardas" << setw(20) << "Pavarde"
              << setw(25) << ("Galutinis (" + tipas + ")") << endl;
        fout2 << string(65, '-') << endl;
        for (const auto& s : saunuoliai) {
            double balas = pagalVidurki ? s.galutinis_vidurkis : s.galutine_mediana;
            fout2 << left << setw(20) << s.vardas << setw(20) << s.pavarde
                  << fixed << setprecision(2) << balas << endl;
        }
        fout2.close();
    }

    auto end_output = high_resolution_clock::now();
    duration<double> diff_output = end_output - start_output;

    auto end_total = high_resolution_clock::now();
    duration<double> diff_total = end_total - start_total;

    cout << "\n--- LAIKO MATAVIMAS (STRATEGIJA 3) ---" << endl;
    cout << "Partition laikas:            " << fixed << setprecision(6) << diff_partition.count() << " s" << endl;
    cout << "Kopijavimo laikas:           " << fixed << setprecision(6) << diff_copy.count() << " s" << endl;
    cout << "Rusiavimo laikas:            " << fixed << setprecision(6) << diff_sort.count() << " s" << endl;
    cout << "Isvedimo laikas:             " << fixed << setprecision(6) << diff_output.count() << " s" << endl;
    cout << "BENDRAS laikas:              " << fixed << setprecision(6) << diff_total.count() << " s" << endl;
    cout << "------------------------------------" << endl;
    cout << "   std::stable_partition - greiciausias sprendimas" << endl;
    cout << "   Sudetingumas: O(n log n)" << endl;
    cout << "   Rekomenduojama VISIEMS duomenu kiekiams" << endl;
    cout << "Vargsiuku: " << vargsiukai.size() << " | Saunuoliu: " << saunuoliai.size() << endl;
    cout << "------------------------------------\n" << endl;
}

// LIST KONTEINERIO FUNKCIJOS

bool skaitytiDuomenisIsFailo_List(const string& failoPavadinimas, list<Studentas>& studentai)
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

        if (!(ss >> studentas.vardas >> studentas.pavarde)) {
            continue;
        }

        int pazymys;
        vector<int> visi_pazymiai;

        while (ss >> pazymys) {
            if (pazymys >= 1 && pazymys <= 10) {
                visi_pazymiai.push_back(pazymys);
            }
        }

        if (visi_pazymiai.empty()) continue;

        studentas.egzrezultatas = visi_pazymiai.back();
        visi_pazymiai.pop_back();
        studentas.ndpazymiai = visi_pazymiai;

        if (studentas.ndpazymiai.size() > 0) {
            int sum = 0;
            for (int nd : studentas.ndpazymiai) {
                sum += nd;
            }
            studentas.galutinis_vidurkis = double(sum) / studentas.ndpazymiai.size() * 0.4 + studentas.egzrezultatas * 0.6;
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

    cout << "Sekmingai nuskaityta " << studentuSkaicius << " studentu duomenys (LIST). " << endl;
    cout << "Duomenu nuskaitymo laikas: " << fixed << setprecision(6) << diff.count() << " s" << endl;
    return true;
}

// LIST - STRATEGIJA 1: Kopijavimas

void StudentuPadalinimas_List_S1(const list<Studentas>& studentai, bool pagalVidurki)
{
    if (studentai.empty()) {
        cout << "Nera studentu duomenu padalijimui!" << endl;
        return;
    }

    cout << "\n=== LIST - STRATEGIJA 1 (Kopijavimas) ===" << endl;
    auto start_total = high_resolution_clock::now();

    list<Studentas> vargsiukai;
    list<Studentas> saunuoliai;

    auto start_split = high_resolution_clock::now();

    for (const auto& studentas : studentai) {
        double galutinisBalas = pagalVidurki ? studentas.galutinis_vidurkis : studentas.galutine_mediana;

        if (galutinisBalas < 5.0) {
            vargsiukai.push_back(studentas);
        } else {
            saunuoliai.push_back(studentas);
        }
    }

    auto end_split = high_resolution_clock::now();
    duration<double> diff_split = end_split - start_split;

    // Rusiavimas
    auto start_sort = high_resolution_clock::now();

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

    auto end_sort = high_resolution_clock::now();
    duration<double> diff_sort = end_sort - start_sort;

    string tipas = pagalVidurki ? "vidurkis" : "mediana";

    // Isvedimas
    auto start_output = high_resolution_clock::now();

    string vargsiukuFailas = "vargsiuku_" + tipas + "_list_s1.txt";
    ofstream fout1(vargsiukuFailas);
    if (fout1.is_open()) {
        fout1 << left << setw(20) << "Vardas" << setw(20) << "Pavarde"
              << setw(25) << ("Galutinis (" + tipas + ")") << endl;
        fout1 << string(65, '-') << endl;
        for (const auto& s : vargsiukai) {
            double balas = pagalVidurki ? s.galutinis_vidurkis : s.galutine_mediana;
            fout1 << left << setw(20) << s.vardas << setw(20) << s.pavarde
                  << fixed << setprecision(2) << balas << endl;
        }
        fout1.close();
    }

    string saunuoliuFailas = "saunuoliu_" + tipas + "_list_s1.txt";
    ofstream fout2(saunuoliuFailas);
    if (fout2.is_open()) {
        fout2 << left << setw(20) << "Vardas" << setw(20) << "Pavarde"
              << setw(25) << ("Galutinis (" + tipas + ")") << endl;
        fout2 << string(65, '-') << endl;
        for (const auto& s : saunuoliai) {
            double balas = pagalVidurki ? s.galutinis_vidurkis : s.galutine_mediana;
            fout2 << left << setw(20) << s.vardas << setw(20) << s.pavarde
                  << fixed << setprecision(2) << balas << endl;
        }
        fout2.close();
    }

    auto end_output = high_resolution_clock::now();
    duration<double> diff_output = end_output - start_output;

    auto end_total = high_resolution_clock::now();
    duration<double> diff_total = end_total - start_total;

    cout << "\n--- LAIKO MATAVIMAS (STRATEGIJA 1) ---" << endl;
    cout << "Padalijimo laikas:           " << fixed << setprecision(6) << diff_split.count() << " s" << endl;
    cout << "Rusiavimo laikas:            " << fixed << setprecision(6) << diff_sort.count() << " s" << endl;
    cout << "Isvedimo laikas:             " << fixed << setprecision(6) << diff_output.count() << " s" << endl;
    cout << "BENDRAS laikas:              " << fixed << setprecision(6) << diff_total.count() << " s" << endl;
    cout << "Vargsiuku: " << vargsiukai.size() << " | Saunuoliu: " << saunuoliai.size() << endl;
    cout << "------------------------------------\n" << endl;
}

// LIST - STRATEGIJA 2: Trynimas

void StudentuPadalinimas_List_S2(list<Studentas>& studentai, bool pagalVidurki)
{
    if (studentai.empty()) {
        cout << "Nera studentu duomenu padalijimui!" << endl;
        return;
    }

    cout << "\n=== LIST - STRATEGIJA 2 (Trynimas) ===" << endl;
    auto start_total = high_resolution_clock::now();

    list<Studentas> vargsiukai;

    auto start_split = high_resolution_clock::now();

    for (auto it = studentai.begin(); it != studentai.end(); ) {
        double galutinisBalas = pagalVidurki ? it->galutinis_vidurkis : it->galutine_mediana;

        if (galutinisBalas < 5.0) {
            vargsiukai.push_back(*it);
            it = studentai.erase(it);
        } else {
            ++it;
        }
    }

    auto end_split = high_resolution_clock::now();
    duration<double> diff_split = end_split - start_split;

    // Rusiavimas
    auto start_sort = high_resolution_clock::now();

    if (pagalVidurki) {
        vargsiukai.sort([](const Studentas& a, const Studentas& b) {
            return a.galutinis_vidurkis < b.galutinis_vidurkis;
        });
        studentai.sort([](const Studentas& a, const Studentas& b) {
            return a.galutinis_vidurkis < b.galutinis_vidurkis;
        });
    } else {
        vargsiukai.sort([](const Studentas& a, const Studentas& b) {
            return a.galutine_mediana < b.galutine_mediana;
        });
        studentai.sort([](const Studentas& a, const Studentas& b) {
            return a.galutine_mediana < b.galutine_mediana;
        });
    }

    auto end_sort = high_resolution_clock::now();
    duration<double> diff_sort = end_sort - start_sort;

    string tipas = pagalVidurki ? "vidurkis" : "mediana";

    // Isvedimas
    auto start_output = high_resolution_clock::now();

    string vargsiukuFailas = "vargsiuku_" + tipas + "_list_s2.txt";
    ofstream fout1(vargsiukuFailas);
    if (fout1.is_open()) {
        fout1 << left << setw(20) << "Vardas" << setw(20) << "Pavarde"
              << setw(25) << ("Galutinis (" + tipas + ")") << endl;
        fout1 << string(65, '-') << endl;
        for (const auto& s : vargsiukai) {
            double balas = pagalVidurki ? s.galutinis_vidurkis : s.galutine_mediana;
            fout1 << left << setw(20) << s.vardas << setw(20) << s.pavarde
                  << fixed << setprecision(2) << balas << endl;
        }
        fout1.close();
    }

    string saunuoliuFailas = "saunuoliu_" + tipas + "_list_s2.txt";
    ofstream fout2(saunuoliuFailas);
    if (fout2.is_open()) {
        fout2 << left << setw(20) << "Vardas" << setw(20) << "Pavarde"
              << setw(25) << ("Galutinis (" + tipas + ")") << endl;
        fout2 << string(65, '-') << endl;
        for (const auto& s : studentai) {
            double balas = pagalVidurki ? s.galutinis_vidurkis : s.galutine_mediana;
            fout2 << left << setw(20) << s.vardas << setw(20) << s.pavarde
                  << fixed << setprecision(2) << balas << endl;
        }
        fout2.close();
    }

    auto end_output = high_resolution_clock::now();
    duration<double> diff_output = end_output - start_output;

    auto end_total = high_resolution_clock::now();
    duration<double> diff_total = end_total - start_total;

    cout << "\n--- LAIKO MATAVIMAS (STRATEGIJA 2) ---" << endl;
    cout << "Padalij.+Trynimo laikas:     " << fixed << setprecision(6) << diff_split.count() << " s" << endl;
    cout << "Rusiavimo laikas:            " << fixed << setprecision(6) << diff_sort.count() << " s" << endl;
    cout << "Isvedimo laikas:             " << fixed << setprecision(6) << diff_output.count() << " s" << endl;
    cout << "BENDRAS laikas:              " << fixed << setprecision(6) << diff_total.count() << " s" << endl;
    cout << "------------------------------------" << endl;
    cout << "Vargsiuku: " << vargsiukai.size() << " | Saunuoliu: " << studentai.size() << endl;
    cout << "------------------------------------\n" << endl;
}
