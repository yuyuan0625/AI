#include <iostream>
#include <string> 
using namespace std;

void decrypt(string& cipher, int key)
{
	char c = '\0';
	for (int i = 0; i < cipher.length(); i++)
	{
		int is_alphabet = 0;
		if ('a' <= cipher[i] && cipher[i] <= 'z')
		{
			c = 'z';
			is_alphabet = 1;
		}
		else if ('A' <= cipher[i] && cipher[i] <= 'Z')
		{
			c = 'Z';
			is_alphabet = 1;
		}

		if (is_alphabet == 1)
		{
			cipher[i] = c - (c - cipher[i] + key) % 26;
		}
	}
}

int main()
{
	string cipher;
	cout << "Please input cipher:\n";
	getline(cin, cipher);

	for (int i = 1; i < 26; i++)
	{
		string temp(cipher);
		decrypt(temp, i);
		cout << "k = " << i << ": ";
		cout<< temp << "\n";
	}
}
