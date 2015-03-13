#include "tesztek.h"
#include "matrix.hpp"
#include "fuggvenyek.hpp"
#include "memtrace.h"

///Tesztelés

///TESZT_1

void teszt_1(){//kiíratás
    Matrix<int> m(4,5); //int elemeket tartalmazó 4x5-ös mátrix a default értékkel, azaz nullákkal feltöltve
    std::cout << "4x5-ös 0-kat tartalmazó mátrix:" << std::endl << std::endl << m << std::endl;
    Matrix<double> n(7,6,3.1); //double elemeket tartalmazó 7x6-os mátrix 3.1-el feltöltve
    std::cout << "7x6-os 3.1-eket tartalmazó mátrix:" << std::endl << std::endl << n << std::endl;
}

///TESZT_2

void teszt_2(){//értékadás, másolókonstruktor
    Matrix<float> m(7,3,4.2); //float elemeket tartalmazó 7x3-as mátrix 4.2-el feltöltve
    std::cout << "m mátrix:" << std::endl << m << std::endl;
    Matrix<float> n(1,1,1); //1 sort és 1 oszlopot tartalmazó 1-es számmal feltöltött mátrix
    n = m; //értékadás
    std::cout << "n mátrix, értékadással:" << std::endl << n << std::endl;
    Matrix<float> a = m; //másolókonstruktor
    std::cout << "a mátrix, másolókonstruktorral:" << std::endl << a << std::endl;
}

///TESZT 3

void teszt_3(){//beolvasás standard inputról, fáljba írás és olvasás
    try{
        Matrix<double> a;
        Matrix<double> m;
        std::cin >> m;
        std::cout << std::endl << std::endl;
        std::cout << "A beolvasott mátrix:" << std::endl << m << std::endl;
        fajlba_kiir(m);
        fajlbol_olvas(a);
        std::cout << "A fájlból beolvasott mátrix:"  << std::endl << a << std::endl;
        std::cout << "A mátrix 1,2 indexû eleme: " << index(a,1,2) << std::endl << std::endl << std::endl;
        std::cout << index(a,7,9) << std::endl << std::endl;
    }
    catch(std::exception const& e){
        std::cerr << e.what() << std::endl << std::endl;
    }
}

///TESZT 4

void teszt_4(){//szorzás skalárral, transzponálás, összehasonlítás
    Matrix<int> m(4,6,7);
    Matrix<int> n = 5*m;
    std::cout << "A mátrix:" << std::endl << m << std::endl;
    std::cout << "A mátrix 5-tel balról szorozva:" << std::endl << n <<std::endl;
    std::cout << "A transzponáltja:" << std::endl << ++n << std::endl;
    bool q = n==++n;
    if(q)
        std::cout << "A két mátrix megegyezik." << std::endl << std::endl;
    else
        std::cout << "A két mátrix nem egyezik meg." << std::endl << std::endl << std::endl;

    std::cout << "A mátrix 3-mal jobbról szorozva:" << std::endl << m*3 << std::endl;
}

///TESZT 5

void teszt_5(){//két mátrix összeadása, szorzása
    try{
        Matrix<double> m;
        Matrix<double> n;
        std::cin >> m >> n;
        std::cout << "Egyik mátrix:" << std::endl << m << std::endl;
        std::cout << "Másik mátrix:" << std::endl << n << std::endl;
        std::cout << "A két mátrix összege:" << std::endl << m+n << std::endl;
        std::cout << "A két mátrix szorzata:" << std::endl << m*n << std::endl;
    }
    catch(std::exception const& e){
        std::cerr << e.what() << std::endl << std::endl;
    }
}




