Kompiuterio specifikacijos:
<img width="1269" height="233" alt="Screenshot 2025-10-30 152721" src="https://github.com/user-attachments/assets/ecc2d86f-47c8-4317-8709-5e4d727c8624" />

Programos veikimas su VECTOR konteineriu:

| Įrašų skaičius | Skaitymas (s) | Rūšiavimas (s) | Įrašymas (s) | Bendras (s) |
|----------------|---------------|----------------|--------------|-------------|
| 1000           | 0.007834      | 0.002363       | 0.017529     | 0.027726    |
| 10000          | 0.081190      | 0.021363       | 0.077949     | 0.180502    |
| 100000         | 0.358425      | 0.166949       | 0.634726     | 1.160100    |
| 1000000        | 3.043680      | 6.361858       | 6.361858     | 15.767396   |
| 10000000       | 30.824641     | 21.298997      | 59.037952    | 111.161590  |


Programos veikimas su LIST konteineriu:

| Įrašų skaičius | Skaitymas (s) | Rūšiavimas (s) | Įrašymas (s) | Bendras (s) |
|----------------|---------------|----------------|--------------|-------------|
| 1000           | 0.006345      | 0.000929       | 0.008174     | 0.015448    |
| 10000          | 0.048941      | 0.009357       | 0.112001     | 0.170299    |
| 100000         | 0.310092      | 0.115957       | 0.688467     | 1.114516    |
| 1000000        | 3.188830      | 1.979922       | 6.420742     | 11.589494   |
| 10000000       | 30.588414     | 29.383065      | 68.121964    | 128.093443  |


Bendras palyginimas:

| Įrašų sk.   | Vector (s)   | List (s)     | Skirtumas | Greičiausias |
|-------------|--------------|--------------|-----------|--------------|
| 1000        | 0.027726     | 0.015448     | -44.3%    | LIST         |
| 10000       | 0.180502     | 0.170299     | -5.7%     | LIST         |
| 100000      | 1.160100     | 1.114516     | -3.9%     | LIST         |
| 1000000     | 11.268161    | 11.589494    | +2.9%     | VECTOR       |
| 10000000    | 111.161590   | 128.093443   | +15.2%    | VECTOR       |


Operacijų analizė:

Skaitymas: Panašus abiem atvejais.
Rūšiavimas: List žymiai greičiau mažiem duomenims, vector - dideliems.
Įrašymas: Vector greičiau įrašo.
