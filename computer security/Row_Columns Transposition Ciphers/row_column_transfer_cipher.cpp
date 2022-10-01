#include<iostream>
#include <string>
#include <stdlib.h> 
#include <stdio.h>
#include <math.h>		//要用無條件進位ceil 
#include <algorithm>	//需要sort 
using namespace std;

int key_len = 0;	//key的長度 
int plain_len = 0;	
int cipher_len = 0;	
int key[100]= {0};	//儲存key 
int key_index[100] = {0};	//儲存key的index 
string plain;	 
string cipher;
char en_arr[100][100] = {'X'};	//encrypt用到的array 
char de_arr[100][100] = {'X'};	//decrypt用到的array 

void init()	//init en_arr and de_arr
{
	for(int i = 0; i < 100; i++)
	{
		for(int j = 0; j < 100; j++)
		{
			en_arr[i][j]= 'X';
			de_arr[i][j]= 'X';
		}
	}
}

int get_key(){	
	string str;
	int cnt = 0;
	cout << "key = ";
	getline(cin, str);
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] != ' ')
		{
			int tmp = str[i] - '0';	//將char轉int，存入key[] 
			key[cnt] = tmp;
			//存每個key的index值(到時候就可以依序print cipher/存cipher)
			key_index[tmp-1] = cnt;	
			cnt++;
		}
	}
	key_len = cnt;
	
	sort(key, key + key_len);	//sort 
	int check = 0;
	for (int i = 0; i < key_len - 1; i++)	//check 是否有重複key 
	{	
		if(key[i] == key[i+1])
		{
			//cout << "duplicate key!" << endl;	
			check = 1;
		} 
	}
	return check;
}

void get_plain(){
	string str;
	int cnt = 0;
	cout << "plain = ";
	getline(cin, str);
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] != ' ')
		{
			plain[cnt] = str[i];
			cnt++;
		}
	}
	
	plain_len = cnt;
}

void get_cipher(){
	string str;
	int cnt = 0;
	
	cout << "cipher = ";
	getline(cin, str);
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] != ' ')
		{
			cipher[cnt] = str[i];
			cnt++;
		}
	}
	cipher_len = cnt;
}

void encrypt(){
 	int row = ceil(float(plain_len)/key_len);	//無條件進位 
 	//加密過程 
 	for(int i = 0; i < row; i++)	//row
 	{
 		for(int j = 0; j < key_len ; j++)	//column
 		{
 			if(j+i*key_len < plain_len)	//將plain存入(依照row存) 
 			{
 				en_arr[j][i] = plain[j+i*key_len];
 				//cout << en_arr[j][i] << " ";
			}
		}
		//cout << endl;
	}
	
	cout << "cipher:";
	for(int i = 0; i < key_len; i++)
	{
		for(int j = 0; j < row; j++)
		{
			cout << en_arr[key_index[i]][j];
		}
	}
	cout << endl;
 	
}

void decrypt()
{
	int row = ceil(float(cipher_len)/key_len);
	for(int i = 0; i < key_len; i++)
	{
		for(int j = 0; j < row; j++)
		{
			de_arr[key_index[i]][j] = cipher[i * row + j];
		}
	}
	
	cout << "plain: ";
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < key_len; j++)
		{
			cout << de_arr[j][i];
		}
	}
	cout << endl;
}

int main()
{
	char ch = '\0';
	while(1){
		init();
		cout << "encrypt: e; decrypt: d; quit: q\n";
		cin>> ch;
		cin.get();	//讀掉換行 
		if(ch=='e')
		{
			int check = 0;
			check = get_key();
			while(check == 1)
			{
				cout << "duplicate key, please again" << endl;
				check = get_key();	
			}
			get_plain();
			encrypt();	
		}		
		else if(ch=='d')
		{
			int check = 0;
			check = get_key();
			while(check == 1)
			{
				cout << "duplicate key, please again" << endl;
				check = get_key();	
			}
			get_cipher();	
			decrypt();
		}
		else if(ch == 'q')
			break;
	}
}

