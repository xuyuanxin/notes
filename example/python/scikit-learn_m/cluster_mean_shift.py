"""
=============================================
A demo of the mean-shift clustering algorithm
=============================================

Reference:

Dorin Comaniciu and Peter Meer, "Mean Shift: A robust approach toward
feature space analysis". IEEE Transactions on Pattern Analysis and
Machine Intelligence. 2002. pp. 603-619.

"""
print(__doc__)

import numpy as np
from sklearn.cluster import MeanShift, estimate_bandwidth
from sklearn.datasets.samples_generator import make_blobs

###############################################################################
# Generate sample data
centers1 = [[1, 1], [-1, -1], [1, -1]]
centers2 = [[-2, -3], [0, 0], [3, 2]]
X, _ = make_blobs(n_samples=10, centers=centers2, cluster_std=0.6)

###############################################################################
# Compute clustering with MeanShift

# The following bandwidth can be automatically detected using
bandwidth = estimate_bandwidth(X, quantile=0.2, n_samples=500)

ms = MeanShift(bandwidth=bandwidth, bin_seeding=True)

ms.fit(X)
labels = ms.labels_
cluster_centers = ms.cluster_centers_
#print labels
#print cluster_centers
labels_unique = np.unique(labels)
n_clusters_ = len(labels_unique)

print("number of estimated clusters : %d" % n_clusters_)

###############################################################################
# Plot result
import matplotlib.pyplot as plt
from itertools import cycle

plt.figure(1)
plt.clf()

print '---->X:\n',X

colors = cycle('bgrcmykbgrcmykbgrcmykbgrcmyk')
for k, col in zip(range(n_clusters_), colors):
    my_members = labels == k
    print '-------------> k,col:',k,col
    print 'labels:\n',labels
    print 'my_members:\n', my_members
    print 'labels:\n', labels
    print 'X[my_members, 0]:\n',X[my_members, 0]
    cluster_center = cluster_centers[k]
    plt.plot(X[my_members, 0], X[my_members, 1], col + '.')
    plt.plot(cluster_center[0], cluster_center[1], 'o', markerfacecolor=col,markeredgecolor='k', markersize=14)
plt.title('Estimated number of clusters: %d' % n_clusters_)
#plt.show()


'''
about .fit
http://blog.csdn.net/u012162613/article/details/42192293


---->X:
[[-0.48267169 -0.04743546]
 [-3.10562769 -3.0899446 ]
 [ 3.83069219  1.06921394]
 [-1.76431748 -3.03153553]
 [ 2.90278095  1.76790763]
 [-0.71963102  0.15765324]
 [-2.13638959 -2.45415303]
 [-0.90484991 -1.32449344]
 [-2.04566195 -2.90624894]
 [ 2.2199847   1.71864085]]
-------------> k,col: 0 b
labels:
[2 4 5 0 1 2 0 3 0 1]
my_members:
[False False False  True False False  True False  True False]
labels:
[2 4 5 0 1 2 0 3 0 1]
X[my_members, 0]:
[-1.76431748 -2.13638959 -2.04566195]
-------------> k,col: 1 g
labels:
[2 4 5 0 1 2 0 3 0 1]
my_members:
[False False False False  True False False False False  True]
labels:
[2 4 5 0 1 2 0 3 0 1]
X[my_members, 0]:
[ 2.90278095  2.2199847 ]

'''