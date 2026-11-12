# 🧠 Brain Tester — Mini Games

A lightweight, zero-dependency C++ web application that turns classic **Data Structures & Algorithms (DSA)** problems into playable, visual mini-games.

Instead of just grinding algorithm problems on a whiteboard or LeetCode, Brain Tester lets you actually play them. While you navigate the puzzles, the C++ backend runs real-time algorithmic solvers (BFS, multi-dimensional Dynamic Programming, Bitmasking, and Backtracking) to calculate the theoretical best score and moves, comparing your play against optimal computer solutions.

---

## 🎮 The Mini-Games

Each mini-game maps directly to a classic computer science problem:

| Game | Inspired By | Core Algorithm | How to Play |
|---|---|---|---|
| 🗝️ **Key Hunter** | Shortest Path with Keys (LeetCode 864) | **State-Space BFS** | Move through a maze with arrow keys or clicks. Collect keys (`a–d`) to unlock matching doors (`A–D`). Find the shortest route! |
| 🛡️ **Dungeon Survival** | Dungeon Game (LeetCode 174) | **2D Dynamic Programming** | Navigate from top-left to bottom-right. Demons drain your HP, potions restore it. Find the route that requires minimum starting HP to survive. |
| 🤖 **Dual Robot Challenge** | Cherry Pickup II (LeetCode 1463) | **3D Dynamic Programming** | Guide two robots down a grid at the same time to scoop up maximum loot. Plan joint moves so they don't block each other. |
| 🍒 **Cherry Expedition** | Cherry Pickup (LeetCode 741) | **Time-Step DP** | Make a full round-trip from start to end and back, dodging thorns and grabbing cherries. Cherries disappear once picked! |
| 🧩 **Permutation Puzzle** | Transform to Chessboard (LeetCode 782) | **Bitwise Parity & Greedy** | Given a scrambled grid, swap entire rows and columns to turn it into an alternating checkerboard in minimum moves. |
| 🔢 **Sudoku Master** | Sudoku Solver (LeetCode 37) | **Backtracking + Bitmasks** | Classic 9×9 Sudoku with multiple difficulty tiers. Test your deduction skills with live error validation. |

---

## ✨ Features

- **Zero External Dependencies**: Pure C++17 using standard library features and native OS sockets. No Boost, no Node.js, no Python, no npm packages.
- **Embedded Single-Binary Frontend**: The entire UI (HTML5, modern responsive CSS, vanilla JavaScript, synthesized Web Audio sound effects, and confetti) is embedded directly inside `index_html.hpp`. Compiling gives you a single portable executable with no asset files to bundle.
- **Verified Procedural Generation**: Puzzles are randomly generated on the fly and immediately solved by backend algorithms before being sent to the browser, ensuring every puzzle is 100% solvable.
- **Multi-Threaded Server**: Each incoming client request runs concurrently in its own detached thread (`std::thread`), with a mutex-protected Mersenne Twister engine for thread-safe random generation.
- **Cross-Platform**: Compiles and runs cleanly on both Linux (POSIX sockets) and Windows (`Winsock2`).
- **Scoring & Rank System**: Evaluates your performance based on completion time, mistakes, and whether you matched the theoretical optimal path.
- **Local Leaderboard & Dark/Light Mode**: Keeps track of your personal best runs per game in `localStorage`, plus theme toggle and sound settings.

---

## 🏆 Scoring & Ranks

Your score for each round is calculated based on:
- **Base Score**: 1,000 points (scaled by difficulty: Easy ×1.0, Medium ×1.5, Hard ×2.0).
- **Time Penalty**: Fast completions preserve points; taking longer slowly reduces score.
- **Mistake Penalty**: Every wrong move or invalid step deducts points.
- **Bonuses**:
  - +200 points for matching the mathematically optimal solution.
  - +100 points for a flawless run (zero mistakes).
  - +150 speed bonus for finishing under 20 seconds.

### Rank Tiers
Based on cumulative score, you level up across 6 tiers:
```
Beginner ➔ Explorer ➔ Challenger ➔ Algorithmist ➔ Master ➔ DSA Legend
```

---

## 🛠️ How It Works Under the Hood

