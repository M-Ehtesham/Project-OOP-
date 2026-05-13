#include <SFML/Graphics.hpp>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//constant members
const int max_enemies = 20;
const int max_towers = 10;
const int wave_count = 5;
const int waves[5] = { 3, 6, 10, 14, 18 };

class Entity {
protected:
	float x;
	float y;
public:
	Entity(float s_X, float s_Y) {
		x = s_X;
		y = s_Y;
	}
	virtual void draw(sf::RenderWindow& window, float offsetX, float offsetY, float titlesize) = 0;

	float getter_x() const {
		return x;
	}

	float getter_y() const {
		return y;
	}


	virtual ~Entity() {}
};




class Enemy :public Entity {   //base class-paren class   ----   abstract class (base for other classes) cant create objects directly
protected:
	float speed;
	int hp;
	int direction;
	float deathtimer;
	bool dead;
	bool escaped;
	int maxHP;
	float baseSpeed;

public:
	Enemy(float startX, float startY) :Entity(startX, startY) {
		speed = 0.20f;
		hp = 300;
		direction = 0;
		deathtimer = 0;
		dead = false;
		escaped = false;
		maxHP = hp;
		baseSpeed = speed;;

	}
	virtual void move(float titlesize) = 0;   //pure virtual functions to make it abstract class

	void moveOnPath(float titlesize) {

		if (direction == 0) {
			x += speed;

			if (x >= titlesize * 7.75f)
				direction = 1;
		}

		else if (direction == 1) {
			y += speed;

			if (y >= titlesize * 2)
				direction = 2;
		}

		else if (direction == 2) {
			x -= speed;

			if (x <= 0)
				direction = 3;
		}

		else if (direction == 3) {
			y += speed;

			if (y >= titlesize * 5)
				direction = 4;
		}

		else if (direction == 4) {
			x += speed;

			if (x >= titlesize * 7 + titlesize * 0.75f) {

				escaped = true;
				dead = true;
				deathtimer = 0;
			}
		}
	}

	virtual void draw(sf::RenderWindow& window, float offsetX, float offsetY, float titlesize) = 0;
	void basedraw(sf::RenderWindow& window, float offsetX, float offsetY, float titlesize) {
		sf::CircleShape circle(titlesize * 0.18f);
		circle.setPosition(offsetX + x, offsetY + y);

		if (isalive())
			circle.setFillColor(sf::Color::Red);
		else
			circle.setFillColor(sf::Color(80, 80, 80));

		window.draw(circle);
	}
	virtual void takeDamage(int a) { //taking the damage as the parameter
		if (dead) {
			return;
		}

		hp -= a;
		if (hp <= 0) {
			dead = true;
			deathtimer = 180;  //1 sec for 60 framerates
		}
		cout << hp << endl;

	}
	int getHP() {
		return hp;
	}
	virtual ~Enemy() {

	}

	bool isalive() {  //for checking that the enemy is still alive or not
		return(!dead);
	}
	bool isReadyForDeletion() const {
		return dead && deathtimer <= 0;
	}
	virtual string getType() const {
		return "Enemy";
	}
	bool hasEscaped() const {
		return escaped;
	}
	void setSpeed(float s) {
		speed = s;
	}
	float getSpeed() {
		return speed;
	}

	void drawHPBar(sf::RenderWindow& window, float offsetX, float offsetY, float titlesize) {
		if (!isalive())
			return;

		float width = titlesize * 0.35f;
		float ratio = (float)hp / maxHP;  //casting

		sf::RectangleShape back(sf::Vector2f(width, 4.f));
		back.setPosition(offsetX + x, offsetY + y - 8.f);
		back.setFillColor(sf::Color(60, 60, 60));

		sf::RectangleShape front(sf::Vector2f(width * ratio, 4.f));
		front.setPosition(offsetX + x, offsetY + y - 8.f);
		front.setFillColor(sf::Color::Red);

		window.draw(back);
		window.draw(front);
	}
	bool operator==(const Enemy& other) const {   //operator overloading
		return x == other.x && y == other.y;
	}
	virtual int get_Reward()const {
		return 10;
	}
	float getBaseSpeed() {
		return baseSpeed;
	}
};

