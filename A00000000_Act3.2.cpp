#include <iostream>
#include <vector>
#include <cstddef>

/**
 * Cola priorizada de enteros implementada con un max-heap.
 * El valor mayor siempre queda en la raíz (índice 0).
 * Espacio total: O(n), donde n es el número de elementos almacenados.
 */
class priority_queue {
private:
    std::vector<int> heap;

    // Restaura el heap subiendo un elemento. Tiempo: O(log n); espacio auxiliar: O(1).
    void sift_up(std::size_t i) {
        while (i > 0) {
            std::size_t parent = (i - 1) / 2;
            if (heap[parent] >= heap[i]) break;
            int temp = heap[parent];
            heap[parent] = heap[i];
            heap[i] = temp;
            i = parent;
        }
    }

    // Restaura el heap bajando un elemento. Tiempo: O(log n); espacio auxiliar: O(1).
    void sift_down(std::size_t i) {
        std::size_t n = heap.size();
        while (true) {
            std::size_t left = 2 * i + 1, right = 2 * i + 2, largest = i;
            if (left < n && heap[left] > heap[largest]) largest = left;
            if (right < n && heap[right] > heap[largest]) largest = right;
            if (largest == i) break;
            int temp = heap[i];
            heap[i] = heap[largest];
            heap[largest] = temp;
            i = largest;
        }
    }

public:
    // Agrega un entero y restaura el max-heap.
    // Tiempo: O(log n) amortizado; O(n) en el peor caso si vector se redimensiona.
    // Espacio adicional: O(1) amortizado; el almacenamiento total es O(n).
    void push(int value) {
        heap.push_back(value);
        sift_up(heap.size() - 1);
    }

    // Elimina el mayor elemento. Si está vacía, no hace nada.
    // Tiempo: O(log n) en el peor caso; espacio auxiliar: O(1).
    void pop() {
        if (heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) sift_down(0);
    }

    // Devuelve el mayor sin eliminarlo; requiere que la cola no esté vacía.
    // Tiempo: O(1); espacio auxiliar: O(1).
    int top() const { return heap[0]; }

    // Imprime todos los elementos en el orden interno del heap.
    // Tiempo: O(n); espacio auxiliar: O(1).
    void print() const {
        for (std::size_t i = 0; i < heap.size(); ++i) {
            if (i) std::cout << ' ';
            std::cout << heap[i];
        }
        std::cout << '\n';
    }

    // Indica si está vacía. Tiempo: O(1); espacio auxiliar: O(1).
    bool is_empty() const { return heap.empty(); }

    // Devuelve la cantidad de elementos. Tiempo: O(1); espacio auxiliar: O(1).
    std::size_t size() const { return heap.size(); }
};

int main() {
    priority_queue pq;
    int option;

    // El menú no se imprime; las opciones se leen desde la entrada estándar.
    // 1: push, 2: pop, 3: print, 4: top, 5: is_empty, 6: size, 0: salir.
    while (std::cin >> option && option != 0) {
        switch (option) {
            case 1: {
                int value;
                if (std::cin >> value) pq.push(value);
                else return 0;
                break;
            }
            case 2:
                // Se imprime el máximo antes de eliminarlo, como en el ejemplo solicitado.
                if (!pq.is_empty()) {
                    std::cout << pq.top() << '\n';
                    pq.pop();
                }
                break;
            case 3: pq.print(); break;
            case 4:
                if (!pq.is_empty()) std::cout << pq.top() << '\n';
                break;
            case 5: std::cout << (pq.is_empty() ? "true" : "false") << '\n'; break;
            case 6: std::cout << pq.size() << '\n'; break;
            default: break;
        }
    }
    return 0;
}