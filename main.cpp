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
    cout << "  Visos Vector strategijos" << endl;
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
        cout << "4 - Testuoti Vector Strategija 3 (OPTIMALI)" << endl;
        cout << "5 - Palyginti visas Vector strategijas" << endl;
        cout << "6 - Baigti programa" << endl;
        cout << "==================================" << endl;

        int pasirinkimas = ivestiSkaiciu("Pasirinkite (1-6): ", 1, 6);

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
                cout << "\nIveskite failo pavadinima: ";
                string failoPavadinimas;
                cin >> failoPavadinimas;

                studentai.clear();
                if (skaitytiDuomenisIsFailo_Vector(failoPavadinimas, studentai))
                {
                    int pasirinkimas_balas = ivestiSkaiciu("\nPagal ka?\n1 - Vidurkis\n2 - Mediana\n: ", 1, 2);
                    bool pagalVidurki = (pasirinkimas_balas == 1);
                    StudentuPadalinimas_Vector_S1(studentai, pagalVidurki);
                }
                break;
            }

            case 3: {
                // Testuojame Vector S2
                cout << "\nIveskite failo pavadinima: ";
                string failoPavadinimas;
                cin >> failoPavadinimas;

                studentai.clear();
                if (skaitytiDuomenisIsFailo_Vector(failoPavadinimas, studentai))
                {
                    int pasirinkimas_balas = ivestiSkaiciu("\nPagal ka?\n1 - Vidurkis\n2 - Mediana\n: ", 1, 2);
                    bool pagalVidurki = (pasirinkimas_balas == 1);

                    cout << "ISPEJIMAS: S2 leta dideliems duomenims!" << endl;
                    StudentuPadalinimas_Vector_S2(studentai, pagalVidurki);
                }
                break;
            }

            case 4: {
                // Testuojame Vector S3
                cout << "\nIveskite failo pavadinima: ";
                string failoPavadinimas;
                cin >> failoPavadinimas;

                studentai.clear();
                if (skaitytiDuomenisIsFailo_Vector(failoPavadinimas, studentai))
                {
                    int pasirinkimas_balas = ivestiSkaiciu("\nPagal ka?\n1 - Vidurkis\n2 - Mediana\n: ", 1, 2);
                    bool pagalVidurki = (pasirinkimas_balas == 1);

                    StudentuPadalinimas_Vector_S3(studentai, pagalVidurki);
                }
                break;
            }

            case 5: {
                // Palyginame visas strategijas
                cout << "\nIveskite failo pavadinima: ";
                string failoPavadinimas;
                cin >> failoPavadinimas;

                int pasirinkimas_balas = ivestiSkaiciu("\nPagal ka?\n1 - Vidurkis\n2 - Mediana\n: ", 1, 2);
                bool pagalVidurki = (pasirinkimas_balas == 1);

                cout << "\n========================================" << endl;
                cout << "  VECTOR STRATEGIJU PALYGINIMAS" << endl;
                cout << "========================================\n" << endl;

                // S1
                studentai.clear();
                if (skaitytiDuomenisIsFailo_Vector(failoPavadinimas, studentai)) {
                    StudentuPadalinimas_Vector_S1(studentai, pagalVidurki);
                }

                // S2
                studentai.clear();
                if (skaitytiDuomenisIsFailo_Vector(failoPavadinimas, studentai)) {
                    StudentuPadalinimas_Vector_S2(studentai, pagalVidurki);
                }

                // S3
                studentai.clear();
                if (skaitytiDuomenisIsFailo_Vector(failoPavadinimas, studentai)) {
                    StudentuPadalinimas_Vector_S3(studentai, pagalVidurki);
                }

                cout << "\n========================================" << endl;
                cout << "  PALYGINIMAS BAIGTAS" << endl;
                cout << "========================================" << endl;
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
