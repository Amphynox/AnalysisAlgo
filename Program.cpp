
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <stdlib.h>

using namespace std;

// temporary for developing
int memo[10][10];
int original_N, original_M { 0 };

int T(int n, int m, std::list<int>* A, std::list<int>* B){
    auto leftEndpointB = next((*B).begin(), original_M - m);
    auto leftEndpointA = next((*A).begin(), original_N - n);
    if (memo[n][m] != -1)
        return memo[n][m];
    if(n == 1 && m == 1) 
    {
        cout << "BASE CASE: n == 1 and m == 1" << endl;
        cout << "current value A = " << *leftEndpointA << endl;
        cout << "current value B = " << *leftEndpointB << endl;
        return *leftEndpointA + *leftEndpointB;
    }
    else if(n == 1) {
        // //extend A until n = m
        // for(int i = 1; i < m; i++)
        //     A.push_back(A.front());  
        //maxsum across pairs
        cout << "BASE CASE: n == 1" << endl;
        cout << *max_element(leftEndpointB, next((*B).begin(), m)) + *leftEndpointA << endl;
        return *max_element(leftEndpointB, next((*B).begin(), m)) + *leftEndpointA;
    }
    else if(m == 1) {
        // //extend B until m = n
        // int j = (*B).front();
        // for(int i = 0; i < n; i++){
        //     (*B).push_back(j);
        // }
        //maxsum across pairs
        cout << "BASE CASE: m == 1" << endl;
        cout << "n = "<< n << endl;
        // cout << *max_element(leftEndpointA, next((*A).begin(), n)) + *leftEndpointB << endl;
        cout << "left ep = " << *leftEndpointA << "max = " << *max_element(leftEndpointA, next((*A).begin(), n)) << endl;
        return *max_element(leftEndpointA, next((*A).begin(), n)) + *leftEndpointB;//*max_element((*A).begin(), next((*A).begin(), n)) + (*B).front();
    }
    else {
        int extendA = T(n, m-1, A, B);
        int keepAB = T(n-1, m-1, A, B);
        int extendB = T(n-1, m, A, B);
        memo[n][m] = min(extendA, min(keepAB, extendB));
        if (memo[n][m] == keepAB)
            puts("Keep same length");
        else if (memo[n][m] == extendA)
        {
            (*A).insert(leftEndpointA, *leftEndpointA);
            puts("Extend A");
        }
        else
        {
            (*B).insert(leftEndpointB, *leftEndpointB);
            puts("extend B");
        }
        int leftmost_sum = *leftEndpointA + *leftEndpointB;
        if (leftmost_sum > memo[n][m])
            memo[n][m] = leftmost_sum;
        return memo[n][m];
    }
}
void Wrapper(int n, int m) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            memo[i][j] = -1;
}
//get size input (line 1 of input file)
void getInput(int *size1, int *size2, fstream *mFile){
    *mFile >> *size1 >> *size2;
}

//get array input (lines 2 nd 3 of input file)
void getInput(int size, std::list<int> *mList, fstream *mFile){
    for(int i = 0; i < size; i++) {
        int j;
        *mFile >> j;
        mList->push_back(j);
    }   
}

void printOutput(std::list<int> A, std::list<int> B) {
    cout << endl << "A: ";
    for (int a_value : A) {
        cout << a_value << " ";
    }
    cout << endl << "B: ";
    for (int b_value : B) {
        cout << b_value << " ";
    }
    cout << endl << endl;
}

int main()
{   
    int n, m;
    list<int> A, B;
    fstream mFile; 
    
    mFile.open("input.txt");
    getInput(&n, &m, &mFile);
    getInput(n, &A, &mFile);
    getInput(m, &B, &mFile);
    mFile.close();
    original_M = m;
    original_N = n;
    Wrapper(n, m);
    printOutput(A, B);
    cout << T(n, m, &A, &B) << endl;
    printOutput(A, B);
    // cout<< "n = " << n << "\nm = " << m << "\nA = " << (*A).back() << "\nB = " << (*B).back() << endl;
}