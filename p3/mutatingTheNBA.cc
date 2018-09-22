#include <bits/stdc++.h>
using namespace std;

int findScore(char A, char B)
{
	if(A == B)
	{
		return 2;
	}
	else
	{
		return -1;
	}
}

// initialize DP array to 0's
int DP[3100][3100] = { {0} };

// store the path that we take in another array so we can trace our tracks
int Path[3100][3100] = { {0} };

int main()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
	
	// deal with user input
	string sA;
	string sB;
	cin >> sA;
	cin >> sB;
	
	int m = sA.length();
	int n = sB.length();
	
	int v1;
	int v2;
	int v3;

	for(int i = 0; i <= m; i++)
	{
		DP[i][0] = -i;
	}
	for(int i = 0; i <= n; i++)
	{
		DP[0][i] = -i;
	}
	
	for(int i = 1; i < m; i++)
	{
		Path[i][0] = -1;
	}
	for(int i = 1; i < n; i++)
	{
		Path[0][i] = 1;
	}
	
	for(int i = 1; i <= m; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			v1 = DP[i-1][j-1] + findScore(sA[i-1],sB[j-1]);	
			v2 = DP[i][j-1] - 1;
			v3 = DP[i-1][j] - 1;
			DP[i][j] = max({v1,v2,v3});
            
            if(DP[i][j] == v1)
			{
				Path[i-1][j-1] = 0;
				continue;
			}
			if(DP[i][j] == v2)
			{
				Path[i-1][j-1] = 1;
				continue;
			}
            if(DP[i][j] == v3)
			{
				Path[i-1][j-1] = -1;
				continue;
			}
		}
	}
	
	// for(int i = 0; i <= m; i++)
	// {
		// for(int j = 0; j <= n; j++)
		// {
			// cout << DP[i][j] << " ";
		// }
		// cout << "\n";
	// }
	
	// trace back to find string alignment
	string aReverse;
	string bReverse;
	
	int i = m-1;
	int j = n-1;
	while(i >= 0 || j >= 0)
	{
		if(i < 0)
		{
			aReverse.append("_");
			bReverse.append(string(1,sB[j]));
			j--;
			continue;
		}
		if(j < 0)
		{
			aReverse.append(string(1,sA[i]));
			bReverse.append("_");
			i--;
			continue;
		}
		if(Path[i][j] == -1)
		{
			aReverse.append(string(1,sA[i]));
			bReverse.append("_");
			i--;
			continue;
		}
		if(Path[i][j] == 0)
		{
			aReverse.append(string(1,sA[i]));
			bReverse.append(string(1,sB[j]));
			i--;
			j--;
			continue;
		}
		if(Path[i][j] == 1)
		{
			aReverse.append("_");
			bReverse.append(string(1,sB[j]));
			j--;
			continue;
		}
	}
	
	string aFinal;
	string bFinal;
	
	// reverse the strings
	reverse(aReverse.begin(),aReverse.end());
	reverse(bReverse.begin(),bReverse.end());
	
	// final output
	cout << DP[m][n] << "\n" << aReverse << "\n" << bReverse;
    return 0;
}
