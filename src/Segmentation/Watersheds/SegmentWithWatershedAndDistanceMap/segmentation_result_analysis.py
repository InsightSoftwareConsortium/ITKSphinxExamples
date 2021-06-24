#!/usr/bin/env python

# Copyright NumFOCUS
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0.txt
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Run with:
# ./segmentation_result_analysis.py <>
# e.g.
# ./segmentation_result_analysis.py P
#
# This is a companion code to the SegmentWithWatershedAndDistanceMap example
# to generate the example segmentation results analysis visualizations.
#


import argparse

import itk
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


parser = argparse.ArgumentParser(description="Analyze the segmentation result.")
parser.add_argument("clean_segmentation_filename")
parser.add_argument("training_bubble_volume_stats_filename")
parser.add_argument("bubble_volume_stats_output_filename")
parser.add_argument("bubble_volume_stats_sample_table_output_filename")
parser.add_argument("bubble_volume_density_stats_plot_output_filename")
parser.add_argument("bubble_centers_plot_output_filename")
parser.add_argument("bubble_stats_comparison_plot_output_filename")
args = parser.parse_args()

# Read segmentation image
bubble_label_image = itk.imread(args.clean_segmentation_filename)


# Calculate bubble centers
def meshgrid3d_like(in_img):
    return np.meshgrid(
        range(in_img.shape[1]), range(in_img.shape[0]), range(in_img.shape[2])
    )


zz, xx, yy = meshgrid3d_like(bubble_label_image)
out_results = []
for c_label in np.unique(bubble_label_image):  # one bubble at a time
    if c_label > 0:  # ignore background
        cur_roi = bubble_label_image == c_label
        out_results += [
            {
                "x": xx[cur_roi].mean(),
                "y": yy[cur_roi].mean(),
                "z": zz[cur_roi].mean(),
                "volume": np.sum(cur_roi),
            }
        ]

# Write the bubble volume stats
out_table = pd.DataFrame(out_results)
out_table.to_csv(args.bubble_volume_stats_output_filename)  # "bubble_volume.csv"

# Write the bubble volume stats sample table
volume_sample = out_table.sample(5)
volume_sample.save(args.bubble_volume_stats_sample_table_output_filename)

# Write the bubble volume density plot
bubble_volume_density = out_table["volume"].plot.density()
bubble_volume_density.save(args.bubble_volume_density_stats_plot_output_filename)

# Write the bubble center plot
bubble_centers_plot = out_table.plot.hexbin("x", "y", gridsize=(5, 5))
bubble_centers_plot.save(args.bubble_centers_plot_output_filename)

# Compare to the training values
train_values = pd.read_csv(
    args.training_bubble_volume_stats_filename
)  # "../input/bubble_volume.csv"

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(8, 4))
_, n_bins, _ = ax1.hist(
    np.log10(train_values["volume"]), bins=20, label="Training volumes"
)
ax1.hist(np.log10(out_table["volume"]), n_bins, alpha=0.5, label="Watershed volumes")
ax1.legend()
ax1.set_title("Volume comparison\n(Log10)")
ax2.plot(
    out_table["x"], out_table["y"], "r.", train_values["x"], train_values["y"], "b."
)
ax2.legend(["Watershed bubbles", "Training bubbles"])

fig.savefig(args.bubble_stats_comparison_plot_output_filename)
