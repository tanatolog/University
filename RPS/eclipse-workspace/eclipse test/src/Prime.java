
import java.util.Arrays;
import java.util.Random;

public class Prime {
	
	private static int getNext(int prime) {
		int i = prime + 1;
		
		for(; !isPrime(i); i++) {}
		
		return i;
	}
	
	public static int getRandomPrime() {
		Random r = new Random();
		return getNext(r.nextInt(999999999));
	}
	
	private static boolean isPrime(int n) {
		for (int j = 2; j < Math.sqrt(n); j++) {
			if (n % j == 0) {
				return false;
			}
		}
		
		return true;
	}
	
	public static int[] getRandomArray(int length) {
		int[] arr = new int[length];
		
		for(int i = 0; i < length; i++) {
			arr[i] = getRandomPrime();
		}
		
		Arrays.sort(arr);
		
		return arr;
	}



}