#include "menu.h"
#include "student_struct.h"
#include "operations.h"
#include "file_operations.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cout << "Laba diena" << endl;
    vector<Studentas> Grupe;

    while (true)
    {
        int pasirinkimas = rodytiMeniu();

        switch (pasirinkimas)
        {
            case 1: {
                int m = ivestiSkaiciu("Kiek studentu grupeje?: ", 1, 100000);
                for (int z = 0; z < m; z++) {
                    Grupe.push_back(Stud_ivestis(z + 1, false));
                }
                rodytiRezultatus(Grupe);
                break;
            }
            case 2: {
                int m = ivestiSkaiciu("Kiek studentu grupeje?: ", 1, 100000);
                for (int z = 0; z < m; z++) {
                    Grupe.push_back(Stud_ivestis(z + 1, true));
                }
                rodytiRezultatus(Grupe);
                break;
            }
            case 3: {
                cout << "Iveskite failo pavadinima (pvz., kursiokai.txt): ";
                string failoPavadinimas;
                cin >> failoPavadinimas;

                if (skaitytiDuomenisIsFailo(failoPavadinimas, Grupe))
                {
                    // Rusiavimas
                    int rusiuotiPagal = ivestiSkaiciu("\nKaip norite rusiuoti studentus?\n1 - Pagal varda\n2 - Pagal pavarde\nPasirinkimas: ", 1, 2);
                    if (rusiuotiPagal == 1) {
                        sort(Grupe.begin(), Grupe.end(), palyginimasPagalVarda);
                    } else {
                        sort(Grupe.begin(), Grupe.end(), palyginimasPagalPavarde);
                    }

                    // Pasirenkamas tipas
                    int pasirinkimas = ivestiSkaiciu("\nPasirinkite galutinio ivertinimo tipa:\n1 - Pagal vidurki\n2 - Pagal mediana\n3 - Rodyti abu\nJusu pasirinkimas: ", 1, 3);

                    string isvestiesFailas = "rezultatai.txt";

                    if (pasirinkimas == 1) {
                        isvestiRezultatusIFaila(isvestiesFailas, Grupe, true, false);
                    } else if (pasirinkimas == 2) {
                        isvestiRezultatusIFaila(isvestiesFailas, Grupe, false, false);
                    } else {
                        isvestiRezultatusIFaila(isvestiesFailas, Grupe, true, true);
                    }
                } else {
                    cout << "Nepavyko nuskaityti duomenu is failo." << endl;
                }
                break;
            }
            case 4: {
                cout << "Geros dienos!" << endl;
                return 0;
            }
            case 5: {
                vector<int> dydziai = {1000, 10000, 100000, 1000000, 10000000};
                for (int kiekis : dydziai) {
                    string failoPav = "studentai_" + to_string(kiekis) + ".txt";
                    GeneruotiStudentuFaila(failoPav, kiekis);
                }
                break;
            }
        }

        cout << "\nAr norite testi programos darba? (1 - taip, 2 - ne): ";
        int testi = ivestiSkaiciu("", 1, 2);
        if (testi == 2)
        {
            cout << "Geros dienos!" << endl;
            break;
        }

        Grupe.clear();
    }
    return 0;
}
