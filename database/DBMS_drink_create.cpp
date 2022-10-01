#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
ofstream file("cap.csv");	//將資金水位輸出到txt
void get_temp()
{
    for(int i = 0; i < 500; i++)
    {
        double r = (double)rand()/RAND_MAX;
        if (r < 0.33)
            file << "cold" << endl;
        else if (r < 0.66)
            file << "hot" << endl;
        else
            file << "both" <<endl;
    }
}

void get_cap()
{
    for(int i = 0; i < 500; i++)
    {
        double r = (double)rand()/RAND_MAX;
        if (r < 0.25)
            file << "XL" << endl;
        else if (r < 0.5)
            file << "L" << endl;
        else if (r < 0.75)
            file << "M" <<endl;
        else 
            file << "S" <<endl;
    }
}

void get_price()
{
    int price[12] = {20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75};
     for(int i = 0; i < 500; i++)
    {
        int a = round(((double)rand() / RAND_MAX) * (12 - 1));
        file << price[a] << endl;
    }
}

int main()
{
    // get_temp();
    get_cap();
    // get_price();
    return 0;
}