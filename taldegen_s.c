/*  KA, Konputagailuen Arkitektura - Informatika Ingeniaritza, 2. maila
    OpenMP laborategia - PROIEKTUA

    taldegen_s.c     SERIEKO BERTSIOA

    Informazio genetikoa prozesatzea eritasunei buruzko informazioa lortzeko
    ALDAKOP aldagaiko elementuak, TALDEKOP taldetan sailkatzeko, "distantzien" arabera

    Sarrera: dbgen.dat      informazio genetikoa duen fitxategia (211640 elementu, 40 aldagai)
             dberi.dat      eritasunei buruzko informazioa duen fitxategia (20 eritasun)
    Irteera: emaitza_s.out  zentroideak (100), taldeen tamaina eta trinkotasuna, eritasunak

    funtg_s.c moduluarekin konpilatu;  -lm aukera gehitu
*****************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "definetg.h"           // konstante eta datu-egituren definizioak
#include "funtg.h"              // programan deitzen diren funtzioak


float elem[EMAX][ALDAKOP];      // prozesatu behar diren elementuak (dbgen.dat fitxategian)
struct tinfo kideak[TALDEKOP];         // talde bakoitzeko kideen zerrenda

float eri[EMAX][ERIMOTA];    // eritasunetako probabilitateak (dberi.dat fitxategian)
struct analisia eripro[ERIMOTA];       // eritasunen probabilitate maximoa, minimoa...



// ================================
//       PROGRAMA NAGUSIA
// ================================

void main(int argc, char *argv[]) {
    float zent[TALDEKOP][ALDAKOP], zentberri[TALDEKOP][ALDAKOP];   // kalkulatzen diren zentroideak (taldeak)
    double baturak[TALDEKOP][ALDAKOP + 1];
    float trinko[TALDEKOP];        // talde bakoitzeko trinkotasuna

    int i, j, elekop, taldea;
    int sailka[EMAX];            // elementu bakoitzeko taldea
    int bukatu = 0, iterkop = 0;
    double diszent;

    FILE *f1, *f2;
    struct timespec t1, t2, t3, t4, t5, t6, t7;
    double t_irak, t_sailka, t_ordena, t_trinko, t_anal, t_idatzi;


    if ((argc < 3) || (argc > 4)) {
        printf("ADI:  progr - f1 (elem) - f2 (eri) - [elem kop])\n");
        exit(-1);
    }

    printf("\n >> Exekuzioa seriean\n");
    clock_gettime(CLOCK_REALTIME, &t1);

    // irakurri datuak fitxategietatik: elem[i][j] eta eri[i][j]
    // =========================================================

    f1 = fopen(argv[1], "r");
    if (f1 == NULL) {
        printf("Errorea %s fitxategia irekitzean\n", argv[1]);
        exit(-1);
    }

    fscanf(f1, "%d", &elekop);
    if (argc == 4) {
        elekop = atoi(argv[3]);    // 4. parametroa = prozesatu behar diren elementuen kopurua
    }

    for (i = 0; i < elekop; i++) {
        for (j = 0; j < ALDAKOP; j++) {
            fscanf(f1, "%f", &(elem[i][j]));        // elementuen zerrenda, ALDAKOP aldagaikoak
        }
    }

    fclose(f1);

    f1 = fopen(argv[2], "r");
    if (f1 == NULL) {
        printf("Errorea %s fitxategia irekitzean\n", argv[2]);
        exit(-1);
    }

    for (i = 0; i < elekop; i++) {
        for (j = 0; j < ERIMOTA; j++) {
            fscanf(f1, "%f", &(eri[i][j]));        // eritasunei buruzko informazioa
        }
    }
    fclose(f1);

    clock_gettime(CLOCK_REALTIME, &t2);


    // aukeratu lehen zentroideak, ausaz
    // =================================

    srand(147);
    for (i = 0; i < TALDEKOP; i++) {
        for (j = 0; j < ALDAKOP / 2; j++) {
            zent[i][j] = (rand() % 10000) / 100.0;
            zent[i][j + ALDAKOP / 2] = zent[i][j];
        }
    }

    // 1. fasea: kalkulatu zentroideak eta sailkatu elementuak
    // =======================================================

    iterkop = 0;
    bukatu = 0;
    while ((bukatu == 0) && (iterkop < ITMAX)) {
        // kalkulatu talde gertuena (OSATZEKO)

        talde_gertuena(elekop, elem, zent, sailka);

        // kalkulatu talde bakoitzeko zentroide berriak: dimentsio bakoitzeko batezbestekoa
        // baturak: 100 aldagaien balioak akumulatzeko; azkena kopurua da.

        for (i = 0; i < TALDEKOP; i++) {
            for (j = 0; j < ALDAKOP + 1; j++) {
                baturak[i][j] = 0.0;
            }
        }

        for (i = 0; i < elekop; i++) {
            for (j = 0; j < ALDAKOP; j++) {
                baturak[sailka[i]][j] += elem[i][j];
            }
            baturak[sailka[i]][ALDAKOP]++;    // azken osagaia (ALDAKOP) kopuruak gordetzeko
        }

        // kalkulatu zentroide berriak eta erabaki bukatu den, DELTAren arabera

        bukatu = 1;
        for (i = 0; i < TALDEKOP; i++) {
            if (baturak[i][ALDAKOP] > 0) {        // taldea ez dago hutsik

                for (j = 0; j < ALDAKOP; j++) {
                    zentberri[i][j] = baturak[i][j] / baturak[i][ALDAKOP];
                }

                // erabaki bukatu behar den
                diszent = distantzia_genetikoa(&zentberri[i][0], &zent[i][0]);
                if (diszent > DELTA) {
                    bukatu = 0;    // dimentsio batean aldaketa dago; segi simulazioarekin
                }

                // kopiatu zentroide berriak
                for (j = 0; j < ALDAKOP; j++) {
                    zent[i][j] = zentberri[i][j];
                }
            }
        }

        iterkop++;
    } // while

    clock_gettime(CLOCK_REALTIME, &t3);


    // 2. fasea: kontatu talde bakoitzaren elementuen kopurua, kalkulatu taldeen "trinkotasuna"
    //           eta analizatu eritasunak
    // ========================================================================================
    printf("Bigarrengo fasea");

    for (i = 0; i < TALDEKOP; i++) {
        kideak[i].kop = 0;
    }

    // talde bakoitzeko elementuak (osagaiak) eta kopurua

    for (i = 0; i < elekop; i++) {
        taldea = sailka[i];
        kideak[taldea].osagaiak[kideak[taldea].kop] = i;
        kideak[taldea].kop++;
    }

    clock_gettime(CLOCK_REALTIME, &t4);


    // trinkotasuna talde bakoitzean: elementuen arteko distantzien batezbestekoa

    talde_trinkotasuna(elem, kideak, trinko);

    clock_gettime(CLOCK_REALTIME, &t5);


    // taldeen analisia eritasunen bila (maximoa, minimoa...)

    eritasun_analisia(kideak, eri, eripro);

    clock_gettime(CLOCK_REALTIME, &t6);


    // idatzi emaitzak emaitzak_s.out fitxategian
    // ==========================================

    f2 = fopen("emaitzak_s.out", "w");
    if (f2 == NULL) {
        printf("Errorea emaitzak_s.out fitxategia irekitzean\n");
        exit(-1);
    }

    fprintf(f2, " Taldeen zentroideak\n\n");
    for (i = 0; i < TALDEKOP; i++) {
        for (j = 0; j < ALDAKOP; j++) {
            fprintf(f2, "%7.3f", zent[i][j]);
        }
        fprintf(f2, "\n");
    }

    fprintf(f2, "\n\n Taldeen elementu kopurua eta trinkotasuna\n\n");
    for (i = 0; i < TALDEKOP; i++) {
        fprintf(f2, " %6d  %.3f \n", kideak[i].kop, trinko[i]);
    }

    fprintf(f2, "\n\n Eritasunen analisia\n\n");
    fprintf(f2, "\n Erit.   Max - Tald    Min - Tald");
    fprintf(f2, "\n ================================\n");
    for (i = 0; i < ERIMOTA; i++) {
        fprintf(f2, "  %2d     %4.2f - %2d     %4.2f - %2d", i, eripro[i].max, eripro[i].tmax, eripro[i].min,
                eripro[i].tmin);
        fprintf(f2, "\n");
    }
    fclose(f2);

    clock_gettime(CLOCK_REALTIME, &t7);


    // pantailaratu emaitza batzuk
    // ===========================

    t_irak = (t2.tv_sec - t1.tv_sec) + (t2.tv_nsec - t1.tv_nsec) / (double) 1e9;
    t_sailka = (t3.tv_sec - t2.tv_sec) + (t3.tv_nsec - t2.tv_nsec) / (double) 1e9;
    t_ordena = (t4.tv_sec - t3.tv_sec) + (t4.tv_nsec - t3.tv_nsec) / (double) 1e9;
    t_trinko = (t5.tv_sec - t4.tv_sec) + (t5.tv_nsec - t4.tv_nsec) / (double) 1e9;
    t_anal = (t6.tv_sec - t5.tv_sec) + (t6.tv_nsec - t5.tv_nsec) / (double) 1e9;
    t_idatzi = (t7.tv_sec - t6.tv_sec) + (t7.tv_nsec - t6.tv_nsec) / (double) 1e9;

    printf("\n    Iterazio kopurua: %d", iterkop);
    printf("\n    T_irak:   %6.3f s", t_irak);
    printf("\n    T_sailka: %6.3f s", t_sailka);
    printf("\n    T_ordena: %6.3f s", t_ordena);
    printf("\n    T_trinko: %6.3f s", t_trinko);
    printf("\n    T_anal:   %6.3f s", t_anal);
    printf("\n    T_idatzi: %6.3f s", t_idatzi);
    printf("\n    ===================");
    printf("\n    T_osoa:   %6.3f s\n\n", t_irak + t_sailka + t_ordena + t_trinko + t_anal + t_idatzi);


    printf("\n  0, 40 eta 80 zentroideak eta haien trinkotasuna\n");
    for (i = 0; i < TALDEKOP; i += 40) {
        printf("\n  z%2d -- ", i);
        for (j = 0; j < ALDAKOP; j++) {
            printf("%5.1f", zent[i][j]);
        }
        printf("\n          %5.6f\n", trinko[i]);
    }

    printf("\n >> Taldeen tamaina \n");
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            printf("%7d", kideak[10 * i + j].kop);
        }
        printf("\n");
    }

    printf("\n >> Eritasunak \n");
    printf("\n Erit.   Max - Tald    Min - Tald");
    printf("\n ================================\n");
    for (i = 0; i < ERIMOTA; i++) {
        printf("  %2d     %4.2f - %2d     %4.2f - %2d", i, eripro[i].max, eripro[i].tmax, eripro[i].min,
               eripro[i].tmin);
        printf("\n");
    }
}
