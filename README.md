# Gomoku 🧮

<img src="https://i.imgur.com/5wrGtpL.gif" style="width: 100%; height: auto;" />

## 📝 Description

This project aims to create a competitive Gomoku AI that evaluates and plays the best moves based on the board's current state.

The AI relies on the [MiniMax](https://en.wikipedia.org/wiki/Minimax) algorithm, enhanced with many optimisations for optimal performance. The back-end, written in **C++**, handles the game logic and AI computations, while the **React** front-end provides an intuitive interface for players to interact with the game.

## 📚 Rules

<img src="https://i.imgur.com/IEQrxiM.png" style="width: 100%; height: auto;" />

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

## 🔭 Minimax

Minimax is a decision-making algorithm commonly used in turn-based games, where players take alternate moves aiming to maximize their advantage while minimizing the opponent's. To make this process efficient, you've implemented several optimizations:

1. **NegaMax**: This is a simplified variant of Minimax tailored for games where moves alternate. By assuming the opponent's loss is the player’s gain, NegaMax reduces code complexity without affecting performance, making it easier to work with.

**_Pseudo-code for the NegaMax algorithm:_**

```cpp
int negamax(Node* node, int color) {
    if (node->isTerminal()) return color * node->evaluate(); // Evaluate the node
    int best = INT_MIN;
    for (Node* child : node->children) {
        best = std::max(best, -negamax(child, -color)); // Recursively call negamax
    }
    return best;
}
```

**_Visualization of the NegaMax algorithm (from [Wikipedia](https://en.wikipedia.org/wiki/Negamax)):_**

<img src="https://i.imgur.com/4el5dIF.gif" style="width: 80%; height: auto;" />

2. **Alpha-Beta Pruning**: This optimization improves the search by skipping branches that won’t affect the final decision, effectively reducing the number of nodes evaluated. Alpha (the best value for the maximizer) and Beta (the best for the minimizer) bounds allow the search to ignore irrelevant moves, enhancing efficiency.

**_Pseudo-code for the Alpha-Beta Pruning algorithm:_**

```cpp
int negamax(Node* node, int depth, int alpha, int beta, int color) {
    if (depth == 0 || node->isTerminal()) return color * node->evaluate(); // Evaluate the node
    for (Node* child : node->children) {
        int score = -negamax(child, depth - 1, -beta, -alpha, -color); // Recursively call alphaBeta
        alpha = std::max(alpha, score);
        if (alpha >= beta) break; // Prune the branch
    }
    return alpha;
}
```

**_Visualization of the Alpha-Beta Pruning algorithm (from [Wikipedia](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning)):_**

<img src="https://i.imgur.com/xvGtOh1.gif" style="width: 80%; height: auto;" />

3. **Transposition Tables**: By storing previously evaluated positions, transposition tables prevent redundant calculations for recurring game states. This is especially beneficial in Gomoku, where similar board states can arise frequently.

**_Diagram of the Transposition Tables optimization:_**
<img src="https://i.imgur.com/8VMlpBZ.png" style="width: 60%; height: auto;" />

4. **Zone of Interest**: To further narrow down the search, this optimization considers only moves within a distance of 1 from already played stones. By limiting the focus to this area, the algorithm reduces unnecessary calculations and concentrates on moves that are more likely to impact the game’s progression.

**_Visualization of the Zone of Interest optimization:_**
<img src="https://i.imgur.com/nqvIUlc.png" style="width: 60%; height: auto;" />

5. **Move Ordering**: Sorting moves to prioritize the most promising options first speeds up the Alpha-Beta pruning. By focusing on moves more likely to lead to favorable outcomes, this technique makes the search process faster and more directed. To sort out the most interesting moves, we have a little heuristic that allows us to evaluate each move that falls within the zone of interest.

These optimizations make your Gomoku AI faster and more capable of handling the complex game space efficiently, focusing on strong, strategic moves and reducing computational load.

## 🧠 Heuristic

TODO

# 🧑 Authors ‍

- [@Seriots](https://github.com/Seriots)
- [@tsannie](https://github.com/tsannie)
