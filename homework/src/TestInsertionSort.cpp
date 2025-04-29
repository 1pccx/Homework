map<int, map<string, double>> average_times;  //4個TestSort共用

void testInsertionSort(ofstream& outFile) {
    cout << "開始測試 Insertion Sort..." << endl;
    vector<int> sizes = { 500, 1000, 2000, 3000, 4000, 5000 };
    for (int size : sizes) {
        long long total_time = 0;
        size_t memory_usage = size * sizeof(int);
        for (int i = 0; i < 5; i++) {
            vector<int> arr = generateRandomArray(size); // 平均用隨機
            auto start = high_resolution_clock::now();
            insertionSort(arr);
            auto end = high_resolution_clock::now();
            total_time += duration_cast<microseconds>(end - start).count();
        }
        double average_time = total_time / 5.0;

        // 最壞情況：反向排序資料
        vector<int> worst_arr = generateReversedArray(size);
        auto start_worst = high_resolution_clock::now();
        insertionSort(worst_arr);
        auto end_worst = high_resolution_clock::now();
        long long worst_time = duration_cast<microseconds>(end_worst - start_worst).count();

        outFile << size << ",Insertion Sort," << average_time << "," << worst_time << "," << memory_usage << "\n";
        average_times[size]["Insertion Sort"] = average_time;
    }
}
