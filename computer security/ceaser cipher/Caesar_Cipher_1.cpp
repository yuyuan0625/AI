#include <iostream>
#include <string> 
using namespace std;

void encrypt(string& plain, int key)	//加密
{
	char c = '\0';	//c為參考字元(a/A -> 因為如果用'z'/'Z'+key後會超出字母範圍)
	for (int i = 0; i < plain.length(); i++)
	{
		int is_alphabet = 0;	//判斷是否是英文字母
		if ('a' <= plain[i] && plain[i] <= 'z')		//如果在'a'~'z'之間
		{
			c = 'a';	//參考字元設為'a'
			is_alphabet = 1;	//屬於字母
		}
		else if ('A' <= plain[i] && plain[i] <= 'Z')	//如果在'A'~'Z'之間
		{
			c = 'A';	//參考字元設為'A'
			is_alphabet = 1;	//屬於字母
		}

		if (is_alphabet == 1)	//屬於字母->做+key
		{
			plain[i] = c + (plain[i] - c + key) % 26;	//'a' + (明文[i] - 'a' + key) % 26 -> 密文;
		}
	}
}

void decrypt(string& cipher, int key)	//解密
{
	char c = '\0';	//c為參考字元(z/Z -> 因為如果用'a'/'A'-key後會超出字母範圍)
	for (int i = 0; i < cipher.length(); i++)
	{
		int is_alphabet = 0;	//判斷是否是英文字母
		if ('a' <= cipher[i] && cipher[i] <= 'z')		//如果在'a'~'z'之間
		{
			c = 'z';	//參考字元設為'z'
			is_alphabet = 1;	//屬於字母
		}
		else if ('A' <= cipher[i] && cipher[i] <= 'Z')	//如果在'A'~'Z'之間
		{
			c = 'Z';	//參考字元設為'Z'
			is_alphabet = 1;	//屬於字母
		}

		if (is_alphabet == 1)	//屬於字母->做-key
		{
			cipher[i] = c - (c - cipher[i] + key) % 26;	//'a' - (密文 - 'a' + key) % 26 -> 明文;
		}
	}
}

int main()
{
	char ch = '\0';
	while(1)	//無窮迴圈
	{
		cout << "encrypt: e; decrypt: d; quit: q\n";	//提示使用者選擇:加密/解密/退出
		cin >> ch;	
		if (ch == 'e')	//加密
		{
			int key;
			string plain;
			cout << "Please input key:\n";
			cin >> key;	
			cin.get();	//要讀掉上一行換行符號
			cout << "Please input plaintext:\n";
			getline(cin, plain);	//讀一整行
			encrypt(plain, key);
			cout << plain << "\n";
		}
		else if (ch == 'd')
		{
			int key;
			string cipher;
			cout << "Please input key:\n";
			cin >> key;
			cin.get();	//要讀掉上一行換行符號
			cout << "Please input ciphertext:\n";
			getline(cin, cipher);	//讀一整行
			decrypt(cipher, key);
			cout << cipher << "\n";
		}
		else if (ch == 'q')	//退出
			break;
		else
			cout << "Please input e/d/q\n";	//請使用者輸入正確指令
	}
}