```
   Browser (Single-Page App)
              │
              │  HTTP GET /api/generate?game=dungeon&diff=easy
              ▼
   ┌──────────────────────────────────────────────┐
   │           server.cpp (Port 8080)             │
   │  • Listens on socket & accepts connections   │
   │  • Dispatches request to a worker thread     │
   └──────────────────────┬───────────────────────┘
                          │
                          ▼
   ┌──────────────────────────────────────────────┐
   │        generator.hpp + solver.hpp            │
   │  1. Generates random grid layout             │
   │  2. Runs algorithm solver (BFS / DP / etc.)  │
   │  3. Validates solvability & optimal baseline │
   │  4. Returns puzzle JSON + optimal target     │
   └──────────────────────────────────────────────┘
```

1. **`server.cpp`**: Minimalist multi-threaded HTTP server. Handles request parsing, static file delivery (`INDEX_HTML`), and JSON API routing.
2. **`generator.hpp`**: Procedural generators for each puzzle type with difficulty settings.
3. **`solver.hpp`**: Clean, self-contained algorithmic solvers for each game:
   - **Key Hunter**: BFS exploring `(row, col, collected_keys)` state tuples.
   - **Dungeon Survival**: Reverse 2D DP calculating minimum incoming HP needed per cell from target back to origin.
   - **Dual Robot**: 3D DP tracking simultaneous row steps and column positions `(row, col1, col2)`.
   - **Cherry Expedition**: Synchronous step DP tracking two simultaneous paths `(t, r1, r2)`.
   - **Permutation Puzzle**: Bitwise XOR row/column signatures and parity counts.
   - **Sudoku Master**: Recursive DFS backtracking with bitmask sets for $O(1)$ safety checks.
4. **`index_html.hpp`**: Complete web client with dark/light themes, keyboard navigation, animated grids, sound effects, and modal dialogs.

---

## 🚀 Quickstart

### Prerequisites
- GCC/Clang with C++17 support (`g++`)
- Make (optional, direct compile command works too)

### Build & Run on Linux / macOS

```bash
# Clone the repository
git clone https://github.com/<your-username>/Brain-Tester-Mini-games.git
cd Brain-Tester-Mini-games

# Build using make
make

# Run the server (default port: 8080)
./brain_tester_server
```

You can also pass a custom port:
```bash
./brain_tester_server 9000
```

Now open your browser and go to:
```
http://localhost:8080
```

### Build on Windows (MinGW / MSYS2)

Using Make:
```bash
make
brain_tester_server.exe
```

Or compiling directly with `g++`:
```bash
g++ -O2 -std=c++17 -o brain_tester_server.exe server.cpp -lws2_32
brain_tester_server.exe
```

---

## 🔌 API Reference

If you want to integrate or build your own client, the server exposes two simple JSON endpoints:

### 1. Generate Puzzle
```http
GET /api/generate?game=<game_name>&diff=<easy|medium|hard>
```
- **`game`**: `keyhunter`, `dungeon`, `dualrobot`, `cherry`, `permutation`, or `sudoku`
- **`diff`**: `easy`, `medium`, or `hard` (or `1`, `2`, `3`)

**Example Response (`/api/generate?game=dungeon&diff=easy`):**
```json
{
  "game": "dungeon",
  "rows": 4,
  "cols": 4,
  "grid": [
    [-3, 4, -8, 2],
    [-5, -10, 6, -4],
    [5, -2, -7, 8],
    [-2, 6, -11, -9]
  ],
  "optimal": 14
}
```

### 2. Calculate Score
```http
GET /api/score?diff=<1-3>&optimal=<0|1>&wrong=<N>&seconds=<T>
```

**Example Response:**
```json
{
  "score": 1450,
  "rank": "Explorer"
}
```

---

## 📁 Project Structure

```
.
├── Makefile            # Build configuration for Linux and Windows
├── README.md           # Documentation
├── server.cpp          # Multi-threaded HTTP server & API router
├── generator.hpp       # Puzzle procedural generators & thread-safe RNG
├── solver.hpp          # Algorithmic solvers (BFS, DP, Backtracking, Bitwise)
└── index_html.hpp      # Single-page web frontend embedded as raw string literal
```

---

## 💡 Why This Project?

Most DSA practice feels abstract — you submit code, see tests pass, and move on. Brain Tester connects algorithm theory with interactive game mechanics:
- You see why a **3D DP** state is required when two actors move simultaneously.
- You see how **BFS with bitmasks** finds the absolute shortest route to grab keys and open doors.
- You experience how a **greedy bitwise check** can determine chessboard solvability in milliseconds without brute-forcing permutations.

Have fun playing, and may your algorithms always run in optimal time! 🚀