int main() {
    srand((unsigned int)time(0));
    ofstream outFile("sorting_algorithms_comparison.csv");
    outFile << "Size,Algorithm,Average Time (microseconds),Worst Time (microseconds),Memory Usage (bytes)\n";

    testInsertionSort(outFile);
    testQuickSort(outFile);
    testMergeSort(outFile);
    testHeapSort(outFile);

    outFile.close();
    cout << "所有排序結果已寫入 sorting_algorithms_comparison.csv！" << endl;

    ofstream fastestFile("fastest_algorithms.csv");
    fastestFile << "Size,Fastest Algorithm,Average Time (microseconds)\n";
    for (const auto& [size, algos] : average_times) {
        string fastest_algo;
        double min_time = 1e18;
        for (const auto& [name, avg] : algos) {
            if (avg < min_time) {
                min_time = avg;
                fastest_algo = name;
            }
        }
        fastestFile << size << "," << fastest_algo << "," << min_time << "\n";
    }
    fastestFile.close();
    cout << "每個 n 最快的排序法結果已寫入 fastest_algorithms.csv！" << endl;
    return 0;
}
