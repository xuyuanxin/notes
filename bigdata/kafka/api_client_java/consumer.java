























/*

--> Class KafkaConsumer<K,V>
 A Kafka client that consumes records from a Kafka cluster. 
 The consumer is not thread-safe.

--> Offsets and Consumer Position
 Kafka maintains a numerical offset for each record in a partition. This offset  acts 
 as a kind of unique identifier of a record within that partition, and also denotes -
 the position of the consumer in the partition. That is, a consumer which has positi-
 on 5 has consumed records with offsets 0 through 4 and will next receive the  record 
 with offset 5. It automatically advances every time the consumer receives data calls 
 @poll(long) and receives messages.

 The "committed position" is the last offset that has been saved securely. Should the 
 process fail and restart, this is the offset that it will recover to. The consumer -
 can either automatically commit offsets periodically; or it can choose to control t-
 his committed position manually by calling @commitSync, which will block until the -
 offsets have been successfully committed or fatal error has happened during the com-
 mit process, or @commitAsync which is non-blocking and will trigger @OffsetCommitCallback 
 upon either successfully committed or fatally failed.

--> Consumer Groups and Topic Subscriptions
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
*/
