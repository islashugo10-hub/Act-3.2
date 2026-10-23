#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <vector>

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

/**
 * @brief Cola priorizada de enteros implementada mediante un max-heap.
 *
 * El entero de mayor valor siempre se encuentra en la raiz (indice 0).
 * Los elementos se imprimen en el orden interno del heap, no ordenados.
 */
class priority_queue {
private:
    std::vector<int> heap_;

    /**
     * Restaura la propiedad del max-heap subiendo un elemento.
     * Complejidad: O(log n).
     */
    void sift_up(std::size_t index) {
        while (index > 0) {
            const std::size_t parent = (index - 1) / 2;
            if (heap_[parent] >= heap_[index]) {
                break;
            }
            int temp = heap_[parent];
            heap_[parent] = heap_[index];
            heap_[index] = temp;
            index = parent;
        }
    }

    /**
     * Restaura la propiedad del max-heap bajando un elemento.
     * Complejidad: O(log n).
     */
    void sift_down(std::size_t index) {
        const std::size_t count = heap_.size();

        while (true) {
            const std::size_t left = 2 * index + 1;
            const std::size_t right = 2 * index + 2;
            std::size_t largest = index;

            if (left < count && heap_[left] > heap_[largest]) {
                largest = left;
            }
            if (right < count && heap_[right] > heap_[largest]) {
                largest = right;
            }
            if (largest == index) {
                break;
            }

            int temp = heap_[index];
            heap_[index] = heap_[largest];
            heap_[largest] = temp;
            index = largest;
        }
    }

public:
    /**
     * Agrega un entero a la cola priorizada.
     * Complejidad: O(log n) amortizada; una realocacion del vector puede
     * requerir O(n) ocasionalmente.
     */
    void push(int value) {
        heap_.push_back(value);
        sift_up(heap_.size() - 1);
    }

    /**
     * Elimina el elemento de mayor prioridad sin devolverlo.
     * Se espera que la cola contenga al menos un elemento.
     * Complejidad: O(log n).
     */
    void pop() {
        if (heap_.empty()) {
            return;
        }

        if (heap_.size() == 1) {
            heap_.pop_back();
            return;
        }

        heap_[0] = heap_.back();
        heap_.pop_back();
        sift_down(0);
    }

    /**
     * Regresa el elemento de mayor prioridad sin eliminarlo.
     * Precondicion: la cola no esta vacia.
     * Complejidad: O(1).
     */
    int top() const {
        if (heap_.empty()) {
            throw std::out_of_range("top() requiere una cola no vacia");
        }
        return heap_[0];
    }

    /**
     * Imprime los elementos en el orden interno del heap, separados por
     * un espacio y sin espacio al final.
     * Complejidad: O(n).
     */
    void print() const {
        for (std::size_t i = 0; i < heap_.size(); ++i) {
            if (i > 0) {
                std::cout << ' ';
            }
            std::cout << heap_[i];
        }
        std::cout << '\n';
    }

    /**
     * Indica si la cola no contiene elementos.
     * Complejidad: O(1).
     */
    bool is_empty() const {
        return heap_.empty();
    }

    /**
     * Regresa la cantidad de elementos almacenados.
     * Complejidad: O(1).
     */
    std::size_t size() const {
        return heap_.size();
    }
};

#include <iostream>

int main() {
    priority_queue queue;
    int option = -1;

    // Se lee una opcion por linea. El menu no se imprime, como indica la tarea.
    while (std::cin >> option && option != 0) {
        switch (option) {
            case 1: {  // push
                int value;
                if (std::cin >> value) {
                    queue.push(value);
                } else {
                    return 0;
                }
                break;
            }

            case 2:  // pop
                // La tabla indica que pop() no devuelve un valor. Para que la
                // interaccion coincida con el ejemplo, se imprime primero el
                // elemento que se va a eliminar y despues se llama a pop().
                if (!queue.is_empty()) {
                    std::cout << queue.top() << '\n';
                    queue.pop();
                }
                break;

            case 3:  // print
                queue.print();
                break;

            case 4:  // top
                if (!queue.is_empty()) {
                    std::cout << queue.top() << '\n';
                }
                break;

            case 5:  // is_empty
                std::cout << (queue.is_empty() ? "true" : "false") << '\n';
                break;

            case 6:  // size
                std::cout << queue.size() << '\n';
                break;

            default:
                // Una opcion fuera del menu se ignora.
                break;
        }
    }

    return 0;
}