class BasicEnemy :public Enemy {
public:
	BasicEnemy(float startX, float startY) :Enemy(startX, startY) {
		hp = 300;
		maxHP = hp;
		speed = 0.25f;
		baseSpeed = speed;
	}
	void move(float titlesize) override {
		if (dead)
		{
			if (deathtimer > 0)
				deathtimer--;
			return;
		}

		moveOnPath(titlesize);
	}
	void draw(sf::RenderWindow& window, float offsetX, float offsetY, float titlesize) override {
		basedraw(window, offsetX, offsetY, titlesize);
	}

};

class FastEnemy :public Enemy {
public:
	FastEnemy(float startX, float startY) :Enemy(startX, startY) {
		hp = 200;
		maxHP = hp;
		speed = 0.30f;
		baseSpeed = speed;
	}
	void move(float titlesize) override {
		if (dead)
		{
			if (deathtimer > 0)
				deathtimer--;
			return;
		}

		moveOnPath(titlesize);

	}
	void draw(sf::RenderWindow& window, float offsetX, float offsetY, float titlesize) override {
		sf::CircleShape circle(titlesize * 0.14f);
		circle.setPosition(offsetX + x, offsetY + y);

		if (isalive())
			circle.setFillColor(sf::Color::Yellow);
		else
			circle.setFillColor(sf::Color(80, 80, 80));

		window.draw(circle);
	}
	int get_Reward()const override {   //overriding funcion  
		return 8;
	}

};
class TankEnemy :public Enemy {
public:
	TankEnemy(float startX, float startY) :Enemy(startX, startY) {
		hp = 450;
		maxHP = hp;
		speed = 0.10f;
		baseSpeed = speed;
	}
	void move(float titlesize) override {
		if (dead)
		{
			if (deathtimer > 0)
				deathtimer--;
			return;
		}

		moveOnPath(titlesize);
	}
	void draw(sf::RenderWindow& window, float offsetX, float offsetY, float titlesize) override {
		sf::CircleShape circle(titlesize * 0.28f);
		circle.setPosition(offsetX + x, offsetY + y);

		if (isalive())
			circle.setFillColor(sf::Color::Black);
		else
			circle.setFillColor(sf::Color(80, 80, 80));

		window.draw(circle);
	}
	int get_Reward()const override {
		return 20;
	}

};
class FlyingEnemy : public Enemy {
public:
	float dx;
	float dy;

public:
	FlyingEnemy(float startX, float startY) : Enemy(startX, startY) {
		hp = 180;
		maxHP = hp;
		speed = 0.25f;
		baseSpeed = speed;

		dx = 1.f;
		dy = 1.f;

	}

	void move(float titlesize) override {
		if (dead) {
			if (deathtimer > 0)
				deathtimer--;
			return;
		}

		// Flying enemy has its on path
		if (!isalive())
			return;

		// digonal movement both x and y component increasing 
		x += speed * dx;;
		y += speed * dy;

		// escape condition 
		if (x > titlesize * 8 || y > titlesize * 6) {
			escaped = true;
			dead = true;
			deathtimer = 0;
		}
	}

	void draw(sf::RenderWindow& window, float offsetX, float offsetY, float titlesize) override {
		sf::CircleShape circle(titlesize * 0.18f);
		circle.setPosition(offsetX + x, offsetY + y);

		if (isalive())
			circle.setFillColor(sf::Color::White);
		else
			circle.setFillColor(sf::Color(80, 80, 80));

		window.draw(circle);
	}
};
class RegeneratingEnemy : public Enemy {
private:
	int regenTimer;

public:
	RegeneratingEnemy(float startX, float startY) : Enemy(startX, startY) {
		hp = 280;
		maxHP = hp;
		speed = 0.18f;
		baseSpeed = speed;
		regenTimer = 60;
	}

	void move(float titlesize) override {

		if (dead) {
			if (deathtimer > 0)
				deathtimer--;
			return;
		}
		if (regenTimer > 0)
			regenTimer--;
		else {
			if (hp < maxHP)
				hp += 2;
			regenTimer = 60;
		}
		moveOnPath(titlesize);
	}

	void draw(sf::RenderWindow& window, float offsetX, float offsetY, float titlesize) override {
		sf::CircleShape circle(titlesize * 0.18f);
		circle.setPosition(offsetX + x, offsetY + y);

		if (isalive())
			circle.setFillColor(sf::Color::Green);
		else
			circle.setFillColor(sf::Color(80, 80, 80));

		window.draw(circle);
	}
	int get_Reward() const override {
		return 15;
	}
};
class Tower :public Entity {
protected:
	float range;
	int damage;
	int cooldown;
	int timer;
	Enemy* currentTarget;
	//bulet details
	float bulletX;
	float bulletY;
	float bulletSpeed;
	bool bulletActive;
	Enemy* bulletTarget;

