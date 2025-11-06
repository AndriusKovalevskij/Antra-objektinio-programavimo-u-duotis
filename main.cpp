#include "student.h"
#include "operations.h"
#include "file_operations.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

void spausdintiStudentus(const vector<Studentas>& studentai, bool pagalVidurki);

int main()
{
    cout << "======================================" << endl;
    cout << "  Studentu pazymiu sistema v1.1" << endl;
    cout << "======================================" << endl;

    vector<Studentas> studentai;

    while (true)
    {
        cout << "\n========================================" << endl;
        cout << "    PAGRINDINIS MENIU" << endl;
        cout << "========================================" << endl;
        cout << "1 - Ivesti studenta ranka" << endl;
        cout << "2 - Ivesti studenta su atsitiktiniais pazymiais" << endl;
        cout << "3 - Nuskaityti duomenis is failo" << endl;
        cout << "4 - Sugeneruoti testini faila" << endl;
        cout << "5 - Padalinti studentus (vargsiukai/saunuoliai)" << endl;
        cout << "6 - Baigti programa" << endl;
        cout << "========================================" << endl;

        int pasirinkimas = ivestiSkaiciu("Pasirinkite (1-6): ", 1, 6);

        switch (pasirinkimas)
        {
            case 1: {
                // Ivedimas rankiniu budu
                int kiekis = ivestiSkaiciu("Kiek studentu norite ivesti? ", 1, 100);
                for (int i = 0; i < kiekis; i++) {
                    Studentas s = Stud_ivestis(i + 1, false);
                    studentai.push_back(s);
                }
                cout << "\nSekmingai ivesta " << kiekis << " studentu!" << endl;
                break;
            }

            case 2: {
                // Ivedimas su atsitiktiniais pazymiais
                int kiekis = ivestiSkaiciu("Kiek studentu norite ivesti? ", 1, 100);
                for (int i = 0; i < kiekis; i++) {
                    Studentas s = Stud_ivestis(i + 1, true);
                    studentai.push_back(s);
                }
                cout << "\nSekmingai ivesta " << kiekis << " studentu!" << endl;
                break;
            }

            case 3: {
                // Skaitymas is failo
                string failoPavadinimas;
                cout << "\nIveskite failo pavadinima: ";
                cin >> failoPavadinimas;

                studentai.clear();
                if (skaitytiDuomenisIsFailo(failoPavadinimas, studentai)) {
                    cout << "Duomenys sekmingai nuskaityti!" << endl;
                } else {
                    cout << "Nepavyko nuskaityti duomenu!" << endl;
                }
                break;
            }

            case 4: {
                // Generavimas
                int kiekis = ivestiSkaiciu("Kiek studentu? (pvz: 1000, 10000, 100000, 1000000): ", 100, 10000000);
                string failoPav = "studentai_" + to_string(kiekis) + ".txt";
                GeneruotiStudentuFaila(failoPav, kiekis);
                break;
            }

            case 5: {
                // Padalijimas
                if (studentai.empty()) {
                    cout << "\nPirmiausia nuskaitykite duomenis is failo (pasirinkimas 3)!" << endl;
                    break;
                }

                int pasirinkimas_balas = ivestiSkaiciu("\nPagal ka?\n1 - Vidurkis\n2 - Mediana\nPasirinkimas: ", 1, 2);
                bool pagalVidurki = (pasirinkimas_balas == 1);

                StudentuPadalinimas_Vector(studentai, pagalVidurki);
                break;
            }

            case 6: {
                cout << "\n======================================" << endl;
                cout << "  Dekojame, kad naudojotes programa!" << endl;
                cout << "======================================" << endl;
                return 0;
            }
        }

        cout << "\nAr norite testi? (1 - taip, 2 - ne): ";
        int testi = ivestiSkaiciu("", 1, 2);

        if (testi == 2) {
            cout << "\n======================================" << endl;
            cout << "  Dekojame, kad naudojotes programa!" << endl;
            cout << "======================================" << endl;
            break;
        }
    }

    return 0;
}

void spausdintiStudentus(const vector<Studentas>& studentai, bool pagalVidurki)
{
    string tipas = pagalVidurki ? "Vidurkis" : "Mediana";

    cout << "\n" << string(70, '=') << endl;
    cout << left << setw(20) << "Vardas"
         << setw(20) << "Pavarde"
         << setw(15) << tipas << endl;
    cout << string(70, '-') << endl;

    for (const auto& s : studentai) {
        double balas = pagalVidurki ? s.galutinisVidurkis() : s.galutineMediana();
        cout << left << setw(20) << s.vardas()
             << setw(20) << s.pavarde()
             << fixed << setprecision(2) << balas << endl;
    }

    cout << string(70, '=') << endl;
    cout << "Viso studentu: " << studentai.size() << endl;
}
