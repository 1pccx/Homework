vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) arr[i] = rand();
    return arr;
}

vector<int> generateReversedArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) arr[i] = size - i;
    return arr;
}
