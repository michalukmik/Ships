#include <iostream>
#include <vector>

using namespace std;

class pole{
private:


public:



};

int main()
{

int tab[9][9];
for(int i=0;i<9;i++)
    for(int j=0;j<9;j++)
    {
    tab[i][j]=0;
    }
for(int i=6;i<7;i++)
    for(int j=2;j<5;j++)
    {
    tab[i][j]=1;
    }

for(int i=0;i<9;i++)
{
    for(int j=0;j<9;j++)
    {
    if(tab[i][j]==0) cout << " . ";
    else if(tab[i][j]==1) cout << " X ";
    }
    cout << endl;
}


    return 0;
}
