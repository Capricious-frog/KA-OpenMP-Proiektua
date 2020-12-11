/*
    definetg.h
    taldegen eta funtg fitxategietan erabiltzen diren konstanteak eta datu-egiturak
**********************************************************************************/


// konstanteak

#define EMAX     230000     // osagai kopuru (elem) maximoa
#define TALDEKOP 100        // talde kopurua
#define ALDAKOP  40         // elementu bakoitzaren aldagai kopurua
#define DELTA    0.01       // konbergentzia: zentroideen aldaketa minimoa
#define ITMAX    1000       // konbergentzia: iterazio kopuru maximoa
#define ERIMOTA  20


// datu-egiturak

struct tinfo            // taldei buruzko informazioa
{
    int osagaiak[EMAX]; // osagaiak
    int kop;            // osagai kopurua
};


struct analisia         // eritasunen analisiaren emaitzak
{
    float max, min;     // maximoa eta minimoa eritasun bakoitzerako
    int tmax, tmin;     // maximoko eta minimoko taldeak
};

