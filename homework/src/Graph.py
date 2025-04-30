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
