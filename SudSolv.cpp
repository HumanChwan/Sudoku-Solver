#include <iostream>
#include <vector>
#define pb push_back

const int r = 9, c = 9;
std :: vector<std :: vector<int>> S(r, std :: vector<int>(c));
void Display(){
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            if(j != c-1) std :: cout << S[i][j] << " ";
            else std :: cout << S[i][j];
            if(j == 2 || j == 5) std :: cout << " ";
        }
        if(i != r-1) std :: cout << "\n";
        else std :: cout << "\n------------------------";
        if(i == 2 || i == 5) std :: cout << "\n";
    }
}
int main(){
    for(auto& Si : S) for(auto& Sij : Si) std :: cin >> Sij;
    Display();
    return 0;
}