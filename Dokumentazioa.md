<h1 align = "center"> Txosten Teknikoa </h1>
<h2 align = "center"> Eritasunen analisi genetikoa </h2>
<h4 align = "right"> Julen Ortiz eta Jon Ander Blanco </h4>

* Sarrera:    2
* Patogenoen laginen analisi genetikoa:    2
* Hardware ezaugarriak:    2
* Software ezaugarriak:    3
* Oinarri Teorikoak:    3
* Aplikazioak:    4
* Ondorioak:    6
* Bibliografia:    7

## Sarrera:

### Patogenoen laginen analisi genetikoa:

COVID-19 bezalako eritasunei aurre egiteko, ikerketa proiektu honek, patogenoen analisi genetikoa egiteko balio du. Lan honek, mota horietako azterketa genetikoak egiten ditu eta horretarako bi fitxategiekin lan egiten dute, horietako bat laginen datu genetikoak aurkitu ditzakegu eta bestean lagin bakoitzetik eritasuna garatzeko probabilitateak. Proiektu honetan fitxategi horiek prozesatuko ditugu eritasunen informazioa eta datuak lortzeko.

dbgen.dat fitxategian 200.000 lagin baino gehiago aurkitu dezakegu, 40 datu lagin bakoitzeko, 0tik 100era. Eta guzti horiek 100 talde genetikotan salkatu behar dira, haien ezaugarrien arabera. Hauek talde genetikoetan sailkatzeko, K-means algoritmoa erabiltzen da, algoritmo honek talde bakoitzeko kideen arteko “distantziak” minimizatzen saiatzen da.

Taldeak sailkatu ondoren, talde guztien trinkotasuna kalkulatu behar da, eta beste aldetik talde bakoitzeko laginen infekzioei buruzko informazioa lortu eta prozesatu beharko da, hauen maximoak eta minimoak lortuz, haien taldea barne.

### Hardware ezaugarriak:

* PowerEdge R740 (DELL)
* 2 Intel Xeon Gold 6130 prozesadore, 16 nukleo - 2,1 GHz
* 32 GB RAM (RDIMM - 2666 MT/s)
* NVIDIA QUADRO P4000 (GPU) 

### Software ezaugarriak:

* Sistema eragilea: “Linux”
* Programazio lengoaia: “C”
* C-ren konpiladorea: “GNU compiler collection (gcc)”
* Textu-editoreak: “nano” eta “vim”
* PDF egiteko eta konpilatzeko programak: “Drive”, “Pandoc” eta "Mathjax"
* Paralelizatzeko erabilitako API-a: “OpenMP”

## Oinarri Teorikoak:

Programen exekuzio denborak txikitu ahal izateko, hainbat estrategia edo metodo aurkitu dezakegu, hala nola: Segmentazioa, nukleo gehiagoko prozesadoreak erabiltzea, Cache memoria gehiago erabiltzea etab… Baino guk, programak/funtzioak paralelizatu ditugu horrela azelerazio faktore onak lortuz eta dena eraginkorrago izateko.

Gure kasuan, ez dugu programa osoa paralelizatu, planteatuta zeuden eta egindako funtzioak baizik (“talde_gertuena”, “talde_trinkotasuna”, “eritasun_analisia”). Funtzioaren arabera “static” edo dynamic” erabilitu ditugu. Esan beharra dago “distantzia_genetikoa” funtzioa ez dugula paralelizatu, beharra ez zegoelako.

## Aplikazioak:

Programaren hasieran bi fitxategiak kargatzen dira memoriara eta 100 zentroide sortzen dira ausaz. Ondoren elementuak zentroide hauen inguruan taldekatu behar dira, horretarako elementu bakoitzaren zentroide hurbilena kalkulatu behar da. Honetarako bi zuntzio erabiltzen dira: distantzia_genetikoa eta talde_gertuena.

Honetarako talde_gertuena talde gertuena funtzioa erabiltzen da, honek elementu bakoitza artu eta zentroide guztientatik gertuena bilatu eta sailka listan zentroidearen indizea gordetzen du.

```
void talde_gertuena(int elekop, float elem[][ALDAKOP], float zent[][ALDAKOP], int *sailka) {
    double dg, dg_min;
    int pos;

  for (int i = 0; i < elekop; i++) {
    dg_min = DBL_MAX;
    pos = 0;
    for (int j = 0; j < TALDEKOP; j++) {
      dg = distantzia_genetikoa(&elem[i][0], &zent[j][0]);
      if (dg_min > dg) {
        dg_min = dg;
         pos = j;
      }
    }
    sailka[i] = pos;
  }
}
```

Bi puntuen arteko distantzia kalkulatzeko distantzia_genetikoa funtzioa erabiltzen da eta izenak esaten duen bezela bi puntuen distantzia kalkulatzen du eta horretarako distatzia euklidestarra erabiltzen da. Algoritmo honek edozein dimentsiotan lan egin dezakeenez ez dago erazorik gure 40 dimenstioko puntuekin. Distantzia euklidestarra honela definitzen da:

$d(p,q) = \sqrt{(p_1- q_1)^2 + (p_2 - q_2)^2+\cdots+(p_i - q_i)^2+\cdots+(p_n - q_n)^2}$

```
double distantzia_genetikoa(float *elem1, float *elem2) {
    double dist = 0;

    for (int i = 0; i < ALDAKOP; i++) {
            dist += pow((double) (elem1[i] - elem2[i]), 2);
    }

    return sqrt(dist);
}
```

Taldeak sailkatu ondoren, talde guztien trinkotasuna kalkulatzen da, trinkotasuna, talde bakoitzaren elementuen arteko bataz besteko distantzia da eta horrela kalkulatzen da:

```
void talde_trinkotasuna(float elem[][ALDAKOP], struct tinfo *kideak, float *trinko) {
    double bataz_bestekoa = 0;
    int kont;
    for (int i = 0; i < TALDEKOP; i++) {
      if (kideak[i].kop <= 1) {
          trinko[i] = (float) 0.000;
      } else  {
        for (int j = 0; j < kideak[i].kop; j++){
          for (int j = 0; j < kideak[i].kop; j++){
              kont++;
              bataz_bestekoa += distantzia_genetikoa(&elem[kideak[i].osagaiak[j][0],&elem[kideak[i].osagaiak[k][0]);
          }
        }
        trinko[i] = (float) (bataz_bestekoa / kont);
      }
    }
}
```

Bukatzeko, eritasun guztiei buruz datauk lortu behar dira. Talde bakoitzeko bataz besteko presentzia neurtu behar da, haien maximo eta minimoekin (baita ere zein taldetan ematen diren maximo eta minimo horiek).


```
void eritasunen_analisia(struct tinfo *kideak, float eri[][ERIMOTA], struct analisia *eripro) {

  float bataz_bestekoa;

  for(int i = 0; i < ERIMOTA; i++) {
    eripro[i].min = DBL_MAX;
    eripro[i].max = DBL_MIN;
    for (int j = 0; j < TALDEKOP; j++) {
      bataz_bestekoa = 0;
        for (int k = 0; k < kideak[j].kop; k++){
          bataz_bestekoa += eri[kideak[j].osagaiak[k]][i];
    }
    bataz_bestekoa = bataz_bestekoa / (float) kideak[j].kop;
      if (bataz_bestekoa > eripro[i].max) {
          eripro[i].max = bataz_bestekoa;
          eripro[i].tmax = j;
      } else if (batez_bestekoa < eripro[i].min) {
        eripro[i].min = bataz_bestekoa;
        eripro[i].tmin = j;
      }
    }
  }
}
```

Ondorioak:


Bibliografia:
