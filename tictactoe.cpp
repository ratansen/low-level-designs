#include<iostream>
#include<cstring>
#include<vector>
using namespace std;

class Move{

public:
    int player, i, j;
    Move(int player, int i, int j) : player(player), i(i), j(j) {};
};
class Board{
private:
    int grid[3][3];
    int currentPlayer;
    int n;

public:
    Board(){
        memset(grid, 0, sizeof(grid));
        // for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) grid[i][j] = 0;
        currentPlayer = 1;
        n = 3;
    }
    void updateMove(Move m){
        grid[m.i][m.j] = m.player == 1 ? 1 : -1;
        currentPlayer = currentPlayer % 2 + 1;
    }
    int getWinner(){
        int cnt = 0;

        for(int i = 0; i < 3; i++) cnt += grid[i][i];
        if(abs(cnt) == 3) return (cnt == 3 ? 1 : 2);

        cnt = 0;
        for(int i = 0; i < 3; i++) cnt += grid[2 - i][i];
        if(abs(cnt) == 3) return (cnt == 3 ? 1 : 2);

        for(int i = 0; i < 3; i++){
            int cnt = 0;
            for(int j = 0; j < 3; j++){
                cnt += grid[i][j];
            }
            if(abs(cnt) == 3) return (cnt == 3 ? 1 : 2);
        }
        for(int i = 0; i < 3; i++){
            int cnt = 0;
            for(int j = 0; j < 3; j++){
                cnt += grid[j][i];
            }
            if(abs(cnt) == 3) return (cnt == 3 ? 1 : 2);
        }
        return 0;
    }
    void showBoard(){
        cout << "\n Current Board State: \n";
        for(int i = 0; i < 3; i++){
            cout << "| ";
            for(int j = 0; j < 3; j++){
                if(grid[i][j] == 1) cout << grid[i][j];
                else if(grid[i][j] == -1) cout << 2;
                else cout << " ";
                cout << " | ";
            }
            cout << "\n| ";
            for(int j = 0; j < 3; j++){
                cout << "_" << " | ";
            }
            cout << endl;
        }
    }
};

class Game{
private:
    Board board;
    vector<Move>moves;

    void gameOver(int winner = 0){
        if(winner) cout << "Winner is: Player " << winner << endl;
        else cout << "Game Drawn\n";
    }
    void announceTurn(int player){
        cout << "\nIt's player " << player % 2 + 1 << "'s turn.\n";
    }
public:
    Game(){
        cout << "Game started\n";
    }
    void makeMove(Move m){
        cout << "Player " << m.player << " made a move at " << m.i << ", " << m.j << endl;
        board.updateMove(m);
        board.showBoard();
        moves.push_back(m);
        if(int winner = board.getWinner()) {gameOver(winner); return;};
        if(moves.size() == 9) {gameOver(); return;}
        announceTurn(m.player);
    }
    void showBoard(){
        board.showBoard();
    }
};


int main(){
    Game game;
    game.makeMove({1, 1, 1});
    game.makeMove({2, 1, 2});
    game.makeMove({1, 0, 0});
    game.makeMove({2, 0, 2});
    game.makeMove({1, 2, 2});
}   