	int level;
public:
	Tower(float s_x, float s_y) :Entity(s_x, s_y) {
		range = 140.f;
		damage = 4;
		cooldown = 30;
		timer = 0;
		currentTarget = nullptr;
		bulletX = 0;
		bulletY = 0;
		bulletSpeed = 2.5f;
		bulletActive = false;
		bulletTarget = nullptr;
		currentTarget = nullptr;
		level = 1;
	}
	virtual void attack(Enemy* enemies[], int count, float titlesize) = 0; //pure virtual functions to make it
	virtual void upgrade() = 0;
	virtual void draw(sf::RenderWindow&, float, float, float) = 0;   // abstract class
	void drawBase(sf::RenderWindow& window, float offsetX, float offsetY, float titlesize) {
		sf::CircleShape tower(titlesize * 0.22f);
		tower.setFillColor(sf::Color::Yellow);
		tower.setPosition(x + titlesize * 0.28f + offsetX, y + titlesize * 0.28f + offsetY);
		tower.setOutlineThickness(level);
		tower.setOutlineColor(sf::Color::Red);
		window.draw(tower);
	}
	void draw_attack(sf::RenderWindow& window, float offsetX, float offsetY, float titlesize) {
		if (currentTarget == nullptr || !(currentTarget->isalive()))
			return;     //validatioin for the current target

		sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f(offsetX + x + titlesize / 2,offsetY + y + titlesize / 2)),
			sf::Vertex(sf::Vector2f(offsetX + currentTarget->getter_x() + titlesize * 0.18f,
				offsetY + currentTarget->getter_y() + titlesize * 0.18f))
		};
		window.draw(line, 2, sf::Lines);
	}
	void baseattack(Enemy* enemies[], int count, float titlesize) {
		if (timer > 0) {         //to slow down the attacking
			timer--;
			return;

		}
		if (bulletActive) {  //one bullet at a time
			return;
		}
		Enemy* target = nullptr;
		float nearest_enemy = range * range; //square because i am not using the square root on the RHS

		float tower_centerX = x + titlesize / 2;
		float tower_centerY = y + titlesize / 2;

		for (int i = 0;i < count;i++) {
			if (enemies[i] != nullptr && enemies[i]->isalive()) {

				float enemy_centerX = enemies[i]->getter_x() + titlesize * 0.18f;  //using center for the better animation later
				float enemy_centerY = enemies[i]->getter_y() + titlesize * 0.18f;

				float dx = tower_centerX - enemy_centerX;
				float dy = tower_centerY - enemy_centerY;

				float distance = dx * dx + dy * dy;  // nt using the cmath

				if (distance <= nearest_enemy) {
					nearest_enemy = distance;
					target = enemies[i];
					currentTarget = target;
					if (target != nullptr && timer == 0) {
						bulletX = x + titlesize / 2;
						bulletY = y + titlesize / 2;

						bulletTarget = target;
						bulletActive = true;
						timer = cooldown;
					}
				}
			}
		}


		if (target != nullptr)
			currentTarget = target;
		else
			currentTarget = nullptr;
	}
	void update_bullet(float titlesize) {
		if (!bulletActive || bulletTarget == nullptr)
			return;

		if (!(bulletTarget->isalive())) {
			bulletActive = false;
			bulletTarget = nullptr;
			return;
		}

		float enemyX = bulletTarget->getter_x() + titlesize * 0.18f;
		float enemyY = bulletTarget->getter_y() + titlesize * 0.18f;

		float dx = enemyX - bulletX;
		float dy = enemyY - bulletY;

		if (dx > 0)
			bulletX += bulletSpeed;
		else if (dx < 0)
			bulletX -= bulletSpeed;
		if (dy > 0)
			bulletY += bulletSpeed;
		else if (dy < 0)
			bulletY -= bulletSpeed;

		float hitdx = enemyX - bulletX;
		float hitdy = enemyY - bulletY;

		float hitDistance = hitdx * hitdx + hitdy * hitdy;

		if (hitDistance < 25) {
			bulletTarget->takeDamage(damage);
			bulletActive = false;
			bulletTarget = nullptr;
		}
	}
	void draw_bullet(sf::RenderWindow& window, float offsetX, float offsetY, float titlesize) {
		if (!bulletActive)
			return;

		sf::CircleShape bullet(4.f);
		bullet.setFillColor(sf::Color::White);
		bullet.setPosition(offsetX + bulletX, offsetY + bulletY);
		window.draw(bullet);
	}
	void clearDead_Targets(Enemy* deadEnemy) {
		if (currentTarget == deadEnemy) {
			currentTarget = nullptr;
		}
		if (bulletTarget == deadEnemy) {
			bulletActive = false;
			bulletTarget = nullptr;
		}
	}
	float getter_x() const {
		return x;
	}

	float getter_y() const {
		return y;
	}
	int getLevel() const {
		return level;
	}

	virtual ~Tower() {}
};
class CannonTower : public Tower {
public:
	CannonTower(float x, float y) : Tower(x, y) {
		range = 140.f;
		damage = 12;
		cooldown = 45;
	}

