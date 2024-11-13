# Gomoku 🧮

## 📝 Description

This project consist of find the best move accordingly to the current move.

We use a [MiniMax](https://en.wikipedia.org/wiki/Minimax) algorithm and our own heuristic to find it.

## 📦 Installation

### Back

To setup the back-end, you need to 'make' and launch the server.

```bash
cd back
make
./Gomoku
```

### Front

To setup the front-end, you need to install the dependencies and launch the server.

```bash
cd front
npm install
npm start
```

## 📑 Summary

- [Minimax](#-data-analysis)
- [Heuristic](#-heuristic)

## 🔭 Minimax

Minimax is a decision-making algorithm commonly used in turn-based games, where players take alternate moves aiming to maximize their advantage while minimizing the opponent's. To make this process efficient, you've implemented several optimizations:

1. **NegaMax**: This is a simplified variant of Minimax tailored for games where moves alternate. By assuming the opponent's loss is the player’s gain, NegaMax reduces code complexity without affecting performance, making it easier to work with.

2. **Alpha-Beta Pruning**: This optimization improves the search by skipping branches that won’t affect the final decision, effectively reducing the number of nodes evaluated. Alpha (the best value for the maximizer) and Beta (the best for the minimizer) bounds allow the search to ignore irrelevant moves, enhancing efficiency.

3. **Transposition Tables**: By storing previously evaluated positions, transposition tables prevent redundant calculations for recurring game states. This is especially beneficial in Gomoku, where similar board states can arise frequently.

4. **Zone of Interest**: To further narrow down the search, this optimization considers only moves within a distance of 1 from already played stones. By limiting the focus to this area, the algorithm reduces unnecessary calculations and concentrates on moves that are more likely to impact the game’s progression.

4. **Move Ordering**: Sorting moves to prioritize the most promising options first speeds up the Alpha-Beta pruning. By focusing on moves more likely to lead to favorable outcomes, this technique makes the search process faster and more directed. To sort out the most interesting moves, we have a little heuristic that allows us to evaluate each move that falls within the zone of interest.

These optimizations make your Gomoku AI faster and more capable of handling the complex game space efficiently, focusing on strong, strategic moves and reducing computational load.

## 🧠 Heuristic

TODO
