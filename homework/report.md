# 41243206 41243209

作業一

## 解題說明
本題要求實現 Insertion Sort, Quick Sort, Merge Sort, Heap Sort,Composite Sort

要求的重點包括：

• 計算每種排序方法在不同資料規模下的執行時間與記憶體使用。

• 進行 worst-case 和 average-case 測試，並將測試結果與理論時間複雜度進行比對。

• 實作一個 Composite Sort 函式，根據輸入資料的特徵選擇最適合的排序方法，以達到最佳性能。

### 解題策略


## 程式實作

以下為主要程式碼：




## 效能分析

| 演算法 | worst-case | average-case | 空間複雜度 |
|-----------------|----------------|-----------------|--------------|
| Insertion Sort | Ο($n^2$) | Ο($n^2$) | Ο(1) |
| Quick Sort | Ο($n^2$) | Ο(n log n) | Ο(log n)~Ο(n) |
| Merge Sort | O(n log n) | Ο(n log n) | Ο(n) |
| Heap Sort | O(n log n) | Ο(n log n) | Ο(n) + Ο(1) |
| Composite Sort | 根據資料特徵選擇 | 根據資料特徵選擇 | 依排序法而定 |

1. Insertion Sort 在小數據集上表現良好，但隨著數據量增大，時間複雜度增長迅速，因此當數據量較大時效率低下。

2. Quick Sort 通常是最快的排序方法，特別是使用 median-of-three 方法選擇樞軸後，可以避免極端情況下的性能下降。

3. Merge Sort 在所有情況下都能保持 O(n log n) 的時間複雜度，但記憶體使用量較大。

4. Heap Sort 是一個穩定的排序算法，時間複雜度也是 O(n log n)，但在某些情況下可能不如 Quick Sort 或 Merge Sort 快。

5. Composite Sort 可以動態選擇最適合的排序方法，對於不同類型的資料具有較高的靈活性和效率。

## 測試與驗證
Worst-case

![worst-case]()

## 申論及開發報告


