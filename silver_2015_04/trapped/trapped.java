import java.io.BufferedReader;
import java.io.FileReader;
import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;

public class trapped {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("trapped.in"));

        int cowPos;
        ArrayList<Integer[]> left = new ArrayList<Integer[]>();
        ArrayList<Integer[]> right = new ArrayList<Integer[]>();
        ArrayList<Integer> additions = new ArrayList<Integer>();

        while (br.ready()) {
            String[] data = br.readLine().split(" ");
            int N = Integer.parseInt(data[0]);
            cowPos = Integer.parseInt(data[1]);

            for (int i = 0 ; i < N ; i++) {
                data = br.readLine().split(" ");
                int pos = Integer.parseInt(data[0]);
                int size = Integer.parseInt(data[1]);
                boolean added = false;
                if (pos < cowPos) {
                    for (int j = 0 ; j < left.size() ; j++) {
                        if (pos > left.get(j)[0]) {
                            left.add(j, new Integer[]{pos, size});
                            added = true;
                            break;
                        }
                    }
                    if (!added) {
                        left.add(new Integer[]{pos, size});
                    }
                }
                else {
                    for (int j = 0 ; j < right.size() ; j++) {
                        if (pos < right.get(j)[0]) {
                            right.add(j, new Integer[]{pos, size});
                            added = true;
                            break;
                        }
                    }
                    if (!added) {
                        right.add(new Integer[]{pos, size});
                    }
                }
            }
        }
        br.close();

        /*
        System.out.println("Left:");
        for (int i = 0 ; i < left.size() ; i++) {
            System.out.println(Arrays.toString(left.get(i)));
        }
        System.out.println("Right:");
        for (int i = 0 ; i < right.size() ; i++) {
            System.out.println(Arrays.toString(right.get(i)));
        }
        */

        additions = additionsNeeded(left, right);
        //int ans = additions.get(0);
        int ans = min(additions);
        //System.out.println(ans);
        //System.out.println(additions);

        PrintWriter pw = new PrintWriter(new File("trapped.out"));
        pw.print(ans);
        pw.close();
    }

    public static ArrayList<Integer> additionsNeeded(ArrayList<Integer[]> left, ArrayList<Integer[]> right) {
        ArrayList<Integer> additions = new ArrayList<Integer>();
        
        if (left.size() == 0 || right.size() == 0) {
            return additions;
        }
        else {
            boolean leftBreakable = left.get(0)[1] < right.get(0)[0] - left.get(0)[0] + 1;
            boolean rightBreakable =right.get(0)[1] < right.get(0)[0] - left.get(0)[0] + 1;
            if (leftBreakable) {
                additions.add(right.get(0)[0] - left.get(0)[0] - left.get(0)[1]);
                ArrayList<Integer[]> newLeft = left;
                newLeft.remove(0);
                additions.addAll(additionsNeeded(newLeft, right));
            }
            if (rightBreakable) {
                additions.add(right.get(0)[0] - left.get(0)[0] - right.get(0)[1]);
                ArrayList<Integer[]> newRight = right;
                newRight.remove(0);
                additions.addAll(additionsNeeded(left, newRight));
            }

            if (!leftBreakable && !rightBreakable) {
                additions.add(0);
            }
            return additions;
        }
    }

    public static int min(ArrayList<Integer> list) {
        int currentMin = list.get(0);
        for (int i = 1 ; i < list.size() ; i++) {
            if (list.get(i) < currentMin) {
                currentMin = list.get(i);
            }
        }
        return currentMin;
    }
}
