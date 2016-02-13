



class Collection(database, name, create=False, **kwargs): # pymongo.collection.Collection
  '''
  '''

  def find():
    '''
    >>> for item in db.Account.find():
          item
    '''
    pass

  def find_one(filter_or_id=None, *args, **kwargs):
    '''
    @filter (optional): 
    a dictionary specifying the query to be performed OR any other type to be used a-
	s the value for a query for "_id".
    @*args (optional): 
    any additional positional arguments are the same as the arguments to find().
    @**kwargs (optional): 
    any additional keyword arguments are the same as the arguments to find().
    @max_time_ms (optional): 
    a value for max_time_ms may be specified as part of **kwargs.
    #func:
    Get a single document from the database.

    All arguments to find() are also valid arguments for find_one(), although any limit -
    argument will be ignored. Returns a single document, or None if no matching  document 
    is found. The find_one() method obeys the read_preference of this Collection.
    '''
    pass

  def insert_one(document):
    '''
    @document: 
    The document to insert. Must be a mutable mapping type. If the document does  not 
	have an _id field one will be added automatically.
    @Returns:	
    An instance of InsertOneResult.
    @func:
    Insert a single document.
    >>> db.test.count({'x': 1})
    0
    >>> result = db.test.insert_one({'x': 1})
    >>> result.inserted_id
    ObjectId('54f112defba522406c9cc208')
    >>> db.test.find_one({'x': 1})
    {u'x': 1, u'_id': ObjectId('54f112defba522406c9cc208')}
    '''
    pass
	
  def insert_many(documents, ordered=True, bypass_document_validation=False):
    '''
    @documents: 
	  A iterable of documents to insert.
    @ordered: 
	  If True (the default) documents will be inserted on the server serially, in the 
	  order provided. If an error occurs all remaining inserts are aborted. If False, 
	  documents will be inserted on the server in arbitrary order, possibly in paral-
	  lel, and all document inserts will be attempted.
    @bypass_document_validation:
	  If True, allows the write to opt-out of document level validation. Default is -
	  False.
    @Returns:	
      An instance of InsertManyResult. 
	
    Insert an iterable of documents.

    >>> db.test.count()
    0
    >>> result = db.test.insert_many([{'x': i} for i in range(2)])
    >>> result.inserted_ids
    [ObjectId('54f113fffba522406c9cc20e'), ObjectId('54f113fffba522406c9cc20f')]
    >>> db.test.count()
    2
    '''
    pass

  def replace_one(filter, replacement, upsert=False, bypass_document_validation=False):
    '''
	@filter: A query that matches the document to replace.
    @replacement: The new document.
    @upsert (optional): If True, perform an insert if no documents match the filter.
    @bypass_document_validation: (optional) If True, allows the write to opt-out of -
	document level validation. Default is False.
    @Returns: An instance of UpdateResult.

	Note bypass_document_validation requires server version >= 3.2. 
	Changed in version 3.2: Added bypass_document_validation support
    New in version 3.0.
  
    Replace a single document matching the filter.

    >>> for doc in db.test.find({}):
    ...     print(doc)
    ...
    {u'x': 1, u'_id': ObjectId('54f4c5befba5220aa4d6dee7')}
    >>> result = db.test.replace_one({'x': 1}, {'y': 1})
    >>> result.matched_count
    1
    >>> result.modified_count
    1
    >>> for doc in db.test.find({}):
    ...     print(doc)
    ...
    {u'y': 1, u'_id': ObjectId('54f4c5befba5220aa4d6dee7')}
    
	The upsert option can be used to insert a new document if a matching document do-
	es not exist.

    >>> result = db.test.replace_one({'x': 1}, {'x': 1}, True)
    >>> result.matched_count
    0
    >>> result.modified_count
    0
    >>> result.upserted_id
    ObjectId('54f11e5c8891e756a6e1abd4')
    >>> db.test.find_one({'x': 1})
    {u'x': 1, u'_id': ObjectId('54f11e5c8891e756a6e1abd4')}
    '''

  def update(spec, document, upsert=False, manipulate=False, multi=False, check_keys=True, **kwargs):
    #Update a document(s) in this collection.
    pass
	
  def update_one(filter, update, upsert=False, bypass_document_validation=False):
    '''
	@filter: A query that matches the document to update.
    @update: The modifications to apply.
    @upsert (optional): If True, perform an insert if no documents match the filter.
    @bypass_document_validation: (optional) If True, allows the write to opt-out of -
	 document level validation. Default is False.
	@Returns: An instance of UpdateResult.
	
    Update a single document matching the filter.
	
    >>> for doc in db.test.find():
    ...     print(doc)
    ...
    {u'x': 1, u'_id': 0}
    {u'x': 1, u'_id': 1}
    {u'x': 1, u'_id': 2}
    >>> result = db.test.update_one({'x': 1}, {'$inc': {'x': 3}})
    >>> result.matched_count
    1
    >>> result.modified_count
    1
    >>> for doc in db.test.find():
    ...     print(doc)
    ...
    {u'x': 4, u'_id': 0}
    {u'x': 1, u'_id': 1}
    {u'x': 1, u'_id': 2}
	'''
    pass
	
  def update_many(filter, update, upsert=False, bypass_document_validation=False):
    '''
	@filter: A query that matches the documents to update.
    @update: The modifications to apply.
    @upsert (optional): If True, perform an insert if no documents match the filter.
    @bypass_document_validation: (optional) If True, allows the write to opt-out of -
	 document level validation. Default is False.
    @Returns: An instance of UpdateResult.
	
    Update one or more documents that match the filter.

    >>> for doc in db.test.find():
    ...     print(doc)
    ...
    {u'x': 1, u'_id': 0}
    {u'x': 1, u'_id': 1}
    {u'x': 1, u'_id': 2}
    >>> result = db.test.update_many({'x': 1}, {'$inc': {'x': 3}})
    >>> result.matched_count
    3
    >>> result.modified_count
    3
    >>> for doc in db.test.find():
    ...     print(doc)
    ...
    {u'x': 4, u'_id': 0}
    {u'x': 4, u'_id': 1}
    {u'x': 4, u'_id': 2}
	'''
    pass
	
