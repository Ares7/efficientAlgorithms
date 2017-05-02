#include <iostream>
#include <vector>

using namespace std;

//performing insertion sort of every member(i) within each team for every team(j):
void teamsSort(int teams[][5], int n) {
    for (int j = 0; j < n; ++j)
    {
        for (int i = 1; i < 5; ++i)
        {
            int max = teams[j][i];
            int k = i - 1;

            while (k >= 0 && max > teams[j][k])
            {
                teams[j][k + 1] = teams[j][k];
                k--;
            }
            teams[j][k + 1] = max;
        }
    }

}

void swapRows(int teams[][5], int pos1, int pos2)
{
    for (int i = 0; i < 5; ++i)
    {
        int tmp = teams[pos1][i];
        teams[pos1][i] = teams[pos2][i];
        teams[pos2][i] = tmp;
    }
}
void teamPrioritizer(int teams[][5], int n, int startRow) {

    for (int k = startRow; k < n; ++k)
    {
        int max = k;

        for (int j = k + 1; j < n; ++j)
        {
            if (teams[j][0] == teams[k][0])
            {
                //checking only two specific rows
                int startCol=1;
                while(startCol<5)
                {
                    if(teams[j][startCol] > teams[k][startCol] )
                    {
                        swapRows(teams, k, j);
                        break;
                    }
                    if(teams[j][startCol] == teams[k][startCol] )
                    {
                        startCol++;
                    }
                    else
                    {
                        break;
                    }


                }
            }

            if (teams[j][0] == teams[max][0])
            {


                //checking only two specific rows
                int startCol=1;
                while(startCol<5)
                {
                    if(teams[j][startCol] > teams[max][startCol] )
                    {
                        swapRows(teams, max, j);
                        break;
                    }
                    if(teams[j][startCol] == teams[max][startCol] )
                    {
                        startCol++;
                    }
                    else
                    {
                        break;
                    }


                }
            }
            if (teams[j][0] > teams[max][0])
            {
                max = j;
            }


        }
        if (max != k)
        {
            swapRows(teams, k, max);
        }

    }


}

int main() {
    std::ios::sync_with_stdio(false);
//
    int t = 1;
    int n = 3;

    cin >> t;
    //cin.ignore();

    struct Cases {
        int num;
        int teams[1000][5];
    };

    vector<Cases> v;
/*
    2
    3
    1 2 5 4 3
    2 5 3 5 8
    1 1 1 1 1

    5
    8 4 3 3 2
    9 3 3 2 1
    8 4 4 3 2
    2 3 4 5 8
    2 5 3 5 8

    1
    3
    6 8 7 1 1
    1 10 10 4 8
    5 8 10 10 8

 */

    for (int k = 1; k <= t; ++k)
    {
        cin >> n;
        Cases t;
        t.num = n;
        for (int i = 0; i < n; ++i)
        {
            cin >> t.teams[i][0] >> t.teams[i][1] >> t.teams[i][2] >> t.teams[i][3] >> t.teams[i][4];
        }
        v.push_back(t);
        cin.ignore();
    }


    for (int l = 0; l < t; ++l)
    {
        teamsSort(v[l].teams, v[l].num);
        teamPrioritizer(v[l].teams, v[l].num,  0);

        cout << "Case #" << l + 1 << ":" << endl;
        for (int i = 0; i < v[l].num; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                cout << v[l].teams[i][j]<< " " ;
            }

            cout << endl;
        }
    }

    return 0;
}
