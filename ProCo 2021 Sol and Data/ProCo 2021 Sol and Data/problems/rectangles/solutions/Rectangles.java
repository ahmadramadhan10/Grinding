import java.io.*;
import java.util.*;

public class Rectangles {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter out = new PrintWriter(System.out);

		StringTokenizer st = new StringTokenizer(in.readLine());
		int N = Integer.parseInt(st.nextToken());
		int M = Integer.parseInt(st.nextToken());
		int K = Integer.parseInt(st.nextToken());
		
		Point[] points = new Point[2*M];
		Set<Integer> yVals = new TreeSet<Integer>();
		for (int i = 0; i < M; i++) {
			st = new StringTokenizer(in.readLine());
			int x = Integer.parseInt(st.nextToken());
			int y = Integer.parseInt(st.nextToken());
			points[2*i] = new Point(x, y, 1);
			points[2*i + 1] = new Point(x + K, y, -1);
			yVals.add(y);
			yVals.add(y - K + 1);
		}
		
		N = yVals.size();
		List<Integer> yValsList = new ArrayList<Integer>(yVals);
		for (int i = 0; i < 2*M; i++) {
			points[i].y0 = Collections.binarySearch(yValsList, points[i].y - K + 1);
			points[i].y1 = Collections.binarySearch(yValsList, points[i].y);
		}
		
		Arrays.sort(points);
		
		LazySegmentTree segTree = new LazySegmentTree();
		int ans = 0;
		for (int i = 0; i < 2*M; i++) {
			int curX = points[i].x;
			while (i < 2*M) {
				Point p = points[i];
				if (p.x > curX) break;
				segTree.updateRange(N, p.y0, p.y1, p.d);
				i++;
			}
			i--;
			ans = Math.max(ans, segTree.getMax(N, 0, N - 1));
		}
		
		out.println(ans);

		out.close();
		in.close();
	}
	
	public static class Point implements Comparable<Point> {
		int x, y, d;
		int y0, y1;
		boolean remove;
		public Point(int x, int y, int d) {
			this.x = x;
			this.y = y;
			this.d = d;
		}
		public int compareTo(Point other) {
			return x - other.x;
		}
	}

	public static class LazySegmentTree {
	    final int MAX = 1000000;        // Max tree size
	    int tree[] = new int[MAX];  // To store segment tree
	    int lazy[] = new int[MAX];  // To store pending updates
	  
	    /*  si -> index of current node in segment tree
	        ss and se -> Starting and ending indexes of elements for
	                     which current nodes stores sum.
	        us and eu -> starting and ending indexes of update query
	        ue  -> ending index of update query
	        diff -> which we need to add in the range us to ue */
	    void updateRangeUtil(int si, int ss, int se, int us,
	                         int ue, int diff)
	    {
	        // If lazy value is non-zero for current node of segment
	        // tree, then there are some pending updates. So we need
	        // to make sure that the pending updates are done before
	        // making new updates. Because this value may be used by
	        // parent after recursive calls (See last line of this
	        // function)
	        if (lazy[si] != 0)
	        {
	            // Make pending updates using value stored in lazy
	            // nodes
	            tree[si] += lazy[si];
	  
	            // checking if it is not leaf node because if
	            // it is leaf node then we cannot go further
	            if (ss != se)
	            {
	                // We can postpone updating children we don't
	                // need their new values now.
	                // Since we are not yet updating children of si,
	                // we need to set lazy flags for the children
	                lazy[si * 2 + 1] += lazy[si];
	                lazy[si * 2 + 2] += lazy[si];
	            }
	  
	            // Set the lazy value for current node as 0 as it
	            // has been updated
	            lazy[si] = 0;
	        }
	  
	        // out of range
	        if (ss > se || ss > ue || se < us)
	            return;
	  
	        // Current segment is fully in range
	        if (ss >= us && se <= ue)
	        {
	            // Add the difference to current node
	            tree[si] += diff;
	  
	            // same logic for checking leaf node or not
	            if (ss != se)
	            {
	                // This is where we store values in lazy nodes,
	                // rather than updating the segment tree itelf
	                // Since we don't need these updated values now
	                // we postpone updates by storing values in lazy[]
	                lazy[si * 2 + 1] += diff;
	                lazy[si * 2 + 2] += diff;
	            }
	            return;
	        }
	  
	        // If not completely in rang, but overlaps, recur for
	        // children,
	        int mid = (ss + se) / 2;
	        updateRangeUtil(si * 2 + 1, ss, mid, us, ue, diff);
	        updateRangeUtil(si * 2 + 2, mid + 1, se, us, ue, diff);
	  
	        // And use the result of children calls to update this
	        // node
	        tree[si] = Math.max(tree[si * 2 + 1], tree[si * 2 + 2]);
	    }
	  
	    // Function to update a range of values in segment
	    // tree
	    /*  us and eu -> starting and ending indexes of update query
	        ue  -> ending index of update query
	        diff -> which we need to add in the range us to ue */
	    void updateRange(int n, int us, int ue, int diff)  {
	        updateRangeUtil(0, 0, n - 1, us, ue, diff);
	    }
	  
	    /*  A recursive function to get the max of values in given
	        range of the array. The following are parameters for
	        this function.
	        si --> Index of current node in the segment tree.
	               Initially 0 is passed as root is always at'
	               index 0
	        ss & se  --> Starting and ending indexes of the
	                     segment represented by current node,
	                     i.e., tree[si]
	        qs & qe  --> Starting and ending indexes of query
	                     range */
	    int getMaxUtil(int ss, int se, int qs, int qe, int si)
	    {
	        // If lazy flag is set for current node of segment tree,
	        // then there are some pending updates. So we need to
	        // make sure that the pending updates are done before
	        // processing the sub sum query
	        if (lazy[si] != 0)
	        {
	            // Make pending updates to this node. Note that this
	            // node represents sum of elements in arr[ss..se] and
	            // all these elements must be increased by lazy[si]
	            tree[si] += lazy[si];
	  
	            // checking if it is not leaf node because if
	            // it is leaf node then we cannot go further
	            if (ss != se)
	            {
	                // Since we are not yet updating children os si,
	                // we need to set lazy values for the children
	                lazy[si * 2 + 1] += lazy[si];
	                lazy[si * 2 + 2] += lazy[si];
	            }
	  
	            // unset the lazy value for current node as it has
	            // been updated
	            lazy[si] = 0;
	        }
	  
	        // Out of range
	        if (ss > se || ss > qe || se < qs)
	            return 0;
	  
	        // At this point sure, pending lazy updates are done
	        // for current node. So we can return value (same as
	        // was for query in our previous post)
	  
	        // If this segment lies in range
	        if (ss >= qs && se <= qe)
	            return tree[si];
	  
	        // If a part of this segment overlaps with the given
	        // range
	        int mid = (ss + se) / 2;
	        return Math.max(getMaxUtil(ss, mid, qs, qe, 2 * si + 1),
	        				getMaxUtil(mid + 1, se, qs, qe, 2 * si + 2));
	    }
	  
	    // Return max of elements in range from index qs (query
	    // start) to qe (query end).  It mainly uses getSumUtil()
	    int getMax(int n, int qs, int qe)
	    {
	        // Check for erroneous input values
	        if (qs < 0 || qe > n - 1 || qs > qe)
	        {
	            System.out.println("Invalid Input");
	            return -1;
	        }
	  
	        return getMaxUtil(0, n - 1, qs, qe, 0);
	    }
	}
}