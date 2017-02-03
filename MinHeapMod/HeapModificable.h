#ifndef TP3_HEAPMODIFICABLE_H
#define TP3_HEAPMODIFICABLE_H

#pragma once

#include <iostream>
#include <stdexcept>

using namespace std;

class HeapModificable
{
	private:
		struct Nodo;

	public:
	
	    class Iterador;
		class const_Iterador;
		
	
	// Observadores
		bool esVacia(); // Vacia?()
		const int& proximo() const;
		
	// Generadores
		HeapModificable(); // Generador Vacia()
		Iterador encolar(const int& a);
		
	// Otras operaciones
		void desencolar();	//por algun motivo, esto esta como obs en el tad... ??
		
	// Destructor
	    ~HeapModificable();
	
	// Iterador
		class Iterador
		{
			public:
				Iterador(HeapModificable::Iterador& otra);
				Iterador(HeapModificable* h, HeapModificable::Nodo* siguiente);	// CrearIt()
				bool haySiguiente() const;
				int& Siguiente() const;
				void eliminarSiguiente();
				void agregarComoSiguiente(const int& a);

				// Operador de asignacion;
				HeapModificable::Iterador& operator = (const HeapModificable::Iterador& otra);

				
			private:
			    HeapModificable* heap;
				Nodo* siguiente;
		};
		
		class const_Iterador
		{
			public:
				const_Iterador(const HeapModificable* h, const HeapModificable::Nodo* siguiente);	// CrearIt()
				bool haySiguiente() const;
				const int& Siguiente() const;

				const HeapModificable::const_Iterador& operator = (const HeapModificable::const_Iterador& otra);
				
			private:
			    const HeapModificable* heap;
				const Nodo* siguiente;
		};
		
	private:
			
		struct Nodo
		{
		    Nodo(int jh, unsigned int rmc, unsigned int rml, Nodo* hI, Nodo* hD, Nodo* padre);
		
			int elemento;
			unsigned int ramaMasCorta;
			unsigned int ramaMasLarga;
			Nodo* hijoIzq;
			Nodo* hijoDer;
			Nodo* padre;
		};
		
		Nodo* tope;
		
		Nodo* ultimoNodo() const;
		Nodo* futuroPadre() const;
		void corregirProfundidad(Nodo* p);
		void siftDown(Nodo* p);
		void siftUp(Nodo* p);
		void intercambio(Nodo* padre, Nodo* hijo);
};

#endif