# 41243206 41243209

作業一

## 解題說明
本題要求實現並分析四種排序演算法，分別是：
1. Insertion Sort
2. Quick Sort
3. Merge Sort
4. Heap Sort

測試這些演算法的效率，並計算它們的 Worst time、Average time 與 Memory Usage

要求的重點包括：

- 計算每種排序方法在不同資料規模下的執行時間與記憶體使用。

- 進行 worst-case 和 average-case 測試，並將測試結果與理論時間複雜度進行比對。

- 實作一個 Composite Sort 函式，根據輸入資料的特徵選擇最適合的排序方法，以達到最佳性能。

### 解題策略

**1. 選擇排序演算法：**

(a) 在測試 Average-case 時，都是用隨機數據

(b) 在 Worst-case 時

- Insertion Sort：對小型數據集或接近有序的數據特別有效。它的時間複雜度為 O(n²)，因此使用反向排序(由大到小)數據來測試。

- Quick Sort：由於我們使用最後一個元素作為 pivot，對已排序或反向排序的數據表現最差， 時間複雜度為 O(n²)，因此選擇反向排序(由大到小)數據來測試。

- Merge Sort：無論數據的排列順序如何，Merge Sort 都會維持 O(n log n) 的時間複雜度，因此對其進行隨機數據的測試。

- Heap Sort：時間複雜度在最壞情況下仍然是 O(n log n)，並且數據的排列順序不會對其性能有顯著影響，因此對其進行隨機數據的測試。

**2. 效能分析：**

針對每個演算法進行時間複雜度和空間複雜度的分析。

**3. 測試與驗證：**

比較各演算法在不同數據量下的效率，分析每個排序算法的 Worst-case 、 Average-case 及 Memory Usage，再將每個數據集大小對應最快的排序算法寫入另一個CSV檔案。

## 程式實作

以下為四種排序法，並使用不同數據集進行測試：

```cpp
#include <iostream>
#include <vector>
#include <cstdlib> // 包含 srand() 和 rand()
#include <ctime>   // 包含 time()
#include <chrono>  // 包含 chrono 用於計時
#include <fstream> // 用於檔案操作
#include <algorithm>
#include <map>

using namespace std;
using namespace chrono;

// 插入排序
void insertionSort(vector<int>& arr) {
    for (int i = 1; i < (int)arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

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

// 合併排序
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSortIterative(vector<int>& arr) {
    int n = arr.size();
    for (int size = 1; size < n; size = 2 * size) {
        for (int left = 0; left < n - 1; left += 2 * size) {
            int mid = min(n - 1, left + size - 1);
            int right = min((left + 2 * size - 1), (n - 1));
            if (mid < right) {
                merge(arr, left, mid, right);
            }
        }
    }
}

// 堆積排序
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

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

map<int, map<string, double>> average_times;

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

void testHeapSort(ofstream& outFile) {
    cout << "開始測試 Heap Sort..." << endl;
    vector<int> sizes = { 500, 1000, 2000, 3000, 4000, 5000 };
    for (int size : sizes) {
        long long total_time = 0;
        long long worst_time = 0;
        size_t memory_usage = size * sizeof(int);
        for (int i = 0; i < 5; i++) {
            vector<int> arr = generateRandomArray(size);
            auto start = high_resolution_clock::now();
            heapSort(arr);
            auto end = high_resolution_clock::now();
            long long duration = duration_cast<microseconds>(end - start).count();
            total_time += duration;
            if (duration > worst_time) worst_time = duration;
        }
        double average_time = total_time / 5.0;
        outFile << size << ",Heap Sort," << average_time << "," << worst_time << "," << memory_usage << "\n";
        average_times[size]["Heap Sort"] = average_time;
    }
}

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
    fastestFile << "Size,Fastest Algorithm,Average Time (microseconds)\n";fasteastfile <<“大小，最快的算法，平均時間（微秒）\ n”;
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
```


## 效能分析

| 演算法 | worst-case | average-case | 空間複雜度 |
|-----------------|----------------|-----------------|--------------|
| Insertion Sort | Ο($n^2$) | Ο($n^2$) | Ο(1) |
| Quick Sort | Ο($n^2$) | Ο(n log n) | Ο(log n)~Ο(n) |
| Merge Sort | O(n log n) | Ο(n log n) | Ο(n) |
| Heap Sort | O(n log n) | Ο(n log n) | Ο(1) |
| Composite Sort | 根據資料特徵選擇 | 根據資料特徵選擇 | 依排序法而定 |

1. Insertion Sort 在小數據集上表現良好，但隨著數據量增大，時間複雜度增長迅速，因此當數據量較大時效率低下。

2. Quick Sort 通常是最快的排序方法，特別是使用 median-of-three 方法選擇樞軸後，可以避免極端情況下的性能下降。

