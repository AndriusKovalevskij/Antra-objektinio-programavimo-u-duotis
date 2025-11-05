Rezultatų analizė:
VECTOR:
Mažas duomenų kiekis (1000 įrašų)
| Strategija           | Padalinimas | Rūšiavimas | Išvedimas  | Bendras laikas | Skirtumas |
|----------------------|-------------|------------|------------|----------------|-----------|
| S1 (Kopijavimas)     | 0.000234 s  | 0.000645 s | 0.004783 s | 0.005674 s     | +0.6%     |
| S2 (Trynimas)        | 0.007552 s  | 0.000391 s | 0.004692 s | 0.012653 s     | +123%     |
| S3 (Partition)       | 0.000169 s  | 0.000103 s | 0.005013 s | 0.005680 s     | bazė      |

<img width="923" height="807" alt="Screenshot 2025-11-04 223459" src="https://github.com/user-attachments/assets/4bc1284e-9be0-4f44-8be1-cb59c15651a3" />
<img width="421" height="216" alt="image" src="https://github.com/user-attachments/assets/08f44b5e-43cb-45ef-b03e-17517284227f" />

Išvada: Mažam kiekiui S1 ir S3 beveik vienodos, bet S2 jau 2x lėtesnė.

Vidutinis duomenų kiekis (10000 įrašų)
| Strategija           | Padalinimas | Rūšiavimas | Išvedimas  | Bendras laikas | Skirtumas      |
|----------------------|-------------|------------|------------|----------------|----------------|
| S1 (Kopijavimas)     | 0.002371 s  | 0.009117 s | 0.130943 s | 0.142440 s     | +11.3%         |
| S2 (Trynimas)        | 1.630165 s  | 0.009068 s | 0.109438 s | 1.748697 s     | +1267%         |
| S3 (Partition)       | 0.002556 s  | 0.002514 s | 0.113813 s | 0.127898 s     | bazė           |

<img width="785" height="604" alt="image" src="https://github.com/user-attachments/assets/78172032-0b6e-4528-ba23-7afa393f102d" />
<img width="507" height="303" alt="image" src="https://github.com/user-attachments/assets/3304d89a-29f3-4f2c-8d0b-2b7e988e766b" />

Išvada: S2 tampa YPAČ lėta (~13.6x lėtesnė). S3 greičiausia.

Didelis duomenų kiekis (100000 įrašų)
| Strategija           | Padalinimas   | Rūšiavimas | Išvedimas  | Bendras laikas | Skirtumas       |
|----------------------|---------------|------------|------------|----------------|-----------------|
| S1 (Kopijavimas)     | 0.024116 s    | 0.010019 s | 0.649790 s | 0.783965 s     | +33.2%          |
| S2 (Trynimas)        | 136.738123 s  | 0.106613 s | 0.681976 s | 137.526746 s   | +23281%         |
| S3 (Partition)       | 0.025512 s    | 0.020395 s | 0.632437 s | 0.786879 s     | bazė            |

<img width="465" height="553" alt="image" src="https://github.com/user-attachments/assets/3816a475-c4a1-4a33-83ce-ac4e21ca63b4" />

Išvada: S2 VISIŠKAI NETINKAMA (>2 minutės!). S1 ir S3 panašios, bet S3 šiek tiek stabilesnė.

Labai didelis duomenų kiekis (1000000 įrašų)
| Strategija           | Padalinimas | Rūšiavimas | Išvedimas  | Bendras laikas | Skirtumas |
|----------------------|-------------|------------|------------|----------------|-----------|
| S1 (Kopijavimas)     | 0.120029 s  | 0.770084 s | 2.906650 s | 3.796790 s     | -8.1%     |
| S2 (Trynimas)        | NETESTUOTA (>20 min)                                               |
| S3 (Partition)       | 0.117033 s  | 0.094365 s | 3.143840 s | 4.136327 s     | bazė      |

<img width="1067" height="451" alt="Screenshot 2025-11-04 225955" src="https://github.com/user-attachments/assets/54f60dfb-6d94-42ec-92a4-fbc028f02756" />
<img width="842" height="548" alt="Screenshot 2025-11-04 230042" src="https://github.com/user-attachments/assets/c7f262d4-f889-4d95-bf7c-1a6e188350a6" />

Pastaba: S3 šiuo atveju šiek tiek lėtesnė dėl išvedimo operacijų, tačiau padalinimo ir kopijavimo etapai greitesni.

Milžiniškas duomenų kiekis (10000000 įrašų)
| Strategija           | Padalinimas | Rūšiavimas  | Išvedimas   | Bendras laikas | Skirtumas |
|----------------------|-------------|-------------|-------------|----------------|-----------|
| S1 (Kopijavimas)     | 1.427589 s  | 13.649002 s | 40.770608 s | 55.847257 s    | -3.7%     |
| S2 (Trynimas)        | NETINKAMA                                                            |
| S3 (Partition)       | 1.723402 s  | 1.248082 s  | 41.748938 s | 58.084020 s    | bazė      |

<img width="1058" height="443" alt="Screenshot 2025-11-04 230438" src="https://github.com/user-attachments/assets/a34208e5-ef25-4a5b-96db-4b8f17801606" />
<img width="865" height="546" alt="Screenshot 2025-11-04 230628" src="https://github.com/user-attachments/assets/473746b7-eef1-42d6-ba88-c5f2a923775f" />

Išvada: Abu S1 ir S3 geri, bet S3 turi greitesnį rūšiavimą (stable_partition optimizacijos).



