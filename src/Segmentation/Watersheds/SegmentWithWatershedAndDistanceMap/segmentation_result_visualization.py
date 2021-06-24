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
# ./segmentation_result_visualization.py <>
# e.g.
# ./segmentation_result_visualization.py P
#
# This is a companion code to the SegmentWithWatershedAndDistanceMap example
# to generate the example segmentation results visualizations.
#


import argparse

import itk
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d.art3d import Poly3DCollection
from skimage import measure
from tqdm import tqdm


parser = argparse.ArgumentParser(
    description="Visualize the segmentation result."
)
parser.add_argument("input_image_filename")
parser.add_argument("bubble_filename")
parser.add_argument("distance_map_filename")
parser.add_argument("watershed_filename")
parser.add_argument("clean_segmentation_filename")
parser.add_argument("input_projections_output_filename")
parser.add_argument("pipeline_images_output_filename")
parser.add_argument("segmentation_projections_output_filename")
parser.add_argument("clean_segmentation_projections_output_filename")
parser.add_argument("volume_rendering_output_filename")
args = parser.parse_args()


stack_image = itk.imread(args.input_image_filename)

# Display the input image projections
fig, (ax1, ax2, ax3) = plt.subplots(1, 3, figsize=(12, 4))
for i, (cax, clabel) in enumerate(zip([ax1, ax2, ax3], ["xy", "zy", "zx"])):
    cax.imshow(np.sum(stack_image, i).squeeze(), cmap="bone_r")
    cax.set_title("{} projection".format(clabel))
    cax.set_xlabel(clabel[0])
    cax.set_ylabel(clabel[1])

fig.savefig(args.input_projections_output_filename)

bubble_image = itk.imread(args.bubble_filename)

plt.imshow(bubble_image[5], cmap="bone")
fig.savefig(args.bubble_filename)

# Cut-through: display the segmentation pipeline image results
# Show the values at a slice in the middle as a way to get a feeling for what
# the distance map and the watershed did

ws_vol = itk.imread(args.watershed_filename)
ws_vol_arr = itk.array_view_from_image(ws_vol)

dmap_vol = itk.imread(args.distance_map_filename)

mid_slice = ws_vol.shape[0] // 2
fig, (ax1, ax2, ax3) = plt.subplots(1, 3, figsize=(20, 7))
ax1.imshow(bubble_image[mid_slice], cmap="bone")
ax1.set_title("Bubble image")
m_val = np.abs(dmap_vol[mid_slice]).std()
ax2.imshow(dmap_vol[mid_slice], cmap="RdBu", vmin=-m_val, vmax=m_val)
ax2.set_title("Distance image\nmin: {:2.2f}; max: {:2.2f}; mean: {:2.2f}".format(
    dmap_vol[mid_slice].min(), dmap_vol[mid_slice].max(), dmap_vol[mid_slice].mean()))
ax3.imshow(ws_vol[mid_slice], cmap="nipy_spectral")
ax3.set_title("Watershed\nLabels found: {}".format(len(np.unique(ws_vol_arr[ws_vol_arr > 0]))))

fig.savefig(args.pipeline_images_output_filename)

# Show segmentation result projections
fig, (ax1, ax2, ax3) = plt.subplots(1, 3, figsize=(12, 4))
for i, (cax, clabel) in enumerate(zip([ax1, ax2, ax3], ["xy", "zy", "zx"])):
    cax.imshow(np.max(ws_vol, i).squeeze(), cmap="nipy_spectral")
    cax.set_title("{} projection".format(clabel))
    cax.set_xlabel(clabel[0])
    cax.set_ylabel(clabel[1])

fig.savefig(args.segmentation_projections_output_filename)

# Clean segmentation result projections
bubble_label_image = itk.imread(args.clean_segmentation_filename)

# ToDo
# Count the kept bubbles in bubble_label_image
new_idx = 1234

fig, (ax1, ax2, ax3) = plt.subplots(1, 3, figsize=(12, 4))
for i, (cax, clabel) in enumerate(zip([ax1, ax2, ax3], ["xy", "zy", "zx"])):
    cax.imshow(np.max(bubble_label_image, i), cmap="jet", vmin=0, vmax=new_idx)
    cax.set_title("{} projection".format(clabel))
    cax.set_xlabel(clabel[0])
    cax.set_ylabel(clabel[1])

fig.savefig(args.clean_segmentation_projections_output_filename)


# Show 3D rendering
def show_3d_mesh(image, thresholds):
    p = image[::-1].swapaxes(1, 2)
    cmap = plt.cm.get_cmap("nipy_spectral_r")
    _fig = plt.figure(figsize=(10, 10))
    ax = _fig.add_subplot(111, projection="3d")
    for _i, c_threshold in tqdm(list(enumerate(thresholds))):
        verts, faces, _, _ = measure.marching_cubes(p == c_threshold, level=0)
        mesh = Poly3DCollection(verts[faces], alpha=0.25, edgecolor=None, linewidth=0.1)
        mesh.set_facecolor(cmap(_i / len(thresholds))[:3])
        mesh.set_edgecolor([1, 0, 0])
        ax.add_collection3d(mesh)

    ax.set_xlim(0, p.shape[0])
    ax.set_ylim(0, p.shape[1])
    ax.set_zlim(0, p.shape[2])

    ax.view_init(45, 45)
    return _fig


fig = show_3d_mesh(bubble_label_image, range(1, np.max(bubble_label_image), 10))

# Write 3D rendering of segmented image
fig.savefig(args.volume_rendering_output_filename)
