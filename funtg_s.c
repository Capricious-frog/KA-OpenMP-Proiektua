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
    return sqrtf(powf(*elem1, 2) + powf(*elem2, 2));
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

}


/* 3 - Taldeen trinkotasuna kalkulatzeko funtzioa (kideen arteko distantzien batezbestekoa)

       Sarrera:  elem     fitxategiko elementuak (EMAX x ALDAKOP tamainako matrizea)
                 kideak   taldekideen zerrenda (TALDEKOP tamainako struct-bektore bat: elem eta kop)
       Irteera:  trinko   trinkotasuna (TALDEKOP tamainako bektorea)
                          osagai kopurua 0 edo 1, trinkotasuna = 0
******************************************************************************************/

void talde_trinkotasuna(float elem[][ALDAKOP], struct tinfo *kideak, float *trinko) {

    // EGITEKO
    // Kalkulatu taldeen trinkotasuna: kideen arteko distantzien batezbestekoa

}


/* 4 - Eritasunak analizatzeko funtzioa

       Sarrera:  kideak  taldekideen zerrenda (TALDEKOP tamainako struct-bektore bat: elem eta kop)
                 eri     eritasunei buruzko informazioa (TALDEKOP x ERIMOTA)
       Irteera:  eripro  eritasunen analisia: maximoa/minimoa, eta taldeak
******************************************************************************************/

void eritas_analisia(struct tinfo *kideak, float eri[][ERIMOTA], struct analisia *eripro) {

    // EGITEKO
    // Prozesatu eritasunei buruzko informazioa, bakoitzaren maximoa/minimoa eta taldea lortzeko

}


