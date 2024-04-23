#ifndef DATASTRUCTURES_SORTING_H
#define DATASTRUCTURES_SORTING_H

#include <functional>

namespace Algorithms {

    template<typename T>
    class Sorting {
        void divide(T *arr, int l, int r, std::function<bool(T &, T &)> &cmp);

        void merge(T *arr, int low, int mid, int high, std::function<bool(T &, T &)> &cmp);

        int partition(T *arr, int low, int high, std::function<bool(T &, T &)> &cmp);

        void quickSort(T *arr, int low, int high, std::function<bool(T &, T &)> &cmp);

    public:
        void InsertionSort(T *arr, int n, std::function<bool(T &, T &)> &cmp);

        void SelectionSort(T arr[], int n, std::function<bool(T &, T &)> &cmp);

        void BubbleSort(T arr[], int n, std::function<bool(T &, T &)> &cmp);

        void MergeSort(T arr[], int n, std::function<bool(T &, T &)> &cmp);

        void QuickSort(T arr[], int n, std::function<bool(T &, T &)> &cmp);

        void ShellSort(T arr[], int n, std::function<bool(T &, T &)> &cmp);
    };

    template<typename T>
    void Sorting<T>::InsertionSort(T *arr, int n, std::function<bool(T &, T &)> &cmp) {
        for (int i = 1; i < n; i++) {
            T to = arr[i];
            int j = i - 1;
            while (j >= 0 && !cmp(arr[j], to)) {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = to;
        }
    }

    template<typename T>
    void Sorting<T>::SelectionSort(T *arr, int n, std::function<bool(T &, T &)> &cmp) {
        for (int i = 0; i < n; i++) {
            int index = i;
            for (int j = i + 1; j < n; ++j) {
                if (cmp(arr[j], arr[index])) index = j;
            }
            if (index != i) std::swap(arr[index], arr[i]);
        }
    }

    template<typename T>
    void Sorting<T>::BubbleSort(T *arr, int n, std::function<bool(T &, T &)> &cmp) {
        for (int i = 0; i < n - 1; i++) {
            bool isSorted = true;
            for (int j = 0; j < n - i - 1; j++) {
                if (!cmp(arr[j], arr[j + 1])) {
                    std::swap(arr[j], arr[j + 1]);
                    isSorted = false;
                }
            }
            if (isSorted) break;
        }
    }

    template<typename T>
    void Sorting<T>::merge(T *arr, int low, int mid, int high, std::function<bool(T &, T &)> &cmp) {
        int left = mid - low + 1;
        int right = high - mid;
        T lArray[left];
        T rArray[right];
        for (int i = low; i <= mid; ++i) lArray[i - low] = arr[i];
        for (int i = mid + 1; i <= high; ++i) rArray[i - (mid + 1)] = arr[i];
        int l = 0, r = 0, top = low;
        while (l < left && r < right) {
            if (cmp(lArray[l], rArray[r])) arr[top] = lArray[l++];
            else arr[top] = rArray[r++];
            ++top;
        }
        while (l < left) arr[top++] = lArray[l++];
        while (r < right) arr[top++] = rArray[r++];
    }

    template<typename T>
    void Sorting<T>::divide(T *arr, int l, int r, std::function<bool(T &, T &)> &cmp) {
        if (l >= r) return;
        int mid = (r + l) / 2;
        divide(arr, l, mid, cmp);
        divide(arr, mid + 1, r, cmp);
        merge(arr, l, mid, r, cmp);
    }

    template<typename T>
    void Sorting<T>::MergeSort(T *arr, int n, std::function<bool(T &, T &)> &cmp) {
        divide(arr, 0, n - 1, cmp);
    }

    template<typename T>
    int Sorting<T>::partition(T *arr, int low, int high, std::function<bool(T &, T &)> &cmp) {
        T pivot = arr[low];
        int i = low + 1;
        for (int j = low + 1; j <= high; ++j) {
            if (cmp(arr[j], pivot)) std::swap(arr[j], arr[i++]);
        }
        std::swap(arr[i - 1], arr[low]);
        return i - 1;
    }

    template<typename T>
    void Sorting<T>::quickSort(T *arr, int low, int high, std::function<bool(T &, T &)> &cmp) {
        if (low >= high) return;
        int p = partition(arr, low, high, cmp);
        quickSort(arr, low, p - 1, cmp);
        quickSort(arr, p + 1, high, cmp);
    }

    template<typename T>
    void Sorting<T>::QuickSort(T *arr, int n, std::function<bool(T &, T &)> &cmp) {
        quickSort(arr, 0, n - 1, cmp);
    }

    template<typename T>
    void Sorting<T>::ShellSort(T *arr, int n, std::function<bool(T &, T &)> &cmp) {
        for (int gap = n >> 1; gap; gap >>= 1) {
            for (int i = gap; i < n; ++i) {
                T to = arr[i];
                int j = i;
                for (j = i; j >= gap; j -= gap) {
                    if (!cmp(arr[j - gap], to)) arr[j] = arr[j - gap];
                    else break;
                }
                arr[j] = to;
            }
        }
    }

}
#endif
