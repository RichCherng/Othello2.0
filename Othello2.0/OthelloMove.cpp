
#include "OthelloMove.h"

using namespace std;

OthelloMove::OthelloMove()
   :mRow(-1), mCol(-1) {

}

OthelloMove::OthelloMove(int row, int col)
   : mRow(row), mCol(col) {

}

OthelloMove& OthelloMove::operator=(const std::string &move) {
   if (move == "pass") {
      mRow = -1;
      mCol = -1;
      return *this;
   }
   else {
      //string r = move.substr(1, move.find(","));
      int ro = atoi(move.substr(1, move.find(",")).c_str());
   }
}