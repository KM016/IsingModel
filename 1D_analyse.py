import numpy as np
import matplotlib.pyplot as plt
import os

def analyse_beta(beta):

    # Create visualisations directory if it doesn't exist
    os.makedirs("visualisations_1D", exist_ok=True)
    
    folder = f"data_1D/beta_{beta:.1f}/results.txt"
    data = np.loadtxt(folder, skiprows=1)
    energies = data[:, 0]
    magnetisations = data[:, 1]
    
    # Compute averages
    avg_E = np.mean(energies)
    avg_M = np.mean(np.abs(magnetisations))  

    # Plot distributions
    plt.figure(figsize=(12, 5))
    
    plt.subplot(121)
    plt.hist(energies, bins=50, density=True, color='skyblue', edgecolor='black')
    plt.title(f"Energy Distribution (β={beta})")
    plt.xlabel("Energy")
    
    plt.subplot(122)
    plt.hist(magnetisations, bins=50, density=True, color='salmon', edgecolor='black')
    plt.title(f"Magnetisation Distribution (β={beta})")
    plt.xlabel("Magnetisation")
    
    plt.tight_layout()
    plt.savefig(f"visualisations_1D/1D_results_beta_{beta:.1f}.png") 
    plt.close()
    
    return avg_E, avg_M

# Main analysis
betas = [0.0, 0.1, 0.5, 1.0, 2.0, 5.0, 10.0]
results = []

for beta in betas:
    avg_E, avg_M = analyse_beta(beta)
    results.append([beta, avg_E, avg_M]) 

results = np.array(results, dtype=float)

# Plot trends
plt.figure(figsize=(10, 5))

plt.subplot(121)
plt.plot(results[:, 0], results[:, 1], 'o-', color='blue')
plt.xlabel("β")
plt.ylabel("Average Energy")
plt.title("1D Average Energy vs β")

plt.subplot(122)
plt.plot(results[:, 0], results[:, 2], 'o-', color='red')
plt.xlabel("β")
plt.ylabel("Average |Magnetisation|")
plt.title("1D Average |Magnetisation| vs β")

plt.tight_layout()
plt.savefig("visualisations_1D/1D_trends.png")
plt.close()

print("1D analysis complete. Visualisations saved in the 'visualisations_1D' directory.")
