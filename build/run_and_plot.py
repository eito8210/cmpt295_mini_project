#!/usr/bin/env python3
import subprocess
import re
import matplotlib.pyplot as plt
import numpy as np

IMPLEMENTATIONS = ["Basic", "Early Stop", "Branchless", "Cocktail", "qsort (ref)"]
PATTERNS = ["Random", "Sorted", "Nearly Sorted", "Reverse"]

def run_exec(cmd):
    print(f"Running: {' '.join(cmd)}")
    out = subprocess.check_output(cmd, text=True)
    return out

def parse_benchmark_output(text):
    pattern = re.compile(
        r'^(Basic|Early Stop|Branchless|Cocktail|qsort \(ref\))\s+'
        r'([A-Za-z]+(?:\s[A-Za-z]+)?)\s+:\s+([0-9.]+)\s+ms$'
    )

    result = {impl: {p: None for p in PATTERNS} for impl in IMPLEMENTATIONS}

    for line in text.splitlines():
        line = line.strip()
        m = pattern.match(line)
        if m:
            impl = m.group(1)
            data_type = m.group(2)
            time_ms = float(m.group(3))
            if impl in result and data_type in result[impl]:
                result[impl][data_type] = time_ms

    return result

def ensure_all_filled(data, label):
    for impl in IMPLEMENTATIONS:
        for p in PATTERNS:
            if data[impl][p] is None:
                print(f"[WARN] {label}: missing value for {impl} / {p}")
    return data

def collect_all_results(n=5000):
    results = {}

    # - O0
    out_O0 = run_exec(["./bubble_O0", str(n)])
    res_O0 = parse_benchmark_output(out_O0)
    ensure_all_filled(res_O0, "O0")
    results["O0"] = res_O0

    # -O2
    out_O2 = run_exec(["./bubble_O2", str(n)])
    res_O2 = parse_benchmark_output(out_O2)
    ensure_all_filled(res_O2, "O2")
    results["O2"] = res_O2

    # -O3
    out_O3 = run_exec(["./bubble_O3", str(n)])
    res_O3 = parse_benchmark_output(out_O3)
    ensure_all_filled(res_O3, "O3")
    results["O3"] = res_O3

    return results

def plot_random_by_opt(results):
    random_O0 = [results["O0"][impl]["Random"] for impl in IMPLEMENTATIONS]
    random_O2 = [results["O2"][impl]["Random"] for impl in IMPLEMENTATIONS]
    random_O3 = [results["O3"][impl]["Random"] for impl in IMPLEMENTATIONS]

    x = np.arange(len(IMPLEMENTATIONS))
    width = 0.25

    plt.figure(figsize=(10, 5))
    plt.bar(x - width, random_O0, width, label="-O0")
    plt.bar(x,         random_O2, width, label="-O2")
    plt.bar(x + width, random_O3, width, label="-O3")

    plt.xticks(x, IMPLEMENTATIONS, rotation=15)
    plt.ylabel("Time (ms)")
    plt.title("Random input (n=5000): optimization level vs implementation")
    plt.legend()
    plt.grid(axis="y", alpha=0.3)
    plt.tight_layout()
    plt.savefig("bubble_random_opt.png")
    print("Saved: bubble_random_opt.png")

def plot_O2_all_patterns(results):
    data_O2 = results["O2"]

    x = np.arange(len(PATTERNS))
    width = 0.15

    plt.figure(figsize=(12, 6))

    for i, impl in enumerate(IMPLEMENTATIONS):
        offset = (i - (len(IMPLEMENTATIONS)-1)/2) * width
        vals = [data_O2[impl][p] for p in PATTERNS]
        plt.bar(x + offset, vals, width, label=impl)

    plt.xticks(x, PATTERNS, rotation=15)
    plt.ylabel("Time (ms)")
    plt.title("All implementations at -O2 (n=5000)")
    plt.legend()
    plt.grid(axis="y", alpha=0.3)
    plt.tight_layout()
    plt.savefig("bubble_O2_all_patterns.png")
    print("Saved: bubble_O2_all_patterns.png")

def plot_O2_all_patterns_no_qsort(results):
    data_O2 = results["O2"]

    bubble_impls = ["Basic", "Early Stop", "Branchless", "Cocktail"]

    x = np.arange(len(PATTERNS))
    width = 0.18

    plt.figure(figsize=(12, 6))

    for i, impl in enumerate(bubble_impls):
        offset = (i - (len(bubble_impls)-1)/2) * width
        vals = [data_O2[impl][p] for p in PATTERNS]
        plt.bar(x + offset, vals, width, label=impl)

    plt.xticks(x, PATTERNS, rotation=15)
    plt.ylabel("Time (ms)")
    plt.title("Bubble implementations at -O2 (n=5000, without qsort)")
    plt.legend()
    plt.grid(axis="y", alpha=0.3)
    plt.tight_layout()
    plt.savefig("bubble_O2_bubbles_only.png")
    print("Saved: bubble_O2_bubbles_only.png")


def plot_sorted_basic_vs_early(results):
    basic_sorted = results["O2"]["Basic"]["Sorted"]
    early_sorted = results["O2"]["Early Stop"]["Sorted"]

    names = ["Basic -O2", "Early Stop -O2"]
    vals  = [basic_sorted, early_sorted]

    plt.figure(figsize=(6, 5))
    bars = plt.bar(names, vals)
    plt.ylabel("Time (ms)")
    plt.title("Sorted input (n=5000): Basic vs Early Stop (-O2)")
    for bar, v in zip(bars, vals):
        plt.text(bar.get_x() + bar.get_width()/2, v, f"{v:.4f}",
                 ha="center", va="bottom")
    plt.grid(axis="y", alpha=0.3)
    plt.tight_layout()
    plt.savefig("bubble_sorted_basic_vs_early.png")
    print("Saved: bubble_sorted_basic_vs_early.png")

def main():
  
    n = 5000
    results = collect_all_results(n=n)

    plot_random_by_opt(results)
    plot_O2_all_patterns(results)
    plot_O2_all_patterns_no_qsort(results)
    plot_sorted_basic_vs_early(results)

    print("All plots generated.")

if __name__ == "__main__":
    main()
