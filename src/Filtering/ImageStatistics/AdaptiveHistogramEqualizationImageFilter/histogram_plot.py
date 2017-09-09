import os
import sys

import matplotlib.pyplot as plt
import matplotlib.image as mpimg


str(sys.argv)

img=mpimg.imread(sys.argv[1])

fig, ax = plt.subplots()

n, bins, patches = ax.hist(img.ravel(), bins=256, fc='k', ec='k')

ax.set_xlabel('Smarts')
ax.set_ylabel('Frequency')
ax.set_title(sys.argv[2])

base = os.path.basename(sys.argv[1])

output_figure_name = os.path.splitext(base)[0] + '_histogram.png'

fig.tight_layout()
plt.show()

fig.savefig(output_figure_name)