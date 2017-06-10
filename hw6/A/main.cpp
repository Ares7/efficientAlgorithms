//Partially adapted from www.geeksforgeeks.org
#define N 4
#include<stdio.h>

#include <iostream>

using namespace std;

//int N;
int en = 0;
int statedN = 0;
void printSolution(char board[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf(" %d ", board[i][j]);
        printf("\n");
    }
}

bool isSafe(char board[N][N], int row, int col)
{
    int i, j;


    /* Check this row on left side */
    for (i = 0; i < col; i++)
        if (board[row][i]== '1' || board[row][i] == 'x')
            return false;

    /* Check this row on right side */
    for (i = col; i < N; i++)
        if (board[row][i]== '1' || board[row][i] == 'x')
            return false;

    /* Check upper diagonal on left side */
    for (i=row, j=col; i>=0 && j>=0; i--, j--)
        if (board[i][j] == '1' || board[row][i] == 'x')
            return false;

    /* Check lower diagonal on left side */
    for (i=row, j=col; j>=0 && i<N; i++, j--)
        if (board[i][j] == '1' || board[row][i] == 'x')
            return false;

    //chk the presence of a permanent node of the right side:

    /* Check upper diagonal on right side */
    for (i=row, j=col; i>=0 && j<N; i--, j++)
        if (board[i][j] == '1' || board[row][i] == 'x')
            return false;

    /* Check lower diagonal on right side */
    for (i=row, j=col; j>N && i<N; i++, j++)
        if (board[i][j] == '1' || board[row][i] == 'x')
            return false;


    return true;
}

/* A recursive utility function to solve N
   Queen problem */
bool solveNQUtil(char board[N][N], int col)
{
    /* base case: If all queens are placed
      then return true */
    if (col >= N)
        return true;

    /* Consider this column and try placing
       this queen in all rows one by one */
    for (int i = 0; i < N; i++)
    {

        if ( isSafe(board, i, col) )
        {
            /* Place this queen in board[i][col] */
            board[i][col] = '1';
            statedN++;
            /* recur to place rest of the queens */
            if ( solveNQUtil(board, col + 1) )
                return true;

            /* If placing queen in board[i][col]
               doesn't lead to a solution, then
               remove queen from board[i][col] */
            board[i][col] = '0'; // BACKTRACK
            statedN--;
        }
    }

    /* If queen can not be place in any row in
       this colum col  then return false */
    if(statedN + en == N)
    {
        return true;
    }
    return false;
}


// driver program to test above function
int main()
{

    //TODO: do we have to chk for top and bottom for x?
    int t = 0;
    cin>>t;

    for (int k = 0; k<t; k++)
    {
        int n;
        cin >> n;
        //N = n;
        char board[N][N] ;


        int inpt;


        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> inpt;
                if (inpt == 'x')
                    en++;
                board[i][j] = inpt;

            }
        }



        if ( solveNQUtil(board, 0) == false )
        {
            cout<<"Solution does not exist";
            return false;
        }
        else
        {
            printSolution(board);
        }

    }






    return 0;
}


////
////  main.cpp
////  A
////
////  Created by Sergey Nasonov on 08/06/2017.
////  Copyright © 2017 Sergey Nasonov. All rights reserved.
////
//
////15: 285053
//
//#include <iostream>
//
//using namespace std;
//
//int main(int argc, const char * argv[]) {
//    // insert code here...
//
//    int t = 0;
//    cin>>t;
//    for (int k = 0; k<t; k++)
//    {
//        int n;
//        char arr[ 15 ][ 15 ];
//        cin>> n;
//
//        for (int i = 0; i<n; i++)
//        {
//            for (int j = 0; j<n; j++)
//            {
//                cin>> arr[i][j];
//
//            }
//        }
//
//        //run the entire array again bc inpur overwrides the markings.
//        for (int i = 0; i<n; i++)
//        {
//            for (int j = 0; j < n; j++)
//            {
//                if(arr[i][j]=='x')
//                {
//                    //mark the row as filled:
//                    for (int r = 0; r<n; r++)
//                    {
//                        if(j != r  && arr[i][r]!='x')
//                            arr[i][r] = 'f';
//                    }
//
//                    //mark the col as filled:
//                    for (int c = 0; c<n; c++)
//                    {
//                        if(i != c  && arr[c][j]!='x')
//                            arr[c][j] = 'f';
//                    }
//
//                    //mark the diagonals.
//
//
//                }
//
//            }
//        }
//
//
//        for (int i = 0; i<n; i++)
//        {
//            for (int j = 0; j < n; j++)
//            {
//                cout << arr[i][j] << " ";
//            }
//            cout << endl;
//        }
//
//    }
//
//    return 0;
//}
