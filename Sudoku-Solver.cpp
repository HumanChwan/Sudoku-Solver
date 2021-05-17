#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

const int R = 9, C = 9, SQ = 9, SET = 9, SQR = 3, SQC = 3;
vector<vector<int>> Board(R, vector<int>(C));
int Empty;
vector<vector<bool>> NUMS_EXIST;
vector<vector<bool>> NUMR_EXIST;
vector<vector<bool>> NUMC_EXIST;

void InputFromFile() {
    ifstream read;
    read.open("board.txt");
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            read >> Board[i][j];
        }
    }
    read.close();
    return;
}

void helpABC() {
    for (int i = 1; i <= SET; ++i) {
        cout << i << ". " << (char)(i - 1 + 'a') << endl;
    }
}

void InputFEN() {
    string FEN;
    helpABC();
    cout << "Enter FEN Notation representing each number as their index in "
            "English alphabets: \n\t--->";
    fflush(stdin);
    cin >> FEN;
    vector<string> ROWS(R);
    int r = 0;
    int init = 0;
    int rLength = 0;
    for (int i = 0; i < FEN.length(); ++i) {
        if (FEN[i] == '/') {
            ROWS[r] = FEN.substr(init, rLength);
            init = i + 1;
            rLength = 0;
            r++;
        } else {
            rLength++;
        }
    }
    ROWS[r] = FEN.substr(init, rLength);
    for (int i = 0; i < R; ++i) {
        int k = 0;
        for (int x : ROWS[i]) {
            if ('1' <= x && x <= '9') {
                k += (int)(x - '0');
            } else {
                Board[i][k] = (int)(x - 'a') + 1;
                k++;
            }
        }
    }
}

bool IncludedIn(string choices, char choice) {
    for (char x : choices) {
        if (choice == x) return true;
    }
    return false;
}

void Input() {
    cout << "\t\tYo!\n";
    cout << "Select Input Method: \n";
    cout << "   1. From [T]ext File\n";
    cout << "   2. From [F]EN Notation\n\n";
    cout << "Enter your choice: ";
    char choice;
    cin >> choice;
    if (IncludedIn("tT1", choice)) {
        InputFromFile();
    } else {
        InputFEN();
    }
}

void Display() {
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C - 1; ++j) {
            cout << Board[i][j] << " ";
            if (j == SQC - 1 || j == 2 * SQC - 1) cout << " ";
        }
        cout << Board[i][C - 1];
        if (i != R - 1)
            cout << "\n";
        else
            cout << "\n------------------------";
        if (i == SQR - 1 || i == 2 * SQR - 1) cout << "\n";
    }
    cout << endl;
    return;
}

int getSquareIndex(int i, int j) { return (i / SQR) * SQR + (j / SQC); }

void initialize_possiblility() {
    NUMR_EXIST.clear();
    NUMR_EXIST.resize(R, vector<bool>(SET));
    NUMC_EXIST.clear();
    NUMC_EXIST.resize(C, vector<bool>(SET));
    NUMS_EXIST.clear();
    NUMS_EXIST.resize(SQ, vector<bool>(SET));
    Empty = 0;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (Board[i][j]) {
                NUMR_EXIST[i][Board[i][j] - 1] = true;
                NUMC_EXIST[j][Board[i][j] - 1] = true;
                NUMS_EXIST[getSquareIndex(i, j)][Board[i][j] - 1] = true;
            } else {
                Empty++;
            }
        }
    }
}

void update_board(int i, int j, int Inference) {
    // Board Update
    Board[i][j] = Inference;
    // Empty var update
    Empty--;

    // Updating Exist Ref. vectors
    // Updating NUMR_EXIST
    NUMR_EXIST[i][Inference - 1] = true;

    // Updating NUMC_EXIST
    NUMC_EXIST[j][Inference - 1] = true;

    // Updating NUMS_EXIST
    NUMS_EXIST[getSquareIndex(i, j)][Inference - 1] = true;
}

bool PossibleAt(int i, int j, int entry) {
    return !(NUMR_EXIST[i][entry - 1] || NUMC_EXIST[j][entry - 1] ||
             NUMS_EXIST[getSquareIndex(i, j)][entry - 1]);
}

void restricted_solve() {
    int StartEmpty = Empty;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (Board[i][j]) continue;
            bool willFill = false;
            int finalEntry;
            for (int entry = 1; entry <= SET; ++entry) {
                if (PossibleAt(i, j, entry)) {
                    if (willFill) {
                        willFill = false;
                        break;
                    }
                    willFill = true;
                    finalEntry = entry;
                }
            }
            if (willFill) {
                update_board(i, j, finalEntry);
            }
        }
    }
    if (StartEmpty == Empty || !Empty)
        return;
    else
        restricted_solve();
}

