


class RandomForest: # pyspark.mllib.tree.RandomForest
  '''
  http://www.cnblogs.com/bourneli/p/4473976.html
  Learning algorithm for a random forest model for classification or regression.
  '''
  
  supportedFeatureSubsetStrategies = ('auto', 'all', 'sqrt', 'log2', 'onethird')
  
  @classmethod 
  def trainClassifier(data, numClasses, categoricalFeaturesInfo, numTrees, \
                      featureSubsetStrategy='auto', impurity='gini', maxDepth=4, \
					  maxBins=32, seed=None):
    '''
    Method to train a decision tree model for binary or multiclass classification.

    @data:
	  Training dataset: RDD of LabeledPoint. Labels should take values              -
	  {0, 1,..., numClasses-1}.
    @numClasses: 
	  number of classes for classification.
    @categoricalFeaturesInfo: Map storing arity of categorical features. E.g., an en-
	  try (n -> k) indicates that feature n is categorical with k categories  indexed 
	  from 0: {0, 1, ..., k-1}.
    @numTrees: 
	  Number of trees in the random forest.
    @featureSubsetStrategy: Number of features to consider for splits at each node. -
	  Supported: ¡°auto¡± (default), ¡°all¡±, ¡°sqrt¡±, ¡°log2¡±, ¡°onethird¡±. If ¡°auto¡± is s-
	  et, this parameter is set based on numTrees: if numTrees == 1, set to ¡°all¡±; i-
	  f numTrees > 1 (forest) set to ¡°sqrt¡±.
    @impurity: 
	  Criterion used for information gain calculation. Supported values: "gini" (rec-
	  ommended) or "entropy".
    @maxDepth: 
	  Maximum depth of the tree. E.g., depth 0 means 1 leaf node; depth 1 means 1 in-
	  ternal node + 2 leaf nodes. (default: 4)
    @maxBins: 
	  maximum number of bins used for splitting features (default: 32)
    @seed: 
	  Random seed for bootstrapping and choosing feature subsets.
    @Returns: 
	  RandomForestModel that can be used for prediction
	
    >>> from pyspark.mllib.regression import LabeledPoint
    >>> from pyspark.mllib.tree import RandomForest
    >>>
    >>> data = [
    ...     LabeledPoint(0.0, [0.0]),
    ...     LabeledPoint(0.0, [1.0]),
    ...     LabeledPoint(1.0, [2.0]),
    ...     LabeledPoint(1.0, [3.0])
    ... ]
    >>> model = RandomForest.trainClassifier(sc.parallelize(data), 2, {}, 3, seed=42)
    >>> model.numTrees()
    3
    >>> model.totalNumNodes()
    7
    >>> print(model)
    TreeEnsembleModel classifier with 3 trees

    >>> print(model.toDebugString())
    TreeEnsembleModel classifier with 3 trees

      Tree 0:
        Predict: 1.0
      Tree 1:
        If (feature 0 <= 1.0)
         Predict: 0.0
        Else (feature 0 > 1.0)
         Predict: 1.0
      Tree 2:
        If (feature 0 <= 1.0)
         Predict: 0.0
        Else (feature 0 > 1.0)
         Predict: 1.0

    >>> model.predict([2.0])
    1.0
    >>> model.predict([0.0])
    0.0
    >>> rdd = sc.parallelize([[3.0], [1.0]])
    >>> model.predict(rdd).collect()
    [1.0, 0.0]	
    '''
    pass
	
class RandomForestModel(java_model): # pyspark.mllib.tree.RandomForestModel
  '''
  Represents a random forest model.
  '''

  def call(name, *a):
    #Call method of java_model
    pass

  @classmethod
  def load(sc, path):

  def numTrees():
    #Get number of trees in ensemble.
    pass

  def predict(x):
    '''
    Predict values for a single data point or an RDD of points using the model train-
	ed. In Python, predict cannot currently be used within an RDD transformation or -
	action. Call predict directly on the RDD instead.
    '''
    pass

  def save(sc, path):
    '''
    @sc: Spark context used to save model data.
    @path: Path specifying the directory in which to save this model. If the directo-
	  ry already exists, this method throws an exception.
    Save this model to the given path.

    This saves:
      human-readable (JSON) model metadata to path/metadata/
      Parquet formatted data to path/data/
    The model may be loaded using py:meth:Loader.load.
    '''
    pass

  def toDebugString()
    #Full model
    pass

  def totalNumNodes():
    #Get total number of nodes, summed over all trees in the ensemble. 
    pass


	
	
	
