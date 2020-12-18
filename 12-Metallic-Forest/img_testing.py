from pathlib import Path

import numpy as np
import matplotlib.pyplot as plt
from skimage.color import rgb2gray, rgba2rgb
from skimage.filters import threshold_otsu
from skimage.restoration import denoise_wavelet


def show_image(image, title='', cmap_type='gray'):
    plt.imshow(image, cmap=cmap_type)
    plt.title(title)
    plt.axis('off')
    plt.show()


def save_image(image, fname, title='', cmap_type='gray'):
    plt.imshow(image, cmap=cmap_type)
    plt.title(title)
    plt.axis('off')
    plt.savefig(fname)


base = Path('Images')

# Import image
image = plt.imread(base / 'DendritesMetallicForest1.png')

# Turn to grayscale
image = rgb2gray(rgba2rgb(image))


# Calculate threshold (this is an algorithm and may not be the best for every image)
thresh = threshold_otsu(image)
binary = image > thresh

fig, axes = plt.subplots(ncols=3, figsize=(15, 2.5))
ax = axes.ravel()
ax[0] = plt.subplot(1, 3, 1)
ax[1] = plt.subplot(1, 3, 2)
ax[2] = plt.subplot(1, 3, 3, sharex=ax[0], sharey=ax[0])

ax[0].imshow(image, cmap=plt.cm.gray)
ax[0].set_title('Original')
ax[0].axis('off')

ax[1].hist(image.ravel(), bins=256)
ax[1].set_title('Histogram')
ax[1].axvline(thresh, color='r')

ax[2].imshow(binary, cmap=plt.cm.gray)
ax[2].set_title('Thresholded')
ax[2].axis('off')

plt.show()

save_image(binary, 'article_test.png')
