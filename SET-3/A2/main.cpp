#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <algorithm>
#include <string>

class ArrayGenerator {
private:
    int minValue, maxValue;
    std::mt19937 rd;
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
        std::sort(arr.rbegin(), arr.rend());
        return arr;
    }

    std::vector<int> generateAlmostSortedArray(int size, int swapCount = 10) {
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
};

void PrintArray(std::vector<int>& arr) {
    for (auto& elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
}

template<typename T>
void PrintArrayIntoFile(std::ofstream &file, const std::vector<T> &array) {
    for (size_t i = 0; i < array.size(); ++i) {
        file << array[i];
        if (i < array.size() - 1) {
            file << ", ";
        }
    }
    file << '\n';
}

void createTestFileFromBigArray(std::vector<int> arr, int maxSize, const char* fileName) {
    std::string fullFileName = std::string("../A2_") + fileName + ".txt";
    std::ofstream outFile(fullFileName);
    for (int size = 500; size < maxSize; size += 100) {
        std::vector<int> curArray(arr.begin(), arr.begin() + size);
        PrintArrayIntoFile(outFile, curArray);
    }
    outFile.close();
}

void createTestFile(
        std::vector<int> (ArrayGenerator::*generatorFunction)(int),
        ArrayGenerator& generator,
        int maxSize,
        const char* fileName) {

    std::string fullFileName = std::string("../A2_") + fileName + ".txt";
    std::ofstream outFile(fullFileName);

    for (int size = 500; size < maxSize; size += 100) {
        std::vector<int> curArray = (generator.*generatorFunction)(size);
        PrintArrayIntoFile(outFile, curArray);
    }

    outFile.close();
}

void createTestFileForAlmostSortedArray(ArrayGenerator& generator, int maxSize, const char* fileName) {

    std::string fullFileName = std::string("../A2_") + fileName + ".txt";
    std::ofstream outFile(fullFileName);

    for (int size = 500; size < maxSize; size += 100) {
        std::vector<int> curArray = generator.generateAlmostSortedArray(size, size / 50);
        PrintArrayIntoFile(outFile, curArray);
    }

    outFile.close();
}

int main() {
    ArrayGenerator generator;
    const int maxSize = 10000;
    std::vector<int> randomArray = generator.generateRandomArray(maxSize);
    std::vector<int> sortedReversedArray = generator.generateSortedReverseArray(maxSize);
    std::vector<int> almostSortedArray = generator.generateAlmostSortedArray(maxSize, 100);

//    PrintArray(randomArray);
//    PrintArray(sortedReversedArray);
//    PrintArray(almostSortedArray);

    // массивы создаём из заранее заготовленного большого массива
    createTestFileFromBigArray(randomArray, maxSize, "RandomArraysFromBigArray");
    createTestFileFromBigArray(sortedReversedArray, maxSize, "SortedReversedArraysFromBigArray");
    createTestFileFromBigArray(almostSortedArray, maxSize, "AlmostSortedArraysFromBigArray");
    
    // массивы создаём заново каждый раз
    createTestFile(&ArrayGenerator::generateRandomArray, generator, maxSize, "RandomArrays");
    createTestFile(&ArrayGenerator::generateSortedReverseArray, generator, maxSize, "SortedReversedArrays");
    createTestFileForAlmostSortedArray(generator, maxSize, "AlmostSortedArrays");

    return 0;
}
