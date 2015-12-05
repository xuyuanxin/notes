# http://www.open-open.com/lib/view/open1407942131801.html

import java.util.Properties; 
   
import kafka.javaapi.producer.Producer; 
import kafka.producer.KeyedMessage; 
import kafka.producer.ProducerConfig; 
   
public class TestProducer {   
     
        public static void main(String[] args) {   
            Properties props = new Properties();   
            props.setProperty("metadata.broker.list","10.XX.XX.XX:9092");   
            props.setProperty("serializer.class","kafka.serializer.StringEncoder");   
            props.put("request.required.acks","1");   
            ProducerConfig config = new ProducerConfig(props);   
            Producer<String, String> producer = new Producer<String, String>(config);   
            KeyedMessage<String, String> data = new KeyedMessage<String, String>("mykafka","test-kafka");   
            try {   
                int i =1; 
                while(i < 1000){ 
                       
                    producer.send(data);   
                } 
            } catch (Exception e) {   
                e.printStackTrace();   
            }   
            producer.close();   
        }   
}

import java.util.HashMap; 
import java.util.List;   
import java.util.Map;   
import java.util.Properties;   
     
import kafka.consumer.ConsumerConfig;   
import kafka.consumer.ConsumerIterator;   
import kafka.consumer.KafkaStream;   
import kafka.javaapi.consumer.ConsumerConnector;  
   
public class TestConsumer extends Thread{   
        private final ConsumerConnector consumer;   
        private final String topic;   
     
        public static void main(String[] args) {   
            TestConsumer consumerThread = new TestConsumer("mykafka");   
            consumerThread.start();   
        }   
        public TestConsumer(String topic) {   
            consumer =kafka.consumer.Consumer   
                    .createJavaConsumerConnector(createConsumerConfig());   
            this.topic =topic;   
        }   
     
    private static ConsumerConfig createConsumerConfig() {   
        Properties props = new Properties();   
        props.put("zookeeper.connect","10.XX.XX.XX:2181,10.XX.XX.XX:2181,10.XX.XX.XX:2181");   
        props.put("group.id", "0");   
        props.put("zookeeper.session.timeout.ms","10000");   
        return new ConsumerConfig(props);   
    }   
     
    public void run(){   
        Map<String,Integer> topickMap = new HashMap<String, Integer>();   
        topickMap.put(topic, 1);   
        Map<String, List<KafkaStream<byte[],byte[]>>>  streamMap =consumer.createMessageStreams(topickMap);   
        KafkaStream<byte[],byte[]>stream = streamMap.get(topic).get(0);   
        ConsumerIterator<byte[],byte[]> it =stream.iterator();   
        System.out.println("*********Results********");   
        while(true){   
            if(it.hasNext()){ 
                   
                System.err.println("get data:" +new String(it.next().message()));   
            } 
            try {   
                Thread.sleep(1000);   
            } catch (InterruptedException e) {   
                e.printStackTrace();   
            }   
        }   
    }   
}