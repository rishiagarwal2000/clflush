import numpy as np
import matplotlib.pyplot as plt
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('-d', '--data', nargs='+', type=str, default=['hits'])
args = parser.parse_args()


plt.clf()
plt.figure(figsize=(7,7), dpi=300)
fname = ''
for d in args.data:
    fname += d
    data = np.loadtxt(f'out/{d}.txt')
    plt.scatter(data[:,0], data[:,1], marker='o', label=f'{d}')
    plt.ylabel('Clock cycles')
plt.ylim((0, 1000))
plt.legend()
plt.savefig(f'plots/{fname}.png')