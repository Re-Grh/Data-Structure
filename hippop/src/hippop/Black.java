package hippop;

import static org.junit.Assert.*;

import java.io.*;
import org.junit.Test;

public class Black {
	@Test
	public void test1() throws Exception {
		String[] s=readFileByChars("C:/Users/Administrator/Desktop/test.txt","C:/Users/Administrator/Desktop/test1.txt");		
		DGraph g=new DGraph(s);
		String result=g.queryBridgeWords("new","and");
		assertEquals("The bridge words from new to and are: [life]",result);
	}
	@Test
	public void test() throws Exception {
		String[] s=readFileByChars("C:/Users/Administrator/Desktop/test.txt","C:/Users/Administrator/Desktop/test1.txt");		
		DGraph g=new DGraph(s);
		String result=g.queryBridgeWords("new","seek");
		assertEquals("No bridge words from word1 to word2!",result);
	}
	@Test
	public void test2() throws Exception {
		String[] s=readFileByChars("C:/Users/Administrator/Desktop/test.txt","C:/Users/Administrator/Desktop/test1.txt");		
		DGraph g=new DGraph(s);
		String result=g.queryBridgeWords("new","one");
		assertEquals("No word1 or word2 in the graph!",result);
	}
	@Test
	public void test3() throws Exception {
		String[] s=readFileByChars("C:/Users/Administrator/Desktop/test.txt","C:/Users/Administrator/Desktop/test1.txt");		
		DGraph g=new DGraph(s);
		String result=g.queryBridgeWords("new","1");
		assertEquals("No word1 or word2 in the graph!",result);
	}
	@Test
	public void test4() throws Exception {
		String[] s=readFileByChars("C:/Users/Administrator/Desktop/test.txt","C:/Users/Administrator/Desktop/test1.txt");		
		DGraph g=new DGraph(s);
		String result=g.queryBridgeWords("new");
		assertEquals("Please enter two words!",result);
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
}
