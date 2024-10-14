# Gomoku

This project consist of find the best move accordingly to the current move.

We use a MiniMax algorithm and our own heuristic to find it

Current Heuristic:
  - Get the interesting zone (x case around all other one)
  - Get the current center of the board
  - Add a distance score with the center define previously
  - Add all move score

Algo min max + elagage AlphaBeta
