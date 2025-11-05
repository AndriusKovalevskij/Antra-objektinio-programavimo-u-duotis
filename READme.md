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

LIST:
Mažas duomenų kiekis (1000 įrašų)
| Strategija           | Padalinimas | Rūšiavimas | Išvedimas  | Bendras laikas  | Skirtumas |
|----------------------|-------------|------------|------------|-----------------|------------|
| S1 (Kopijavimas)     | 0.000329 s  | 0.000209 s | 0.005135 s | 0.005675 s      | +0.1%      |
| S2 (Trynimas)        | 0.000170 s  | 0.000157 s | 0.006203 s | 0.006530 s      | +15.2%     |
| S3 (Splice)          | 0.000060 s  | 0.000175 s | 0.005434 s | 0.005671 s      | bazė       |

<img width="435" height="354" alt="image" src="https://github.com/user-attachments/assets/3f7edbe9-99e3-44b8-8986-612f4733e4b7" />
<img width="616" height="315" alt="image" src="https://github.com/user-attachments/assets/217655c6-c958-461f-8982-6a53b5f5854e" />

Išvada: Minimalūs skirtumai, splice šiek tiek efektyvesnė.

Vidutinis duomenų kiekis (10000 įrašų)
| Strategija           | Padalinimas | Rūšiavimas | Išvedimas  | Bendras laikas | Skirtumas |
|----------------------|-------------|------------|------------|----------------|-----------|
| S1 (Kopijavimas)     | 0.003650 s  | 0.003856 s | 0.123821 s | 0.131330 s     | +11.4%    |
| S2 (Trynimas)        | 0.002018 s  | 0.003959 s | 0.113596 s | 0.119578 s     | +1.5%     |
| S3 (Splice)          | 0.000582 s  | 0.003533 s | 0.113648 s | 0.117765 s     | bazė      |

<img width="494" height="217" alt="image" src="https://github.com/user-attachments/assets/8c29ef2b-3c1a-4d88-8b4f-80c10c5c0ac9" />
<img width="318" height="303" alt="image" src="https://github.com/user-attachments/assets/a16b9b76-e0ba-45fc-9fb8-8f3b3e5fe255" />

Išvada: Splice ~10% greitesnė už kopijavimą.

Didelis duomenų kiekis (100000 įrašų)
| Strategija           | Padalinimas | Rūšiavimas | Išvedimas  | Bendras laikas | Skirtumas |
|----------------------|-------------|------------|------------|----------------|-----------|
| S1 (Kopijavimas)     | 0.033863 s  | 0.061847 s | 0.677043 s | 0.772763 s     | +0.6%     |
| S2 (Trynimas)        | 0.018526 s  | 0.079227 s | 0.675436 s | 0.773199 s     | +0.6%     |
| S3 (Splice)          | 0.007197 s  | 0.071687 s | 0.690178 s | 0.769071 s     | bazė      |

<img width="405" height="616" alt="image" src="https://github.com/user-attachments/assets/943e8bb3-451b-406a-9d7a-8bd00743f183" />

Išvada: Splice turi greičiausią padalijimą (~4-5x greičiau), bendras skirtumas ~0.5%.

 Labai didelis duomenų kiekis (1000000 įrašų)
| Strategija           | Padalinimas | Rūšiavimas | Išvedimas  | Bendras laikas  | Skirtumas |
|----------------------|-------------|------------|------------|-----------------|-----------|
| S1 (Kopijavimas)     | 0.179364 s  | 0.690237 s | 3.162443 s | 4.032047 s      | +5.6%     |
| S2 (Trynimas)        | 0.091222 s  | 0.704253 s | 3.231950 s | 4.027429 s      | +5.5%     |
| S3 (Splice)          | 0.037101 s  | 0.693594 s | 3.084502 s | 3.815202 s      | bazė      |

<img width="380" height="166" alt="image" src="https://github.com/user-attachments/assets/73fc8bb7-f9a3-4504-949f-15e861c5dcaa" />
<img width="777" height="418" alt="image" src="https://github.com/user-attachments/assets/98d3e699-d49c-45ba-94ff-f0a9b78b0589" />
<img width="388" height="214" alt="image" src="https://github.com/user-attachments/assets/510372a2-210a-46db-9219-32bda6ba8c80" />

Išvada: Splice ~5% greitesnė, ypač dėl efektyvaus padalijimo.

Milžiniškas duomenų kiekis (10000000 įrašų)
| Strategija           | Padalinimas | Rūšiavimas  | Išvedimas    | Bendras laikas  | Skirtumas |
|----------------------|-------------|-------------|--------------|-----------------|-----------|
| S1 (Kopijavimas)     | 4.564978 s  | 17.896376 s | 127.976135 s | 150.437496 s    | +3.2%     |
| S2 (Trynimas)        | 2.076061 s  | 18.048989 s | 122.073833 s | 142.198890 s    | -2.5%     |
| S3 (Splice)          | 0.656178 s  | 17.885075 s | 127.269474 s | 145.810736 s    | bazė      |

<img width="689" height="846" alt="image" src="https://github.com/user-attachments/assets/b92a9198-a16a-4838-8825-ee59423925c0" />

Pastaba: Dėl labai didelio duomenų kiekio ir atminties perkėlimų, S2 netikėtai gerai veikia. Splice greičiausias padalinimas (~7x greičiau).

Bendras visų strategijų palyginimas (sekundėmis)
| Įrašai     | V-S1    | V-S2    | V-S3    | L-S1    | L-S2    | L-S3    | Geriausia     |
|------------|---------|---------|---------|---------|---------|---------|---------------|
| 1K         | 0.006   | 0.013   | 0.006   | 0.006   | 0.007   | 0.006   | V-S3 / L-S3 ≈ |
| 10K        | 0.142   | 1.749   | 0.128   | 0.131   | 0.120   | 0.118   | **L-S3**      |
| 100K       | 0.784   | 137.5   | 0.787   | 0.773   | 0.773   | 0.769   | **L-S3**      |
| 1M         | 3.797   | -       | 4.136   | 4.032   | 4.027   | 3.815   | **L-S3**      |
| 10M        | 55.85   | -       | 58.08   | 150.4   | 142.2   | 145.8   | **V-S3**      |
