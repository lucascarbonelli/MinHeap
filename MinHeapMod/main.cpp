#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <vector>
#include <set>
#include <algorithm>
#include <time.h>
#include "HeapModificable.h"

#define MAX_VALOR	20

using namespace std;

int main()
{
	HeapModificable *h = new HeapModificable();
	set<int> numerosEnHeap;
	vector<HeapModificable::Iterador> iteradores;
	srand(time(NULL));

	int num = rand() % MAX_VALOR;
	numerosEnHeap.insert(num);
	iteradores.push_back(h->encolar(num));
	printf("Elemento encolado:\t%d\tProximo elemento:\t%d\n", num, h->proximo());

	for (size_t i = 0; i < 10; i++)
	{
		int num;
		if (iteradores.size() > 0) {
			vector<HeapModificable::Iterador>::iterator it = iteradores.begin();
			int opcion = rand() % 3;
			switch (opcion)
			{
			case 0:
				do {
					num = rand() % MAX_VALOR;
				} while (numerosEnHeap.find(num) != numerosEnHeap.end());
				numerosEnHeap.insert(num);
				iteradores.push_back(h->encolar(num));
				printf("Elemento encolado:\t%d\tProximo elemento:\t%d\n", num, h->proximo());
				break;

			case 1:
				num = h->proximo();
				numerosEnHeap.erase(num);

				it = iteradores.begin();
				while (it->Siguiente() != num)
				{
					++it;
				}

				iteradores.erase(it);

				h->desencolar();
				printf("Elemento desencolado:\t%d", num);
				if (!h->esVacia()) {
					printf("\tProximo elemento:\t%d", h->proximo());
				}
				printf("\n");
				break;

			case 2:
				int numEliminar = rand() % iteradores.size();
				num = iteradores[numEliminar].Siguiente();

				numerosEnHeap.erase(num);
				
				it = iteradores.begin();
				while (it->Siguiente() != iteradores[numEliminar].Siguiente())
				{
					++it;
				}

				iteradores[numEliminar].eliminarSiguiente();
				iteradores.erase(it);

				printf("Elemento eliminado:\t%d", num);
				if (!h->esVacia()) {
					printf("\tProximo elemento:\t%d", h->proximo());
				}
				printf("\n");
				break;
			}
		} else {
			num = rand() % MAX_VALOR;
			numerosEnHeap.insert(num);
			iteradores.push_back(h->encolar(num));
			printf("Elemento encolado:\t%d\tProximo elemento:\t%d\n", num, h->proximo());
		}
	}

	return 0;
}