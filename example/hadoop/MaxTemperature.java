/*-----------------------------------------------------------------------------------
 ----> A Weather Dataset

 ----> Map and Reduce
 MapReduce works by breaking the processing into two phases: the map phase and the r-
 educe phase. Each phase has key-value pairs as input and output , the types of which 
 may be chosen by the programmer. The programmer also specifies two functions:the map
 function and the reduce function.

 ----> map input
 The input to our map phase is the raw NCDC data. We choose a text input format  that
 gives us each line in the dataset as a text value. The key is the offset of the beg-
 inning of the line from the beginning of the file, but as we have no need for  this, 
 we ignore it. Our map function is simple. We pull out the year and the air temperat-
 ure, because these are the only fields we are interested in. 

 To visualize the way the map works, consider the following sample lines of input da-
 ta(some unused columns have been dropped to fit the page, indicated by ellipses):
     0067011990999991950051507004...9999999N9+00001+99999999999...
     0043011990999991950051512004...9999999N9+00221+99999999999...
     0043011990999991950051518004...9999999N9-00111+99999999999...
     0043012650999991949032412004...0500001N9+01111+99999999999...
     0043012650999991949032418004...0500001N9+00781+99999999999...
 These lines are presented to the map function as the key-value pairs:
     (0, 0067011990999991950051507004бн9999999N9+00001+99999999999бн)
     (106, 0043011990999991950051512004бн9999999N9+00221+99999999999бн)
     (212, 0043011990999991950051518004бн9999999N9-00111+99999999999бн)
     (318, 0043012650999991949032412004бн0500001N9+01111+99999999999бн)
     (424, 0043012650999991949032418004бн0500001N9+00781+99999999999бн)
 The keys are the line offsets within the file , which we ignore in our map function. 
 The map function merely extracts the year and the air temperature (indicated in bold 
 text), and emits them as its output (the temperature values have been interpreted as 
 integers):
     (1950, 0)
     (1950, 22)
     (1950, -11)
     (1949, 111)
     (1949, 78)
 The output from the map function is processed by the MapReduce framework before bei-
 ng sent to the reduce function. This processing sorts and groups the key-value pairs 
 by key. So, continuing the example, our reduce function sees the following input:
     (1949, [111, 78])
     (1950, [0, 22, -11])
 Each year appears with a list of all its air temperature readings. All the reduce f-
 unction has to do now is iterate through the list and pick up the maximum reading:
     (1949, 111)
     (1950, 22)
 This is the final output: the maximum global temperature recorded in each year.
 ----------------------------------------------------------------------------------*/
import java.io.IOException;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

public class MaxTemperatureMapper
extends Mapper<LongWritable, Text, Text, IntWritable> 
{
private static final int MISSING = 9999;

@Override

/*-----------------------------------------------------------------------------------
 Mapper for the maximum temperature example

 The Mapper class is a generic type,with four formal type parameters that specify the 
 input key, input value, output key, and output value types of the map function . For 
 the present example, the input key is a long integer offset, the input value is a l-
 ine of text, the output key is a year, and the output value is an air temperature (-
 an integer). 

 Rather than using built-in Java types, Hadoop provides its own set of basic types t-
 hat are optimized for network serialization. These are found in the org.apache.hadoop.io package. 
 Here we use LongWritable, which corresponds to a Java Long, Text (like Java String), 
 and IntWritable (like Java Integer).

 The map() method is passed a key and a value. We convert the Text value containing -
 the line of input into a Java String, then use its substring() method to extract the 
 columns we are interested in . The map() method also provides an instance of Context 
 to write the output to. In this case, we write the year as a Text object (since we -
 are just using it as a key), and the temperature is wrapped in an IntWritable.
 ----------------------------------------------------------------------------------*/
public void map(LongWritable key, Text value, Context context)
throws IOException, InterruptedException 
{
    String line = value.toString();
    String year = line.substring(15, 19);
    int airTemperature;
	
    if (line.charAt(87) == '+') { // parseInt doesn't like leading plus signs
        airTemperature = Integer.parseInt(line.substring(88, 92));
    } else {
        airTemperature = Integer.parseInt(line.substring(87, 92));
    }
	
	String quality = line.substring(92, 93);
    if (airTemperature != MISSING && quality.matches("[01459]")) {
        context.write(new Text(year), new IntWritable(airTemperature));
    }
}

}


