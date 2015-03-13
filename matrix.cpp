#include<iostream>
#include<stdexcept>
#include<locale>
#if defined(WIN32) || defined(_WIN32)
    #include <windows.h>
#endif
#include "matrix.hpp"
#include "tesztek.h"
#include "memtrace.h"


int main(){
    _StartMemoryCheck(){
    #if defined(WIN32) || defined(_WIN32)
        SetConsoleCP(1250);
        SetConsoleOutputCP(1250);
    #endif

    std::cout << std::endl;


    std::cout << "              Generikus intelligens mátrixot megvalósító osztály" << std::endl;
    std::cout <<"          ---------------------------------------------------------" << std::endl << std::endl << std::endl;


    try{

        int i, meret,valasztas;

        typedef void (*MenuFv)(void);

        struct MenuPont{
            char const *nev;
            MenuFv pfv;
        };

        MenuPont menupontok[] = {
            { "teszteset: kiíratás default értékkel, adott értékkel", teszt_1 },
            { "teszteset: értékadás, másolókonstruktor", teszt_2 },
            { "teszteset: beolvasás standard inputról, fájlba írás és olvasás, indexelés", teszt_3 },
            { "teszteset: szorzás skalárral, transzponálás, két mátrix összehasonlítása", teszt_4 },
            { "teszteset: két mátrix összeadása, összeszorzása", teszt_5 },
            { NULL, NULL }
        };

        meret = 0;
        for (i = 1; menupontok[i-1].nev != NULL; ++i)
            std::cout << i << "." << menupontok[i-1].nev << std::endl << std::endl;

        meret = i;

        std::cout << std::endl;
        std::cout << "Melyik tesztesetet futassam? ";
        std::cin >> valasztas;
        std::cout << std::endl << std::endl;

        if (0 < valasztas && valasztas < meret)
           menupontok[valasztas-1].pfv();
        else
           throw std::runtime_error("Nincs ilyen teszteset");

    }

    catch(std::exception const& e){
        std::cerr << e.what() << std::endl << std::endl;
    }
    }

    _CrtDumpMemoryLeaks();
	return 0;
}
