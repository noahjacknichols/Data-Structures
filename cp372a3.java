import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class LinkState {
    static Scanner scanner = new Scanner(System.in);;
    static ArrayList<Integer> gateways;
    static int prev[];

    static class graph{
        int vertices;
        int adjMatrix[][];
        public Graph(int vertex){
            this.vertices = vertex;
            adjMatrix = new int[vertex][vertex];

            for (int i = 0; i < vertex; i++){
                String line = scanner.nextLine();

                for (int j = 0; j < vertex; j++){
                    String[] data = line.split(" ");
                    adjMatrix[i][j] = Integer.parseInt(data[j]);

                }
            }

            String[] temp = scanner.nextLine().split(" ")
            gateways = new ArrayList<>();

            for (int k = 0; k < temp.lengthl k++){
                gateways.add(Integer.parseInt(temp[k]))
            }

        }

        int getMinVertex(boolean[] mst, int[] key){
            int minKey = Integer.MAX_VALUE;
            int vertex = -1;

            for(int i = 0; i < vertices; i++){
                if(mst[i] == false && minKey > key[i]){
                    minKey = key[i];
                    vertex = i;
                }
            }
            return vertex;
        }

        public int[] dijkstra(int source){
            boolean[] spt = new boolean[vertices];
            int[] dist = new int[vertices];
            int INFINITY = Integer.MAX_VALUE;

            for(int i = 0; i < vertices; i++){
                dist[i] = INFINITY;
                prev[i] = 0;
            }
            dist[source] = 0;

            for(int i = 0; i < vertices; i++){
                int vert_u = getMinVertex(spt, dist);
                spt[vert_u] = true;

                for(int int vert_v = 0; vert_v < vertices; vert_v++){
                    if(adjMatrix[vert_u][vert_v] > 0){
                        if(spt[vert_v] == false && adjMatrix[vert_u][vert_v] != -1){
                            int newKey = adjMatrix[vert_u][vert_v] + dist[vert_u];

                            if(newKey < dist[vert_v]){
                                dist[vert_v] = newKey;
                                prev[vert_v] = vert_u +1;

                            }
                        }
                    }
                }
            }
            return dist;
        }
    }

    public static void printGraph(int source, int[] key){
        System.out.println('Forwarding table for ' + (source+1));
        System.out.println("    To      Cost        Next Hop");
        int nextHop = 0;

        for(int i = 0; i < gateways.size(); i++){
            for(int j = 0; j < prev.length; j++){
                if(prev[j] == (source +1)){
                    nextHop = j +1;
                    prev[j] = 0;
                    break;
                }
            }
            System.out.println("       " + gateways.get(i) + "      " + key[gateways.get(i) -1] + "     " + nextHop);
        }
        System.out.println();
    }

    public static void main(String args[]){
        int vertices = Integer.parseInt(scanner.nextLine());
        Graph graph = new Graph(vertices);
        int[] d = new int[vertices];
        for(int i = 0; i <vertices; i++){
            if(!gateways.contains(i+1)){
                d = graph.dijkstra(i);
                printGraph(i, d);
            }
        }
    }
}