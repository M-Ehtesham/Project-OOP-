Tower Defense Game 🏰
A fully functional Tower Defense game built in C++ using SFML, developed as the semester project for Object Oriented Programming at National University of Computing & Emerging Sciences.
🎮 Gameplay
Place defensive towers on a grid-based map to stop waves of enemies from reaching your base. Earn gold by defeating enemies and use it to build or upgrade towers. Survive all 5 progressively harder waves to win!
Controls: | Key | Action | |—–|——–| ---------------- | 1-5 | Select tower type | ----- | Left Click | Place tower | ------------ | Right Click | Upgrade existing tower |
🏗️ Tower Types
Tower	Color	Strength
Cannon	Yellow	High damage, slow fire rate
Sniper	Magenta	Very long range, high damage
Machine Gun	Cyan	Rapid fire, low damage per shot
Splash	Orange	Area-of-effect damage
Slow	Blue	Reduces enemy speed
All towers can be upgraded twice (right-click) to improve stats.
👾 Enemy Types
Enemy	Color	Trait
Basic	Red	Balanced speed and HP
Fast	Yellow	High speed, low HP
Tank	Black	Slow, extremely high HP
Flying	White	Ignores path, diagonal movement
Regenerating	Green	Heals over time
⚙️ Build & Run
Requirements
•	C++ compiler (g++/MSVC)
•	SFML 2.5+
Windows (Visual Studio)
1.	Install SFML and link sfml-graphics, sfml-window, sfml-system libraries
2.	Place ARIAL.ttf and scores.txt in the same folder as the executable
3.	Build and run
Note: The game looks for ARIAL.ttf in the working directory. Make sure the font file is present before running.
📁 Project Structure
.
├── main.cpp          # Single-file game implementation
├── ARIAL.ttf         # Font file (required)
├── highscore.txt     # score file
└── README.md         # This file
✅ OOP Concepts Demonstrated
•	Abstraction — Entity, Enemy, Tower are abstract base classes with pure virtual functions
•	Inheritance — All enemies inherit from Enemy; all towers inherit from Tower
•	Polymorphism — Enemies and towers stored as base-class pointers; virtual functions resolved at runtime
•	Encapsulation — Private/protected members with getters/setters
•	Operator Overloading — operator== in Enemy for position comparison
•	Memory Management — Dynamic allocation with proper cleanup; virtual destructors prevent leaks
🎯 Features
•	☒ 5 distinct enemy types with unique behaviors
•	☒ 5 distinct tower types with unique attack mechanics
•	☒ 5 progressive waves with increasing difficulty
•	☒ Economy system (gold on kills, spend to build/upgrade)
•	☒ Lives/HP system with game-over and win screens
•	☒ Tower upgrade system (2 levels per tower)
•	☒ Persistent high score (saved to file)
•	☒ Enemy HP bars and targeting lines
•	☒ Custom enemy: RegeneratingEnemy (heals over time)
•	☒ Custom tower: SplashTower (area damage)
📝 Known Limitations
•	Single fixed map layout
•	No sound effects or background music
•	Font file (ARIAL.ttf) must be manually provided
👤 Author
Ehtesham 25L-2557
Semester Project — Object Oriented Programming
National University of Computing & Emerging Sciences
