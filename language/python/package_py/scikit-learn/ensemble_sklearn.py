

class RandomForestClassifier(): # sklearn.ensemble.RandomForestClassifier
  '''
  @n_estimators : integer, optional (default=10)
    The number of trees in the forest.
  @criterion : string, optional (default=¡±gini¡±)
    The function to measure the quality of a split. Supported criteria are ¡°gini¡± for 
	the Gini impurity and ¡°entropy¡± for the information gain. Note: this parameter is 
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
	
  def predict(self, X):
    """Predict class for X.
        The predicted class of an input sample is a vote by the trees in
        the forest, weighted by their probability estimates. That is,
        the predicted class is the one with highest mean probability
        estimate across the trees.
        Parameters
        ----------
        X : array-like or sparse matrix of shape = [n_samples, n_features]
            The input samples. Internally, it will be converted to
            ``dtype=np.float32`` and if a sparse matrix is provided
            to a sparse ``csr_matrix``.
        Returns
        -------
        y : array of shape = [n_samples] or [n_samples, n_outputs]
            The predicted classes.
        """
	pass