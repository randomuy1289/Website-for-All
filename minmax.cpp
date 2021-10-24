#include <bits/stdc++.h>

#define rep(i,n) for(int (i)=0;(i)<(int)(n);++(i))

class Board{
  public:
  Board(){}
  ~Board(){}
  bool legalMoves();
  int evaluateBoard();
  int minimax(bool player); // true if player, false if opponent
  void nextBestMove();
  private:
    char board[3][3] = 
    {{'o','-','x'},
     {'x','-','x'},
     {'-','o','o'}
    };
    char player = 'x';
    char opponent = 'o';
};

bool Board::legalMoves(){
  rep(i, 3){
    rep(j, 3){
      if(board[i][j] == '-')
        return true;
    }
  }
  return false;
}

int Board::evaluateBoard(){
  // checking for horizontal victories
  rep(i, 3){
    if(board[i][0] == board[i][1] && board[i][1] == board[i][2]){
      if(board[i][0] == player)
        return 10;
      else
        return -10;
    }
  }

  // checking for vertical victories
  rep(i, 3){
    if(board[0][i] == board[1][i] && board[1][i] == board[2][i]){
      if(board[0][i] == player)
        return 10;
      else
        return -10;
    }
  }
  // checking for diagonal victories
  if(board[0][0] == board[1][1] && board[1][1] == board[2][2]){
    if(board[0][0] == player)
      return 10;
    else
      return -10;
  }
  if(board[0][2] == board[1][1] && board[1][1] == board[2][0]){
    if(board[0][2] == player)
      return 10;
    else
      return -10;
  }

  return 0;
}

int Board::minimax(bool player){

  // check if game is over
  int score = evaluateBoard();
  if(score == 10)
    return score;
  if(score == -10)
    return score;

  // check if any legal moves are left
  if(!legalMoves()){
    return 0;
  }

  // if player's turn
  if(player){
    int maxEval = -10000;

    rep(i, 3){

      rep(j, 3){

        if(board[i][j] == '-'){
          board[i][j] = player;
          maxEval = std::max(maxEval, minimax(!player));
          board[i][j] = '-'; // undo the move
        }
      }
    }

    return maxEval;
  }
  // if opponent's turn
  else{
    int minEval = 10000;
    rep(i, 3){
      rep(j, 3){
        if(board[i][j] == '-'){
          board[i][j] = opponent;
          minEval = std::min(minEval, minimax(!player));
          board[i][j] = '-'; // undo the move
        }
      }
    }

    return minEval;
  }

}

void Board::nextBestMove(){
  // assuming it is player's turn
  int maxEval = -10000;
  int row = -1, col = -1;
  int moveEVal;
  rep(i, 3){
    rep(j, 3){
      if(board[i][j] == '-'){
        board[i][j] = player;
        moveEVal = minimax(true);
        board[i][j] = '-';
        if(moveEVal > maxEval){
          row = i;
          col = j;
          maxEval = moveEVal;
        }
      }
    }
  }
  std::cout << "Next best move is " << row << " " << col << std::endl;

}

int main(){
  Board board;
  board.nextBestMove();
}
