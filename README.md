# KA-OpenMP-Proiektua
## Exekuzio denborak
* Seriean

    | Iterazio kopurua: | 111       |
    |-------------------|---------  |
    | T_irak:           | 4.988 s   |
    | T-sailka:         | 180.388 s |
    | T_ordena:         | 0.020 s   |
    | T_trinko:         | 28.810 s  |
    | T_anal:           | 0.025 s   |
    | T_idatzi:         | 0.004 s   |
    |===================|=========  |
    | T_osoa:           | 214.235 s |
    
* Paraleloan

    * 2 Threads

        | Iterazio kopurua: | 111       |
        |-------------------|---------  |
        | T_irak:           | 3.340 s   |
        | T-sailka:         | 100.870 s |
        | T_ordena:         | 0.019 s   |
        | T_trinko:         | 14.528 s  |
        | T_anal:           | 0.025 s   |
        | T_idatzi:         | 0.003 s   |
        |===================|=========  |
        | T_osoa:           | 118.785 s |

    * 4 Threads
    
        | Iterazio kopurua: | 111      |
        |-------------------|--------- |
        | T_irak:           | 3.302 s  |
        | T-sailka:         | 43.934 s |
        | T_ordena:         | 0.044 s  |
        | T_trinko:         | 9.358 s  |
        | T_anal:           | 0.027 s  |
        | T_idatzi:         | 0.003 s  |
        |===================|========= |
        | T_osoa:           | 56.669 s |
    
    * 8 Threads
    
        | Iterazio kopurua: | 111       |
        |-------------------|---------  |
        | T_irak:           | 5.349 s   |
        | T-sailka:         | 51.629 s  |
        | T_ordena:         | 0.045 s   |
        | T_trinko:         | 7.491 s   |
        | T_anal:           | 0.025 s   |
        | T_idatzi:         | 0.003 s   |
        |===================|=========  |
        | T_osoa:           | 64.542 s  |
    
    * 16 Threads

        | Iterazio kopurua: | 111     |
        |-------------------|---------|
        | T_irak:           | 4.743 s |
        | T-sailka:         | 28.712 s |
        | T_ordena:         | 0.040 s |
        | T_trinko:         | 7.140 s |
        | T_anal:           | 0.057 s |
        | T_idatzi:         | 0.005 s |
        |===================|=========|
        | T_osoa:           | 40.698 s |

    * 32 Threads

        | Iterazio kopurua: | 111      |
        |-------------------|--------- |
        | T_irak:           | 3.303  s |
        | T-sailka:         | 8.341  s |
        | T_ordena:         | 0.020  s |
        | T_trinko:         | 4.133  s |
        | T_anal:           | 0.019  s |
        | T_idatzi:         | 0.003  s |
        |===================|========= |
        | T_osoa:           | 15.818 s |
        
     * 64 Threads

        | Iterazio kopurua: | 111      |
        |-------------------|--------- |
        | T_irak:           | 3.298  s |
        | T-sailka:         | 5.586  s |
        | T_ordena:         | 0.020  s |
        | T_trinko:         | 4.261  s |
        | T_anal:           | 0.036  s |
        | T_idatzi:         | 0.003  s |
        |===================|========= |
        | T_osoa:           | 13.205 s |
