import java.io.*;
import java.util.*;

public class HedgehogGridPrecomp {
	
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter out = new PrintWriter(System.out);

		StringTokenizer st = new StringTokenizer(in.readLine());
		int N = Integer.parseInt(st.nextToken());
		int M = Integer.parseInt(st.nextToken());
		
		boolean[][] civilian = new boolean[N][M];
		for (int r = 0; r < N; r++) {
			String line = in.readLine();
			for (int c = 0; c < M; c++) {
				civilian[r][c] = line.charAt(c) == '1';
			}
		}
		
		// max speed can't exceed sqrt(2N)
		int MAX_SPEED = (int) Math.ceil(Math.sqrt(2 * Math.max(N, M)));
				
		// precompute max possible move lengths for each grid space
		int[][][] maxMoveDist = new int[N][M][4];
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				for (int dir = 0; dir < 4; dir++) {
					int rDiff = dir % 2 == 0 ? dir - 1 : 0;
					int cDiff = dir % 2 == 1 ? dir - 2 : 0;
					int row = r;
					int col = c;
					maxMoveDist[r][c][dir] = -1;
					while (row >= 0 && row < N &&
						   col >= 0 && col < M &&
						   !civilian[row][col]) {
						row += rDiff;
						col += cDiff;
						maxMoveDist[r][c][dir]++;
					}
				}
			}
		}
				
		boolean[][][][] inQueue = new boolean[N][M][4][MAX_SPEED + 1];
		ArrayDeque<State> toVisit = new ArrayDeque<State>();
		
		// start in top left corner facing South and at speed 0
		toVisit.add(new State(0, 0, 2, 0, 0));
		inQueue[0][0][2][0] = true;
		
		boolean foundPath = false;
		while (!toVisit.isEmpty()) {
			State node = toVisit.remove();
			
			if (node.row == N - 1 && node.col == M - 1) {
				foundPath = true;
				out.println(node.dist);
				break;
			}
			
			int rDiff = node.dir % 2 == 0 ? node.dir - 1 : 0;
			int cDiff = node.dir % 2 == 1 ? node.dir - 2 : 0;
			
			int nextRow = node.row + node.speed * rDiff;
			int nextCol = node.col + node.speed * cDiff;
			
			int incrNextRow = nextRow + rDiff;
			int incrNextCol = nextCol + cDiff;
			int decrNextRow = nextRow - rDiff;
			int decrNextCol = nextCol - cDiff;
			
			// increase speed
			if (node.speed + 1 <= maxMoveDist[node.row][node.col][node.dir] &&
				!inQueue[incrNextRow][incrNextCol][node.dir][node.speed + 1]) {
				toVisit.add(new State(incrNextRow,
									  incrNextCol,
									  node.dir,
									  node.speed + 1,
									  node.dist + 1));
				inQueue[incrNextRow][incrNextCol][node.dir][node.speed + 1] = true;
			}
			
			// decrease speed
			if (node.speed > 0 &&
				node.speed - 1 <= maxMoveDist[node.row][node.col][node.dir] &&
				!inQueue[decrNextRow][decrNextCol][node.dir][node.speed - 1]) {
				toVisit.add(new State(decrNextRow,
									  decrNextCol,
									  node.dir,
									  node.speed - 1,
									  node.dist + 1));
				inQueue[decrNextRow][decrNextCol][node.dir][node.speed - 1] = true;
			}
			
			// change direction
			if (node.speed == 0) {
				for (int dir = 0; dir < 4; dir++) {
					if (!inQueue[node.row][node.col][dir][0]) {
						toVisit.add(new State(node.row, node.col, dir, 0, node.dist + 1));
						inQueue[node.row][node.col][dir][0] = true;
					}
				}
			}
			
		}

		if (!foundPath) out.println(-1);
				
		out.close();
		in.close();
	}
		
	public static class State {
		int row, col, dir, speed, dist;
		public State(int row, int col, int dir, int speed, int dist) {
			this.row = row;
			this.col = col;
			this.dir = dir;
			this.speed = speed;
			this.dist = dist;
		}
	}
}