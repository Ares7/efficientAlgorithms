//Partially adapted from www.geeksforgeeks.org

#include <iostream>
#include <vector>

using namespace std;

int N;
int en = 0;
int statedN = 0;

typedef struct ans
{
    int an;
    string imp;
    char arr_out[15][15];
}ans1;

vector<ans1> v;


bool isInitSafe(char** board, int row, int col)
{
    int i, j;

    /* Check this row on left side */
    for (i = 0; i < col; i++)
        if ( board[row][i] == 'x' && board[row][col]=='x' )
            return false;

    /* Check this row on right side */
    for (i = col+1; i < N; i++)
        if ( board[row][i] == 'x' && board[row][col]=='x')
            return false;

    /* Check upper diagonal on left side */
    for (i=row-1, j=col-1; i>=0 && j>=0; i--, j--)
        if ( board[i][j] == 'x' && board[row][col]=='x')
            return false;

    /* Check lower diagonal on left side */
    for (i=row+1, j=col-1; j>=0 && i<N; i++, j--)
        if (board[i][j] == 'x' && board[row][col]=='x')
            return false;

    //chk the presence of a permanent node of the right side:

    /* Check upper diagonal on right side */
    for (i=row-1, j=col+1; i>=0 && j<N; i--, j++)
        if (board[i][j] == 'x' && board[row][col]=='x')
            return false;

    /* Check lower diagonal on right side */
    for (i=row+1, j=col+1; j<N && i<N; i++, j++)
        if ( board[i][j] == 'x' && board[row][col]=='x')
            return false;

    /* Check TOP and BOT*/
    for (i=0; i<N ; i++)
    {
        if (board[i][col] == 'x' && i!=row && board[row][col]=='x')
        {
            return false;
        }
    }

    return true;
}



bool isSafe(char** board, int row, int col)
{
    int i, j;

    //mode = 1 is operational
    // mode = 0 is inital check
    if(board[row][col] == 'x' )
        return true;
    /* Check this row on left side */
    for (i = 0; i < col; i++)
        if (board[row][i]== '1' || board[row][i] == 'x')
            return false;

    /* Check this row on right side */
    for (i = col+1; i < N; i++)
        if (board[row][i]== '1' || board[row][i] == 'x')
            return false;

    /* Check upper diagonal on left side */
    for (i=row-1, j=col-1; i>=0 && j>=0; i--, j--)
        if (board[i][j] == '1' || board[i][j] == 'x')
            return false;

    /* Check lower diagonal on left side */
    for (i=row+1, j=col-1; j>=0 && i<N; i++, j--)
        if (board[i][j] == '1' || board[i][j] == 'x')
            return false;

    //chk the presence of a permanent node of the right side:

    /* Check upper diagonal on right side */
    for (i=row-1, j=col+1; i>=0 && j<N; i--, j++)
        if (board[i][j] == '1' || board[i][j] == 'x')
            return false;

    /* Check lower diagonal on right side */
    for (i=row+1, j=col+1; j<N && i<N; i++, j++)
        if (board[i][j] == '1' || board[i][j] == 'x')
            return false;

    /* Check TOP and BOT*/
    for (i=0; i<N ; i++)
    {
        if (board[i][col] == 'x' && i!=row)
        {
            return false;
        }
    }

    return true;
}

bool solveNQUtil(char** board, int col)
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
            if(board[i][col] != 'x')
            {
                board[i][col] = '1';
                statedN++;
            }

            /* recur to place rest of the queens */
            if ( solveNQUtil(board, col + 1) )
                return true;

            /* If placing queen in board[i][col]
               doesn't lead to a solution, then
               remove queen from board[i][col]
               and continue with next i (row) */
            if(board[i][col] != 'x')
            {
                board[i][col] = '0';
                statedN--;
            }
             // BACKTRACK

        }
    }

    return false;
}


int main()
{

    int t = 0;
    cin>>t;

    for (int k = 0; k<t; k++)
    {
        int n;
        cin >> n;
        N = n;

        ans aw;
        aw.an = n;


        char** board = new char*[N];

        for (int i = 0; i < n; i++)
        {
            board[i] = new char [N];
            for (int j = 0; j < n; j++)
            {
                cin >> board[i][j];
                if (board[i][j] == 'x')
                    en++;
            }
        }

        if(n==2 || n==3)
        {
            aw.imp = "impossible";
            v.push_back(aw);
            continue;
        }

        for (int i = 0; i < n && aw.imp != "impossible"; i++)
        {
            for (int j = 0; j < n && aw.imp != "impossible"; j++)
            {
                if (isInitSafe(board, i, j) == false && n!=1)
                {
                    aw.imp = "impossible";
                    //v.push_back(aw);
                    //continue;
                }
            }
        }


        if ( solveNQUtil(board, 0) == false && n!=1 && aw.imp != "impossible")
        {
            aw.imp = "impossible";
        }
        else if (aw.imp != "impossible")
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    aw.arr_out[i][j] = board[i][j];
                }

                delete[] board[i];
            }
            delete[] board;

        }

        v.push_back(aw);

    }

    cout<<endl;
    for (int l = 0; l < v.size(); ++l)
    {
        cout<<"Case #" << l+1<<":";
        cout<<endl;

        if(v[l].imp.length()>0 )
        {
            cout<<v[l].imp<<endl;
        }
        else
        {
            for (int i = 0; i < v[l].an; i++)
            {
                for (int j = 0; j < v[l].an; j++)
                {
                    if(v[l].arr_out[i][j] == '1')
                    {
                        cout<<'x';
                    }
                    else if(v[l].arr_out[i][j] == '0')
                    {
                        cout<<'.';
                    }
                    else
                    {
                        cout<<v[l].arr_out[i][j];
                    }

                }


                cout<<endl;
            }

        }

    }


    return 0;
}