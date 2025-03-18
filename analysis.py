import numpy as np
import matplotlib.pyplot as plt
import os

def analyse_beta_1D(beta):
    """Analyze 1D simulation results for a given beta value."""
    os.makedirs("visualisations_1D", exist_ok=True)
    
    folder = f"data_1D/beta_{beta:.1f}/results.txt"
    data = np.loadtxt(folder, skiprows=1)
    energies = data[:, 0]
    magnetisations = data[:, 1]
    
    # Compute averages
    avg_E = np.mean(energies)
    avg_M = np.mean(np.abs(magnetisations))
    
    # Plot histograms for 1D
    plt.figure(figsize=(12, 5))
    plt.subplot(121)
    plt.hist(energies, bins=15, color='skyblue', edgecolor='black')
    plt.title(f"1D Energy Histogram (β={beta})")
    plt.ylabel("Frequency")
    plt.xlabel("Energy")
    
    plt.subplot(122)
    plt.hist(magnetisations, bins=15, color='salmon', edgecolor='black')
    plt.title(f"1D Magnetisation Histogram (β={beta})")
    plt.ylabel("Frequency")
    plt.xlabel("Magnetisation")
    
    plt.tight_layout()
    plt.savefig(f"visualisations_1D/1D_results_beta_{beta:.1f}.png")
    plt.close()
    
    return avg_E, avg_M

def analyse_beta_2D(beta):
    """Analyze 2D simulation results for a given beta value."""
    folder = f"data_2D/beta_{beta:.1f}/results.txt"
    if not os.path.exists(folder):
        print(f"File not found: {folder}")
        return None, None
    
    data = np.loadtxt(folder, skiprows=1)
    energies2 = data[:, 0]
    magnetisations2 = data[:, 1]
    
    avg_energy = np.mean(energies2)
    avg_magnetisation = np.mean(np.abs(magnetisations2))
    
    # Plot histograms for 2D
    plt.figure(figsize=(12, 5))
    plt.subplot(121)
    plt.hist(energies2, bins=15, color='skyblue', edgecolor='black')
    plt.title(f"2D Energy Histogram (β={beta})")
    plt.xlabel("Energy")
    plt.ylabel("Frequency")
    
    plt.subplot(122)
    plt.hist(magnetisations2,bins=15, color='salmon', edgecolor='black')
    plt.title(f"2D Magnetisation Histogram (β={beta})")
    plt.xlabel("Magnetisation")
    plt.ylabel("Frequency")
    
    plt.tight_layout()
    os.makedirs("visualisations_2D", exist_ok=True)
    plt.savefig(f"visualisations_2D/2D_results_beta_{beta:.1f}.png")
    plt.close()
    
    return avg_energy, avg_magnetisation

def main():
    # List of beta values to analyse
    betas = [0.0, 0.1, 0.5, 1.0, 2.0, 5.0, 10.0]
    
    # ANALYSIS FOR 1D
    results_1D = []
    for beta in betas:
        avg_E, avg_M = analyse_beta_1D(beta)
        results_1D.append([beta, avg_E, avg_M])
    results_1D = np.array(results_1D, dtype=float)
    
    plt.figure(figsize=(10,5))
    plt.subplot(121)
    plt.plot(results_1D[:, 0], results_1D[:, 1], 'o-', color='blue')
    plt.xlabel("β")
    plt.ylabel("Average Energy")
    plt.title("1D Average Energy vs β")
    
    plt.subplot(122)
    plt.plot(results_1D[:, 0], results_1D[:, 2], 'o-', color='red')
    plt.xlabel("β")
    plt.ylabel("Average |Magnetisation|")
    plt.title("1D Average |Magnetisation| vs β")
    
    plt.tight_layout()
    os.makedirs("visualisations_1D", exist_ok=True)
    plt.savefig("visualisations_1D/1D_trends.png")
    plt.close()
    
    # ANALYSIS FOR 2D
    results_2D = []
    for beta in betas:
        avg_E, avg_M = analyse_beta_2D(beta)
        if avg_E is not None:
            results_2D.append([beta, avg_E, avg_M])
    results_2D = np.array(results_2D, dtype=float)
    
    plt.figure(figsize=(10,5))
    plt.subplot(121)
    plt.plot(results_2D[:, 0], results_2D[:, 1], 'o-', color='blue')
    plt.xlabel("β")
    plt.ylabel("Average Energy")
    plt.title("2D Average Energy vs β")
    
    plt.subplot(122)
    plt.plot(results_2D[:, 0], results_2D[:, 2], 'o-', color='red')
    plt.xlabel("β")
    plt.ylabel("Average |Magnetisation|")
    plt.title("2D Average |Magnetisation| vs β")
    
    plt.tight_layout()
    os.makedirs("visualisations_2D", exist_ok=True)
    plt.savefig("visualisations_2D/2D_trends.png")
    plt.close()
    
    print("Analysis complete. Visualisations saved in 'visualisations_1D' and 'visualisations_2D' directories.")

if __name__ == "__main__":
    main()
