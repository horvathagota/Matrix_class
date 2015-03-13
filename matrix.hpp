#ifndef MATRIX_HPP
#define MATRIX_HPP
#include<iostream>
#include<stdexcept>
#include<iomanip>

template<class T>
class Matrix{
	int oszlop, sor;
	static T alap;
public:
    T **p;
	Matrix<T>(int sor, int oszlop, T alap);
	Matrix<T>(const Matrix<T>&);
	~Matrix();
	int getSor()const{ return sor; }
	int getOszlop()const{ return oszlop; }
	T getElem(int oszlop, int sor)const{return p[oszlop][sor];}
	void setSor(int sor){ this->sor = sor; }
	void setOszlop(int oszlop){ this->oszlop = oszlop; }
	void setElem(int oszlop, int sor, T elem){p[oszlop][sor] = elem;}
	Matrix<T>& operator=(const Matrix<T>&);
	bool operator==(const Matrix<T>&)const;
	void operator+=(double);
	Matrix<T> operator+(double)const;
	void operator+=(const Matrix<T>&);
	Matrix<T> operator+(const Matrix<T>&)const;
	void operator*=(double);
	Matrix<T> operator*(double)const;
	Matrix<T> operator*(Matrix<T>& m)const;
	Matrix<T> operator++()const;
};

template<class T>
T Matrix<T>::alap = T();

template<class T>
Matrix<T>::Matrix(int oszlop = 1, int sor = 1, T a = alap) :oszlop(oszlop), sor(sor){
    p = new T*[sor];
    p[0] = new T[sor*oszlop];
    for(int i = 0; i < sor; ++i)
        p[i]= p[0] + i*oszlop;
	for (int i = 0; i < sor; ++i)
		for (int j = 0; j < oszlop; ++j)
			p[i][j] = a;
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& m){
	sor = m.sor;
	oszlop = m.oszlop;
    p = new T*[sor];
    p[0] = new T[sor*oszlop];
    for(int i = 0; i < sor; ++i)
        p[i]= p[0] + i*oszlop;
	for (int i = 0; i < sor; ++i)
		for (int j = 0; j < oszlop; ++j)
			p[i][j] = m.p[i][j];
}

template<class T>
Matrix<T>::~Matrix(){
    delete[] p[0];
    delete[] p;
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m){
	if (this == &m)
		return *this;
    delete[] p[0];
	delete[] p;
	sor = m.sor;
	oszlop = m.oszlop;
    p = new T*[sor];
    p[0] = new T[sor*oszlop];
    for(int i = 0; i < sor; ++i)
        p[i]= p[0] + i*oszlop;
	for (int i = 0; i < sor; ++i)
		for (int j = 0; j < oszlop; ++j)
			p[i][j] = m.p[i][j];
	return *this;
}

template<class T>
bool Matrix<T>::operator==(const Matrix<T>& m)const{
	if (this == &m)
		return true;
	if (sor != m.sor || oszlop != m.oszlop)
		return false;
	for (int i = 0; i < sor; ++i)
		for (int j = 0; j < oszlop; ++j)
			if (p[i][j] != m.p[i][j])
				return false;
	return true;
}

template<class T>
void Matrix<T>::operator+=(double szam){
	for (int i = 0; i < sor; ++i)
		for (int j = 0; j < oszlop; ++j)
			p[i][j] += szam;
}
template<class T>
Matrix<T> Matrix<T>::operator+(double szam)const{
	Matrix<T> eredmeny = (*this);
	eredmeny += szam;
	return eredmeny;
}

template<class T>
Matrix<T> operator+(int szam, const Matrix<T>& m){
	return m + szam;
}

template<class T>
void Matrix<T>::operator+=(const Matrix<T>& m){
	if (sor != m.sor || oszlop != m.oszlop)
		throw std::runtime_error("A két mátrix dimenziói nem egyeznek");
	for (int i = 0; i < sor; ++i)
		for (int j = 0; j < oszlop; ++j)
				p[i][j] += m.p[i][j];
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& m)const{
	if (sor != m.sor || oszlop != m.oszlop)
		throw std::runtime_error("A két mátrix dimenziói nem egyeznek");
	Matrix<T> eredmeny = (*this);
	eredmeny += m;
	return eredmeny;
}

template<class T>
void Matrix<T>::operator*=(double szam){
	for (int i = 0; i < sor; ++i)
		for (int j = 0; j < oszlop; ++j)
			p[i][j] *= szam;
}

template<class T>
Matrix<T> Matrix<T>::operator*(double szam)const{
	Matrix<T> eredmeny = (*this);
	eredmeny *= szam;
	return eredmeny;
}

template<class T>
Matrix<T> operator*(int szam, const Matrix<T>& m){
	return m * szam;
}

template<class T>
Matrix<T> Matrix<T>::operator*(Matrix<T>& m)const{
	if (oszlop != m.getSor())
		throw std::runtime_error("A két mátrix nem szorozható össze");
	Matrix<T> eredmeny;
	eredmeny.setSor(sor);
	eredmeny.setOszlop(m.getOszlop());
	delete[] eredmeny.p[0];
	delete[] eredmeny.p;
	eredmeny.p = new T*[eredmeny.getSor()];
	eredmeny.p[0] = new T[eredmeny.getSor()*eredmeny.getOszlop()];
	for (int i = 0; i < eredmeny.getSor(); ++i)
		eredmeny.p[i] = eredmeny.p[0] + i*eredmeny.getOszlop();
	int osszeg = 0;
	for (int i = 0; i < sor; ++i)
		for (int k = 0; k < m.getOszlop(); ++k){
			for (int j = 0; j < oszlop; ++j){
				osszeg += getElem(i,j) * m.getElem(j,k);
				eredmeny.setElem(i,k,osszeg);
			}
		osszeg = 0;
		}
	return eredmeny;
}

template<class T>
Matrix<T> Matrix<T>::operator++()const{
	Matrix<T> eredmeny;
    eredmeny.setSor(oszlop);
	eredmeny.setOszlop(sor);
	delete[] eredmeny.p[0];
	delete[] eredmeny.p;
	eredmeny.p = new T*[eredmeny.getSor()];
	eredmeny.p[0] = new T[eredmeny.getSor()*eredmeny.getOszlop()];
    for (int i = 0; i < eredmeny.getSor(); ++i)
		eredmeny.p[i] = eredmeny.p[0] + i*eredmeny.getOszlop();
	for (int i = 0; i < sor; ++i)
		for (int j = 0; j < oszlop; ++j)
			eredmeny.p[j][i] = getElem(i,j);
    return eredmeny;
}


#endif // M
