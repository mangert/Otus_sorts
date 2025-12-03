#pragma once
#include <concepts>

template <std::integral T>
class Sorter {
public:    

    // Для сырых указателей
    //обычная сортировка пузырьком
    static void bubble_sort(T* data, size_t size) {

        for (size_t j = size - 1; j != 0; --j) {
            for (size_t i = 0; i < j; ++i) {
                if (data[i] > data[i + 1]) {
                    swap_idx(data, i, i + 1);
                }
            }
        }
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

    //поиск элемента (бинарный) для вставки
    static size_t b_find(const T& val, const T* data, const size_t a) {

    }
};
