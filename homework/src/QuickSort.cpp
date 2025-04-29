// 快速排序 (使用迴圈代替遞迴)
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSortIterative(vector<int>& arr, int low, int high) {
    vector<int> stack;
    stack.push_back(low);
    stack.push_back(high);

    while (!stack.empty()) {
        high = stack.back(); stack.pop_back();
        low = stack.back(); stack.pop_back();

        if (low < high) {
            int pi = partition(arr, low, high);
            stack.push_back(low);
            stack.push_back(pi - 1);
            stack.push_back(pi + 1);
            stack.push_back(high);
        }
    }
}
