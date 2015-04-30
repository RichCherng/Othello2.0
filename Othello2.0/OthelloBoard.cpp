#include "OthelloBoard.h"

using namespace std;

OthelloBoard::OthelloBoard() {
   for (int row = 0; row < BOARD_SIZE; row++) {
      for (int col = 0; col < BOARD_SIZE; col++) {
         mBoard[row][col] = Player::EMPTY;
      }
   }
   int strPos = 3, SdStrPos = 4;
   mBoard[(BOARD_SIZE / 2) - 1][BOARD_SIZE / 2] = Player::BLACK;
   mBoard[BOARD_SIZE / 2][(BOARD_SIZE / 2) - 1] = Player::BLACK;
   mBoard[(BOARD_SIZE / 2) - 1][(BOARD_SIZE / 2) - 1] = Player::WHITE;
   mBoard[BOARD_SIZE / 2][BOARD_SIZE / 2] = Player::WHITE;
   mNextPlayer = Player::BLACK;
}

void OthelloBoard::GetPossibleMoves(std::vector<OthelloMove *> *list) const {
   for (int row = 0; row < BOARD_SIZE; row++) {
      for (int col = 0; col < BOARD_SIZE; col++) {
         bool valid = false;
         if (mBoard[row][col] == Player::EMPTY) {
            for (int r = -1; r <= 1 && valid == false; r++) {
               for (int c = -1; c <= 1 && valid == false; c++) {
                  int bRow = row + r, bCol = col + c;
                  if (mBoard[bRow][bCol] == -mNextPlayer
                     && !(c == 0 && r == 0)) {
                     while (InBounds(bRow, bCol)
                        && mBoard[bRow][bCol] == -mNextPlayer
                        && mBoard[bRow][bCol] != Player::EMPTY) {
                        bRow += r;
                        bCol += c;
                        if (mBoard[bRow][bCol] == mNextPlayer
                           && InBounds(bRow, bCol)) {
                           (*list).push_back(new OthelloMove(row, col));
                           valid = true;
                           break;
                        }
                     }
                  }
               }
            }
         }
      }
   }
   if ((*list).size() == 0)
      (*list).push_back(new OthelloMove());
}

void OthelloBoard::ApplyMove(OthelloMove *move) {
   if (move->IsPass()) {
      mPassCount++;
      mHistory.push_back(move);
   }
   else {
      mPassCount = 0;
      mHistory.push_back(move);
      mValue += GetNextPlayer();
      mBoard[move->mRow][move->mCol] = GetNextPlayer();
      for (int r = -1; r <= 1; r++) {
         for (int c = -1; c <= 1; c++) {
            int bRow = move->mRow + r, bCol = move->mCol + c, count = 0;
            while ((InBounds(bRow, bCol) && (mBoard[bRow][bCol] != 0))) {
               if (mBoard[bRow][bCol] != GetNextPlayer()) {
                  count++;
               }
               else {
                  move->AddFlipSet(OthelloMove::FlipSet(count, r, c));
                  for (; count > 0; count--) {
                     bRow -= r;
                     bCol -= c;
                     mBoard[bRow][bCol] = GetNextPlayer();
                     mValue += 2 * GetNextPlayer();
                  }
                  break;
               }
               bRow += r;
               bCol += c;
            }
         }
      }
   }
   mNextPlayer = -mNextPlayer;
}

void OthelloBoard::UndoLastMove() {
   if (mHistory.size() > 0) {
      mNextPlayer = -mNextPlayer;
      OthelloMove* m = mHistory.back();
      vector<OthelloMove::FlipSet> flipset = m->mFlips;
      mBoard[(*m).mRow][(*m).mCol] = Player::EMPTY;
      for (OthelloMove::FlipSet f : flipset) {
         int bRow = (*m).mRow, bCol = (*m).mCol;
         for (int fliped = 0; fliped < f.switched; fliped++) {
            bRow += f.rowDelta;
            bCol += f.colDelta;
            mBoard[bRow][bCol] = -mBoard[bRow][bCol];
            mValue -= 2 * mNextPlayer;
         }
      }
      delete m;
      mHistory.pop_back();
      mValue -= mNextPlayer;
   }
}
