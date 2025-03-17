# Multiplayer Networked Tic-Tac-Toe Game

## 📌 Project Overview
This project is a **multiplayer networked Tic-Tac-Toe game** implemented in **C** using **socket programming**. It enables two players (client and server) to compete over a network, facilitating real-time gameplay.

The project features a **server-client model**, where:
- The **server** manages the game state.
- The **client** connects to the server and interacts with the game.

---

## 📜 Table of Contents
- [Project Overview](#project-overview)
- [Features](#features)
- [Technologies Used](#technologies-used)
- [Installation](#installation)
- [Usage](#usage)
- [Project Files](#project-files)
- [Gameplay](#gameplay)
- [Future Enhancements](#future-enhancements)
- [Contributors](#contributors)
- [License](#license)

---

## 🎮 Features
- **Networked Gameplay**: Players can connect remotely to play.
- **Server-Client Architecture**: One player hosts the game (server), while the other connects (client).
- **Real-time Move Validation**: Ensures valid moves and game progression.
- **Win, Draw, and Play Again Features**.
- **Turn-based Game Logic**.

---

## 💡 Technologies Used
- **Programming Language**: C
- **Socket Programming**: Used for client-server communication
- **POSIX APIs**: For networking and process control
- **Makefile**: Automates compilation

---

## 🛠 Installation
To set up the game on your system:

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/Dx2905/CS5100-Foundation-Of-AI.git
   cd CS5100-Foundation-Of-AI/TicTacToe
   ```
2. **Compile the Game**:
   ```bash
   make
   ```
   This will generate the `ttt` executable.

---

## 🚀 Usage
### **Starting the Server**
Run the following command to start the server:
```bash
./ttt -s
```
This sets up the game server, waiting for a client to connect.

### **Starting the Client**
Run the client with the server’s IP and port number:
```bash
./ttt -c <server-port>
```
Replace `<server-port>` with the actual port number.

---

## 📂 Project Files
| File Name | Description |
|-----------|------------|
| `ttt.c` | Core game logic (gameplay, moves, validation) |
| `unixserver.c` | Server-side implementation |
| `unixclient.c` | Client-side implementation |
| `server.h` | Header file for server functions |
| `client.h` | Header file for client functions |
| `Makefile` | Automates compilation |

---

## 🎲 Gameplay
- The **server** starts the game and waits for a connection.
- The **client** joins and chooses a symbol (`X` or `O`).
- Players take turns placing their marks on the board.
- The game checks for a win or draw after every move.
- The game announces the winner or if it ends in a draw.
- Players have the option to restart after a match.

---

## 🔮 Future Enhancements
- **Graphical Interface**: Replace terminal-based gameplay with a GUI.
- **Multiple Clients**: Support for matchmaking with multiple players.
- **Leaderboard & Score Tracking**.
- **Enhanced Security**: Prevent unauthorized connections.

---

## 👥 Contributors
- **Gaurav** ([@Dx2905](https://github.com/Dx2905))

📍 **Khoury College, Northeastern University, Portland, Maine, USA**

For inquiries, contact: `lnu.gau@northeastern.edu`

---

## 📜 License
This project is licensed under the **MIT License**. See the [LICENSE](https://github.com/Dx2905/CS5100-Foundation-Of-AI/blob/main/LICENSE) file for more details.

---

🚀 **If you found this project useful, give it a ⭐ on GitHub!** 🎉

