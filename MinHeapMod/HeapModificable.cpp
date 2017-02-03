#pragma once

#include "HeapModificable.h"

HeapModificable::Iterador& HeapModificable::Iterador::operator = (const HeapModificable::Iterador& otra)
{
	heap = otra.heap;
	siguiente = otra.siguiente;
	return *this;
}


const HeapModificable::const_Iterador& HeapModificable::const_Iterador::operator = (const HeapModificable::const_Iterador& otra)
{
	heap = otra.heap;
	siguiente = otra.siguiente;
	return *this;
}


// Observadores
bool HeapModificable::esVacia()
{
	return tope == NULL;
}

const int& HeapModificable::proximo() const 
{
	return tope->elemento;
}

// Generadores
HeapModificable::HeapModificable() : tope(NULL) {}

HeapModificable::Iterador HeapModificable::encolar(const int& a)
{
    Nodo* siguienteIt;
    
	if(tope == NULL){
		tope = new Nodo(a, 0, 0, NULL, NULL, NULL);
		siguienteIt = tope;
	}
	else {
		Nodo* ftrPadre = futuroPadre();
		
		if(ftrPadre->hijoIzq == NULL){
			ftrPadre->hijoIzq = new Nodo(a, 0, 0, NULL, NULL, ftrPadre);
			ftrPadre = ftrPadre->hijoIzq;
		}
		else {
			ftrPadre->hijoDer = new Nodo(a, 0, 0, NULL, NULL, ftrPadre);
			ftrPadre = ftrPadre->hijoDer;
		}
		corregirProfundidad(ftrPadre->padre);
		siftUp(ftrPadre);
		siguienteIt = ftrPadre;
	}
	
	return Iterador(this, siguienteIt);
}

// Otras operaciones
void HeapModificable::desencolar()
{
	Nodo* destruir = tope;
	
	if ((*tope).hijoIzq == NULL && (*tope).hijoDer == NULL)
	{
		tope = NULL;
	}
	else
	{
		Nodo* ultNodo = ultimoNodo();
		Nodo* padreUlt = (*ultNodo).padre;
		if ((*padreUlt).hijoDer == ultNodo)	(*padreUlt).hijoDer = NULL;
		else (*padreUlt).hijoIzq = NULL;

		corregirProfundidad(padreUlt);

		(*ultNodo).padre = NULL;
		(*ultNodo).hijoIzq = (*tope).hijoIzq;
		(*ultNodo).hijoDer = (*tope).hijoDer;
		(*ultNodo).ramaMasCorta = (*tope).ramaMasCorta;
		(*ultNodo).ramaMasLarga = (*tope).ramaMasLarga;

		tope = ultNodo;

		if ((*tope).hijoDer != NULL) (*(*tope).hijoDer).padre = tope;
		if ((*tope).hijoIzq != NULL) (*(*tope).hijoIzq).padre = tope;
		if ((*tope).hijoIzq != NULL || (*tope).hijoDer != NULL)
		{
			siftDown(tope);
		}
	}
	delete destruir;
}

// Destructor
HeapModificable::~HeapModificable()
{
    while(tope != NULL){
        desencolar();
    }
}

// Iterador
HeapModificable::Iterador::Iterador(HeapModificable::Iterador& otra)	// CrearIt()
	: heap(otra.heap), siguiente(otra.siguiente)
{}


HeapModificable::Iterador::Iterador(HeapModificable* h, HeapModificable::Nodo* siguiente)	// CrearIt()
	: heap(h), siguiente(siguiente)
{}

bool HeapModificable::Iterador::haySiguiente() const
{
	return heap->tope != NULL;
}

int& HeapModificable::Iterador::Siguiente() const
{
	return (*siguiente).elemento;
}

void HeapModificable::Iterador::eliminarSiguiente()
{

	Nodo* ultimoNodo = (*heap).tope;

	if ((*heap).tope == siguiente)
	{
		(*heap).desencolar();
	}
	else
	{
		ultimoNodo = heap->ultimoNodo();	//en diseño: quedo de c, era del heap del it
		Nodo* padreUlt = (*ultimoNodo).padre;
		if ((*padreUlt).hijoDer == ultimoNodo)
		{
			(*padreUlt).hijoDer = NULL;
		}
		else
		{
			(*padreUlt).hijoIzq = NULL;
		}
		heap->corregirProfundidad(padreUlt);	//idem
		(*ultimoNodo).padre = (*siguiente).padre;
		(*ultimoNodo).hijoIzq = (*siguiente).hijoIzq;
		(*ultimoNodo).hijoDer = (*siguiente).hijoDer;
		(*ultimoNodo).ramaMasCorta = (*siguiente).ramaMasCorta;

		(*ultimoNodo).ramaMasLarga = (*siguiente).ramaMasLarga;

		if ((*siguiente).padre != NULL)
		{
			if ((*(*siguiente).padre).hijoIzq == siguiente)
			{
				(*(*siguiente).padre).hijoIzq = ultimoNodo;
			}
			else
			{
				(*(*siguiente).padre).hijoDer = ultimoNodo;
			}
		}
		delete siguiente;
		heap->siftDown(ultimoNodo);
		heap->siftUp(ultimoNodo);
	}
	siguiente = NULL;	// se invalida el iterador
	heap = NULL;
}

void HeapModificable::Iterador::agregarComoSiguiente(const int& a)
{
	heap->encolar(a);
}


HeapModificable::const_Iterador::const_Iterador(const HeapModificable* h, const HeapModificable::Nodo* siguiente) 	// CrearIt()
	: heap(h), siguiente(siguiente)
{}


