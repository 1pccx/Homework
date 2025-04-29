void testQuickSort(ofstream& outFile) {
    cout << "開始測試 Quick Sort..." << endl;
    vector<int> sizes = { 500, 1000, 2000, 3000, 4000, 5000 };
    for (int size : sizes) {
        long long total_time = 0;
        size_t memory_usage = size * sizeof(int);
        for (int i = 0; i < 5; i++) {
            vector<int> arr = generateRandomArray(size); // 平均用隨機
            auto start = high_resolution_clock::now();
            quickSortIterative(arr, 0, arr.size() - 1);
            auto end = high_resolution_clock::now();
            total_time += duration_cast<microseconds>(end - start).count();
        }
        double average_time = total_time / 5.0;

        // 最壞情況：反向排序資料
        vector<int> worst_arr = generateReversedArray(size);
        auto start_worst = high_resolution_clock::now();
        quickSortIterative(worst_arr, 0, worst_arr.size() - 1);
        auto end_worst = high_resolution_clock::now();
        long long worst_time = duration_cast<microseconds>(end_worst - start_worst).count();

        outFile << size << ",Quick Sort," << average_time << "," << worst_time << "," << memory_usage << "\n";
        average_times[size]["Quick Sort"] = average_time;
    }
}
