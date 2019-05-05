package hippop;
import java.io.*;
import java.util.*;

public class Test {
	public static void main(String[] args) throws Exception{  
		
		String[] s=readFileByChars("C:/Users/Administrator/Desktop/test.txt","C:/Users/Administrator/Desktop/test1.txt");
		DGraph g=new DGraph(s);
//		showDirectedGraph(s);
		System.out.println(g.queryBridgeWords());
		String[] n=readnew("C:/Users/Administrator/Desktop/new.txt");
		g.generateNewText(n);
		Scanner sc=new Scanner(System.in);
		System.out.println("waiting Dijkstra:enter two words"); 
		String a=sc.next(); 
		String b=sc.next();
		g.calcShortestPath(a,b);
		g.randomWalk();
		sc.close();
	}
	public static void showDirectedGraph(String [] s)throws Exception{
		GraphViz gv = new GraphViz();	   
		 gv.addln(gv.start_graph());
	     for(int i=0;i<s.length-1;i++){
	    	 gv.addln(s[i]+" -> "+s[i+1]+";");
	     }
	     gv.addln(gv.end_graph());
	     System.out.println("Graph created and Draw finish.");;
	     String type = "gif";
	     File out = new File("out." + type);   // out.gif in this example
	     gv.writeGraphToFile( gv.getGraph( gv.getDotSource(), type ), out );
	}
	public static String[] readFileByChars(String fileName,String fileName1) throws Exception{
        File file = new File(fileName);
        Reader reader = null;
        Writer writer = null;    
    	writer =new FileWriter(new File(fileName1));
        reader = new InputStreamReader(new FileInputStream(file));
        int tempchar;
        while ((tempchar = reader.read()) != -1) {
            if (tempchar>= 'a' && tempchar<= 'z'||(char) tempchar == ' '){
            	writer.write((char) tempchar);
            }
            else if(tempchar>= 'A' && tempchar<= 'Z'){
            	writer.write((char) (tempchar+32));
            }
            else {
            	 if (((char) tempchar) != 'r')
            		 writer.write(" ");}
        } 
        if (reader != null&&writer!= null) {         
                reader.close();
                writer.close();              
        }     
        BufferedReader isr = new BufferedReader(new FileReader(fileName1));
        String str = isr.readLine();
        String  strings[]= str.split("\\s+");
        //for(int i=0;i<strings.length;i++) System.out.println(strings[i]);
        if (isr!= null){
            isr.close();
        }
        return strings;
    }
	public static String[] readnew(String fileName) throws Exception{       
        BufferedReader isr = new BufferedReader(new FileReader(fileName));
        String str = isr.readLine();
        String  strings[]= str.split("\\s+");
        if (isr!= null){
            isr.close();
        }
        return strings;
    }
}