3. Merge Sort 在所有情況下都能保持 O(n log n) 的時間複雜度，但記憶體使用量較大。

4. Heap Sort 是一個穩定的排序算法，時間複雜度也是 O(n log n)，但在某些情況下可能不如 Quick Sort 或 Merge Sort 快。

5. Composite Sort 可以動態選擇最適合的排序方法，對於不同類型的資料具有較高的靈活性和效率。

## 測試與驗證

P.S. 1. 表格 <mark style="color:red;">註記</mark> 為最快執行時間
     2. 在 Visual Studio 2019 編譯
     
### Worst-case

| n | Insertion Sort (µs) | Quick Sort (µs) | Merge Sort (µs) | Heap Sort (µs) |
|---------------|---------------|----------------|--------------|--------------|
| 500 | 5451 | 14341 | 8845 | <mark style="color:red;"> 3015 </mark>  |
| 1000 | 52586 | 43110 | 22193 | <mark style="color:red;"> 6599 </mark> |
| 2000 | 191947 | 165673 | 42206 | <mark style="color:red;"> 14690 </mark> |
| 3000 | 253646 | 460435 | 70955 | <mark style="color:red;"> 24031 </mark> |
| 4000 | 866550 | 1024925 | 77897 | <mark style="color:red;"> 34525 </mark> |
| 5000 | 718773 | 3363906 | 98356 | <mark style="color:red;"> 43328 </mark> |

