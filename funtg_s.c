/*
    KA - OpenmP

    funtg_s.c
    taldegen_s.c programan erabiltzen diren errutinak

    OSATZEKO
******************************************************************************************/


#include <math.h>
#include <float.h>

#include "definetg.h"        // konstanteen definizioak


/* 1 - Bi elementuren arteko distantzia genetikoa kalkulatzeko funtzioa
       (distantzia euklidearra)

       Sarrera:  ALDAKOP aldagaiko bi elementu (erreferentziaz)
       Irteera:  distantzia (double)
******************************************************************************************/

double distantzia_genetikoa(float *elem1, float *elem2) {
    // EGITEKO
    // kalkulatu bi elementuren arteko distantzia (euklidearra)
    double dist = 0;

    for (int i = 0; i < ALDAKOP; i++) {
        dist += pow((double) (elem1[i] - elem2[i]), 2);
    }

    return sqrt(dist);
}


/* 2 - Talde gertuena kalkulatzeko funtzioa (zentroide gertuena)

       Sarrera:  elekop   elementu kopurua, int
                 elem     EMAX x ALDAKOP tamainako matrizea
                 zent     TALDEKOP x ALDAKOP tamainako matrizea
       Irteera:  sailka   EMAX tamainako bektorea, elementu bakoitzari dagokion taldea
******************************************************************************************/

void talde_gertuena(int elekop, float elem[][ALDAKOP], float zent[][ALDAKOP], int *sailka) {
    // EGITEKO
    // sailka: elementu bakoitzaren zentroide hurbilena, haren "taldea"
    double dg;
    double dg_min;
    int pos;

    for (int i = 0; i < elekop; i++) {
        dg_min = DBL_MAX;
        pos = 0;
        for (int j = 0; j < elekop; j++) {
            dg = distantzia_genetikoa(&elem[i][0], &zent[j][0]);
            if (dg_min > dg) {
                dg_min = dg;
                pos = j;
            }
        }
        sailka[i] = pos;
    }
}


/* 3 - Taldeen trinkotasuna kalkulatzeko funtzioa (kideen arteko distantzien batezbestekoa)

       Sarrera:  elem     fitxategiko elementuak (EMAX x ALDAKOP tamainako matrizea)
                 kideak   taldekideen zerrenda (TALDEKOP tamainako struct-bektore bat: elem eta kop)
       Irteera:  trinko   trinkotasuna (TALDEKOP tamainako bektorea)
                          osagai kopurua 0 edo 1, trinkotasuna = 0
******************************************************************************************/

void talde_trinkotasuna(float elem[][ALDAKOP], struct tinfo *kideak, float *trinko) {
    // EGITEKO
    // Kalkulatu taldeen trinkotasuna: kideen arteko distantzien batezbesteko
    double batez_bestekoa;

    for (int i = 0; i < TALDEKOP; i++) {
        batez_bestekoa = 0;

        if (kideak[i].kop <= 1) {
            trinko[i] = (float) 0.000;
        } else {
            for (int j = 0; j < kideak[i].kop; j++) {
                for (int k = 0; k < kideak[i].kop; k++) {
                    batez_bestekoa += distantzia_genetikoa(&elem[kideak[i].osagaiak[j]][0],
                                                           &elem[kideak[i].osagaiak[k]][0]);
                }
            }

            // Pow egiten da distantziaren kalkulua errepikatu egiten delako, adib: dist(a, b) eta dist(b, a).
            trinko[i] = (float) (batez_bestekoa / pow(kideak[i].kop, 2));
        }
    }
}


/* 4 - Eritasunak analizatzeko funtzioa

       Sarrera:  kideak  taldekideen zerrenda (TALDEKOP tamainako struct-bektore bat: elem eta kop)
                 eri     eritasunei buruzko informazioa (EMAX x ERIMOTA)
       Irteera:  eripro  eritasunen analisia: maximoa/minimoa, eta taldeak
******************************************************************************************/

void eritasun_analisia(struct tinfo *kideak, float eri[][ERIMOTA], struct analisia *eripro) {
    // EGITEKO
    // Prozesatu eritasunei buruzko informazioa, bakoitzaren maximoa/minimoa eta taldea lortzeko
    float bataz_bestekoa;

    for (int i = 0; i < ERIMOTA; i++) {
        eripro[i].min = DBL_MAX;
        eripro[i].max = DBL_MIN;
        bataz_bestekoa = 0;
        for (int j = 0; j < TALDEKOP; j++) {
            for (int k = 0; k < kideak[j].kop; k++) {
                bataz_bestekoa += eri[kideak[j].osagaiak[k]][i];
            }
            bataz_bestekoa = bataz_bestekoa / (float) kideak[j].kop;
            if (bataz_bestekoa > eripro[i].max) {
                eripro[i].max = bataz_bestekoa;
                eripro[i].tmax = j;
            } else if (bataz_bestekoa < eripro[i].min) {
                eripro[i].min = bataz_bestekoa;
                eripro[i].tmin = j;
            }

        }
    }
}


