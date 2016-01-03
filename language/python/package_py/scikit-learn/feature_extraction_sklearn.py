
#sklearn.feature_extraction.text.CountVectorizer
class CountVectorizer(input='content', encoding='utf-8', decode_error='strict', \
                      strip_accents=None, lowercase=True, preprocessor=None, \
                      tokenizer=None, stop_words=None, token_pattern='(?u)\b\w\w+\b', \
                      ngram_range=(1, 1), analyzer='word', max_df=1.0, min_df=1, \
                      max_features=None, vocabulary=None, binary=False, dtype=<class 'numpy.int64'>)
  '''
  @analyzer : string, {¡®word¡¯, ¡®char¡¯, ¡®char_wb¡¯} or callable
   Whether the feature should be made of word or character n-grams. Option  ¡®char_wb¡¯ 
   creates character n-grams only from text inside word boundaries. If a callable  is 
   passed it is used to extract the sequence of features out of the raw,  unprocessed 
   input. Only applies if analyzer == 'word'.
  @ngram_range : tuple (min_n, max_n)
   The lower and upper boundary of the range of n-values for different n-grams to  be 
   extracted. All values of n such that min_n <= n <= max_n will be used.
  @max_df : float in range [0.0, 1.0] or int, default=1.0
   When building the vocabulary ignore terms that have a document frequency  strictly 
   higher than the given threshold (corpus-specific stop words). If float, the param-
   eter represents a proportion of documents, integer absolute counts. This parameter 
   is ignored if vocabulary is not None.
  @min_df : float in range [0.0, 1.0] or int, default=1
   When building the vocabulary ignore terms that have a document frequency  strictly 
   lower than the given threshold. This value is also called cut-off in the literatu-
   re. If float, the parameter represents a proportion of documents, integer absolute 
   counts. This parameter is ignored if vocabulary is not None.
  '''
  
  vocabulary_ : dict
    # A mapping of terms to feature indices.
  
  def build_analyzer():
    # Return a callable that handles preprocessing and tokenization
    pass

  def get_feature_names():
    # Array mapping from feature integer indices to feature name
    pass

  def fit_transform(raw_documents, y=None):
    ''' 
    @raw_documents : iterable
      An iterable which yields either str, unicode or file objects.
    @Returns: X : array, [n_samples, n_features]
      Document-term matrix.    
    
    Learn the vocabulary dictionary and return term-document matrix. This is equival-
    ent to fit followed by transform, but more efficiently implemented.
    '''
    pass

--> Common Vectorizer usage(4.2.3.3. )
 CountVectorizer implements both tokenization and occurrence counting in a single cl-
 ass:
 
 >>> from sklearn.feature_extraction.text import CountVectorizer
 >>> vectorizer = CountVectorizer(min_df=1)
 >>> corpus = ['This is the first document.', 'This is the second second document.',
 ...           'And the third one.','Is this the first document?',]
 >>> X = vectorizer.fit_transform(corpus)
        
 The default configuration tokenizes the string by extracting words of at least 2 le-
 tters. The specific function that does this step can be requested explicitly:
 >>> analyze = vectorizer.build_analyzer()
 >>> analyze("This is a text document to analyze.") == (['this', 'is', 'text', 'document', 'to', 'analyze'])
 True

 Each term found by the analyzer during the fit is assigned a unique integer index c-
 orresponding to a column in the resulting matrix. This interpretation of the columns 
 can be retrieved as follows:
 >>> vectorizer.get_feature_names() == (
 ...     ['and', 'document', 'first', 'is', 'one',
 ...      'second', 'the', 'third', 'this'])
 True

 >>> X.toarray()           
 array([[0, 1, 1, 1, 0, 0, 1, 0, 1],
        [0, 1, 0, 1, 0, 2, 1, 0, 1],
        [1, 0, 0, 0, 1, 0, 1, 1, 0],
        [0, 1, 1, 1, 0, 0, 1, 0, 1]]...)

 The converse mapping from feature name to column index is stored in the  vocabulary_ 
 attribute of the vectorizer:
 >>> vectorizer.vocabulary_.get('document')
 1
 
 Hence words that were not seen in the training corpus will be completely ignored  in 
 future calls to the transform method:
 >>> vectorizer.transform(['Something completely new.']).toarray()
 ...                           
 array([[0, 0, 0, 0, 0, 0, 0, 0, 0]]...)
 
 Note that in the previous corpus, the first and the last documents have exactly  the 
 same words hence are encoded in equal vectors. In particular we lose the information 
 that the last document is an interrogative form. To preserve some of the local orde-
 ring information we can extract 2-grams of words in addition to the 1-grams (indivi-
 dual words):
 >>> bigram_vectorizer = CountVectorizer(ngram_range=(1, 2),
 ...                                     token_pattern=r'\b\w+\b', min_df=1)
 >>> analyze = bigram_vectorizer.build_analyzer()
 >>> analyze('Bi-grams are cool!') == (
 ...     ['bi', 'grams', 'are', 'cool', 'bi grams', 'grams are', 'are cool'])
 True
 The vocabulary extracted by this vectorizer is hence much bigger and can now resolve 
 ambiguities encoded in local positioning patterns:
 >>> X_2 = bigram_vectorizer.fit_transform(corpus).toarray()
 >>> X_2
 ...                           
 array([[0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0],
        [0, 0, 1, 0, 0, 1, 1, 0, 0, 2, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0],
        [1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0],
        [0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1]]...)
 In particular the interrogative form ¡°Is this¡± is only present in the last document:
 >>> feature_index = bigram_vectorizer.vocabulary_.get('is this')
 >>> X_2[:, feature_index]     
 array([0, 0, 0, 1]...)


    
    
    
    
    
    
    
