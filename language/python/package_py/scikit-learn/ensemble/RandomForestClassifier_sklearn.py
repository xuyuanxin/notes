

class RandomForestClassifier(): # sklearn.ensemble.RandomForestClassifier
  '''
  @n_estimators : integer, optional (default=10)
    The number of trees in the forest.
  @criterion : string, optional (default=”gini”)
    The function to measure the quality of a split. Supported criteria are “gini” for 
	the Gini impurity and “entropy” for the information gain. Note: this parameter is 
	tree-specific  
  
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