	void attack(Enemy* enemies[], int count, float titlesize) override {
		baseattack(enemies, count, titlesize); // it will call the function defined in the tower as i already wrote it 
	}

	void draw(sf::RenderWindow& window, float offsetX, float offsetY, float titlesize) override {
		drawBase(window, offsetX, offsetY, titlesize); // same it will refer to the funtion of the tower
	}
	void upgrade() override {

		if (level == 1) {
			damage += 8;
			cooldown -= 10;
			level++;
		}

		else if (level == 2) {
			damage += 10;
			range += 20.f;
			level++;
		}
	}
};
class SniperTower : public Tower {
public:
	SniperTower(float x, float y) : Tower(x, y) {
		range = 240.f;
		damage = 20;
		cooldown = 70;
	}

	void attack(Enemy* enemies[], int count, float titlesize) override {
		baseattack(enemies, count, titlesize);
	}

	void draw(sf::RenderWindow& window, float offsetX, float offsetY, float titlesize) override {
		sf::CircleShape tower(titlesize * 0.22f);
		tower.setFillColor(sf::Color::Magenta);
		tower.setPosition(x + titlesize * 0.28f + offsetX,
			y + titlesize * 0.28f + offsetY);
		tower.setOutlineThickness(level);
		tower.setOutlineColor(sf::Color::White);
		window.draw(tower);
	}
	void upgrade() override {

		if (level == 1) {
			damage += 15;
			range += 30.f;
			level++;
		}

		else if (level == 2) {
			cooldown -= 20;
			damage += 10;
			level++;
		}
	}
};
class MachineGunTower : public Tower {
public:
	MachineGunTower(float x, float y) : Tower(x, y) {
		range = 110.f;
		damage = 3;
		cooldown = 10;
	}

	void attack(Enemy* enemies[], int count, float titlesize) override {
		baseattack(enemies, count, titlesize);
	}

	void draw(sf::RenderWindow& window, float offsetX, float offsetY, float titlesize) override {
		sf::CircleShape tower(titlesize * 0.22f);
		tower.setFillColor(sf::Color::Cyan);
		tower.setPosition(x + titlesize * 0.28f + offsetX,
			y + titlesize * 0.28f + offsetY);
		tower.setOutlineThickness(level);
		tower.setOutlineColor(sf::Color::White);
		window.draw(tower);
	}
	void upgrade() override {

		if (level == 1) {
			cooldown -= 3;
			damage += 2;
			level++;
		}

		else if (level == 2) {
			cooldown -= 2;
			range += 20.f;
			damage += 3;
			level++;
		}
	}
};

class SplashTower : public Tower {
public:

	SplashTower(float x, float y) : Tower(x, y) {
		range = 130.f;
		damage = 10;
		cooldown = 55;
	}

