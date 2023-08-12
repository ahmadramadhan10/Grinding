import java.util.HashMap;
import java.util.Scanner;

public class pipes {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int [] a = new int[n];
		long avg = 0;
		for(int i = 0; i < n; i++) {
			a[i] = in.nextInt();
			avg += a[i];
		}
		avg /= n;
		long [] cumf = new long[n+1];
		HashMap<Long, Integer> freq = new HashMap<>();
		for(int i = 1; i < n+1; i++) {
			cumf[i] = cumf[i-1] + a[i-1] - avg;
			freq.put(cumf[i], freq.getOrDefault(cumf[i], 0) + 1);
		}
		
		int max = 0;
		for(long key: freq.keySet()) { 
			max = Math.max(max, freq.get(key));
		}
		System.out.println(n - max);
	}
}
