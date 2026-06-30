import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results.csv")

plt.figure(figsize=(8,5))
plt.bar(df["Algorithm"], df["ExecutionTime"])
plt.ylabel("Execution Time (ms)")
plt.title("Execution Time Comparison")
plt.tight_layout()
plt.savefig("execution_time.png")

plt.figure(figsize=(8,5))
plt.bar(df["Algorithm"], df["HitRate"])
plt.ylabel("Hit Rate (%)")
plt.title("Hit Rate Comparison")
plt.tight_layout()
plt.savefig("hit_rate.png")

plt.figure(figsize=(8,5))
plt.bar(df["Algorithm"], df["PageFaults"])
plt.ylabel("Page Faults")
plt.title("Page Fault Comparison")
plt.tight_layout()
plt.savefig("page_faults.png")

print("Graphs generated.")