	void attack(Enemy* enemies[], int count, float titlesize) override {

		if (timer > 0) {
			timer--;
			return;
		}

		Enemy* target = nullptr;

		float nearest_enemy = range * range;

		float tower_centerX = x + titlesize / 2;
		float tower_centerY = y + titlesize / 2;

		for (int i = 0; i < count; i++) {

			if (enemies[i] != nullptr && enemies[i]->isalive()) {

				float enemy_centerX =
					enemies[i]->getter_x() + titlesize * 0.18f;

				float enemy_centerY =
					enemies[i]->getter_y() + titlesize * 0.18f;

				float dx = tower_centerX - enemy_centerX;
				float dy = tower_centerY - enemy_centerY;

				float distance = dx * dx + dy * dy;

				if (distance <= nearest_enemy) {
					nearest_enemy = distance;
					target = enemies[i];
				}
			}
		}

		if (target != nullptr) {
			currentTarget = target;

			float splashRadius = 80.f;

			if (level == 2)
				splashRadius = 100.f;
			else if (level == 3)
				splashRadius = 130.f;

			float targetX = target->getter_x();
			float targetY = target->getter_y();

			for (int i = 0; i < count; i++) {

				if (enemies[i] != nullptr &&
					enemies[i]->isalive()) {

					float dx =
						enemies[i]->getter_x() - targetX;

					float dy =
						enemies[i]->getter_y() - targetY;

					float splashDistance =
						dx * dx + dy * dy;

					if (splashDistance <=
						splashRadius * splashRadius) {

						enemies[i]->takeDamage(damage);
					}
				}
			}

			timer = cooldown;
		}
	}

	void draw(sf::RenderWindow& window,
		float offsetX,
		float offsetY,
		float titlesize) override {

		sf::CircleShape tower(titlesize * 0.22f);

		tower.setFillColor(sf::Color(255, 140, 0));

		tower.setPosition(
			x + titlesize * 0.28f + offsetX,
			y + titlesize * 0.28f + offsetY
		);

		tower.setOutlineThickness(level);

		tower.setOutlineColor(sf::Color::White);

		window.draw(tower);
	}

	void upgrade() override {

		if (level == 1) {

			damage += 6;

			range += 15.f;

			level++;
		}

		else if (level == 2) {

			damage += 8;

			cooldown -= 10;

			level++;
		}
	}
};
class SlowTower : public Tower {
public:
	SlowTower(float x, float y) : Tower(x, y) {
		range = 130.f;
		damage = 0;
		cooldown = 0;
	}

	void attack(Enemy* enemies[], int count, float titlesize) override {
		float tower_centerX = x + titlesize / 2;
		float tower_centerY = y + titlesize / 2;

		float slowFactor = 0.5f;   // slows to 50% speed
		if (level == 2) slowFactor = 0.4f;
		if (level == 3) slowFactor = 0.3f;

		for (int i = 0; i < count; i++) {
			if (enemies[i] != nullptr && enemies[i]->isalive()) {

				float ex = enemies[i]->getter_x() + titlesize * 0.18f;
				float ey = enemies[i]->getter_y() + titlesize * 0.18f;

				float dx = tower_centerX - ex;
				float dy = tower_centerY - ey;
				float dist = dx * dx + dy * dy;

				if (dist <= range * range) {
					enemies[i]->setSpeed(enemies[i]->getBaseSpeed() * slowFactor);
				}
			}
		}
	}

	void draw(sf::RenderWindow& window, float offsetX, float offsetY, float titlesize) override {
		sf::CircleShape tower(titlesize * 0.22f);
		tower.setFillColor(sf::Color::Blue);
		tower.setPosition(x + titlesize * 0.28f + offsetX,
			y + titlesize * 0.28f + offsetY);
		tower.setOutlineThickness(level);
		tower.setOutlineColor(sf::Color::White);
		window.draw(tower);
	}

	void upgrade() override {
		if (level == 1) {
			range += 20.f;
			level++;
		}
		else if (level == 2) {
			range += 20.f;
			level++;
		}
	}
};

class WaveManager {
private:
	int current_wave;
	int enemies_spawned;
	int spawn_timer;
	int spawn_delay;

public:
	WaveManager() {
		current_wave = 0;
		enemies_spawned = 0;
		spawn_timer = 0;
		spawn_delay = 300;
	}

	bool gameFinished() {
		return current_wave >= wave_count;
	}

	void update(Enemy* enemies[]) {
		if (current_wave >= wave_count)
			return;
		if (gameFinished())
			return;

		if (spawn_timer > 0) {
			spawn_timer--;
		}

		if (spawn_timer <= 0 && enemies_spawned < waves[current_wave]) {
			spawnEnemy(enemies);
		}
	}

