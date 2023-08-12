import java.io.*;
import java.util.*;

public class LongestSequences {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter out = new PrintWriter(System.out);

		StringTokenizer st = new StringTokenizer(in.readLine());
		int N = Integer.parseInt(st.nextToken());
		int X = Integer.parseInt(st.nextToken());
		int Y = Integer.parseInt(st.nextToken());
		
		if (X * Y < N || X + Y - 1 > N) {
			out.println(-1);
		} else {
			int numLeft = N;
			int[] arr = new int[N];
			int idx = 0;
			while (numLeft - X >= Y - 1 && numLeft > 0) {
				for (int i = 1; i <= X; i++) {
					arr[idx++] = numLeft - X + i;
				}
				numLeft -=X;
				Y--;
			}
			if (Y > 0) {
				for (int i = 0; i < numLeft - Y + 1; i++) {
					arr[idx++] = Y + i;
				}
				Y--;
				for (int i = Y; i >= 1; i--) {
					arr[idx++] = i;
				}
			}
			for (int i = 0; i < N - 1; i++) {
				out.print(arr[i] + " ");
			}
			out.println(arr[N - 1]);
		}

		out.close();
		in.close();
	}
}