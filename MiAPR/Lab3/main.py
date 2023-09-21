import sys

import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import scipy.stats as stats
matplotlib.use('TkAgg')


if len(sys.argv) != 4 or not sys.argv[3].replace(".", "", 1).isdigit():
    print('invalid parameters: python ' + sys.argv[0] + ' name1.npy name2.npy P(C1)')
    exit()

data1 = np.random.normal(float(0), float(1.0), 1000)
data2 = np.random.normal(float(0), float(5.0), 1000)
# data1, data2 = np.load((sys.argv[1], False), np.load(sys.argv[2], False))

mu1, sigma1 = np.mean(data1), np.std(data1)
mu2, sigma2 = np.mean(data2), np.std(data2)

pc1 = float(0.1)
pc2 = 1 - pc1

range = (min(np.min(data1), np.min(data2)), max(np.max(data1), np.max(data2)))

x = np.linspace(range[0], range[1], 10000)

pxc1, pxc2 = stats.norm.pdf(x, mu1, sigma1), stats.norm.pdf(x, mu2, sigma2)

y1, y2 = pxc1 * pc1, pxc2 * pc2

y1_max, y2_max = np.argmax(y1), np.argmax(y2)

count_for_left = y1_max < y2_max

if count_for_left:
    intersection = y1_max + np.argmin(np.abs(y1[y1_max:y2_max] - y2[y1_max:y2_max]))
    false_alert = np.sum(pxc2[:intersection]) / np.sum(pxc2) * pc2
    detection_skip = np.sum(pxc1[intersection:]) / np.sum(pxc1) * pc1
else:
    intersection = y2_max + np.argmin(np.abs(y1[y2_max:y1_max] - y2[y2_max:y1_max]))
    false_alert = np.sum(pxc2[intersection:]) / np.sum(pxc2) * pc2
    detection_skip = np.sum(pxc1[:intersection]) / np.sum(pxc1) * pc1

classification_error = false_alert + detection_skip

plt.figure(figsize=(8, 8))

if count_for_left:
    plt.fill_between(x[:intersection], y2[:intersection], color="khaki")
    plt.fill_between(x[intersection:], y1[intersection:], color="pink")
else:
    plt.fill_between(x[intersection:], y2[intersection:], color="khaki")
    plt.fill_between(x[:intersection], y1[:intersection], color="pink")

plt.plot(x, y1)
plt.plot(x, y2)
plt.scatter(x[intersection], y1[intersection], color="black")
# plt.xlabel("False alert (khaki): {false_alert:.{4}f} Warning skip (pink): {detection_skip:.{4}f} Classification error: {classification_error:.{4}f}")
plt.xlabel("False alert (khaki): " + format(false_alert, '.4f') + " Warning skip (pink): " + format(detection_skip,
                                                                                                    '.4f') + " Classification error: " + format(
    classification_error, '.4f'), fontsize=18)
plt.show()
