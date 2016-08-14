public class buffet {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("buffet.in"));
        int E, N;
        while (br.ready()) {
            String[] data = br.readLine().split(" ");
            N = data[0];
            E = data[1];

        }
    }
}

public class field {
    private int q;
    private int[] neighbors;

    public field(int newQ, int[] newNeighbors) {
        q = newQ;
        neighbors = newNeighbors;
    }

    public int getQ() {
        return q;
    }

    public int[] getNeighbors() {
        return neighbors;
    }
}

public class fieldList {
    private field[] total;
}
