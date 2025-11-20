**RULE OF THREE**

-Kopijavimo konstruktorius (Studentas(const Studentas& other)) - sukuria pilną objekto kopiją, nukopijuodamas visus privačius duomenis (vardas_, pavarde_, ndpazymiai_, egzrezultatas_, galutinis_vidurkis_, galutine_mediana_).

-Priskyrimo operatorius (operator=) - saugiai priskiria vieną objektą kitam su savęs priskyrimo patikra (if (this != &other)), užtikrinant, kad objektas nebūtų priskiriamas pats sau.

-Destruktorius (~Studentas()) - atlaisvina resursus išvalydamas string ir vector tipus bei nustatydamas skaičinius kintamuosius į nulines vertes.


**DUOMENŲ ĮVESTIS**

Sistema palaiko tris būdus įvesti studentų duomenis:
1. Rankinė įvestis
   
  Rankinio įvedimo metu naudotojas interaktyviai įveda:
  
  Vardą - validuojamas ivestiVarda() funkcija, tikrinama, kad būtų sudarytas tik iš raidžių
  Pavardę - validuojama analogiškai vardui
  Namų darbų pažymius - įvedami per NDpazymiuivestis(), kiekvienas pažymys tikrinamas, ar yra intervale [1, 10]
  Egzamino rezultatą - validuojamas ivestiSkaiciu() funkcija
  
  Duomenys saugomi naudojant:
  
  setVardas() - nustato studento vardą
  setPavarde() - nustato studento pavardę
  setNdPazymiai() - nustato namų darbų pažymių vektorių
  setEgzRezultatas() - nustato egzamino rezultatą

Po įvedimo automatiškai iškviečiamas skaiciuotiGalutini() metodas galutiniam vidurkiui ir medianai apskaičiuoti.

2. Automatinė įvestis su atsitiktiniais pažymiais
  
  Automatinės įvesties metu:
  
  Naudotojas įveda tik vardą ir pavardę rankiniu būdu
  Namų darbų pažymiai generuojami AtsitiktinioPazymioGeneravimas() funkcija, kuri naudoja <random> biblioteką (std::mt19937 generatorių ir std::uniform_int_distribution<int> pasiskirstymą)
  Egzamino rezultatas taip pat generuojamas atsitiktinai
  Visi sugeneruoti pažymiai yra intervale [1, 10]
  Sugeneruoti pažymiai rodomi konsolėje prieš įrašant

3. Įvestis iš failo

  Failo skaitymo funkcija skaitytiDuomenisIsFailo():
  
  -Atidaro failą su ifstream
  -Praleidžia antraštės eilutę
  -Skaito kiekvieną eilutę naudodama getline() ir analizuoja ją su stringstream
  -Ekstraktuoja vardą, pavardę, visus pažymius (namų darbai + egzaminas)
  -Paskutinis pažymys laikomas egzamino rezultatu
  -Validuoja, kad visi pažymiai būtų intervale [1, 10]
  -Kuria Studentas objektą ir prideda į vector<Studentas> konteinerį
  -Matuoja ir atspausdina nuskaitymo laiką naudodama <chrono> biblioteką


**DUOMENŲ IŠVESTIS**

Sistema palaiko du duomenų išvesties metodus:
1. Išvestis į konsolę
   Funkcija spausdintiStudentus() išveda duomenis į konsolę:
   
   Naudoja cout srautą
   Formatavimui naudoja <iomanip> manipuliatorius:
   
   left - lygiuoja tekstą į kairę
   setw() - nustato lauko plotį
   fixed - fiksuoto kablelio formatas
   setprecision(2) - du skaičiai po kablelio

2. Išvestis į failus
   Vargšiukų failas (vargsiuku_vidurkis.txt arba vargsiuku_mediana.txt):
      -Saugo studentus, kurių galutinis balas < 5.0
      -Surūšiuoti pagal pasirinktą kriterijų (vidurkį arba medianą)
      -Formatas: Vardas, Pavardė, Galutinis balas
   
   Saunuolių failas (saunuoliu_vidurkis.txt arba saunuoliu_mediana.txt):
      -Saugo studentus, kurių galutinis balas ≥ 5.0
      -Surūšiuoti pagal pasirinktą kriterijų
      -Tas pats formatas kaip vargšiukų faile
   
   Generuojamas testavimo failas
      Funkcija GeneruotiStudentuFaila():
         -Sukuria testinį failą su nurodytu studentų skaičiumi

