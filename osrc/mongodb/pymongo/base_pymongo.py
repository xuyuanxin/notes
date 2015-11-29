'''
http://api.mongodb.org/python/current/index.html     恅紫翋珜
http://api.mongodb.org/python/current/tutorial.html
http://www.cnblogs.com/libingql/archive/2011/06/15/2081545.html PyMongo基本使用

API
  bson 每 BSON (Binary JSON) Encoding and Decoding
    binary 每 Tools for representing binary data to be stored in MongoDB
    regex 每 Tools for representing MongoDB regular expressions
    code 每 Tools for representing JavaScript code
    codec_options 每 Tools for specifying BSON codec options
    dbref 每 Tools for manipulating DBRefs (references to documents stored in MongoDB)
    errors 每 Exceptions raised by the bson package
    int64 每 Tools for representing BSON int64
    json_util 每 Tools for using Python＊s json module with BSON documents
    max_key 每 Representation for the MongoDB internal MaxKey type
    min_key 每 Representation for the MongoDB internal MinKey type
    objectid 每 Tools for working with MongoDB ObjectIds
    son 每 Tools for working with SON, an ordered mapping
    timestamp 每 Tools for representing MongoDB internal Timestamps
    tz_util 每 Utilities for dealing with timezones in Python
  pymongo 每 Python driver for MongoDB
    database 每 Database level operations
    collection 每 Collection level operations
    command_cursor 每 Tools for iterating over MongoDB command results
    cursor 每 Tools for iterating over MongoDB query results
    bulk 每 The bulk write operations interface
    errors 每 Exceptions raised by the pymongo package
    message 每 Tools for creating messages to be sent to MongoDB
    monitoring 每 Tools for monitoring driver events.
    mongo_client 每 Tools for connecting to MongoDB
    mongo_replica_set_client 每 Tools for connecting to a MongoDB replica set
    operations 每 Operation class definitions
    pool 每 Pool module for use with a MongoDB client.
    read_preferences 每 Utilities for choosing which member of a replica set to read from.
    results 每 Result class definitions
    son_manipulator 每 Manipulators that can edit SON documents as they are saved or retrieved
    cursor_manager 每 Managers to handle when cursors are killed after being closed
    uri_parser 每 Tools to parse and validate a MongoDB URI
    write_concern 每 Tools for specifying write concern
  gridfs 每 Tools for working with GridFS
    errors 每 Exceptions raised by the gridfs package
    grid_file 每 Tools for representing files stored in GridFS


'''

''' 
----> Making a Connection with MongoClient
  The first step when working with PyMongo is to create a MongoClient to the  running 
  mongod instance. Doing so is easy:
  >>> from pymongo import MongoClient
  >>> client = MongoClient() # connect on the default host and port
  >>> client = MongoClient('localhost', 27017) # specify the host and port explicitly
  >>> client = MongoClient('mongodb://localhost:27017/') #use the MongoDB URI format

----> Getting a Database
  A single instance of MongoDB can support multiple independent databases. When work-
  ing with PyMongo you access databases using attribute style access on MongoClient -
  instances: 
  >>> db = client.test_database
  # If your database name is such that using attribute style access won＊t work ( like  
  # test-database), you can use dictionary style access instead:
  >>> db = client['test-database']

----> Getting a Collection
  A collection is a group of documents stored in MongoDB, and can be thought of as r-
  oughly the equivalent of a table in a relational database. Getting a collection  in 
  PyMongo works the same as getting a database:
  >>> collection = db.test_collection
  # or (using dictionary style access):
  >>> collection = db['test-collection']
  # An important note about collections (and databases) in MongoDB is that they are -
  # created lazily - none of the above commands have actually performed any operatio-
  # ns on the MongoDB server. Collections and databases are created when the first d-
  # ocument is inserted into them.
  >>>

----> Documents
  Data in MongoDB is represented (and stored) using JSON-style documents. In  PyMongo 
  we use dictionaries to represent documents. As an example, the following dictionary 
  might be used to represent a blog post:
  >>> import datetime
  >>> post = {"author": "Mike",
  ...         "text": "My first blog post!",
  ...         "tags": ["mongodb", "python", "pymongo"],
  ...         "date": datetime.datetime.utcnow()}
  Note that documents can contain native Python types (like datetime.datetime instan-
  ces) which will be automatically converted to and from the appropriate BSON types.

----> Inserting a Document
  To insert a document into a collection we can use the insert_one() method: 
  >>> posts = db.posts
  >>> post_id = posts.insert_one(post).inserted_id
  >>> post_id
  ObjectId('...')

  When a document is inserted a special key, "_id", is automatically added if the docu-
ment doesn＊t already contain an "_id" key. The value of "_id" must be unique across -
the collection. insert_one() returns an instance of InsertOneResult. For more inform-
ation on "_id", see the documentation on _id. After inserting the first document, the 
posts collection has actually been created on the server. We can verify this by list-
ing all of the collections in our database: 
>>> db.collection_names(include_system_collections=False)
[u'posts']

----> Getting a Single Document With find_one() 
The most basic type of query that can be performed in MongoDB is find_one(). This me-
thod returns a single document matching a query (or None if there are no matches). It 
is useful when you know there is only one matching document, or are only interested -
in the first match. Here we use find_one() to get the first document from the posts -
collection: '''
>>> posts.find_one()
{u'date': datetime.datetime(...), u'text': u'My first blog post!', u'_id': ObjectId('...'), u'author': u'Mike', u'tags': [u'mongodb', u'python', u'pymongo']}

''' The result is a dictionary matching the one that we inserted previously. Note The 
returned document contains an "_id", which was automatically added on insert.       -
find_one() also supports querying on specific elements that the resulting document m-
ust match. To limit our results to a document with author ※Mike§ we do:
'''
>>> posts.find_one({"author": "Mike"})
{u'date': datetime.datetime(...), u'text': u'My first blog post!', u'_id': ObjectId('...'), u'author': u'Mike', u'tags': [u'mongodb', u'python', u'pymongo']}

''' If we try with a different author, like ※Eliot§, we＊ll get no result: '''
>>> posts.find_one({"author": "Eliot"})
>>>







