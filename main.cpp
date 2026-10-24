/*
 * Programa: Cola priorizada de enteros implementada con un max-heap,
 * controlada mediante opciones leidas desde la entrada estandar.
 * Autores: Jaime Hugo Islas Trujillo, A01821293
 *          Francisco Xavier Olivos Barranco, A01820288
 * Fecha: 24 de octubre de 2026
 */

#include <iostream>
#include <vector>
#include <cstddef>

const int OPCION_SALIR = 0;
const int OPCION_PUSH = 1;
const int OPCION_POP = 2;
const int OPCION_PRINT = 3;
const int OPCION_TOP = 4;
const int OPCION_EMPTY = 5;
const int OPCION_SIZE = 6;

/**
 * Cola priorizada de enteros implementada con un max-heap.
 * El valor mayor siempre queda en la raiz (indice 0).
 * Espacio total: O(n), donde n es el numero de elementos almacenados.
 */
class PriorityQueue {
private:
	std::vector<int> elementos;

	// Intercambia dos elementos del heap. Tiempo: O(1); espacio auxiliar: O(1).
	// Parametro indiceA: posicion del primer elemento.
	// Parametro indiceB: posicion del segundo elemento.
	void intercambiar(std::size_t indiceA, std::size_t indiceB) {
		int valorAuxiliar = elementos[indiceA];
		elementos[indiceA] = elementos[indiceB];
		elementos[indiceB] = valorAuxiliar;
	}

	// Restaura el heap subiendo un elemento. Tiempo: O(log n); espacio auxiliar: O(1).
	// Parametro indice: posicion del elemento que se desea subir.
	void siftUp(std::size_t indice) {
		while (indice > 0 && elementos[(indice - 1) / 2] < elementos[indice]) {
			std::size_t padre = (indice - 1) / 2;
			intercambiar(padre, indice);
			indice = padre;
		}
	}

	// Restaura el heap bajando un elemento. Tiempo: O(log n); espacio auxiliar: O(1).
	// Parametro indice: posicion del elemento que se desea bajar.
	void siftDown(std::size_t indice) {
		std::size_t totalElementos = elementos.size();
		bool terminado = false;
		while (!terminado) {
			std::size_t izquierdo = 2 * indice + 1;
			std::size_t derecho = 2 * indice + 2;
			std::size_t mayor = indice;
			if (izquierdo < totalElementos && elementos[izquierdo] > elementos[mayor]) {
				mayor = izquierdo;
			}
			if (derecho < totalElementos && elementos[derecho] > elementos[mayor]) {
				mayor = derecho;
			}
			if (mayor == indice) {
				terminado = true;
			} else {
				intercambiar(indice, mayor);
				indice = mayor;
			}
		}
	}

public:
	// Agrega un entero y restaura el max-heap.
	// Tiempo: O(log n) amortizado; O(n) en el peor caso si el vector se redimensiona.
	// Espacio adicional: O(1) amortizado; el almacenamiento total es O(n).
	// Parametro valor: entero que se agrega a la cola.
	void push(int valor) {
		elementos.push_back(valor);
		siftUp(elementos.size() - 1);
	}

	// Elimina el mayor elemento. Si esta vacia, no hace nada.
	// Tiempo: O(log n) en el peor caso; espacio auxiliar: O(1).
	void pop() {
		if (!elementos.empty()) {
			elementos[0] = elementos.back();
			elementos.pop_back();
			if (!elementos.empty()) {
				siftDown(0);
			}
		}
	}

	// Devuelve el mayor sin eliminarlo; requiere que la cola no este vacia.
	// Tiempo: O(1); espacio auxiliar: O(1).
	// Retorna: el elemento mayor de la cola.
	int top() const {
		return elementos[0];
	}

	// Imprime todos los elementos en el orden interno del heap.
	// Tiempo: O(n); espacio auxiliar: O(1).
	void print() const {
		for (std::size_t indice = 0; indice < elementos.size(); indice++) {
			if (indice > 0) {
				std::cout << ' ';
			}
			std::cout << elementos[indice];
		}
		std::cout << '\n';
	}

	// Indica si la cola esta vacia. Tiempo: O(1); espacio auxiliar: O(1).
	// Retorna: true si no hay elementos, false en caso contrario.
	bool empty() const {
		return elementos.empty();
	}

	// Devuelve la cantidad de elementos. Tiempo: O(1); espacio auxiliar: O(1).
	// Retorna: numero de elementos almacenados.
	std::size_t size() const {
		return elementos.size();
	}
};

// Ejecuta la operacion de la cola que corresponde a la opcion leida.
// El menu no se imprime; el resultado de cada opcion se escribe en la salida estandar.
// Parametro cola: cola priorizada sobre la que se opera.
// Parametro opcion: numero de operacion solicitada.
// Retorna: false si faltaba el valor a insertar y hay que terminar, true en otro caso.
bool procesarOpcion(PriorityQueue &cola, int opcion) {
	bool entradaValida = true;
	if (opcion == OPCION_PUSH) {
		int valor = 0;
		if (std::cin >> valor) {
			cola.push(valor);
		} else {
			entradaValida = false;
		}
	} else if (opcion == OPCION_POP) {
		// Se imprime el maximo antes de eliminarlo, como en el ejemplo solicitado.
		if (!cola.empty()) {
			std::cout << cola.top() << '\n';
			cola.pop();
		}
	} else if (opcion == OPCION_PRINT) {
		cola.print();
	} else if (opcion == OPCION_TOP) {
		if (!cola.empty()) {
			std::cout << cola.top() << '\n';
		}
	} else if (opcion == OPCION_EMPTY) {
		std::cout << (cola.empty() ? "true" : "false") << '\n';
	} else if (opcion == OPCION_SIZE) {
		std::cout << cola.size() << '\n';
	}
	return entradaValida;
}

int main() {
	PriorityQueue colaPrioridad;
	int opcion = OPCION_SALIR;
	bool continuar = true;

	while (continuar && std::cin >> opcion && opcion != OPCION_SALIR) {
		continuar = procesarOpcion(colaPrioridad, opcion);
	}
	return 0;
}
