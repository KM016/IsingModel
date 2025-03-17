import numpy as np
import matplotlib.pyplot as plt
import os

def analyse_beta_2D(beta):
    # Construct the folder path (e.g., "data_2D/beta_0.44/results.txt")
    folder = f"data_2D/beta_{beta:.1f}/results.txt"
    if not os.path.exists(folder):
        print(f"File not found: {folder}")
        return None, None
    
    # Load the data, skipping the header line
    data = np.loadtxt(folder, skiprows=1)
    energies = data[:, 0]
    magnetisations = data[:, 1]
    
    # Compute averages
    avg_energy = np.mean(energies)
    avg_magnetisation = np.mean(np.abs(magnetisations))
    
    # Plot energy and magnetisation distributions
    plt.figure(figsize=(12, 5))
    
    plt.subplot(121)
    plt.hist(energies, bins=50, density=True, color='skyblue', edgecolor='black')
    plt.title(f"2D Energy Distribution (β={beta})")
    plt.xlabel("Energy")
    plt.ylabel("Density")
    
    plt.subplot(122)
    plt.hist(magnetisations, bins=50, density=True, color='salmon', edgecolor='black')
    plt.title(f"2D Magnetisation Distribution (β={beta})")
    plt.xlabel("Magnetisation")
    plt.ylabel("Density")
    
    plt.tight_layout()

    # Save the plot in a folder for visualisations
    os.makedirs("visualisations_2D", exist_ok=True)
    plt.savefig(f"visualisations_2D/2D_results_beta_{beta:.1f}.png")
    plt.close()
    
    return avg_energy, avg_magnetisation

# Main analysis
betas = [0.0, 0.1, 0.5, 1.0, 2.0, 5.0, 10.0]
results = []

for beta in betas:
    avg_E, avg_M = analyse_beta_2D(beta)
    if avg_E is not None:
        results.append([beta, avg_E, avg_M])
results = np.array(results, dtype=float)


# Plot trends of average energy and magnetisation vs beta
plt.figure(figsize=(10, 5))

plt.subplot(121)
plt.plot(results[:, 0], results[:, 1], 'o-', color='blue')
plt.xlabel("β")
plt.ylabel("Average Energy")
plt.title("2D Average Energy vs β")

plt.subplot(122)
plt.plot(results[:, 0], results[:, 2], 'o-', color='red')
plt.xlabel("β")
plt.ylabel("Average |Magnetisation|")
plt.title("2D Average |Magnetisation| vs β")

plt.tight_layout()
plt.savefig("visualisations_2D/2D_trends.png")
plt.close()

print("2D analysis complete. Visualisations saved in the 'visualisations_2D' directory.")
