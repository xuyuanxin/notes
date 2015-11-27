class pymongo.results.InsertOneResult(inserted_id, acknowledged)
The return type for insert_one().

acknowledged
Is this the result of an acknowledged write operation?

The acknowledged attribute will be False when using WriteConcern(w=0), otherwise True.

Note If the acknowledged attribute is False all other attibutes of this class will raise InvalidOperation when accessed. Values for other attributes cannot be determined if the write operation was unacknowledged.
See also WriteConcern

inserted_id
The inserted document¡¯s _id.