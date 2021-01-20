#include <iostream>
#include <vector>
#include <algorithm>
#define pb push_back
#define fl(i, a, b) for(int i = a; i < b; ++i)

using namespace std;

const int r = 9, c = 9;
int S[r][c];
vector < int > b_i;
int row[9], column[9], square[9];
void Input(){
    fl(i, 0, r) fl(j, 0, c) cin >> S[i][j];
    return;
}
void Display(){
    fl(i, 0, r){
        fl(j, 0, c){
            if(j != c-1) cout << S[i][j] << " ";
            else cout << S[i][j];
            if(j == 2 || j == 5) cout << " ";
        }
        if(i != r-1) cout << "\n";
        else cout << "\n------------------------";
        if(i == 2 || i == 5) cout << "\n";
    }
    cout << endl;
    return;
}
void blank_init(){
    fl(i, 0, r){
        fl(j, 0, c){
            if(!S[i][j]) b_i.pb(i*10 + j);
        }
    }
    //fl(i, 0, b_i.size()) cout << b_i[i] << " ";
}
void mod_init(int rm){
    int start = 0;
    int ender = b_i.size();
    vector < int >::iterator it;
    it = b_i.begin();
    while(start <= ender){
        int mid = (start + ender)/2;
        if(b_i[mid] == rm){
            advance(it, mid);
            b_i.erase(it);
            break;
        }
        else if(b_i[mid] > rm){
            ender = mid;
        }
        else{
            start = mid + 1;
        }
    }
}
void row_init(int rn){
    fl(i, 0, r) row[i] = S[rn][i];
    return;
}
void column_init(int cn){
    fl(i, 0, c) column[i] = S[i][cn];
    return;
}
void square_init(int sn){
    int row_index = ((sn/10)/3) * 3;
    int column_index = ((sn%10)/3) * 3;
    fl(i, 0, r/3) fl(j, 0, c/3) square[(i*3) + j] = S[row_index + i][column_index + j];
    return;
}
void Solve(){
    void brute_solve();
    blank_init();
    brute_solve();
}
void brute_solve(){

    while(true){
        int temp = b_i.size();
        fl(i, 0, b_i.size()){
            row_init(b_i[i]/10);
            column_init(b_i[i]%10);
            square_init(b_i[i]);
            sort(row, row+r);
            sort(column, column+c);
            sort(square, square+(r/3 + c/3));
            vector < int > row_empty{1, 2, 3, 4, 5, 6, 7, 8, 9}, column_empty{1, 2, 3, 4, 5, 6, 7, 8, 9},
                    square_empty{1, 2, 3, 4, 5, 6, 7, 8, 9};
            //vector < int >::iterator it;
            for(auto it = row_empty.begin(); it != row_empty.end(); it++){
                if(binary_search(row, row+r, *it)) row_empty.erase(it), --it;
            }
            for(auto it = column_empty.begin(); it != column_empty.end(); it++){
                if(binary_search(column, column+c, *it)) column_empty.erase(it), --it;
            }
            for(auto it = square_empty.begin(); it != square_empty.end(); it++){
                if(binary_search(square, square+(r/3 + c/3), *it)) square_empty.erase(it), --it;
            }
            vector < int > temp, final;
            for(auto it = row_empty.begin(); it != row_empty.end(); ++it){
                if(binary_search(column_empty.begin(), column_empty.end(), *it)) temp.pb(*it);
            }
            for(auto it = temp.begin(); it != temp.end(); ++it){
                if(binary_search(square_empty.begin(), square_empty.end(), *it)) final.pb(*it);
            }

            if(final.size() == 1){
                S[b_i[i]/10][b_i[i]%10] = final[0];
                mod_init(b_i[i]);
                if(!b_i.size()) return;
            }
        }
        if(temp == b_i.size()) return;
    }
}
int main(){
    Input();
    //for(int i = 0; i < r; ++i) for(int j = 0; j < c; ++j) std :: cin >> S[i][j];
    Display();
    blank_init();
    Solve();
    Display();
    return 0;
}