void possibility_eliminator_solve() {
    int StartEmpty = Empty;
    for (int i = 0; i < R; ++i) {
        for (int NUM = 1; NUM <= SET; ++NUM) {
            if (NUMR_EXIST[i][NUM - 1]) continue;
            bool willFill = false;
            int y;
            for (int j = 0; j < C; ++j) {
                if (Board[i][j]) continue;
                if (PossibleAt(i, j, NUM)) {
                    if (willFill) {
                        willFill = false;
                        break;
                    }
                    willFill = true;
                    y = j;
                }
            }
            if (willFill) {
                update_board(i, y, NUM);
            }
        }
    }
    for (int j = 0; j < C; ++j) {
        for (int NUM = 1; NUM <= SET; ++NUM) {
            if (NUMC_EXIST[j][NUM - 1]) continue;
            bool willFill = false;
            int x;
            for (int i = 0; i < R; ++i) {
                if (Board[i][j]) continue;
                if (PossibleAt(i, j, NUM)) {
                    if (willFill) {
                        willFill = false;
                        break;
                    }
                    willFill = true;
                    x = i;
                }
            }
            if (willFill) {
                update_board(x, j, NUM);
            }
        }
    }
    for (int SquareIndex = 0; SquareIndex < SQ; ++SquareIndex) {
        for (int NUM = 1; NUM <= SET; ++NUM) {
            if (NUMS_EXIST[SquareIndex][NUM - 1]) continue;
            int count_possibilities = 0;
            int x, y;
            int rowF = (SquareIndex / SQC) * SQR;
            int colF = (SquareIndex % SQC) * SQC;
            for (int i = rowF; i < rowF + SQR; i++) {
                for (int j = colF; j < colF + SQC; ++j) {
                    if (Board[i][j]) continue;
                    if (PossibleAt(i, j, NUM)) {
                        count_possibilities++;
                        x = i;
                        y = j;
                        if (count_possibilities == 2) break;
                    }
                }
                if (count_possibilities == 2) break;
            }
            if (count_possibilities == 1) {
                update_board(x, y, NUM);
            }
        }
    }
    if (StartEmpty == Empty || !Empty)
        return;
    else
        possibility_eliminator_solve();
}

bool finalCheck() {
    for (int i = 0; i < R; ++i) {
        vector<bool> NUM(SET);
        for (int j = 0; j < C; ++j) {
            if (!Board[i][j] || NUM[Board[i][j] - 1]) return false;
            NUM[Board[i][j] - 1] = true;
        }
    }
    for (int i = 0; i < C; ++i) {
        vector<bool> NUM(SET);
        for (int j = 0; j < R; ++j) {
            if (!Board[j][i] || NUM[Board[j][i] - 1]) return false;
            NUM[Board[j][i] - 1] = true;
        }
    }
    for (int SquareIndex = 0; SquareIndex < SQ; ++SquareIndex) {
        int rowF = (SquareIndex / SQC) * SQR;
        int colF = (SquareIndex % SQC) * SQC;
        vector<bool> NUM(SET);
        for (int i = rowF; i < rowF + SQR; ++i) {
            for (int j = colF; j < SQC + colF; ++j) {
                if (!Board[i][j] || NUM[Board[i][j] - 1]) return false;
                NUM[Board[i][j] - 1] = true;
            }
        }
    }
    return true;
}

void backtrack_solve() {
    void Solve();
    vector<vector<int>> BoardHist;
    BoardHist = Board;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (Board[i][j]) continue;
            int count = 0;
            vector<int> POSS;
            for (int NUM = 1; NUM <= SET; ++NUM) {
                if (PossibleAt(i, j, NUM)) {
                    count++;
                    POSS.push_back(NUM);
                }
                if (count > 2) break;
            }
            if (count > 2) continue;
            for (int x : POSS) {
                update_board(i, j, x);
                Solve();
                if (!Empty) return;
                Board = BoardHist;
                initialize_possiblility();
            }
        }
    }
}

bool failCase() {
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (Board[i][j]) continue;
            bool atleastOne = false;
            for (int NUM = 1; NUM <= SET; ++NUM) {
                if (PossibleAt(i, j, NUM)) {
                    atleastOne = true;
                    break;
                }
            }
            if (!atleastOne) return true;
        }
    }
    return false;
}

void Solve() {
    if (!Empty || failCase()) return;
    int StartEmpty = Empty;
    restricted_solve();
    if (!Empty) return;
    possibility_eliminator_solve();
    if (!Empty) return;
    if (StartEmpty == Empty) {
        backtrack_solve();
    } else
        Solve();
}

int main() {
    Input();
    Display();
    initialize_possiblility();
    Solve();
    if (!Empty) {
        cout << "Solved!!\n";
    } else {
        cout << ":(\n";
    }
    Display();
}