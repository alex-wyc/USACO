import java.io.BufferedReader;
import java.io.FileReader;
import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;

public class bgm {
  // Before submitting, make sure the main method hasn"t been changed!
  public static void main(String[] args) throws IOException {
    BufferedReader br = new BufferedReader(new FileReader("bgm.in"));
    HashMap<String, ArrayList<Integer>> map = new HashMap<String, ArrayList<Integer>>(7);
    map.put("B", new ArrayList<Integer>());
    map.put("E", new ArrayList<Integer>());
    map.put("S", new ArrayList<Integer>());
    map.put("I", new ArrayList<Integer>());
    map.put("G", new ArrayList<Integer>());
    map.put("O", new ArrayList<Integer>());
    map.put("M", new ArrayList<Integer>());

    while (br.ready()) {
      int N = Integer.parseInt(br.readLine());
      for (int i = 0; i < N; i++) {
        String[] data = br.readLine().split(" ");
        ArrayList<Integer> current = map.get(data[0]);
        current.add(Integer.parseInt(data[1]));
        map.put(data[0], current);
      }
    }
    br.close();
    //System.out.println(map);
    
    int count = 0;
    int bessieCount = 0;
    int goesCount = 0;
    int mooCount = 0;
    /*
    for (int B : map.get("B")) {
        for (int E : map.get("E")) {
            for (int S : map.get("S")) {
                for (int I : map.get("I")) {
                    for (int G : map.get("G")) {
                        for (int O : map.get("O")) {
                            for (int M : map.get("M")) {
                                if ((div7(M + O + O)) || (div7(G + O + E + S)) || (div7(B + E + S + S + I + E))) {
                                    count++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    */
    boolean isDiv = false;
    for (int M : map.get("M")) {
        for (int O : map.get("O")) {
            if (div7(M + O + O)) {
                //count = count + map.get("G").size() * map.get("E").size() * map.get("S").size() * map.get("B").size() * map.get("I").size();
                mooCount++;
            }
        }
    }
    for (int E : map.get("E")) {
        for (int S : map.get("S")) {
            for (int B : map.get("B")) {
                for (int I : map.get("I")) {
                    if (div7(B + E + S + S + I + E)) {
                        bessieCount++;
                    }
                }
            }
            for (int O : map.get("O")) {
                for (int G : map.get("G")) {
                    if (div7(G + O + E + S)) {
                        goesCount++;
                    }
                }
            }
        }
    }
    int GSize = map.get("G").size();
    int ESize = map.get("E").size();
    int SSize = map.get("S").size();
    int BSize = map.get("B").size();
    int ISize = map.get("I").size();
    int MSize = map.get("M").size();
    int OSize = map.get("O").size();

    count = count + mooCount * GSize * ESize * SSize * BSize * ISize;
    count = count + goesCount * (MSize - mooCount)* BSize * ISize;
    count = count + bessieCount * (MSize * OSize + GSize) - mooCount - goesCount - mooCount * goesCount;
 

    //System.out.println(count);

    PrintWriter pw = new PrintWriter(new File("bgm.out"));
    pw.print(count);
    pw.close();
  }

  public static boolean div7(long n) {
      /*
      if (n < 0) {
          return div7(-n);
      }
      if (n == 0 || n == 7) {
          return true;
      }
      if (n < 10) {
          return false;
      }

      else {
          return div7(n / 10 - 2 * (n - n / 10 * 10));
      }
      */
      return n % 7 == 0;
  }
}
