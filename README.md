# MinHeap

MinHeapMod es una aplicación de consola de comandos que muestra el funcionamiento
de un MinHeap. MinHeapMod está programado en C++.

Un Heap es una estructura de datos que permite realizar en O(log(n)), siendo n
la cantidad de elemento que se encuentran en el heap, las siguientes operaciones:

-Obtener el mínimo elemento
-Insertar un elemento (encolar)
-Eliminar el mínimo elemento (desencolar)
-Eliminar un elemento al cual se tiene una referencia

Los heap pueden implementarse utilizando un array/vector o un árbol, MinHeapMod está
implementado sobre un árbol.


La aplicación realiza 10 iteraciones, elegiendo de forma aleatoria alguna de las
operaciones anteriomente descriptas. Los elementos de este heap son numeros enteros
entre 0 y 20.
En cada iteración indica cual es la operación que realiza, sobre cual elemento la realiza
y cual es el mínimo(próximo) al finalizar la operación.


Atención!
Esta versión contiene algunos bugs y en algunas secuencias de operaciones no 
reordena el árbol correctamente, lo cual se puede ver obsevando el mínimo.
