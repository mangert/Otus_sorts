#pragma once
#include <concepts>
#include <functional>

template <std::integral T>
class Sorter {
public:        
// ---------- Bubble sort -----------------

    //обычная сортировка пузырьком
    static void bubble_sort(T* data, size_t size) {

        for (size_t i = size - 1; i != 0; --i) {
            for (size_t j = 0; j < i; ++j) {
                if (data[j] > data[j + 1]) {
                    swap_idx(data, j, j + 1);
                }
            }
        }
    };

    //модифицированная сортировка пузырьком
    static void bubble_sort_opt(T* data, size_t size) {
        bool flag = true;
        for (size_t i = size - 1, flag; i != 0; --i) {
            flag = false;
            for (size_t j = 0; j < i; ++j) {
                if (data[j] > data[j + 1]) {
                    swap_idx(data, j, j + 1);
                    flag = true;
                }
            }
        }
    };
// ---------- Insertion sort -----------------    
    
    //сортировка вставками
    static void insertion_sort(T* data, size_t size) {

        for (size_t i = 1; i != size; ++i) {
            for (size_t j = i; j > 0 && (data[j - 1] > data[j]); --j) {
                        swap_idx(data, j, j - 1);
             }
        }
    };

    //модифицированная сортировка вставками (со сдвигом)
    static void insertion_sort_shift(T* data, size_t size) {
        
        for (size_t i = 1; i < size; ++i) {
            // Сохраняем текущий элемент
            T curr = data[i];
            
            size_t j = i;
            // Сдвигаем элементы вправо
            while (j > 0 && curr < data[j - 1]) {
                data[j] = data[j - 1];  // сдвиг вместо обмена
                --j;
            };

            // Вставляем рассматриваемый элемент на выбранную позицию на правильное место
            data[j] = curr;
        };
    }
    
    //сортировка вставками с бинанрным поиском
    static void insertion_sort_bin(T* data, size_t size) {
        
        for (size_t i = 1; i < size; ++i) {
            T curr = data[i];

            // Ищем позицию для curr в уже отсортированной части [0..i-1]
            size_t pos = binary_find(data, curr, i); 

            // Сдвигаем элементы вправо от pos до i-1
            for (size_t j = i; j > pos; --j) {
                data[j] = data[j - 1];
            }

            // Вставляем curr на найденную позицию
            data[pos] = curr;
        }
    }
    
    // ---------- Shell sort -----------------    
    
    // 1. Стандартный (gap = n/2, n/4, ...)
    static void shell_sort(T* data, size_t size) {
        if (size <= 1) return;
        shell_sort_core(data, size, size / 2,
            [](size_t g) { return g / 2; });
    }

    // 2. Кнута (1, 4, 13, 40, 121, ...)
    static void shell_sort_knuth(T* data, size_t size) {
        if (size <= 1) return;

        // Вычисляем максимальный gap < size
        size_t gap = 1;
        while (gap < size / 3) {
            gap = 3 * gap + 1;
        }

        shell_sort_core(data, size, gap,
            [](size_t g) { return (g - 1) / 3; });  // точная формула
    }

    // 3. Хиббарда (1, 3, 7, 15, 31, ...)
    static void shell_sort_hibbard(T* data, size_t size) {
        if (size <= 1) return;

        // Находим максимальный 2^k - 1 < size
        size_t k = 1;
        while ((1 << k) - 1 < size) ++k;
        size_t gap = (1 << (k - 1)) - 1;  // предыдущая степень

        shell_sort_core(data, size, gap,
            [](size_t g) { return (g + 1) / 2 - 1; });
    }

    // 4. Седжвика
    static void shell_sort_sedgewick(T* data, size_t size) {
        if (size <= 1) return;

        // Генерация последовательности Седжвика
        std::vector<size_t> gaps;
        size_t k = 0;
        while (true) {
            size_t gap;
            if (k % 2 == 0) {
                gap = 9 * (1 << k) - 9 * (1 << (k / 2)) + 1;
            }
            else {
                gap = 8 * (1 << k) - 6 * (1 << ((k + 1) / 2)) + 1;
            }
            if (gap >= size) break;
            gaps.push_back(gap);
            ++k;
        }

        // Сортируем с gaps в обратном порядке (от большего к меньшему)
        for (auto it = gaps.rbegin(); it != gaps.rend(); ++it) {
            size_t gap = *it;
            // Вставками с шагом gap
            for (size_t i = gap; i < size; ++i) {
                T current = data[i];
                size_t j = i;
                while (j >= gap && data[j - gap] > current) {
                    data[j] = data[j - gap];
                    j -= gap;
                }
                data[j] = current;
            }
        }
    }
    // ---------- Selection sort -----------------    
    //сортировка выбором
    static void selection_sort(T* data, size_t size) {

        for (size_t i = 0; i != size - 1; ++i) {
            size_t min_idx = i;
            for (size_t j = i + 1; j != size; ++j) {
                if (data[j] < data[min_idx])
                    min_idx = j;
            }
            if (min_idx != i)
                swap_idx(data, min_idx, i);
        };
    };
    
   // 6. quick_sort (нужен partition)
   // 7. merge_sort (нужен merge)
   // 8. heap_sort (нужны heapify)
   // 9. counting_sort (если требуется)

    //TODO Перегрузки всех сортировок для контейнеров с .data() и .size()
    template <typename Container>
    static void bubble_sort(Container& container) {
        bubble_sort(container.data(), container.size());
    }
private:    
    // Обобщенная версия сортировки Шелла
    template<typename GapFunc>
    static void shell_sort_core(T* data, size_t size, size_t initial_gap, GapFunc next_gap) {
        if (size <= 1) return;

        size_t gap = initial_gap;

        while (gap > 0) {
            for (size_t i = gap; i < size; ++i) {
                T current = data[i];
                size_t j = i;

                while (j >= gap && data[j - gap] > current) {
                    data[j] = data[j - gap];
                    j -= gap;
                }

                data[j] = current;
            }

            gap = next_gap(gap);
        }
    }
    
    //служебная функция обмена элементов с заданными индексами    
    static void swap_idx(T* data, size_t a, size_t b) noexcept {
        T tmp = data[a];
        data[a] = data[b];
        data[b] = tmp;
    };

    //поиск (бинарный) места для вставки
    static size_t binary_find(const T* data, const T& val, size_t n) {
        // Ищем позицию для вставки val в отсортированный массив data[0..n-1]
        size_t low = 0;
        size_t high = n;  // high = n, потому что вставлять можно после последнего элемента

        while (low < high) {
            size_t mid = low + (high - low) / 2;

            if (val > data[mid]) {
                low = mid + 1;  // Ищем в правой половине
            }
            else {
                high = mid;     // Ищем в левой половине (включая текущий mid)
            }
        }

        return low;  // low == high - позиция для вставки
    }
};
