#include "operations.h"
#include <iostream>
#include <sstream>
#include <random>
#include <cctype>

using namespace std;

static std::mt19937 gen(std::random_device{}());

void ivestiesIsvalymas()
{
    cin.clear();
    cin.ignore(10000, '\n');
}

int ivestiSkaiciu(const string& zinute, int min_pazymys, int max_pazymys)
{
    int skaicius;
    while (true)
    {
        cout << zinute;
        if (!(cin >> skaicius))
        {
            cout << "Klaida: ivestis turi buti skaicius! Pabandykite dar karta." << endl;
            ivestiesIsvalymas();
            continue;
        }
        if (skaicius < min_pazymys || skaicius > max_pazymys) {
            cout << "Klaida: skaicius turi buti nuo " << min_pazymys << " iki " << max_pazymys << "! Pabandykite dar karta." << endl;
            continue;
        }
        break;
    }
    return skaicius;
}

string ivestiVarda(const string& zinute)
{
    string vardas;
    while (true)
    {
        cout << zinute;
        cin >> vardas;
        bool tinkamas = true;

        if (vardas.empty())
        {
            cout << "Klaida: vardas/pavarde negali buti be raidziu! Pabandykite dar karta." << endl;
            tinkamas = false;
        } else {
            for (char c : vardas)
            {
                if (!isalpha(c))
                {
                    cout << "Klaida: vardas/pavarde turi buti tik is raidziu! Pabandykite dar karta." << endl;
                    tinkamas = false;
                    break;
                }
            }
        }
        if (tinkamas) break;
        ivestiesIsvalymas();
    }
    return vardas;
}

void NDpazymiuivestis(vector<int>& ndpazymiai)
{
    string eilute;
    int pazymys;
    cout << "Iveskite namu darbu pazymius (1-10). Norint baigti ivedima, paspauskite ENTER 2 kartus:" << endl;
    cin.ignore();
    int numeris = 1;
    while (true)
    {
        cout << numeris << ": ";
        getline(cin, eilute);
        if (eilute.empty()) break;
        stringstream ss(eilute);
        if (ss >> pazymys)
        {
            if (pazymys >= 1 && pazymys <= 10)
            {
                ndpazymiai.push_back(pazymys);
                numeris++;
            } else {
                cout << "Klaida: pazymys turi buti nuo 1 iki 10!" << endl;
            }
        } else {
            cout << "Klaida: ivestis turi buti skaicius!" << endl;
        }
    }
}

int AtsitiktinioPazymioGeneravimas()
{
    static uniform_int_distribution<int> dist(1, 10);
    return dist(gen);
}

void NDPazymiuGeneravimas(vector<int>& ndpazymiai)
{
    int kiekis = ivestiSkaiciu("Kiek namu darbu pazymiu generuoti? ");
    if (kiekis == 0)
    {
        cout << "Negeneruojami namu darbu pazymiai." << endl;
        return;
    }
    cout << "Sugeneruoti namu darbu pazymiai: ";
    for (int i = 0; i < kiekis; i++)
    {
        int pazymys = AtsitiktinioPazymioGeneravimas();
        ndpazymiai.push_back(pazymys);
        cout << pazymys << " ";
    }
    cout << endl;
}

Studentas Stud_ivestis(int studentoNr, bool atsitiktinai)
{
    Studentas studentas;

    cout << "\nIveskite " << studentoNr << "-o studento duomenis" << endl;

    string vardas = ivestiVarda("Vardas: ");
    string pavarde = ivestiVarda("Pavarde: ");

    studentas.setVardas(vardas);
    studentas.setPavarde(pavarde);

    vector<int> ndpazymiai;

    if (atsitiktinai)
    {
        NDPazymiuGeneravimas(ndpazymiai);
        studentas.setNdPazymiai(ndpazymiai);

        int egz = AtsitiktinioPazymioGeneravimas();
        studentas.setEgzRezultatas(egz);
        cout << "Sugeneruotas egzamino pazymys: " << egz << endl;
    } else {
        NDpazymiuivestis(ndpazymiai);
        studentas.setNdPazymiai(ndpazymiai);

        int egz = ivestiSkaiciu("Iveskite egzamino rezultata (1-10): ");
        studentas.setEgzRezultatas(egz);
    }

    int n = ndpazymiai.size();
    if (n == 0) {
        cout << "Studentas neturi namu darbu pazymiu." << endl;
    } else {
        cout << "Ivesti " << n << " namu darbu pazymiai." << endl;
    }

    studentas.skaiciuotiGalutini();

    return studentas;
}
