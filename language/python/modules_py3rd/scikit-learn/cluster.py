# sklearn.cluster.

'''----------------------------------------------------------------------------------
Parameters:	
X : array-like, shape=[n_samples, n_features]
    Input points.
quantile : float, default 0.3
    should be between [0, 1] 0.5 means that the median of all pairwise distances is -
	used.
n_samples : int, optional
    The number of samples to use. If not given, all samples are used.
random_state : int or RandomState
    Pseudo-random number generator state used for random sampling.
Returns: bandwidth : float
    The bandwidth parameter.

Estimate the bandwidth to use with the mean-shift algorithm. That this function takes 
time at least quadratic in n_samples. For large datasets, it¡¯s wise to set that para-
meter to a small value.
----------------------------------------------------------------------------------'''
def estimate_bandwidth(X, quantile=0.3, n_samples=None, random_state=0):
    pass
	
'''----------------------------------------------------------------------------------
Perform mean shift clustering of data using a flat kernel.
Parameters:	
X : array-like, shape=[n_samples, n_features]
Input data.
bandwidth : float, optional
Kernel bandwidth.
If bandwidth is not given, it is determined using a heuristic based on the median of all pairwise distances. This will take quadratic time in the number of samples. The sklearn.cluster.estimate_bandwidth function can be used to do this more efficiently.
seeds : array-like, shape=[n_seeds, n_features] or None
Point used as initial kernel locations. If None and bin_seeding=False, each data point is used as a seed. If None and bin_seeding=True, see bin_seeding.
bin_seeding : boolean, default=False
If true, initial kernel locations are not locations of all points, but rather the location of the discretized version of points, where points are binned onto a grid whose coarseness corresponds to the bandwidth. Setting this option to True will speed up the algorithm because fewer seeds will be initialized. Ignored if seeds argument is not None.
min_bin_freq : int, default=1
To speed up the algorithm, accept only those bins with at least min_bin_freq points as seeds.
cluster_all : boolean, default True
If true, then all points are clustered, even those orphans that are not within any kernel. Orphans are assigned to the nearest kernel. If false, then orphans are given cluster label -1.
max_iter : int, default 300
Maximum number of iterations, per seed point before the clustering operation terminates (for that seed point), if has not converged yet.
Returns:	
cluster_centers : array, shape=[n_clusters, n_features]
Coordinates of cluster centers.
labels : array, shape=[n_samples]
Cluster labels for each point.
----------------------------------------------------------------------------------'''
def mean_shift(X, bandwidth=None, seeds=None, bin_seeding=False, min_bin_freq=1, 
               cluster_all=True, max_iter=300, max_iterations=None):
    pass


	


	
						   
						   