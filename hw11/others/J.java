import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Comparator;

public class Boredom {
	
public static void main(String args[]) throws NumberFormatException, IOException
{
	BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
	int cases=Integer.parseInt(br.readLine());
	for(int t=1;t<=cases;t++)
	{
		String input[]=br.readLine().split(" ");
		int n=Integer.parseInt(input[0]);
		int m=Integer.parseInt(input[1]);
		int j,k,l;
		Integer arr[][]=new Integer[n][2];
		for(j=0;j<n;j++)
		{
			String inp[]=br.readLine().split(" ");
			arr[j][0]=Integer.parseInt(inp[1]);
			arr[j][1]=Integer.parseInt(inp[2]);
		}
		Arrays.sort(arr, new Comparator<Integer[]>() {
            @Override
            public int compare(final Integer[] entry1, final Integer[] entry2) {
                final Integer time1 = entry1[0];
                final Integer time2 = entry2[0];
                return time2-time1;
            }
        });
		int totalMinutes=m*60;
		int minutesPassed=0;k=0;
		int totalfunsies=0;
		while(minutesPassed<=totalMinutes && k<n)
		{
			minutesPassed=minutesPassed+arr[k][1];
			if(minutesPassed<=totalMinutes)
			{
				totalfunsies=totalfunsies+(arr[k][0]*arr[k][1]);
			}
			else
			{
				totalfunsies=totalfunsies+(arr[k][0]*(totalMinutes-(minutesPassed-arr[k][1])));
			}
			k++;
		}
		System.out.println("Case #"+t+": "+totalfunsies);
		br.readLine();
	}
}
}
