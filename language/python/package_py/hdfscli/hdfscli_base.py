HdfsCLI: API and command line interface for HDFS.



--> Reading files
 The read() method provides a file-like interface for reading files from HDFS. It mu-
 st be used in a with block (making sure that connections are always properly closed-
 ):

 # Loading a file in memory.
 with client.read('features') as reader:
   features = reader.read()

 # Directly deserializing a JSON object.
 with client.read('model.json', encoding='utf-8') as reader:
   from json import load
   model = load(reader)
 
 If a chunk_size argument is passed, the method will return a generator instead, mak-
 ing it sometimes simpler to stream the file¡¯s contents.

 # Stream a file.
 with client.read('features', chunk_size=8096) as reader:
   for chunk in reader:
     pass
 
 Similarly, if a delimiter argument is passed, the method will return a generator  of 
 the delimited chunks.

 with client.read('samples.csv', encoding='utf-8', delimiter='\n') as reader:
   for line in reader:
     pass
	 
--> writing files	 
 Writing files to HDFS is done using the write() method which returns a file-like wr-
 itable object:

 # Writing part of a file.
 with open('samples') as reader, client.write('samples') as writer:
   for line in reader:
     if line.startswith('-'):
       writer.write(line)

 # Writing a serialized JSON object.
 with client.write('model.json', encoding='utf-8') as writer:
   from json import dump
   dump(model, writer)
 For convenience, it is also possible to pass an iterable data argument directly to -
 the method.

 # This is equivalent to the JSON example above.
 from json import dumps
 client.write('model.json', dumps(model))	 
 
	 
	 
