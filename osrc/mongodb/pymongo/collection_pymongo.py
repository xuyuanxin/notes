

def find():
  '''
  >>> for item in db.Account.find():
        item
  '''
  pass

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
def find_one(filter_or_id=None, *args, **kwargs):
    pass
	
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
def insert_one(document):
    pass