bool HeapModificable::const_Iterador::haySiguiente() const
{
	return heap != NULL;
}

const int& HeapModificable::const_Iterador::Siguiente() const
{
	return (*siguiente).elemento;
}


// private
HeapModificable::Nodo* HeapModificable::ultimoNodo() const 
{
	Nodo* ultimoNodo = tope;

	while ((*ultimoNodo).hijoIzq != NULL && (*ultimoNodo).hijoDer != NULL)
	{
		if ( (*(*ultimoNodo).hijoIzq).ramaMasLarga == (*(*ultimoNodo).hijoDer).ramaMasLarga )
		{
			ultimoNodo = (*ultimoNodo).hijoDer;
		}
		else
		{
			ultimoNodo = (*ultimoNodo).hijoIzq;
		}
	}
	if ((*ultimoNodo).hijoDer != NULL)
	{
		ultimoNodo = (*ultimoNodo).hijoDer;
	}
	else if((*ultimoNodo).hijoIzq != NULL)
	{
		ultimoNodo = (*ultimoNodo).hijoIzq;
	}

	return ultimoNodo;
}

HeapModificable::Nodo* HeapModificable::futuroPadre() const 
{
	Nodo* ultimoNodo = tope;
	while ((*ultimoNodo).hijoIzq != NULL && (*ultimoNodo).hijoDer != NULL)
	{
		if ( (ultimoNodo->hijoIzq)->ramaMasCorta == (ultimoNodo->hijoDer)->ramaMasCorta )
		{
			ultimoNodo = (*ultimoNodo).hijoIzq;
		}
		else
		{
			ultimoNodo = (*ultimoNodo).hijoDer;
		}
	}
	return ultimoNodo;
}

void HeapModificable::corregirProfundidad(Nodo* p)
{
	if ((*p).hijoIzq == NULL && (*p).hijoDer == NULL)
	{
		(*p).ramaMasCorta = 0;
		(*p).ramaMasLarga = 0;
	}
	else
	{
		if ((*p).hijoIzq != NULL && (*p).hijoDer != NULL)
		{
			(*p).ramaMasCorta = 1;
			(*p).ramaMasLarga = 1;
		}
		else
		{
			(*p).ramaMasCorta = 0;
			(*p).ramaMasLarga = 1;
		}
	}
	
	while((*p).padre != NULL)
	{
		p = (*p).padre;
		if ((*p).hijoDer != NULL)
		{
			(*p).ramaMasCorta = (*((*p).hijoDer)).ramaMasCorta + 1;
		}
		if ((*p).hijoIzq != NULL)
		{
			(*p).ramaMasLarga = (*((*p).hijoIzq)).ramaMasLarga + 1;
		}
		
	}
}

void HeapModificable::siftDown(Nodo* p)
{
	Nodo* swap = p;

	if ((*p).hijoIzq != NULL )
	{
		if (((*(*p).hijoIzq).elemento < (*p).elemento))
		{
		    swap = (*p).hijoIzq;
		}
	}

	if ((*p).hijoDer != NULL)
	{
		if ((*(*p).hijoDer).elemento < (*p).elemento)
		{
			swap = (*p).hijoDer;
		}
	}

	if (p != swap)
	{
		intercambio(p, swap);
		if(p == tope) tope = swap;
		siftDown(p);
	}
}

void HeapModificable::siftUp(Nodo* p)
{
	if ((*p).padre == NULL){
		tope = p;
	}
	else{
		Nodo* swap = p;
		if(p->elemento < (p->padre)->elemento){
		    swap = p->padre;
	    }
    	if(p != swap){
	    	intercambio(swap, p);
		    siftUp(p);
	    }
	}
}

void HeapModificable::intercambio(Nodo* padre, Nodo* hijo)
{
	Nodo* abuelo = padre->padre;
	if(abuelo != NULL){
		if(abuelo->hijoIzq == padre) abuelo->hijoIzq = hijo;
		else abuelo->hijoDer = hijo; 
	}

	if(hijo->hijoIzq != NULL) hijo->hijoIzq->padre = padre;
	if(hijo->hijoDer != NULL) hijo->hijoDer->padre = padre;

	unsigned int rmc = hijo->ramaMasCorta;
	unsigned int rml = hijo->ramaMasLarga;
	hijo->padre = padre->padre;
	hijo->ramaMasCorta = padre->ramaMasCorta;
	hijo->ramaMasLarga = padre->ramaMasLarga;
	padre->padre = hijo;
	padre->ramaMasCorta = rmc;
	padre->ramaMasLarga = rml;
	
	if(padre->hijoIzq == hijo){
		Nodo* hijoDerDelPadre = padre->hijoDer;
		padre->hijoIzq = hijo->hijoIzq;
		padre->hijoDer = hijo->hijoDer;
		hijo->hijoIzq = padre;
		hijo->hijoDer = hijoDerDelPadre;
		if(hijoDerDelPadre != NULL) hijoDerDelPadre->padre = hijo;
	} else {
		Nodo* hijoIzqDelPadre = padre->hijoIzq;
		padre->hijoIzq = hijo->hijoIzq;
		padre->hijoDer = hijo->hijoDer;
		hijo->hijoIzq = hijoIzqDelPadre;
		hijo->hijoDer = padre;
		hijoIzqDelPadre->padre = hijo;
	}
}

// Nodo

HeapModificable::Nodo::Nodo(int jh, unsigned int rmc, unsigned int rml, Nodo* hI, Nodo* hD, Nodo* padre)
    : elemento(jh), ramaMasCorta(rmc), ramaMasLarga(rml), hijoIzq(hI), hijoDer(hD), padre(padre)
{}