	void spawnEnemy(Enemy* enemies[]) {
		for (int i = 0; i < max_enemies; i++) {

			if (i < max_enemies && enemies[i] == nullptr) {

				float startX = -60 - enemies_spawned * 40;
				float startY = 0;

				if (enemies_spawned % 5 == 4)
					enemies[i] = new RegeneratingEnemy(startX, startY);
				else if (enemies_spawned % 4 == 0)
					enemies[i] = new BasicEnemy(startX, startY);
				else if (enemies_spawned % 4 == 1)
					enemies[i] = new FastEnemy(startX, startY);
				else if (enemies_spawned % 4 == 2)
					enemies[i] = new TankEnemy(startX, startY);
				else
					enemies[i] = new FlyingEnemy(0, 100*1.5f);

				enemies_spawned++;
				spawn_timer = spawn_delay;
				break;
			}
		}
	}

	bool waveFinished(Enemy* enemies[]) {
		if (enemies_spawned < waves[current_wave])
			return false;

		for (int i = 0; i < max_enemies; i++) {
			if (enemies[i] != nullptr)
				return false;
		}

		return true;
	}

	void nextWave() {
		current_wave++;
		enemies_spawned = 0;
		spawn_timer = 60;
	}

	int getCurrentWave() {
		return current_wave;
	}
};



// removing dead enemies function
void removing_DeadEnemies(Enemy* enemies[], Tower* towers[], int tower_count, int& lives, int& gold) {
	for (int i = 0; i < max_enemies; i++) {
		if (enemies[i] != nullptr && enemies[i]->isReadyForDeletion()) {
			if (enemies[i]->hasEscaped()) {
				lives--;
			}
			else {
				gold += enemies[i]->get_Reward();   // example of run time polymorphism
			}
			for (int j = 0; j < tower_count; j++) {
				towers[j]->clearDead_Targets(enemies[i]);
			}

			delete enemies[i];
			enemies[i] = nullptr;
		}
	}
}


