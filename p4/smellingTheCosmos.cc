#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// brute force multiplication method for when n <= 8
vector<int> bruteForce(vector<int> a, vector<int> b)
{
	int n = a.size();
	vector<int> sum(2*n-1,0);
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			sum[i+j] += a[i] * b[j];
		}
	}
	
	return sum;
}

// karatsuba multiplication method
vector<int> karatsuba(vector<int> a, vector<int> b)
{
	
	int n = a.size();
	if(n <= 8)
	{
		return bruteForce(a, b);
	}
	
	vector<int> sum(2*n-1,0);
	
	vector<int> aHigh(n/2,0);
	vector<int> aMid(n/2,0);
	vector<int> aLow(n/2,0);
	vector<int> bHigh(n/2,0);
	vector<int> bMid(n/2,0);
	vector<int> bLow(n/2,0);

	for(int i = 0; i < n/2; i++)
	{
		aHigh[i] = a[i];
		bHigh[i] = b[i];
	}	
	for(int i = 0; i < n/2; i++)
	{
		aLow[i] = a[i+n/2];
		bLow[i] = b[i+n/2];
	}
	
	for(int i = 0; i < n/2; i++)
	{
		aMid[i] = aHigh[i] + aLow[i];
		bMid[i] = bHigh[i] + bLow[i];
	}
	
	vector<int> subPoly1(n-1,0);
	vector<int> subPoly2(n-1,0);
	vector<int> subPoly3(n-1,0);
	
	subPoly1 = karatsuba(aHigh,bHigh);
	subPoly3 = karatsuba(aLow,bLow);
	subPoly2 = karatsuba(aMid,bMid);
	for(int i = 0; i < n-1; i++)
	{
		subPoly2[i] = subPoly2[i] - subPoly1[i] - subPoly3[i];
	}			
	
	// 0 1 2 ... n-2 n-1 n n+1 n+2 ... 2n-3 2n-2 2n-1
	
	// n=8
	// 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
	// 0 1 2 3 4 5 6 7
	        // 4 5 6 7 8 9 10 11
			        // 8 9 10 11 12 13 14 15
	
	// calculate the sum of our subPoly's
	for(int i = 0; i < n; i++)
	{
		sum[i] += subPoly1[i];
	}
	for(int i = n/2; i < 3*n/2; i++)
	{
		sum[i] += subPoly2[i-n/2];
	}
	for(int i = n; i < 2*n; i++)
	{
		sum[i] += subPoly3[i-n];
	}
	return sum;
}

int main()
{
	// deal with user input
	
	// n: degree of polynomials
	int n;
	cin >> n;
	
	// a[] and b[]: coefficiants of polynomials
	vector<int> a(n+1,0);
	vector<int> b(n+1,0);
	for(int i = 0; i <= n; i++)
	{
		cin >> a[i];
	}
	for(int i = 0; i <= n; i++)
	{
		cin >> b[i];
	}
	
	// if the degree of the polynomials is less than 8, brute force the multiplication
	if(n <= 8)
	{
		vector<int> output = bruteForce(a,b);
		for(int i = 0; i < output.size(); i++)
		{
			cout << output[i] << " ";
		}
	}
	
	// otherwise multiply using the karatsuba method
	if(n > 8)
	{
		vector<int> output = karatsuba(a,b);
		for(int i = 0; i < output.size(); i++)
		{
			cout << output[i] << " ";
		}
	}
	
    return 0;
}