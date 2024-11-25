#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

class ArrayGenerator {
public:
    ArrayGenerator(int minValue = 0, int maxValue = 6000)
        : minValue(minValue), maxValue(maxValue), rd(std::random_device{}()) {}

    std::vector<int> generateRandomArray(int size) {
        std::uniform_int_distribution<int> dist(minValue, maxValue);
        std::vector<int> arr(size);
        for (int i = 0; i < size; ++i) {
            arr[i] = dist(rd);
        }
        return arr;
    }

    std::vector<int> generateSortedReverseArray(int size) {
        std::vector<int> arr = generateRandomArray(size);
        std::sort(arr.begin(), arr.end(), std::greater<int>());
        return arr;
    }

    std::vector<int> generateNearlySortedArray(int size, int swapCount = 10) {
        std::vector<int> arr = generateRandomArray(size);
        std::sort(arr.begin(), arr.end());

        std::uniform_int_distribution<int> dist(0, size - 1);
        for (int i = 0; i < swapCount; ++i) {
            int index1 = dist(rd);
            int index2 = dist(rd);
            std::swap(arr[index1], arr[index2]);
        }
        return arr;
    }

    std::vector<int> generateSubarray(int size) {
        std::vector<int> fullArray = generateRandomArray(10000);
        return std::vector<int>(fullArray.begin(), fullArray.begin() + size);
    }

private:
    int minValue, maxValue;
    std::mt19937 rd;
};

int main() {
    ArrayGenerator generator;


    return 0;
}
