#include <iostream>
#include <vector>

template<class T, class Iter>
void Merge(Iter aBegin, Iter aEnd, Iter bBegin, Iter bEnd) {
    std::vector<T> answer(aEnd - aBegin + bEnd - bBegin);
    Iter i = aBegin, j = bBegin;
    int k = 0;
    while (i != aEnd || j != bEnd) {
        if (i == aEnd) {
            answer[k] = *j;
            ++j;
        } else if (j == bEnd) {
            answer[k] = *i;
            ++i;
        } else if ((*j) < (*i)) {
            answer[k] = *j;
            ++j;
        } else {
            answer[k] = *i;
            ++i;
        }
        ++k;
    }

    i = aBegin;
    for (const auto& x : answer) {
        *(i) = x;
        ++i;
    }

}

template<class T, class Iter>
void MergeSort(Iter begin, Iter end) {
    if (end - begin < 2) {
        return;
    }

    int midInt = (end - begin) / 2;
    Iter mid = begin + midInt;
    MergeSort<T, Iter>(begin, mid);
    MergeSort<T, Iter>(mid, end);
    Merge<T, Iter>(begin, mid, mid, end);
}

template<class T, class Iter>
static void insertionSort(Iter begin, Iter end) {
    for (Iter it = begin; it != end; ++it) {
        T value = *it;
        Iter prev = it;

        while (prev != begin && *(std::prev(prev)) > value) {
            *prev = *(std::prev(prev));
            --prev;
        }

        *prev = value;
    }
}

template<class T, class Iter>
void hybridMergeSort(Iter begin, Iter end) {
    if (end - begin < 15) {
        insertionSort<T>(begin, end);
    }

    int midInt = (end - begin) / 2;
    Iter mid = begin + midInt;
    MergeSort<T, Iter>(begin, mid);
    MergeSort<T, Iter>(mid, end);
    Merge<T, Iter>(begin, mid, mid, end);
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (auto& elem : arr) {
        std::cin >> elem;
    }

    hybridMergeSort<int>(arr.begin(), arr.end());

    for (auto& elem : arr) {
        std::cout << elem << " ";
    }
}
