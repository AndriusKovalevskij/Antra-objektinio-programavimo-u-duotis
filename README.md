RULE OF THREE

-Kopijavimo konstruktorius (Studentas(const Studentas& other)) - sukuria pilną objekto kopiją, nukopijuodamas visus privačius duomenis (vardas_, pavarde_, ndpazymiai_, egzrezultatas_, galutinis_vidurkis_, galutine_mediana_).
-Priskyrimo operatorius (operator=) - saugiai priskiria vieną objektą kitam su savęs priskyrimo patikra (if (this != &other)), užtikrinant, kad objektas nebūtų priskiriamas pats sau.
-Destruktorius (~Studentas()) - atlaisvina resursus išvalydamas string ir vector tipus bei nustatydamas skaičinius kintamuosius į nulines vertes.
