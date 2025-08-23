🏍️ SpeedRush -- 2D Bike Racing Game
===================================

A **fast-paced retro side-scroller** built using **C++** and [raylib](https://www.raylib.com/).\
Dodge obstacles, boost through levels, and test your reflexes in an adrenaline-packed racing experience.

* * * * *

✨ Project Overview
------------------

**SpeedRush** is a minimal yet thrilling 2D racing game featuring:

-   🎯 **Simple controls** with smooth movement and responsive boosts

-   🔊 **Inbuilt audio** for background music and effects

-   ⚡ **Boost system** to accelerate past obstacles

-   🛒 **Shop system** for upgrades and customizations

-   🏆 **Highscore tracking** stored in a local file

-   🌄 **Dynamic maps** that change as you progress

-   🖼️ **Custom graphics and sounds** stored in dedicated folders

* * * * *

📷 Preview
----------

*Coming soon...*

* * * * *

🔧 Installation & Setup
-----------------------

### 1\. Clone the Repository

`git clone https://github.com/wasiq345/SpeedRush-2D.git
cd SpeedRush-2D`

### 2\. Install raylib

Follow the official [raylib installation guide](https://github.com/raysan5/raylib#building) for your OS.

### 3\. Build the Game

#### 🔹 Windows (using `build.bat`)

A preconfigured build script is included. From the project root, run:

`.\build.bat main main.exe`

This will:

-   Compile all `.cpp` files inside `src/`

-   Use headers from `include/`

-   Link against **raylib** automatically

Your executable (`main.exe`) will appear in the project root.

#### 🔹 Other Platforms (manual build)

If you're on Linux/macOS, compile manually with:

`g++ src/*.cpp -I include -o SpeedRush -lraylib -lopengl32 -lgdi32 -lwinmm`

> ⚠️ Adjust libraries depending on your OS.

### 4\. Run the Game

`./main.exe   # on Windows
./SpeedRush  # on Linux/macOS`

* * * * *

🎮 Controls
-----------

| Action | Key |
| --- | --- |
| Move Left | ⬅️ Left Arrow |
| Move Right | ➡️ Right Arrow |
| Boost | Spacebar |
| Mute Music | M |
| Pause Game | P |

* * * * *

📂 File Structure
-----------------

SpeedRush-2D/
│── build.bat               # Windows build script
│── include/                # Header files
│   └── game.h
│── src/                    # Source code
│   ├── main.cpp
│   └── game.cpp
│── highscore.txt           # Stores player's best score
│── sounds/                 # Background music & SFX
│── graphics/               # Sprites & visual assets
│── README.md               # Project documentation

* * * * *

📜 License
----------

This project is licensed under the MIT License -- feel free to use and modify it.

* * * * *

🙌 Credits
----------

-   [raylib](https://www.raylib.com/) -- Graphics & game framework

-   Sound & graphic assets by [Wasiq]

-   Developed by Wasiq

-   Connect with me on [LinkedIn](https://www.linkedin.com/in/wasiq-azeem-730215367/)