#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

using namespace std;

int longest(int *arr, int *start, int n, int k) //O(N)
{ 
    int j, max = 0, total; 
    *start = 0;
    for (int i = 0; i <= k; ++i)
    	max += arr[i];
    total = max;
    for (int i = k+1; i < n; i++) 
    { 
        max += arr[i]; 
  	    max -= arr[i-k-1];
        if (max > total){ 
            total = max; 
            *start = i-k;
        }
    } 
    return total;
} 


void memoize(int**arr, int **mem, int** mem2, int size){ 
    int temp[size], sum, start, finish; 
    for (int left = 0; left < size; ++left) //O(N^2)
    { 
        for (int i = 0; i < size; ++i)
            temp[i] = 0;

        for (int right = left; right < size; ++right)  
        { 
            for (int i = 0; i < size; ++i) 
                temp[i] += arr[i][right];

            sum = longest(temp, &start, size, right-left); //O(N)
            mem[left][right] = sum;
            mem2[left][right] = start;
        } 
    } 
} 

int main(int argc, char const *argv[])
{
	ifstream file;
	string s_temp;
	int choice;
	int size, **arr, i_temp, **mem, **mem2;
	char buff[256] = "stuff.txt";
	cout << "press 1 to use file\npress 2 to use random\n";
	cin >> choice;
	if(choice == 1){
		file.open(buff);
		file >> s_temp >> size;
		arr = new int*[size];
		mem = new int*[size];
		mem2 = new int*[size];
		for (int i = 0; i < size; ++i){
			arr[i] = new int[size];
			mem[i] = new int[size];
			mem2[i] = new int[size];
		}

		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				file >> s_temp >> i_temp;
				arr[i][j] = i_temp;
			}
		}
	} else if (choice == 2){
		srand(time(NULL));
		cout << "enter array size: ";
		cin >> size;
		arr = new int*[size];
		mem = new int*[size];
		mem2 = new int*[size];
		for (int i = 0; i < size; ++i){
			arr[i] = new int[size];
			mem[i] = new int[size];
			mem2[i] = new int[size];
		}

		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				if(rand() % 2 == 1)
					arr[i][j] = rand()%50;
				else
					arr[i][j] = -1 * rand()%50;
			}
		}

	}
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	memoize(arr, mem, mem2, size);	//O(N^3)

	int sum = 0, left, right, top, width;
	for (int i = 0; i < size; ++i)	//O(N^2)
	{
		for (int j = i; j < size; ++j)
		{
			if(mem[i][j] > sum){
				sum = mem[i][j];
				left = i;
				right = j;
				top = mem2[i][j];
				width = right - left + 1;
			}
		}
	}
	cout << endl;
	cout << "width = " << width << endl;
    cout << "Top right = (" << top << ", " <<  right << ")" << endl; 
    cout << "Bottom right = (" << top + width - 1 << ", " << right<< ")" << endl; 
    cout << "Sum is " << sum; 
	return 0;
}