![worst-case](https://github.com/1pccx/HW/blob/main/worst_case.png)

### Average-case

| n | Insertion Sort (µs) | Quick Sort (µs) | Merge Sort (µs) | Heap Sort (µs) |
|---------------|---------------|----------------|-------------|---------------|
| 500 | 3504.4 | <mark style="color:red;"> 1753.8 </mark> | 8681.8 | 2795.4 || 500 | 3504.4 |  1753.8  | 8681.8 | 2795.4 |
| 1000 | 16029.2 | <mark style="color:red;"> 3299 </mark> | 18609.4 | 6278.2 | 
| 2000 | 89841.6 | <mark style="color:red;"> 5004.2 </mark> | 36445 | 13804.6 |
| 3000 | 138060 | <mark style="color:red;"> 9380.8 </mark> | 59122.2 | 22400 || 3000 | 138060 |  9380.8  | 59122.2 | 22400 |
| 4000 | 268474 | <mark style="color:red;"> 20875.2 </mark> | 71296.8 | 31886 |
| 5000 | 379469 | 45393.2 | 93194.8 | <mark style="color:red;"> 41111.4 </mark> |

![average-case](https://github.com/1pccx/HW/blob/main/average_case.png)

### Memory Usage

| n | Insertion Sort (Bytes) | Quick Sort (Bytes) | Merge Sort (Bytes) | Heap Sort (Bytes) |
|---------------|---------------|---------------|--------------|---------------|
| 500 | 2000 | 2000 | 2000 | 2000 |
| 1000 | 4000 | 4000 | 4000 | 4000 |
| 2000 | 8000 | 8000 | 8000 | 8000 |
| 3000 | 12000 | 12000 | 12000 | 12000 |
| 4000 | 16000 | 16000 | 16000 | 16000 |
| 5000 | 20000 | 20000 | 20000 | 20000 |

### 圖表生成程式

```python
import pandas as pd
import matplotlib.pyplot as plt

# 假設你已經讀取了 CSV 檔案並且它的資料已經存在於 df 中
df = pd.read_csv('2sorting_algorithms_comparison.csv')

# 確認我們有正確的欄位
print(df.columns)

# 第一張圖：展示每個算法的平均時間
plt.figure(figsize=(12, 8))  # 增加圖表的大小
for algo in df['Algorithm'].unique():
    algo_data = df[df['Algorithm'] == algo]
    plt.plot(algo_data['Size'], algo_data['Average Time (microseconds)'], label=algo, marker='o', markersize=6)

# 設置標題和標籤
plt.title('Average Sorting Time (microseconds) by Algorithm', fontsize=16)
plt.xlabel('Array Size', fontsize=14)
plt.ylabel('Average Time (microseconds)', fontsize=14)
plt.legend(title='Algorithm', loc='upper left')
plt.grid(True)

# 設置Y軸範圍，縮放讓圖表更明顯
#plt.yscale('log')  # 使用對數縮放，這樣時間差異更為突出
plt.tight_layout()

# 顯示圖表
plt.show()

# 第二張圖：展示每個算法的最壞情況時間
plt.figure(figsize=(12, 8))  # 增加圖表的大小
for algo in df['Algorithm'].unique():
    algo_data = df[df['Algorithm'] == algo]
    plt.plot(algo_data['Size'], algo_data['Worst Time (microseconds)'], label=algo, marker='x', markersize=6)

# 設置標題和標籤
plt.title('Worst Sorting Time (microseconds) by Algorithm', fontsize=16)
plt.xlabel('Array Size', fontsize=14)
plt.ylabel('Worst Time (microseconds)', fontsize=14)
plt.legend(title='Algorithm', loc='upper left')
plt.grid(True)

# 設置Y軸範圍，縮放讓圖表更明顯
#plt.yscale('log')  # 使用對數縮放
plt.tight_layout()

# 顯示圖表
plt.show()
```

### 結論

- Insertion Sort 在 Worst-case 時，因時間複雜度為 O(n²)，又隨著數據量增加，執行時間較長，效率較低。

- Quick Sort 是對於大多數情況（尤其是 Average-case ）下最優、最快速的演算法，尤其對小至中型數據集最為有效。 然而，在 Worst-case 以及 在 Average-case 可能因選擇固定 pivot 而退化，性能會大幅下降。
  
- Merge Sort 是一個穩定的排序算法，適合於數據量較大且對 Worst-case 有要求的情況，但相較於 Quick Sort 和 Heap Sort，它的執行時間略慢。

- Heap Sort 在 Worst-case 和較大數據集下表現穩定，並且在處理較大數據集時，成為最快的排序算法。


## 申論及開發報告

本專案的目的是使用迭代法實作並比較四種常見的排序演算法：Insertion Sort、Quick Sort、Merge Sort 和 Heap Sort。針對每個算法，我們測試其在不同數據量（500、1000、2000、3000、4000、5000）下的執行時間與記憶體使用量。並分別測量這些演算法的 Average-case 和 Worst-case 下的性能，找出每種演算法的優劣，並選擇最適合的排序方法。最終，我們還會生成兩個CSV文件，一個用來顯示每個排序算法在不同數據集下的執行時間與記憶體使用量，另一個顯示每個數據集下最有效的排序算法。

### 選擇排序演算法的理由

**1. Insertion Sort：**

- 資料結構：簡單的數組（Array）。

- 適用場景：適用於小型數據集或接近有序的數據。因為其時間複雜度為 O(n²)，當數據量較大或數據不接近有序時，效率較低。

- 缺點：在處理大數據集時表現較差，特別是在最壞情況下（如反向排序數據）。

**2. Quick Sort：**

- 資料結構：數組（Array）和棧（Stack）來實現迭代。

- 適用場景：對於大數據集，特別是當數據分布較均勻時，通常是最優選擇。它的平均情況時間複雜度為 O(n log n)。

- 缺點：使用「固定 pivot」選擇策略（選擇最後一個元素作為樞軸）時，在某些數據分布（如已排序或反向排序）下，會退化為 O(n²)，因此可能會在最壞情況下表現不佳。

**3. Merge Sort：**

- 資料結構：數組（Array）和臨時數組來存儲分割後的子數組。

- 適用場景：適合需要穩定排序的情況，並且在最壞情況下也能保證 O(n log n) 的時間複雜度。

- 缺點：需要額外的 O(n) 空間來存儲臨時數據，因此在處理大數據集時，會消耗更多的記憶體。

**4. Heap Sort：**

- 資料結構：二叉堆（Binary Heap）作為內部數據結構。

- 適用場景：對於大數據集，Heap Sort 是一個穩定的選擇，因為它的時間複雜度穩定為 O(n log n)，並且是原地排序（in-place），不需要額外的記憶體空間。

- 缺點：相比 Quick Sort，Heap Sort 在常數因子上稍慢，但在最壞情況下表現穩定。

**5. Quick Sort vs. Heap Sort：**

- 在一般情況下對於較大數據集， Quick Sort 可能會因為選擇的 pivot 差 以及 迭代法(導致較多操作)，而比 Heap Sort 來得慢。


在開發過程中，我們面臨的主要挑戰是如何確保每個算法在不同情況下的效能測試準確，並且對每個算法進行適當的優化。特別是 Quick Sort，我們使用了迴圈代替遞迴來避免遞迴深度過深導致的堆疊溢出問題。這樣做的優勢在於，迴圈實現可以更有效地控制堆疊使用，但也可能增加一些額外的操作。

另一個挑戰是如何準確測量每個算法的記憶體使用量。我們使用了每個數據元素的大小來估算記憶體使用量，但這並未完全反映實際的內存消耗，只能提供一個大致的估算，對於像 Merge Sort 這樣需要額外空間的算法，未來仍需進一步改進測量方法以更準確地反映實際的內存消耗。

### 結論

**Heap Sort** 是最適合處理各種數據情況的排序算法，尤其在記憶體受限且要求穩定時間複雜度的情況下，表現尤為出色。