import java.io.IOException;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

public class MaxTemperatureReducer
extends Reducer<Text, IntWritable, Text, IntWritable> 
{

/*-----------------------------------------------------------------------------------
 Reducer for the maximum temperature example

 Again, four formal type parameters are used to specify the input and output types, -
 this time for the reduce function. 

 The input types of the reduce function must match the output types of the map funct-
 ion: Text and IntWritable. And in this case, the output types of the reduce function 
 are Text and IntWritable, for a year and its maximum temperature,
 ----------------------------------------------------------------------------------*/
@Override
public void reduce(Text key, Iterable<IntWritable> values, Context context)
throws IOException, InterruptedException 
{
    int maxValue = Integer.MIN_VALUE;
	
    for (IntWritable value : values) {
        maxValue = Math.max(maxValue, value.get());
    }
	context.write(key, new IntWritable(maxValue));
}

}


import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class MaxTemperature 
{

/*-----------------------------------------------------------------------------------
 A Job object forms the specification of the job and gives you control over how the -
 job is run. When we run this job on a Hadoop cluster , we will package the code into 
 a JAR file (which Hadoop will distribute around the cluster). Rather than explicitly 
 specifying the name of the JAR file,we can pass a class in the Job's setJarByClass() 
 method, which Hadoop will use to locate the relevant JAR file by looking for the JAR 
 file containing this class.

 Having constructed a Job object, we specify the input and output paths. An input pa-
 th is specified by calling the static addInputPath() method on FileInputFormat , and 
 it can be a single file, a directory (in which case, the input forms all the files -
 in that directory), or a file pattern. As the name suggests, addInputPath() can be -
 called more than once to use input from multiple paths. The output path (of which t-
 here is only one) is specified by the static setOutputPath() method on FileOutputFo-
 rmat. It specifies a directory where the output files from the reduce function are -
 written. The directory shouldn't exist before running the job because Hadoop will c-
 omplain and not run the job. This precaution is to prevent data loss (it can be very 
 annoying to accidentally overwrite the output of a long job with that of another).

 Next, we specify the map and reduce types to use via the setMapperClass() and setRe-
 ducerClass() methods. The setOutputKeyClass() and setOutputValueClass() methods con-
 trol the output types for the reduce function, and must match what the Reduce  class 
 produces. The map output types default to the same types , so they do not need to be 
 set if the mapper produces the same types as the reducer (as it does in our case). -
 However, if they are different, the map output types must be set using the setMapOu-
 tputKeyClass() and setMapOutputValueClass() methods.

 The input types are controlled via the input format, which we have not explicitly s-
 et because we are using the default TextInputFormat.

 After setting the classes that define the map and reduce functions , we are ready to 
 run the job . The waitForCompletion() method on Job submits the job and waits for it 
 to finish. The single argument to the method is a flag indicating whether verbose o-
 utput is generated. When true , the job writes information about its progress to the 
 console . The return value of the waitForCompletion() method is a Boolean indicating 
 success (true) or failure (false), which we translate into the program's exit code -
 of 0 or 1.
 ----------------------------------------------------------------------------------*/
public static void main(String[] args) throws Exception 
{
    if (args.length != 2) 
	{
        System.err.println("Usage: MaxTemperature <input path> <output path>");
        System.exit(-1);
    }
	
	Job job = new Job();
    job.setJarByClass(MaxTemperature.class);
    job.setJobName("Max temperature");
	
	FileInputFormat.addInputPath(job, new Path(args[0]));
    FileOutputFormat.setOutputPath(job, new Path(args[1]));
	
    job.setMapperClass(MaxTemperatureMapper.class);
    job.setReducerClass(MaxTemperatureReducer.class);
	
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(IntWritable.class);
	
    System.exit(job.waitForCompletion(true) ? 0 : 1);
}

}