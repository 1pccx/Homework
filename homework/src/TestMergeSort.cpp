void testMergeSort(ofstream& outFile) {
    cout << "開始測試 Merge Sort..." << endl;
    vector<int> sizes = { 500, 1000, 2000, 3000, 4000, 5000 };
    for (int size : sizes) {
        long long total_time = 0;
        long long worst_time = 0;
        size_t memory_usage = size * sizeof(int);
        for (int i = 0; i < 5; i++) {
            vector<int> arr = generateRandomArray(size);
            auto start = high_resolution_clock::now();
            mergeSortIterative(arr);
            auto end = high_resolution_clock::now();
            long long duration = duration_cast<microseconds>(end - start).count();
            total_time += duration;
            if (duration > worst_time) worst_time = duration;
        }
        double average_time = total_time / 5.0;
        outFile << size << ",Merge Sort," << average_time << "," << worst_time << "," << memory_usage << "\n";
        average_times[size]["Merge Sort"] = average_time;
    }
}
