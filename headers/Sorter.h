#pragma once
#include <concepts>

template <std::integral T>
class Sorter {
public:    

    // Для сырых указателей
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
                data[j] = data[j - 1];  // не swap, а сдвиг
                --j;
            };

            // Вставляем рассматриваемый элемент на выбранную позицию на правильное место
            data[j] = curr;
        };
    }

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
    //сортировка вставками
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

    //shell 
    static void shell_sort(T* data, size_t size) {
        
    };

    

   // 3. selection_sort
   // 4. insertion_sort  
   // 5. shell_sort
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
