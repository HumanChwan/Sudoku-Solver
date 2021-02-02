#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#define pb push_back
#define fl(i, a, b) for(int i = a; i < b; ++i)

using namespace std;

const int r = 9, c = 9;
int S[r][c];
vector < int > b_i;
set < int > row, column, square;
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
}
void mod_init(int rm){
    b_i.erase(remove(b_i.begin(), b_i.end(), rm), b_i.end());
    return;
}
void row_init(int rn){
    row.clear();
    fl(i, 0, r) row.insert(S[rn][i]);
    return;
}
void column_init(int cn){
    column.clear();
    fl(i, 0, r) column.insert(S[i][cn]);
    return;
}
void square_init(int sn){
    square.clear();
    int row_index = ((sn/10)/3) * 3;
    int column_index = ((sn%10)/3) * 3;
    fl(i, 0, r/3) fl(j, 0, c/3) square.insert(S[row_index + i][column_index + j]);
    return;
}
void Solve(){
    void brute_solve();
    void num_solve();
    void eliminator_solve();
    blank_init();
    int temp = b_i.size();
    while(true){
        temp = b_i.size();
        brute_solve();
        if(!b_i.size()) break;
        num_solve();
        if(!b_i.size()) break;
        if(temp == b_i.size())
            eliminator_solve();
        if(temp == b_i.size() || !b_i.size()) break;
    }
}
void brute_solve(){

    while(true){
        int temp = b_i.size();
        fl(i, 0, b_i.size()){
            row_init(b_i[i]/10);
            column_init(b_i[i]%10);
            square_init(b_i[i]);
            vector < int > netcnt{1, 2, 3, 4, 5, 6, 7, 8, 9};
            for(auto it = netcnt.begin(); it != netcnt.end(); it++){
                if(binary_search(row.begin(), row.end(), *it)) netcnt.erase(it), --it;
            }
            for(auto it = netcnt.begin(); it != netcnt.end(); it++){
                if(binary_search(column.begin(), column.end(), *it)) netcnt.erase(it), --it;
            }
            for(auto it = netcnt.begin(); it != netcnt.end(); it++){
                if(binary_search(square.begin(), square.end(), *it)) netcnt.erase(it), --it;
            }
            if(netcnt.size() == 1){
                S[b_i[i]/10][b_i[i]%10] = netcnt[0];
                mod_init(b_i[i]);
                if(!b_i.size()) return;
            }
        }
        if(temp == b_i.size()) return;
    }
}
void num_solve(){
    while(true){
        int temp = b_i.size();
        fl(i, 1, 10){
            fl(j, 0 , 9){
                square_init((j/3)*30 + (j%3)*3);
                if(!binary_search(square.begin(), square.end(), i)){
                    bool ra[3] = {false, false, false}, ca[3] = {false, false, false};

                    row_init((j/3)*3);
                    if(!binary_search(row.begin(), row.end(), i)) ra[0] = true;
                    row_init((j/3)*3 + 1);
                    if(!binary_search(row.begin(), row.end(), i)) ra[1] = true;
                    row_init((j/3)*3 + 2);
                    if(!binary_search(row.begin(), row.end(), i)) ra[2] = true;

                    column_init((j%3)*3);
                    if(!binary_search(column.begin(), column.end(), i)) ca[0] = true;
                    column_init((j%3)*3 + 1);
                    if(!binary_search(column.begin(), column.end(), i)) ca[1] = true;
                    column_init((j%3)*3 + 2);
                    if(!binary_search(column.begin(), column.end(), i)) ca[2] = true;

                    int ct = 0, fill;
                    fl(k, 0, 3){
                        if(!ra[k]) continue;
                        fl(l, 0, 3){
                            if(ca[l] && !S[(j/3)*3 + k][(j%3)*3 + l]){
                                ct++;
                                if(ct > 1) break;
                                fill = ((j/3)*3 + k)*10 + ((j%3)*3 + l);
                            }
                        }
                        if(ct > 1) break;
                    }
                    if(ct == 1){
                        S[fill/10][fill%10] = i;
                        mod_init(fill);
                        if(!b_i.size()) return;
                    }
                }
            }
        }
        if(temp == b_i.size()) return;
    }
}
void eliminator_solve(){
    while(true){
        int temp = b_i.size();
        fl(i, 0, 9){
            vector < int > net{1, 2, 3, 4, 5, 6, 7, 8, 9};
            row_init(i);
            for(auto it = net.begin(); it != net.end(); it++){
                if(binary_search(row.begin(), row.end(), *it)) net.erase(it), --it;
            }
            for(auto it = net.begin(); it != net.end(); it++){
                int ct = 0, fill;
                fl(j, 0, 9){
                    if(!S[i][j]){
                        column_init(j);
                        if(binary_search(column.begin(), column.end(), *it)) continue;
                        square_init(i*10 + j);
                        if(binary_search(square.begin(), square.end(), *it)) continue;
                        ct++;
                        fill = i*10 + j;
                    }
                }
                if(ct == 1){
                    S[fill/10][fill%10] = *it;
                    mod_init(fill);
                    if(!b_i.size()) return;
                }
            }
        }
        fl(j, 0, 9){
            vector < int > net{1, 2, 3, 4, 5, 6, 7, 8, 9};
            column_init(j);
            for(auto it = net.begin(); it != net.end(); it++){
                if(binary_search(column.begin(), column.end(), *it)) net.erase(it), --it;
            }
            for(auto it = net.begin(); it != net.end(); it++){
                int ct = 0, fill;
                fl(i, 0, 9){
                    if(!S[i][j]){
                        row_init(i);
                        if(binary_search(row.begin(), row.end(), *it)) continue;
                        square_init(i*10 + j);
                        if(binary_search(square.begin(), square.end(), *it)) continue;
                        ct++;
                        fill = i*10 + j;
                    }
                }
                if(ct == 1){
                    S[fill/10][fill%10] = *it;
                    mod_init(fill);
                    if(!b_i.size()) return;
                }
            }
        }
        if(temp == b_i.size()) return;
    }
}

void probable_solve(){
    
}


int main(){
    Input();
    Display();
    blank_init();
    Solve();
    if(b_i.size())
        probable_solve();
    if(b_i.size())
        cout << "Has either more than one solution or no solution\n"; 
    Display();
    return 0;
}
