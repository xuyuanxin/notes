

class RandomForestClassifier(): # sklearn.ensemble.RandomForestClassifier
  '''
  As other classifiers, forest classifiers have to be fitted with two arrays: a spar-
  se or dense array X of size [n_samples, n_features] holding the training samples, -
  and an array Y of size [n_samples] holding the target values (class labels) for the 
  training samples:
 
  >>> from sklearn.ensemble import RandomForestClassifier
  >>> X = [[0, 0], [1, 1]]
  >>> Y = [0, 1]
  >>> clf = RandomForestClassifier(n_estimators=10)
  >>> clf = clf.fit(X, Y)
  '''
  
  def fit(X, y, sample_weight=None):
    '''
    Build a forest of trees from the training set (X, y).
	'''
    pass