int main()
{
	WaveManager wave;
	int lives = 10;
	int gold = 100;
	int state = 0;  // 0-playing 1-Game over 2-Win
	int selectedTower = 1;
	int highScore = 0;
	int highGold = 0;
	bool scoreSaved = false;

	// read existing high score from file
	ifstream readFile("highscore.txt");
	if (readFile.is_open()) {
		readFile >> highScore >> highGold;
		readFile.close();
	}


	// old system
	// Enemy* enemies[max_enemies];
	// enemies[0] = new BasicEnemy(-60, 0); //() for the running of the constructor
	// enemies[1] = new FastEnemy(-120, 0);// negatie sign so it starts from out of the screen
	// enemies[2] = new TankEnemy(-180, 0);

	// new system
	Enemy* enemies[max_enemies];

	for (int i = 0;i < max_enemies;i++) {
		enemies[i] = nullptr;
	}


	float titlesize = 100.f; //it will define the width and length
	float mapWidth = 8 * titlesize;
	float mapHeight = 6 * titlesize;
	float offsetX = (1200 - mapWidth) / 2;  //this is for the fixing of the scree issue happening in beginning
	float offsetY = (1000 - mapHeight) / 2;
	sf::RenderWindow window(sf::VideoMode(1200, 1000), "Tower Defense");
	sf::RectangleShape rectangle(sf::Vector2f(titlesize, titlesize));

	sf::Font font;    //font loading 
	font.loadFromFile("ARIAL.ttf");

	sf::Text hud;
	hud.setFont(font);
	hud.setCharacterSize(28);
	hud.setFillColor(sf::Color::White);
	hud.setPosition(40.f, 30.f);

	sf::Text controls;
	controls.setFont(font);
	controls.setCharacterSize(22);
	controls.setFillColor(sf::Color::White);
	controls.setPosition(40.f, 75.f);
	hud.setFont(font);
	hud.setCharacterSize(28);
	hud.setFillColor(sf::Color::White);
	hud.setPosition(40.f, 30.f);

	sf::Text endText;
	endText.setFont(font);
	endText.setCharacterSize(60);
	endText.setFillColor(sf::Color::White);
	endText.setPosition(350.f, 400.f);

	Tower* towers[max_towers];    //pointer to store the number of towers
	int tower_count = 0;
	for (int i = 0;i < max_towers;i++) {
		towers[i] = nullptr;
	}



	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Num1)
					selectedTower = 1;
				else if (event.key.code == sf::Keyboard::Num2)
					selectedTower = 2;
				else if (event.key.code == sf::Keyboard::Num3)
					selectedTower = 3;
				else if (event.key.code == sf::Keyboard::Num4)
					selectedTower = 4;
				else if (event.key.code == sf::Keyboard::Num5)
					selectedTower = 5;
			}

			if (event.type == sf::Event::MouseButtonPressed &&   //upgrade
				event.mouseButton.button == sf::Mouse::Right) {

				if (state != 0)  //to prevent from upgrading after the game ends
					continue;


				int mouseX = event.mouseButton.x;
				int mouseY = event.mouseButton.y;

				int col = (mouseX - offsetX) / titlesize;
				int row = (mouseY - offsetY) / titlesize;

				for (int i = 0; i < tower_count; i++) {

					if (towers[i] != nullptr) {

						if (towers[i]->getter_x() == col * titlesize &&
							towers[i]->getter_y() == row * titlesize) {

							int upgradeCost = 30 * towers[i]->getLevel();

							if (towers[i]->getLevel() < 3 &&
								gold >= upgradeCost) {

								towers[i]->upgrade();

								gold -= upgradeCost;
							}
						}
					}
				}
			}

			if (event.type == sf::Event::MouseButtonPressed &&  //handling of the mouse button
				event.mouseButton.button == sf::Mouse::Left) {

				if (state != 0)
					continue;

				int mouseX = event.mouseButton.x;
				int mouseY = event.mouseButton.y;

				int col = (mouseX - offsetX) / titlesize;
				int row = (mouseY - offsetY) / titlesize;

				if (row >= 0 && row < 6 && col >= 0 && col < 8) {

					bool path = (row == 0 && col <= 7) || (row == 1 && col == 7) || (row == 2 && col <= 7) ||
						(row == 3 && col == 0) || (row == 4 && col == 0) || (row == 5 && col <= 7);

					bool occupied = false;    // to prevent placing of multiple towers on the same block

					for (int i = 0; i < tower_count; i++) {
						if (towers[i] != nullptr) {

							if (towers[i]->getter_x() == col * titlesize &&
								towers[i]->getter_y() == row * titlesize) {

								occupied = true;
								break;
							}
						}
					}

					int towerCost = 25;
					if (selectedTower == 1)
						towerCost = 25;    // CAnnon
					else if (selectedTower == 2)
						towerCost = 40;    //Sniper

					else if (selectedTower == 3)
						towerCost = 30;    //MAchine Gun
					else if (selectedTower == 4)
						towerCost = 50;  //splash tower
					else if (selectedTower == 5)
						towerCost = 35;  // slow tower

					if (!path && !occupied && tower_count < max_towers && gold >= towerCost) {
						float towerX = col * titlesize;
						float towerY = row * titlesize;

						if (selectedTower == 1)
							towers[tower_count] = new CannonTower(towerX, towerY);
						else if (selectedTower == 2)
							towers[tower_count] = new SniperTower(towerX, towerY);
						else if (selectedTower == 3)
							towers[tower_count] = new MachineGunTower(towerX, towerY);
						else if (selectedTower == 4)
							towers[tower_count] = new SplashTower(towerX, towerY);
						else if (selectedTower == 5)
							towers[tower_count] = new SlowTower(towerX, towerY);
						gold -= towerCost;
						tower_count++;
					}
				}
			}
		}

		window.clear();
		//making of the tiles
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 8; j++) {
				rectangle.setPosition(offsetX + j * titlesize,
					offsetY + i * titlesize);

				if ((i == 0 && j <= 7) || (i == 1 && j == 7) || (i == 2 && j <= 7) || (i == 3 && j == 0) ||
					(i == 4 && j == 0) || (i == 5 && j <= 7)) {
					rectangle.setFillColor(sf::Color::Blue);
				}
				else {
					rectangle.setFillColor(sf::Color::Green);
				}

				rectangle.setOutlineThickness(1);
				rectangle.setOutlineColor(sf::Color::Black);

				window.draw(rectangle);
			}
		}
		if (state == 0) {
			wave.update(enemies);
			//movement of the enemies
			for (int i = 0; i < max_enemies; i++) {
				if (enemies[i] != nullptr) {
					enemies[i]->move(titlesize);
					enemies[i]->draw(window, offsetX, offsetY, titlesize);
					enemies[i]->drawHPBar(window, offsetX, offsetY, titlesize);
				}
			}
		}
		removing_DeadEnemies(enemies, towers, tower_count, lives, gold);
		if (lives <= 0) {
			state = 1; // GAME OVER
		}

		if (wave.gameFinished()) {
			bool enemiesRemaining = false;

			for (int i = 0; i < max_enemies; i++) {
				if (enemies[i] != nullptr) {
					enemiesRemaining = true;
					break;
				}
			}

			if (!enemiesRemaining) {
				state = 2; // WIN
			}
		}

		for (int i = 0; i < max_enemies; i++) {
			if (enemies[i] != nullptr && enemies[i]->isalive()) {
				enemies[i]->setSpeed(enemies[i]->getBaseSpeed());
			}
		}
		//firing logic
		if (state == 0) {
			for (int i = 0; i < tower_count; i++) {
				towers[i]->attack(enemies, max_enemies, titlesize);
				towers[i]->update_bullet(titlesize);
				towers[i]->draw_bullet(window, offsetX, offsetY, titlesize);
				towers[i]->draw_attack(window, offsetX, offsetY, titlesize);
				towers[i]->draw(window, offsetX, offsetY, titlesize);
			}
		}
		bool enemiesRemaining = false;

		for (int i = 0; i < max_enemies; i++) {
			if (enemies[i] != nullptr) {
				enemiesRemaining = true;
				break;
			}
		}
		if (state == 0 && wave.waveFinished(enemies)) {
			wave.nextWave();
		}
		if (state == 0 && wave.gameFinished() && !enemiesRemaining)
		{
			state = 2; // WIN
		}
		int displayWave = wave.getCurrentWave() + 1;
		if (displayWave > wave_count) displayWave = wave_count;

		hud.setString("Wave: " + to_string(displayWave) +
			"   Gold: " + to_string(gold) +
			"   Lives: " + to_string(lives));

		if (selectedTower == 1)
			controls.setString("1:Cannon  2:Sniper  3:MachineGun  4:Splash  5:Slow  Selected: Cannon  Right Click = Upgrade");
		else if (selectedTower == 2)
			controls.setString("1:Cannon  2:Sniper  3:MachineGun  4:Splash  5:Slow  Selected: Sniper  Right Click = Upgrade");
		else if (selectedTower == 3)
			controls.setString("1:Cannon  2:Sniper  3:MachineGun  4:Splash  5:Slow Selected: MachineGun  Right Click = Upgrade");
		else if (selectedTower == 4)
			controls.setString("1:Cannon  2:Sniper  3:MachineGun  4:Splash  5:Slow  Selected: Splash Right Click = Upgrade");
		else if (selectedTower == 5)
			controls.setString("1:Cannon  2:Sniper  3:MachineGun  4:Splash  5:Slow  Selected: Slow  RightClick=Upgrade");
		window.draw(controls);
		window.draw(hud);

		if (state == 1) {
			endText.setString("GAME OVER\nWave Reached: " + to_string(wave.getCurrentWave() + 1) +"   Gold: " + to_string(gold) +
				"\nBest Wave: " + to_string(highScore) +"   Best Gold: " + to_string(highGold));
			window.draw(endText);
		}
		if (state == 1 && !scoreSaved) {
			int reached = wave.getCurrentWave() + 1;
			if (reached > highScore || (reached == highScore && gold > highGold)) {
				highScore = reached;
				highGold = gold;
			}

			ofstream writeFile("highscore.txt");
			if (writeFile.is_open()) {
				writeFile << highScore << " " << highGold;
				writeFile.close();
			}
			scoreSaved = true;
		}

		if (state == 2 && !scoreSaved) {
			if (wave_count > highScore || (wave_count == highScore && gold > highGold)) {
				highScore = wave_count;
				highGold = gold;
			}

			ofstream writeFile("highscore.txt");
			if (writeFile.is_open()) {
				writeFile << highScore << " " << highGold;
				writeFile.close();
			}
			scoreSaved = true;	
		}

		if (state == 2) {
			endText.setString("YOU WIN!\nGold Remaining: " + to_string(gold) +"\nBest Wave: " + to_string(highScore) +
				"   Best Gold: " + to_string(highGold));
			window.draw(endText);
		}
		window.display();

	}
	// deletion
	for (int i = 0; i < max_enemies; i++) {
		delete enemies[i];
	}
	for (int i = 0; i < tower_count; i++) {
		delete towers[i];
	}

	return 0;
}