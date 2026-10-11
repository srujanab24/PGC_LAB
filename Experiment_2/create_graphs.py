import matplotlib.pyplot as plt

threads = [1, 2, 4, 6, 16]

pthread_time = [3.251077, 1.784038, 1.166245, 1.180707, 1.237177]
openmp_time = [3.344914, 1.745858, 1.169528, 1.197885, 1.189052]

# Pthreads graph
plt.figure()
plt.plot(threads, pthread_time, marker='o')
plt.xlabel("Number of Threads")
plt.ylabel("Execution Time (seconds)")
plt.title("Pthreads Performance")
plt.grid(True)
plt.savefig("screenshots/graphs/pthreads_execution_time.png", dpi=300, bbox_inches="tight")
plt.close()

# OpenMP graph
plt.figure()
plt.plot(threads, openmp_time, marker='o')
plt.xlabel("Number of Threads")
plt.ylabel("Execution Time (seconds)")
plt.title("OpenMP Performance")
plt.grid(True)
plt.savefig("screenshots/graphs/openmp_execution_time.png", dpi=300, bbox_inches="tight")
plt.close()

# Comparison graph
plt.figure()
plt.plot(threads, pthread_time, marker='o', label="Pthreads")
plt.plot(threads, openmp_time, marker='o', label="OpenMP")
plt.xlabel("Number of Threads")
plt.ylabel("Execution Time (seconds)")
plt.title("Pthreads vs OpenMP Performance")
plt.legend()
plt.grid(True)
plt.savefig("screenshots/graphs/pthreads_vs_openmp.png", dpi=300, bbox_inches="tight")
plt.close()

print("Graphs created successfully.")

