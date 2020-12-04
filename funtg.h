/*
    funtg.h
    taldegen fitxategian erabiltzen diren funtzioen goiburukoak
*******************************************************************/

extern double distantzia_genetikoa(float *elem1, float *elem2);

extern void talde_gertuena(int elekop, float elem[][ALDAKOP], float zent[][ALDAKOP], int *sailka);

extern void talde_trinkotasuna(float elem[][ALDAKOP], struct tinfo *kideak, float *trinko);

extern void eritasun_analisia(struct tinfo *kideak, float eri[][ERIMOTA], struct analisia *eripro);

