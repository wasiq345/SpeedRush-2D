# 🏍️ SpeedRush – 2D Bike Racing Game

A **fast-paced retro side-scroller** built using **C++** and [raylib](https://www.raylib.com/).  
Dodge obstacles, boost through levels, and test your reflexes in an adrenaline-packed racing experience.

---

## ✨ Project Overview

**SpeedRush** is a minimal yet thrilling 2D racing game featuring:

- 🎯 **Simple controls** with smooth movement and responsive boosts  
- 🔊 **Inbuilt audio** for background music and effects  
- ⚡ **Boost system** to accelerate past obstacles  
- 🛒 **Shop system** for upgrades and customizations  
- 🏆 **Highscore tracking** stored in a local file  
- 🌄 **Dynamic maps** that change as you progress  
- 🖼️ **Custom graphics and sounds** stored in dedicated folders

---

## 📷 Preview

_Coming soon..._

---

## 🔧 Installation & Setup

### 1. Clone the Repository
```bash
git clone https://github.com/wasiq345/SpeedRush-2D.git
cd SpeedRush-2D
```

### 2. Install raylib
Follow the official [raylib installation guide](https://github.com/raysan5/raylib#building) for your OS.

### 3. Compile the Game
```bash
g++ main.cpp -o SpeedRush -lraylib -lopengl32 -lgdi32 -lwinmm
```
> ⚠️ Modify the compile command based on your OS (Windows/Mac/Linux) and IDE setup.

### 4. Run the Simulation

Execute the C++ compiled executable:

```bash
./SpeedRush-2D
```

> Ensure the data files and graph image are in the **same directory** as the executable.

---

## 🎮 Controls

| Action       | Key              |
|--------------|------------------|
| Move Left    | ⬅️ Left Arrow     |
| Move Right   | ➡️ Right Arrow    |
| Boost        | ␣ Spacebar        |
| Mute Music   | Key M             |
| Pause Game   | key P            |

---

## 📂 File Structure

```
SpeedRush-2D/
│── main.cpp                # Main game logic
│── highscore.h             # Highscore logic
│── highscore.txt           # Stores player’s best score
│── sounds/                 # Background music & SFX
│── graphics/               # Sprites & visual assets
│── README.md               # Project documentation
```

---

## 📜 License

This project is licensed under the MIT License – feel free to use and modify it.

---

## 🙌 Credits

- [raylib](https://www.raylib.com/) – Graphics & game framework  
- Sound & graphic assets by [Wasiq]  
- Developed by Wasiq
- Connect with me on [LinkedIn](https://www.linkedin.com/in/wasiq-azeem-730215367/)
