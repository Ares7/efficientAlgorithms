
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int X;
int Y;
int AM;

int en = 0;
int statedN = 0;


typedef struct ans
{
    int ax;
    int ay;
    char arr_out[250][250];
} ans1;

vector<ans1> v;

vector<string> dict;

void revertHorizChanges(char **board, string backup, int i, int j, int k)
{
    //restore the state of cells
    for (int l = 0; l < k; ++l)
    {
        board[i][j + l] = backup[l];
    }
}

void revertVertChanges(char **board, string backup, int i, int j, int k)
{
    //restore the state of cells
    for (int l = 0; l < k; ++l)
    {
        board[i + l][j] = backup[l];
    }
}

bool solveNQUtil(char **board)
{

    /*
 1. start from first _ and proceed for every _.
 2. for every _ for every word try to put it:
    a: from top to bottom
    b. from left to right.
 3. always consider all words.
 4. make sure the word fits into the _ gaps up until +.
 5. if thw words firts in way a or b then go to the next _ and
    try to fit it as well, if its descendadnt fills too, then
    proceed to the next and so on,
    otw BACKTRACK: (try to go to left/right) or tra another word.
  6. if word detects there is the same symbol as it indends to put, proceed futher.
     otw, check a or b or another word.

 */
    int i, j, hasEmpty = 0;
    for (i = 0; i < Y; ++i)
    {
        for (j = 0; j < X; ++j)
        {
            //step 1.

            //perform seach on all symbols exc for +(give it a chance)
            // when we measure the length left or vertical we see _ then
            // we can try to put a word from the inital position.
            if (board[i][j] != '+' )
            {

                //figuring out the RIGHT gap length:
                int rightlen = 0;
                int ColPos = j;
                int eligible = 0;
                while (ColPos < X && board[i][ColPos] != '+')
                {
                    if (board[i][ColPos] == '_' )
                    {
                        eligible = 1;
                    }
                    ColPos++;
                }
                rightlen = ColPos - j;

                if (rightlen > 1 && eligible == 1)
                {
                    //step 3.
                    for (auto iter : dict)
                    {
                        //measure the length of every word in the Dict.
                        int wordlen = (iter.length());
                        string backup;

                        //step 4
                        if (rightlen == wordlen && (board[i][j] == iter.data()[0] || board[i][j] == '_'))
                        {
                            /*
                               1. save the existing chars of the board
                                  before overwriting them into backup.
                                  *if succ => call itself with params i, j
                                  and wait for false(put it later (bto-top check)
                                  of the fun)
                                  or true(put in the very end).
                                1a. if nested fun returned false, return the overwritten
                                    block to the previous state.
                                    cont with next word of same len or with
                                   bot direction or another _ posiition.
                                1b. if returned true cont with next position of _.
                               */
                            bool putWord = 1;
                            bool succPutWord = 0;

                            int k;
                            for (k = 0; k < wordlen; ++k)
                            {
                                if (board[i][j + k] == '_' || board[i][j + k] == iter.data()[k])
                                {
                                    backup += board[i][j + k];
                                    board[i][j + k] = iter.data()[k];
                                }
                                else
                                {
                                    putWord = 0;
                                    revertHorizChanges(board, backup, i, j, k);

                                    break;
                                }
                            }

                            if (putWord == 1)
                            {
                                //call this fun again.
                                succPutWord = solveNQUtil(board);
                                if (succPutWord == 1)
                                {
                                    return true;
                                }
                                else
                                {
                                    revertHorizChanges(board, backup, i, j, k);
                                    continue;
                                }
                            }


                        }

                    }

                    //reset stats for the Vertical chk.
                    eligible = 0;
                }


                //figuring out the VERTICAL gap length :

                int vertlen = 0;
                int RowPos = i;
                while (RowPos < Y && board[RowPos][j] != '+')
                {
                    if (board[RowPos][j] == '_' )
                    {
                        eligible = 1;
                    }
                    RowPos++;
                }
                vertlen = RowPos - i;

                if (vertlen > 1 && eligible == 1)
                {
                    //step 3.
                    for (auto iter : dict)
                    {
                        //measure the length of every word in the Dict.
                        int wordlen = (iter.length());
                        string backup;

                        //step 4
                        if (vertlen == wordlen && (board[i][j] == iter.data()[0] || board[i][j] == '_'))
                        {
                            bool putWord = 1;
                            bool succPutWord = 0;

                            int k;
                            for (k = 0; k < wordlen; ++k)
                            {
                                //TODO: the problem is that once the begininng of the
                                // gap is filled with some other word, then this code fails to
                                // detect that the word
                                if (board[i + k][j] == '_' || board[i + k][j] == iter.data()[k])
                                {
                                    backup += board[i + k][j];
                                    board[i + k][j] = iter.data()[k];
                                }
                                else
                                {
                                    putWord = 0;
                                    revertVertChanges(board, backup, i, j, k);

                                    break;
                                }
                            }

                            if (putWord == 1)
                            {
                                //call this fun again.
                                succPutWord = solveNQUtil(board);
                                if (succPutWord == 1)
                                {
                                    return true;
                                }
                                else
                                {
                                    revertVertChanges(board, backup, i, j, k);
                                    continue;
                                }
                            }


                        }

                    }


                }

            }
        }

    }

    for (int l = 0; l < Y; ++l)
    {
        for (int k = 0; k < X; ++k)
        {
            if(board[l][k] == '_' )
            {
                hasEmpty = 1;
            }
        }
    }

    if (i == Y  && j == X && hasEmpty == 0)
    {
        return true;
    }

    // in case for every _ position no
    // suitable words were found in both
    // RIGHT and VERTICAL directions.
    return false;
}


int main()
{

    int t = 0;
    cin >> t;

    for (int k = 0; k < t; k++)
    {
        int x, y, am;
        cin >> x >> y >> am;
        X = x;
        Y = y;
        AM = am;

        ans aw;
        aw.ax = x;
        aw.ay = y;


        char **board = new char *[y];

        for (int i = 0; i < y; i++)
        {
            board[i] = new char[x];
            for (int j = 0; j < x; j++)
            {
                cin >> board[i][j];
            }
        }

        string word;
        for (int l = 0; l < am; ++l)
        {
            cin >> word;
            dict.push_back(word);
        }
        sort(dict.begin(), dict.end());
//        cout<<endl;
//        for (int m = 0; m < dict.size(); ++m)
//        {
//            cout<<dict[m].data()<<endl;
//        }



        solveNQUtil(board);

        for (int i = 0; i < y; i++)
        {
            for (int j = 0; j < x; j++)
            {
                aw.arr_out[i][j] = board[i][j];
            }

            delete[] board[i];
        }
        delete[] board;

        v.push_back(aw);

    }

    cout << endl;
    for (int l = 0; l < v.size(); ++l)
    {
        cout << "Case #" << l + 1 << ":";
        cout << endl;


        for (int i = 0; i < v[l].ay; i++)
        {
            for (int j = 0; j < v[l].ax; j++)
            {
                cout << v[l].arr_out[i][j];

            }


            cout << endl;
        }


    }


    return 0;
}