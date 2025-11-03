#include "student_struct.h"
#include "operations.h"
#include "file_operations.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cout << "======================================" << endl;
    cout << "  Studentu pazymiu sistema v1.0" << endl;
    cout << "  Strategijos 1-2 - Vector" << endl;
    cout << "======================================" << endl;

    vector<Studentas> studentai;

    while (true)
    {
        cout << "\n==================================" << endl;
        cout << "    MENIU" << endl;
        cout << "==================================" << endl;
        cout << "1 - Sugeneruoti testini faila" << endl;
        cout << "2 - Testuoti Vector Strategija 1" << endl;
        cout << "3 - Testuoti Vector Strategija 2" << endl;
        cout << "4 - Baigti programa" << endl;
        cout << "==================================" << endl;

        int pasirinkimas = ivestiSkaiciu("Pasirinkite (1-4): ", 1, 4);

        switch (pasirinkimas)
        {
            case 1: {
                // Generuojame testini faila
                int kiekis = ivestiSkaiciu("Kiek studentu generuoti? (pvz: 1000, 10000): ", 100, 10000000);
                string failoPav = "studentai_" + to_string(kiekis) + ".txt";
                GeneruotiStudentuFaila(failoPav, kiekis);
                break;
            }

            case 2: {
                // Testuojame Vector S1
                cout << "\nIveskite failo pavadinima (pvz., studentai_1000.txt): ";
                string failoPavadinimas;
                cin >> failoPavadinimas;

                studentai.clear();
                if (skaitytiDuomenisIsFailo_Vector(failoPavadinimas, studentai))
                {
                    int pasirinkimas_balas = ivestiSkaiciu("\nPagal ka padalinti?\n1 - Pagal vidurki\n2 - Pagal mediana\nPasirinkimas: ", 1, 2);
                    bool pagalVidurki = (pasirinkimas_balas == 1);

                    StudentuPadalinimas_Vector_S1(studentai, pagalVidurki);
                } else {
                    cout << "Nepavyko nuskaityti duomenu is failo." << endl;
                }
                break;
            }

            case 3: {
                // Testuojame Vector S2
                cout << "\nIveskite failo pavadinima (pvz., studentai_1000.txt): ";
                string failoPavadinimas;
                cin >> failoPavadinimas;

                studentai.clear();
                if (skaitytiDuomenisIsFailo_Vector(failoPavadinimas, studentai))
                {
                    int pasirinkimas_balas = ivestiSkaiciu("\nPagal ka padalinti?\n1 - Pagal vidurki\n2 - Pagal mediana\nPasirinkimas: ", 1, 2);
                    bool pagalVidurki = (pasirinkimas_balas == 1);
                    StudentuPadalinimas_Vector_S2(studentai, pagalVidurki);
                } else {
                    cout << "Nepavyko nuskaityti duomenu is failo." << endl;
                }
                break;
            }

            case 4: {
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
