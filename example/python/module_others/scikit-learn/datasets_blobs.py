'''
>>> from sklearn.datasets.samples_generator import make_blobs
>>> X, y = make_blobs(n_samples=10, centers=3, n_features=2,
...                   random_state=0)
>>> print(X.shape)
(10, 2)
>>> y
array([0, 0, 1, 0, 2, 2, 2, 1, 1, 0])
'''

from sklearn.datasets.samples_generator import make_blobs

X, y = make_blobs(n_samples=10, centers=3, n_features=3, random_state=0)

print X
print(X.shape)
print y
