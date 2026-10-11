import csv
import matplotlib.pyplot as plt

threads = []
execution_times = []
speedups = []
data_sizes = []
data_times = []

with open("results/thread_results.csv") as f:
    reader = csv.DictReader(f)
    for row in reader:
        threads.append(int(row["Threads"]))
        execution_times.append(float(row["Execution_Time"]))

with open("results/speedup_efficiency.csv") as f:
    reader = csv.DictReader(f)
    for row in reader:
        speedups.append(float(row["Speedup"]))

with open("results/data_size_results.csv") as f:
    reader = csv.DictReader(f)
    for row in reader:
        data_sizes.append(int(row["Data_Size"]))
        data_times.append(float(row["Execution_Time"]))

plt.figure()
plt.plot(threads, execution_times, marker="o")
plt.xlabel("Number of Threads")
plt.ylabel("Execution Time (seconds)")
plt.title("Execution Time vs Number of Threads")
plt.grid(True)
plt.savefig("graphs/execution_time_vs_threads.png", dpi=300, bbox_inches="tight")
plt.close()

plt.figure()
plt.plot(threads, speedups, marker="o")
plt.xlabel("Number of Threads")
plt.ylabel("Speedup")
plt.title("Speedup vs Number of Threads")
plt.grid(True)
plt.savefig("graphs/speedup_vs_threads.png", dpi=300, bbox_inches="tight")
plt.close()

plt.figure()
plt.plot(data_sizes, data_times, marker="o")
plt.xlabel("Data Size")
plt.ylabel("Execution Time (seconds)")
plt.title("Execution Time vs Data Size")
plt.grid(True)
plt.savefig("graphs/execution_time_vs_data_size.png", dpi=300, bbox_inches="tight")
plt.close()

print("All graphs generated successfully.")
