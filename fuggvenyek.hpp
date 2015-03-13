#ifndef FUGGVENYEK_HPP
#define FUGGVENYEK_HPP
#include<iostream>
#include<fstream>

template<class T>
void fajlba_kiir(const Matrix<T>& m){
	std::ofstream out;
	out.open("matrix.dat");
	for (int i = 0; i < m.getSor(); ++i){
		for (int j = 0; j < m.getOszlop(); ++j)
			out << m.getElem(i,j) << '?';
        out << ';';
		out << std::endl;
	}
	out.close();
}

template<class T>
int fajlbol_olvas(Matrix<T>& m){
	std::ifstream inp;
	std::ofstream out;
	inp.open("matrix.dat");
	if (inp.fail()) {
		std::cerr << "nem tudom megnyitni a fájlt" << std::endl;
		return 0;
	}
	out.open("temp.dat");
	int osszes = 0;
	int tizedespont = 0;
	int sor = 0;
	char szam;
	while (!inp.eof()){
        inp >> szam;
        if(szam == '?')
        ++osszes;
        if(szam == '.')
            ++tizedespont;
        if(szam != ';' && szam != '?')
            out << szam;
        if(szam == '?')
            out << ' ';
        if(szam == ';')
            ++sor;
	}

	m.setSor(sor-1);
	m.setOszlop((osszes)/(sor-1));
	delete[] m.p[0];
	delete[] m.p;
    m.p = new T*[m.getSor()];
    m.p[0] = new T[m.getSor()*m.getOszlop()];
    for(int i = 0; i < m.getSor(); ++i)
        m.p[i]= m.p[0] + i*m.getOszlop();
	inp.close();
	out.close();
	std::ifstream inp2;
    inp2.open("temp.dat");
	if (inp2.fail()) {
		std::cerr << "nem tudom megnyitni a fájlt." << std::endl;
		return 0;
	}
    for (int i = 0; i < m.getSor(); ++i){
        for (int j = 0; j < m.getOszlop(); ++j){
            inp2 >> m.p[i][j];
        }
    }
	inp2.close();
	return 0;
}

template<class T>
std::istream& operator>>(std::istream& is, Matrix<T>& m){
    double oszlop, sor;
    T elem;
    std::cout << "Oszlopok száma: ";
    is >> oszlop;
    std::cout << std::endl;
    if(oszlop != (int)oszlop || oszlop <= 0)
        throw std::runtime_error("Hibás oszlopszám!");
    std::cout << std::endl;
    std::cout << "Sorok száma: ";
    is >> sor;
    std::cout << std::endl;
    if(sor != (int)sor || sor <= 0)
        throw std::runtime_error("Hibás sorszám");
    std::cout << std::endl;
    m.setOszlop(oszlop);
    m.setSor(sor);
    delete[] m.p[0];
    delete[] m.p;
    m.p = new T*[m.getSor()];
    m.p[0] = new T[m.getSor()*m.getOszlop()];
    for(int i = 0; i < m.getSor(); ++i)
        m.p[i]= m.p[0] + i*m.getOszlop();
    for(int i = 0; i < m.getSor(); ++i)
        for(int j = 0; j < m.getOszlop(); ++j){
            is >> elem;
            m.setElem(i, j, elem);
        }
    std::cout << std::endl;
    return is;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& m){
    int hossz = 5;//legnagyobb_szamjegyek(m);
	for (int i = 0; i < m.getOszlop(); ++i)
        for(int j = 0; j < hossz+2; ++j)
            os << "-";
    os << "-" << std::endl;
    int k;
	for (int i = 0; i < m.getSor(); ++i){
		for (int j = 0; j < m.getOszlop(); ++j)
			os << "|" << " " << std::setw(hossz) << m.getElem(i,j);
        os << "|" << std::endl;
        k = i;
		for (int i = 0; i < m.getOszlop(); ++i)
            for(int j = 0; j < hossz+2; ++j)
                os << "-";
        os << "-";
        if(k < m.getSor()-1)
            os << std::endl;
	}
	os << m.getOszlop() << "x" << m.getSor() << std::endl << std::endl;
	return os;
}

template<class T>
T index(const Matrix<T>& m, int sor_idx, int oszlop_idx){
    if(oszlop_idx < 0 || oszlop_idx > m.getOszlop() || sor_idx < 0 || sor_idx > m.getSor()){
        throw std::out_of_range("Túlindexelés");
    }
    else
        return m.p[sor_idx-1][oszlop_idx-1];
}

#endif // FUGGVENYEK_HPP

