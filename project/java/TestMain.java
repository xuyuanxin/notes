
import java.io.*;
import java.util.*;

public class TestMain {
	public static void main(String[] args) 
	{
		int num = 0x11020304;
		System.out.println("num:" + num);

		byte[] int2bytes = Utilities.int2Bytes(num);
		System.out.printf("int2bytes: ");
		for (int i = 0; i < 4; ++i) {
			System.out.print(int2bytes[i] + " ");
		}
		System.out.println();

		int bytes2int = Utilities.bytes2Int(int2bytes);
		System.out.println("bytes2int: " + bytes2int);

		byte int2OneByte = Utilities.int2OneByte(num);
		System.out.println("int转行成one byte: " + int2OneByte);

		int oneByte2Int = Utilities.oneByte2Int(int2OneByte);
		System.out.println("one byte转行成int: " + oneByte2Int);
		System.out.println();

		long longNum = 100000;
		System.out.println("测试的long值为：" + longNum);

		byte[] long2Bytes = Utilities.long2Bytes(longNum);
		System.out.printf("long转行成bytes: ");
		for (int ix = 0; ix < long2Bytes.length; ++ix) {
			System.out.print(long2Bytes[ix] + " ");
		}
		System.out.println();

		long bytes2Long = Utilities.bytes2Long(long2Bytes);
		System.out.println("bytes转行成long: " + bytes2Long);
	}
}

