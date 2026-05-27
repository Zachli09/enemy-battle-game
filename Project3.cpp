#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

class Enemy {
public:
    static int total;

private:
    int instanceNum;
    int health;

public:
    Enemy(int h) {
        health = h;
        total++;
        instanceNum = total;
    }

    Enemy(const Enemy& other) {
        health = other.health;
        instanceNum = other.instanceNum;
    }

    Enemy duplicate() {
        Enemy copy(*this);
        total++;
        copy.health *= 2;
        copy.instanceNum = total;
        return copy;
    }

    bool isDead() {
        return health <= 0;
    }

    void takeDamage(int damage) {
        health -= damage;
    }

    int attack() {
        int chance = rand() % 2;

        if (chance == 1)
            return rand() % 3 + 1;
        else
            return 0;
    }

    void print() {
        cout << "Health: " << health << " (Enemy #" << instanceNum << ")";
    }
};

int Enemy::total = 0;

int main() {
    srand(time(0));

    vector<Enemy> enemies;
    enemies.push_back(Enemy(150));

    int playerHealth = 150;
    int choice;

    while (!enemies.empty() && playerHealth > 0) {
        cout << endl;
        cout << "Player Health: " << playerHealth << endl;
        cout << "There are " << enemies.size() << " enemies alive!" << endl;
        cout << endl;

        for (int i = 0; i < enemies.size(); i++) {
            cout << "Location: " << i + 1 << ": ";
            enemies[i].print();
            cout << endl;
        }

        cout << endl;
        cout << "Enter 0 to attack all enemies" << endl;
        cout << "Or enter an enemy location to attack one enemy: ";
        cin >> choice;

        while (choice < 0 || choice > enemies.size()) {
            cout << "Invalid location. Try again: ";
            cin >> choice;
        }

        if (choice == 0) {
            int damage = rand() % 16 + 15;

            cout << "You attack all enemies for " << damage << " damage!" << endl;

            for (int i = 0; i < enemies.size(); i++) {
                enemies[i].takeDamage(damage);
            }
        }
        else {
            int damage = rand() % 51 + 75;

            cout << "You attack enemy at location " << choice
                << " for " << damage << " damage!" << endl;

            enemies[choice - 1].takeDamage(damage);
        }

        enemies.erase(
            remove_if(enemies.begin(), enemies.end(),
                [&](Enemy& e) -> bool { return e.isDead(); }),
            enemies.end()
        );

        if (!enemies.empty()) {
            int enemyDamage = 0;

            for (int i = 0; i < enemies.size(); i++) {
                enemyDamage += enemies[i].attack();
            }

            cout << "Enemies attack you for " << enemyDamage << " damage!" << endl;
            playerHealth -= enemyDamage;

            if (playerHealth <= 0)
                break;

            int randomIndex = rand() % enemies.size();
            Enemy newEnemy = enemies[randomIndex].duplicate();
            enemies.push_back(newEnemy);

            cout << "An enemy duplicated itself!" << endl;
        }
    }

    cout << endl;

    if (playerHealth <= 0) {
        cout << "You lost!" << endl;
    }
    else {
        cout << "You won!" << endl;
    }

    cout << "Enemies defeated: " << Enemy::total - enemies.size() << endl;
    return 0;
}