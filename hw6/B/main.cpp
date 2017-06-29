
#include <iostream>
#include <vector>


using namespace std;

int N;

vector<int> v;


bool isSafe(char *arrmt)
{
    //TODO: need to chk for EVERY PAIR, not only running sum.
    for (int j = 0; j < 11; ++j)
    {
        if (arrmt[j] == 'D')
        {
            for (int i = j+1; i < 11; i++)
            {
                if (arrmt[i] == 'D')
                {
                    //+2 is neccessary to transform from indeces to player #s
                    if (i+j+2 == 13)
                    {
                        return false;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }

        if (arrmt[j] == 'S')
        {
            for (int i = j+1; i < 11; i++)
            {
                if (arrmt[i] == 'S')
                {
                    //+2 is neccessary to transform from indeces to player #s
                    if (i+j+2 == 13)
                    {
                        return false;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }

        if (arrmt[j] == 'M')
        {
            for (int i = j+1; i < 11; i++)
            {
                if (arrmt[i] == 'M')
                {
                    //+2 is neccessary to transform from indeces to player #s
                    if (i+j+2 == 13)
                    {
                        return false;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }

    }

    return  true;


}

int solveNQUtil(char **board, int row, char *arrmt, int fillFactor )
{
    int i = 0;
    while (row < 11 && i<4 && (board[row][i] == 'G' || board[row][i] == 'D'
                       || board[row][i] == 'S' || board[row][i] == 'M') )
    {
        //todo:
        //1. recurrence ends after i ==3
        //2. manage carefully the arrmt and fillfactor for REC and while i<4.
        //"row" for "arrmt" actually works as a column.
        arrmt[row]  = board[row][i];
        fillFactor++;

        if (fillFactor < 11)
        {
            int processed = solveNQUtil(board, row+1, arrmt, fillFactor);
            if( processed == 0)
            {
                fillFactor--;
            }
        }
        else
        {
            if (isSafe(arrmt))
            {
                N++;
            }
            else
            {
                fillFactor--;
            }
        }

        i++;
    }


    return N;
}


int main()
{

    int t = 0;
    cin >> t;

    for (int k = 0; k < t; k++)
    {
        int n;
        char *arrmt = new char[11];

        char **board = new char *[11];
        cin.ignore();

        for (int i = 0; i < 11; i++)
        {
            board[i] = new char[4];
            string playerPos;
            int j = 0;
            getline(cin, playerPos);
            while (j < playerPos.length())
            {
                board[i][j] = playerPos[j];
                j++;
            }
        }


        for (int l = 0; l < 11; ++l)
        {
            int i = 0;
            while(i<4  )
            {
                cout<<board[l][i] << " ";
                i++;
            }
            cout << endl;
        }

        n = solveNQUtil(board, 0, arrmt, 0);
        delete[] arrmt;


        for (int i = 0; i < 11; i++)
        {
            delete[] board[i];
        }
        delete[] board;

        v.push_back(n);

    }

    cout << endl;
    for (int l = 0; l < v.size(); ++l)
    {
        cout << "Case #" << l + 1 << ": ";
        cout << v[l] << endl;

    }


    return 0;
}