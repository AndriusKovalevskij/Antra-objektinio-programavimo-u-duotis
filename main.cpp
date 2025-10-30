#include "menu.h"
#include "student_struct.h"
#include "operations.h"
#include "file_operations.h"
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

int main()
{
    cout << "======================================" << endl;
    cout << "  Studentu pazymiu sistema v0.3" << endl;
    cout << "  Konteineriu testavimas: Vector vs List" << endl;
    cout << "======================================" << endl;

    vector<Studentas> GrupeVector;
    list<Studentas> GrupeList;

    while (true)
    {
        int pasirinkimas = rodytiMeniu();

        switch (pasirinkimas)
        {
            case 1: {
                // Rankinis ivedimas su VECTOR
                int m = ivestiSkaiciu("Kiek studentu grupeje?: ", 1, 100000);
                for (int z = 0; z < m; z++) {
                    GrupeVector.push_back(Stud_ivestis(z + 1, false));
                }
                rodytiRezultatus_Vector(GrupeVector);
                break;
            }

            case 2: {
                // Atsitiktinis generavimas su VECTOR
                int m = ivestiSkaiciu("Kiek studentu grupeje?: ", 1, 100000);
                for (int z = 0; z < m; z++) {
                    GrupeVector.push_back(Stud_ivestis(z + 1, true));
                }
                rodytiRezultatus_Vector(GrupeVector);
                break;
            }

            case 3: {
                // Skaitymas is failo su VECTOR
                cout << "Iveskite failo pavadinima (pvz., studentai_1000.txt): ";
                string failoPavadinimas;
                cin >> failoPavadinimas;

                if (skaitytiDuomenisIsFailo_Vector(failoPavadinimas, GrupeVector))
                {
                    int pasirinkimas = ivestiSkaiciu("\nPagal ka padalinti studentus?\n1 - Pagal vidurki\n2 - Pagal mediana\nJusu pasirinkimas: ", 1, 2);
                    bool pagalVidurki = (pasirinkimas == 1);
                    StudentuPadalinimas_Vector(GrupeVector, pagalVidurki);
                } else {
                    cout << "Nepavyko nuskaityti duomenu is failo." << endl;
                }
                break;
            }

            case 4: {
                // Skaitymas is failo su LIST
                cout << "Iveskite failo pavadinima (pvz., studentai_1000.txt): ";
                string failoPavadinimas;
                cin >> failoPavadinimas;

                if (skaitytiDuomenisIsFailo_List(failoPavadinimas, GrupeList))
                {
                    int pasirinkimas = ivestiSkaiciu("\nPagal ka padalinti studentus?\n1 - Pagal vidurki\n2 - Pagal mediana\nJusu pasirinkimas: ", 1, 2);
                    bool pagalVidurki = (pasirinkimas == 1);
                    StudentuPadalinimas_List(GrupeList, pagalVidurki);
                } else {
                    cout << "Nepavyko nuskaityti duomenu is failo." << endl;
                }
                break;
            }

            case 5: {
                // Testavimo failu generavimas
                cout << "\n=== TESTAVIMO FAILU GENERAVIMAS ===" << endl;
                vector<int> dydziai = {1000, 10000, 100000, 1000000, 10000000};

                for (int kiekis : dydziai) {
                    string failoPav = "studentai_" + to_string(kiekis) + ".txt";
                    GeneruotiStudentuFaila(failoPav, kiekis);
                }

                cout << "\nVisi testiniai failai sugeneruoti!" << endl;
                break;
            }

            case 6: {
                cout << "\n======================================" << endl;
                cout << "  Dekojame, kad naudojotes programa!" << endl;
                cout << "======================================" << endl;
                return 0;
            }
        }

        cout << "\nAr norite testi programos darba? (1 - taip, 2 - ne): ";
        int testi = ivestiSkaiciu("", 1, 2);

        if (testi == 2)
        {
            cout << "\n======================================" << endl;
            cout << "  Dekojame, kad naudojotes programa!" << endl;
            cout << "======================================" << endl;
            break;
        }

        GrupeVector.clear();
        GrupeList.clear();
    }

    return 0;
}
