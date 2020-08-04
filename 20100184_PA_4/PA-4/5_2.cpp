// Program to find maximum sum subarray in a given 2D array 
#include <stdio.h> 
#include <string.h> 
#include <limits.h> 
#define ROW 8
#define COL 8 
#include <fstream>
#include <iostream>
using namespace std;
// Implementation of Kadane's algorithm for 1D array. The function  
// returns the maximum sum and stores starting and ending indexes of the  
// maximum sum subarray at addresses pointed by start and finish pointers  
// respectively. 
int kadane(int *arr, int *start, int *finish, int n, int k) //O(N^2)
{ 
    int j, max, total = 0; 
    *start = 0;
    *finish = k;
    for (int i = 0; i < n-k; i++) 
    { 
        max = arr[i]; 
  
        for (j = 1; j <= k; j++) 
        { 
            max += arr[i+j];
        } 
        if (max > total){ 
            total = max; 
            *start = i;
            *finish = i+k;
        }
    } 
    return total;
} 

  
void findMaxSum(int M[][COL]) 
{ 
    // Variables to store the final output 
    int maxSum = INT_MIN, finalLeft, finalRight, finalTop, finalBottom; 
  
    int left, right, i; 
    int temp[ROW], sum, start, finish; 
  
    // Set the left column 
    for (left = 0; left < COL; ++left) //O(N^4)
    { 
        // Initialize all elements of temp as 0 
        memset(temp, 0, sizeof(temp)); 
  
        // Set the right column for the left column set by outer loop 
        for (right = left; right < COL; ++right)  //O(N^3)
        { 
           // Calculate sum between current left and right for every row 'i' 
            for (i = 0; i < ROW; ++i) 
                temp[i] += M[i][right]; 
  
            // Find the maximum sum subarray in temp[]. The kadane()  
            // function also sets values of start and finish.  So 'sum' is  
            // sum of rectangle between (start, left) and (finish, right)  
            //  which is the maximum sum with boundary columns strictly as 
            //  left and right. 
            sum = kadane(temp, &start, &finish, ROW, right-left); //O(N^2)
  
            // Compare sum with maximum sum so far. If sum is more, then  
            // update maxSum and other output values 
            if (sum > maxSum) 
            { 
                maxSum = sum; 
                finalLeft = left; 
                finalRight = right; 
                finalTop = start; 
                finalBottom = finish; 
            } 
        } 
    } 
    cout << "width = " << finalBottom - finalTop + 1<< endl;
    cout << "Top right = " << finalTop << " " <<  finalRight << endl; 
    cout << "Bottom right = " << finalBottom << " " << finalRight << endl; 
    cout << "Sum is " << maxSum; 
} 
  
// Driver program to test above functions 
int main() 
{ 
    ifstream file;
    string s_temp;
    int size, i_temp;
    char buff[256] = "stuff.txt";

    int arr[ROW][COL];

    file.open(buff);
    file >> s_temp >> size;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            file >> s_temp >> i_temp;
            arr[i][j] = i_temp;
        }
    } 
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            cout << arr[i][j] << " ";
        }
        cout  << endl;
    }
  
    findMaxSum(arr); 
  
    return 0; 
} 