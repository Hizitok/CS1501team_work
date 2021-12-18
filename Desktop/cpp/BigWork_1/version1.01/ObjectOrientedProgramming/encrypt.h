
#ifndef Encrypt_H
#define Encrypt_H


#include<iostream>
#include<string>
using namespace std;

string encrypt(string s)
{
	string ans;
	ans = s;
	for(int i=0 ; i<s.size() ;i++)
		ans[i] = ans[i] ^ (32+i);
	return ans;
	
}



#endif
