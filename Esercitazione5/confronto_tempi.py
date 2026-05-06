import pandas as pd
import matplotlib.pyplot as plt

# Carica il file .txt (assicurati che sia nella cartella corretta)
# Se il file si trova in una cartella specifica, inserisci il percorso completo
df = pd.read_csv('tempi_medi.txt', header=None)

df.columns = [
    'dimensione', 
    'std_sort', 
    'bubble_sort', 
    'insertion_sort', 
    'selection_sort', 
    'merge_sort', 
    'quick_sort'
]

# Applichiamo una mediana mobile (finestra di 3 o 5 punti) per "smussare" i picchi
window_size = 7
for col in ['std_sort', 'bubble_sort', 'insertion_sort', 'selection_sort', 'merge_sort', 'quick_sort']:
    df[col] = df[col].rolling(window=window_size, min_periods=1).median()

# Creazione del grafico
plt.figure(figsize=(12, 6))

plt.plot(df['dimensione'], df['std_sort'], marker='o', linestyle='-', linewidth=2, label='std::sort')
plt.plot(df['dimensione'], df['bubble_sort'], marker='s', linestyle='-', linewidth=2, label='Bubble Sort')
plt.plot(df['dimensione'], df['insertion_sort'], marker='^', linestyle='-', linewidth=2, label='Insertion Sort')
plt.plot(df['dimensione'], df['selection_sort'], marker='d', linestyle='-', linewidth=2, label='Selection Sort')
plt.plot(df['dimensione'], df['merge_sort'], marker='x', linestyle='-', linewidth=2, label='Merge Sort')
plt.plot(df['dimensione'], df['quick_sort'], marker='*', linestyle='-', linewidth=2, label='Quick Sort')

# Personalizzazione
plt.title('Confronto dei tempi di ordinamento ', fontsize=14)
plt.xlabel('Dimensione del vettore', fontsize=12)
plt.ylabel('Tempo medio (secondi)', fontsize=12)

# Scala logaritmica opzionale per gestire i diversi ordini di grandezza
plt.yscale('log')

plt.grid(True, which="both", ls="--", alpha=0.5)
plt.legend(loc='upper left', fontsize=10)
plt.tight_layout()

plt.show()