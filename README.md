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

### Run

Now you can go to `localhost:3000` to access to the website

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

6. **End Game Cutting**: During the creation of the tree, we checks if any player win in any matters, if so we stop the process from this branch and return a high value dependent from the depth of the actual search. If we are in an early step, the value is going to be higher than from an end leaf. 

These optimizations make your Gomoku AI faster and more capable of handling the complex game space efficiently, focusing on strong, strategic moves and reducing computational load.

## 🧠 Heuristic

The heuristic is the process used to evaluate the value of a board. It's represent nothing in particular and can take very varied forms. So it's always a bias choosen by the developper often in the search of a balance between optimisation and accuracy.

For this project our method to evaluate the value of the board is simple, but strong. We take every alignement of `five stones` and capture during `minimax` to gave to the board a value 

1. **Define a DNA**: From biology, `DNA` is the system used to encode any living thing and can describe is construction. Here our `DNA` is the system that we used to describe each interesting alignement of five stones. To do so, we declare some abstract values ​​which together gives an optimized result. 

**_DNA of our Heuristic_**

<img src="https://github.com/user-attachments/assets/9dbf6f31-c954-4431-b101-ba137975d744" style="width: 60%; height: auto;" />


2. **Associate DNA with alignements**: Next, we search for all interesting alignement of `five stones` that can be interesting in our process such as `White-White-White-White-Wwhite` that is a win alignement or `White-Black-Black-Nothing-Nothing` which is an alignement that can lead to a capture for `White`.

**_Part of all associated values_**

<img src="https://github.com/user-attachments/assets/49fca551-e20a-43c3-b08b-f0852a888ecc" style="width: 60%; height: auto;" />

3. **Check the board**: To process the calculation, we need to check on every row, column and diagonal, on every alignement of `five stones`. If the alignement is known, the given value is added to the total value of the board. When every alignement is checked, the result is added with the value of `capture` found during `minimax` process and all of this is the value associated with this board.

**_ Exemple of a board value calculation :_**

<img src="https://github.com/user-attachments/assets/deb19a87-2924-4947-86c5-dc1c5092882a" style="width: 60%; height: auto;" />

With that, we can perform our `minimax` calculation with a great accuracy, without losing to much time 

# 🧑 Authors ‍

- [@Seriots](https://github.com/Seriots)
- [@tsannie](https://github.com/tsannie)
