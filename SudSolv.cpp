#include <iostream>
#include <vector>
#define pb push_back

using namespace std;
const int r = 9, c = 9;
vector<vector<int>> S(r, vector<int>(c));
void Display(){
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            if(j != c-1) cout<<S[i][j]<<" ";
            else cout<<S[i][j];
            if(j == 2 || j == 5) cout<<" ";
        }
        if(i != r-1) cout<<"\n";
        else cout<<"\n\n------------------------";
        if(i == 2 || i == 5) cout<<"\n";
    }
}
int main(){
    for(auto& Si : S) for(auto& Sij : Si) cin>>Sij;
    Display();
    return 0;
}