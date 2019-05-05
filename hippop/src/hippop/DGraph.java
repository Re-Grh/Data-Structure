package hippop;
import java.io.File;
import java.io.FileWriter;
import java.io.Writer;
import java.util.*;

public class DGraph {
	int max=1001;
	int n,e;
	int G[][];
	List<String> list;
	int V[][];
	int x2;
	DGraph(String s[]){
		list=new ArrayList<String>();
		for(int i=0;i<s.length;i++){
			if(!list.contains(s[i])||list.isEmpty()){
				list.add(s[i]);
			}
		}
		n=list.size();
		e=s.length-1;
		G =new int [n][n];
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				G[i][j]=0;
			}
		}
		for(int i=0;i<e;i++){
			G[list.indexOf(s[i])][list.indexOf(s[i+1])]+=1;
		}
	}
	public String queryBridgeWords(){
		List<String> tmp=new ArrayList<String>();
		Scanner sc=new Scanner(System.in);
		System.out.println("waiting Bridge:enter two words"); 
		String a=sc.next(); 
		String b=sc.next();
		tmp=Bridge(a, b);
		if(tmp.contains("0")){
			return "No bridge words from word1 to word2!";
		}
		else if(tmp.contains("-1")) return "No word1 or word2 in the graph!";
		else return "The bridge words from "+a+" to "+b+" are: "+tmp;
	}
	public String queryBridgeWords(String a){
	  return "Please enter two words!";
	}
	public String queryBridgeWords(String a,String b){
		List<String> tmp=new ArrayList<String>();
		tmp=Bridge(a, b);
		if(tmp.contains("0")){
			return "No bridge words from word1 to word2!";
		}
		else if(tmp.contains("-1")) return "No word1 or word2 in the graph!";
		else return "The bridge words from "+a+" to "+b+" are: "+tmp;
	}
	public List<String> Bridge(String a,String b)
	{
		List<String> l=new ArrayList<String>();
		int flag=0;
		if(!list.contains(a)||!list.contains(b)) 
			{l.add("-1");
			return l;
			}
		
		else{
			for(int i=0;i<n;i++)
			{
				if(G[list.indexOf(a)][i]>0&&G[i][list.indexOf(b)]>0){
					l.add(list.get(i));
					flag=1;
				}
						
			}
			if(flag==0){
				l.add("0");
			return l;
			}
			return l;
		}
	}
	public void generateNewText(String s[]){
		List<String> tmp=new ArrayList<String>();
		int i;
		for(i=0;i<s.length-1;i++)
		{
			List<String> l=Bridge(s[i], s[i+1]);
			tmp.add(s[i]);
			if(!l.contains("0")&&!l.contains("-1")){
				tmp.add(l.get(0));
			}
		}
		tmp.add(s[i]);
		 System.out.println("Bridgetxt is: ");
		for(i=0;i<tmp.size();i++) System.out.print(tmp.get(i)+" ");
		System.out.print("\n");
	}
	public String calcShortestPath(String s,String m){
		List<String> tmp=new ArrayList<String>();
		List<String> tmp2=new ArrayList<String>();
		if(!list.contains(s)||!list.contains(m)){
			return "No word1 or word2.";
		}
		int v=list.indexOf(s);
		int v1=list.indexOf(m);
		int []S=new int[n];
		int[] P=new int[n];
		int[] D=new int[n];
		int i, j,k=0,min;
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				if(G[i][j]==0){G[i][j]=max;}
			}
		}
		for (i = 0; i < n; i++)
		{
			S[i] = 0;
		}
		for (i = 0; i <n; i++)
		{
			D[i] = G[v][i];
			if (D[i] < max) P[i] = v;
			else P[i] = -1;
		}
		P[v] = -1; S[v] = 1;
		for (i = 2; i <= n; i++)
		{
			min = max;
			for (j = 0; j <n; j++)
			{
				if (D[j] < min&&S[j]==0)
				{
					k = j;
					min = D[k];
				}
			}
			S[k] = 1;
			for (j = 0; j <n; j++)
			{
				if (S[j]==0)
				{
					if (D[j] > D[k] + G[k][j])
					{
						D[j] = D[k] + G[k][j];
						P[j] = k;
					}
				}
			}
		}
		int t=v1;
		if(P[v1]!=-1){
		while(P[t]!=v){
			tmp.add(list.get(t));
			t=P[t];
		}
		tmp.add(list.get(t));
		tmp.add(s);
//		for(i=tmp.size()-1;i>0;i--)
//		System.out.print(tmp.get(i)+"->");
//		System.out.println(tmp.get(0));
//		System.out.println("the length is :"+D[v1]);
//		}
		for(i=tmp.size()-1,j=0;i>0;i--,j++)
			tmp2.add(tmp.get(i)+"->");
			tmp2.add(tmp.get(0));
			tmp2.add(" the length is :"+D[v1]);		
			return tmp2.toString();
			}
		else return("no way");
	};
	public void randomWalk()throws Exception{
		Scanner sc=new Scanner(System.in);
		Random ran = new Random();
		int x=0,flag=0;
		int x1 = ran.nextInt(n);
		V=new int[n][n];
		List<String> l=new ArrayList<String>();
		l.add(list.get(x1));
		int i=x1;
		System.out.print("RanWalk start(enter 0 to finish): "+l.get(0)+" ");
		while(true){
			int j=next(i);
			if(j<0){
				if(j==-1){l.add(list.get(x2));
				if(flag==1) System.out.println(l.get(x+1));}
				System.out.println("No path,RanWalk finish");
				break;
			}
			flag=1;
			l.add(list.get(j));
			i=j;
			x++;
			System.out.println(l.get(x));
			System.out.println("Continue? ");
			String a=sc.next();
			if(a.equals("0")) { System.out.println("RanWalk finish");break;}
		}
		Writer writer = null;    
    	writer =new FileWriter(new File("C:/Users/Administrator/Desktop/1.txt"));
    	for(i=0;i<l.size();i++){
    		for(int j=0;j<l.get(i).length();j++){
    			writer.write(l.get(i).toCharArray()[j]);
    		}
    		writer.write(" ");
    	}
    	 writer.close(); 
	}
	public int next(int x1){
		Random ran = new Random();
		int flag=0;
		List<Integer> l=new ArrayList<Integer>();
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				if(G[i][j]==max){G[i][j]=0;}
			}
		}
		for (int i = 0; i <n; i++)
		{
			if(G[x1][i]>0){
				flag=1;
				l.add(i);
			}
		}
		if(flag==0) return -2;
		else{
			int tmp = ran.nextInt(l.size());
			x2=l.get(tmp);
			if(V[x1][x2]!=1){
				V[x1][x2]=1;
				return x2;
			}
			else {
				return -1;
			}
		}
	}
}
