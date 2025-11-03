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
    cout << "  Vector ir List strategiju tyrimas" << endl;
    cout << "======================================" << endl;

    vector<Studentas> studentaiVector;
    list<Studentas> studentaiList;

    while (true)
    {
        cout << "\n========================================" << endl;
        cout << "    PAGRINDINIS MENIU" << endl;
        cout << "========================================" << endl;
        cout << "GENERAVIMAS:" << endl;
        cout << "1 - Sugeneruoti testini faila" << endl;
        cout << "\nVECTOR STRATEGIJOS:" << endl;
        cout << "2 - Vector Strategija 1" << endl;
        cout << "3 - Vector Strategija 2 (leta)" << endl;
        cout << "4 - Vector Strategija 3 (optimali)" << endl;
        cout << "5 - Palyginti visas Vector strategijas" << endl;
        cout << "\nLIST STRATEGIJOS:" << endl;
        cout << "6 - List Strategija 1" << endl;
        cout << "7 - List Strategija 2" << endl;
        cout << "8 - List Strategija 3" << endl;
        cout << "----------------------------------" << endl;
        cout << "9 - Baigti programa" << endl;
        cout << "==================================" << endl;

        int pasirinkimas = ivestiSkaiciu("Pasirinkite (1-8): ", 1, 8);

        string failoPavadinimas;
        bool pagalVidurki;
        int pasirinkimas_balas;

        switch (pasirinkimas)
        {
            case 1: {
                // Generuojame testini faila
                int kiekis = ivestiSkaiciu("Kiek studentu? (pvz: 1000, 10000, 100000): ", 100, 10000000);
                string failoPav = "studentai_" + to_string(kiekis) + ".txt";
                GeneruotiStudentuFaila(failoPav, kiekis);
                break;
            }

            // ============ VECTOR STRATEGIJOS ============
            case 2: {
                cout << "\nIveskite failo pavadinima: ";
                cin >> failoPavadinimas;
                pasirinkimas_balas = ivestiSkaiciu("\nPagal ka?\n1 - Vidurkis\n2 - Mediana\n: ", 1, 2);
                pagalVidurki = (pasirinkimas_balas == 1);

                studentaiVector.clear();
                if (skaitytiDuomenisIsFailo_Vector(failoPavadinimas, studentaiVector)) {
                    StudentuPadalinimas_Vector_S1(studentaiVector, pagalVidurki);
                }
                break;
            }

            case 3: {
                cout << "\nIveskite failo pavadinima: ";
                cin >> failoPavadinimas;
                pasirinkimas_balas = ivestiSkaiciu("\nPagal ka?\n1 - Vidurkis\n2 - Mediana\n: ", 1, 2);
                pagalVidurki = (pasirinkimas_balas == 1);

                studentaiVector.clear();
                if (skaitytiDuomenisIsFailo_Vector(failoPavadinimas, studentaiVector)) {
                    cout << "\n ISPEJIMAS: S2 leta >10K irasu!" << endl;
                    StudentuPadalinimas_Vector_S2(studentaiVector, pagalVidurki);
                }
                break;
            }

            case 4: {
                cout << "\nIveskite failo pavadinima: ";
                cin >> failoPavadinimas;
                pasirinkimas_balas = ivestiSkaiciu("\nPagal ka?\n1 - Vidurkis\n2 - Mediana\n: ", 1, 2);
                pagalVidurki = (pasirinkimas_balas == 1);

                studentaiVector.clear();
                if (skaitytiDuomenisIsFailo_Vector(failoPavadinimas, studentaiVector)) {
                    cout << "\n Optimali Vector strategija!" << endl;
                    StudentuPadalinimas_Vector_S3(studentaiVector, pagalVidurki);
                }
                break;
            }

            case 5: {
                cout << "\nIveskite failo pavadinima: ";
                cin >> failoPavadinimas;
                pasirinkimas_balas = ivestiSkaiciu("\nPagal ka?\n1 - Vidurkis\n2 - Mediana\n: ", 1, 2);
                pagalVidurki = (pasirinkimas_balas == 1);

                cout << "\n========================================" << endl;
                cout << "  VECTOR STRATEGIJU PALYGINIMAS" << endl;
                cout << "========================================\n" << endl;

                studentaiVector.clear();
                if (skaitytiDuomenisIsFailo_Vector(failoPavadinimas, studentaiVector)) {
                    StudentuPadalinimas_Vector_S1(studentaiVector, pagalVidurki);
                }

                studentaiVector.clear();
                if (skaitytiDuomenisIsFailo_Vector(failoPavadinimas, studentaiVector)) {
                    StudentuPadalinimas_Vector_S2(studentaiVector, pagalVidurki);
                }

                studentaiVector.clear();
                if (skaitytiDuomenisIsFailo_Vector(failoPavadinimas, studentaiVector)) {
                    StudentuPadalinimas_Vector_S3(studentaiVector, pagalVidurki);
                }
                break;
            }

            // ============ LIST STRATEGIJOS ============
            case 6: {
                cout << "\nIveskite failo pavadinima: ";
                cin >> failoPavadinimas;
                pasirinkimas_balas = ivestiSkaiciu("\nPagal ka?\n1 - Vidurkis\n2 - Mediana\n: ", 1, 2);
                pagalVidurki = (pasirinkimas_balas == 1);

                studentaiList.clear();
                if (skaitytiDuomenisIsFailo_List(failoPavadinimas, studentaiList)) {
                    StudentuPadalinimas_List_S1(studentaiList, pagalVidurki);
                }
                break;
            }

            case 7: {
                cout << "\nIveskite failo pavadinima: ";
                cin >> failoPavadinimas;
                pasirinkimas_balas = ivestiSkaiciu("\nPagal ka?\n1 - Vidurkis\n2 - Mediana\n: ", 1, 2);
                pagalVidurki = (pasirinkimas_balas == 1);

                studentaiList.clear();
                if (skaitytiDuomenisIsFailo_List(failoPavadinimas, studentaiList)) {
                    cout << "\nList'ui efektyvu - O(1) trynimas!" << endl;
                    StudentuPadalinimas_List_S2(studentaiList, pagalVidurki);
                }
                break;
            }

            case 8: {
                cout << "\nIveskite failo pavadinima: ";
                cin >> failoPavadinimas;
                pasirinkimas_balas = ivestiSkaiciu("\nPagal ka?\n1 - Vidurkis\n2 - Mediana\n: ", 1, 2);
                pagalVidurki = (pasirinkimas_balas == 1);

                studentaiList.clear();
                if (skaitytiDuomenisIsFailo_List(failoPavadinimas, studentaiList)) {
                    cout << "\n OPTIMALI List strategija!" << endl;
                    StudentuPadalinimas_List_S3(studentaiList, pagalVidurki);
                }
                break;
            }

            case 9: {
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
