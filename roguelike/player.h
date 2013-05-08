#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cassert>
using namespace std;

/************************************************
Player class

    Player()

*************************************************/
class Player : public Character
{
public:
    Inventory playerInventory;
    //0 = armor
    //1 = weapon
    //2 = NYI
    //3 = NYI
    //4 = NYI
    //5 = NYI
    Item equipped[5];

    // Create a player with default attributes.
    Player(int inLevel, int inHealth, int inMagicAmount, int inMagicAmount_cap, int inHealth_cap,
           int inDamage, int inMagicPower, int inDefence, int inMagicDefence, int inEvasion,
           int inCritical, int inExperience, int inExperience_Cap)
    {
        level = inLevel;
        health = inHealth;
        magicAmount = inMagicAmount;
        magicAmount_Cap = inMagicAmount_cap;
        health_cap = inHealth_cap;
        damage = inDamage;
        magicPower = inMagicPower;
        defense = inDefence;
        magicDefense = inMagicDefence;
        evasion = inEvasion;
        critical = inCritical;
        Experience = inExperience;
        //player reaches lvl 2 with 100 experience
        Experience_Cap = inExperience_Cap;

        for (int i = 0; i < 5; i++)
            equipped[i].setName("");
    }
    int getLevel()
    {
        return level;
    }
    void gainExperience(int inEnemyLevel)
    {
        XPgained = inEnemyLevel * 10;
        Experience = Experience + XPgained;
        if (Experience >= Experience_Cap)
        {
            levelUp();
        }
    }
    int getXPgained()
    {
        return XPgained;
    }
    void levelUp()
    {
        move(44, 0);
        //printw("LEVEL UP!! \n");
        //randomchance is variable for randomization
        int randomChance = (rand() % 100);
        //chance to increase health cap
        if (randomChance > 29)
        {
            health_cap = (health_cap/5) + health_cap;
            //printw("Max Health Increased! \n");
        }
        //give full health
        health = health_cap;

        //chance to increase magic amount cap
        randomChance = (rand() % 100);
        if (randomChance > 29)
        {
            magicAmount_Cap = (magicAmount_Cap/5) + magicAmount_Cap;
            //printw("Max MP increased! \n);
        }
        //give full MP
        magicAmount = magicAmount_Cap;

        //chance to increase damage
        randomChance = (rand() % 100);
        if (randomChance > 29)
        {
            damage++;
            //printw("Damage Increased!\n");
        }
        //chance to increase magic damage
        randomChance = (rand() % 100);
        if (randomChance > 29)
        {
            magicPower++;
            //printw("Magic Damage Increased!\n");
        }
        //chance to increase defense
        randomChance = (rand() % 100);
        if (randomChance > 29)
        {
            defense++;
            //printw("Defense Increased! \n");
        }
        //chance to increase magic defense
        randomChance = (rand() % 100);
        if (randomChance > 49)
        {
            magicDefense++;
            //printw("Magic Defense Increased! \n");
        }
        //chance to increase evasion
        randomChance = (rand() % 100);
        if (randomChance > 79)
        {
            evasion++;
            //printw("Evasion Increased! \n");
        }
        randomChance = (rand() % 100);
        //chance to increase critical
        if (randomChance > 79)
        {
            critical++;
            //printw("Critical Increased! \n");
        }
        Experience_Cap = Experience_Cap * 1.2;
        Experience = 0;
        level++;
        if (level == 3)
        {
            printw("You can now use Directional magic attack! \n");
        }
        if (level == 4)
        {
            printw("You can now use Heal magic! \n");
        }
    }
    //method to determine if player will get a critical hit
    bool CritHit()
    {
        int randomChance = (rand() % 100);
        if (randomChance < critical)
        {
            successfulCrit = true;
            return successfulCrit;
        }
        else
        {
            successfulCrit = false;
            return successfulCrit;
        }
    }
    //method to determine if player will evade an enemy attack
    bool evade()
    {
        int randomChance = (rand() % 100);
        if (randomChance < evasion)
        {
            successfulEvade = true;
            return successfulEvade;
        }
        else
        {
            successfulEvade = false;
            return successfulEvade;
        }
    }
    void useStairs(Floor*& currentFloor)
    {
        move(44, 0);
        if (currentFloor -> tileArray[currentX][currentY].hasDownStairs() == 1)
        {
            currentFloor = currentFloor -> next;
            printw("You moved down a floor.");
        }
        else if (currentFloor -> tileArray[currentX][currentY].hasUpStairs() == 1)
        {
            currentFloor = currentFloor -> prev;
            printw("You moved up a floor.");
        }
        else
        {
            printw("You are not currently on any stairs...");
        }

    }
    void movePlayer(char input, Floor*& floor, Enemy enemyArray[50], Item itemArray[50])
    {
        move(44, 0);
        // Destination X,Y
        int destX = currentX;
        int destY = currentY;

        // Up
        if (input == 3)
            destX = currentX-1;

        // Left
        else if (input == 4)
            destY = currentY-1;

        // Right
        else if (input == 5)
            destY = currentY+1;

        // Down
        else if (input == 2)
            destX = currentX+1;

        //if you move into a tile with an enemy
        if (floor -> tileArray[destX][destY].hasEnemy() == 1)
        {
            for (int q = 0; q < 51; q++)
            {
            //enemy damages player
                if ((enemyArray[q].getCurrentX() == destX) &&
                    (enemyArray[q].getCurrentY() == destY))
                {
                    takeMeleeDamage(enemyArray[q].getDamage());
                    char buffer [50];
                    sprintf(buffer, "%i", getDamageTkn());
                    printw("The enemy attacked you for ");
                    printw(buffer);
                    printw(" damage!\n");
                }
            }
        }

        // Tile has an item.
        else if (floor -> tileArray[destX][destY].hasItem() == 1)
        {
            for (int q = 0; q < 50; q++)
            {
                if ((itemArray[q].getCurrentX() == destX) && (itemArray[q].getCurrentY() == destY))
                {
                    // Add the new item. Remove item from map. Move player.
                    playerInventory.storage.push_back(itemArray[q]);
                    floor -> tileArray[destX][destY].setItem(0);
                    floor -> tileArray[currentX][currentY].setPlayer(0);
                    floor -> tileArray[destX][destY].setPlayer(1);
                    currentX = destX;
                    currentY = destY;
                    printw("You picked up an item.\n");
                }
            }
        }

        // Regular movement.
        else if (floor -> tileArray[destX][destY].hasFloor() == 1)
        {
            floor -> tileArray[currentX][currentY].setPlayer(0);
            floor -> tileArray[destX][destY].setPlayer(1);
            currentX = destX;
            currentY = destY;
        }
        else
        {
            printw("%s", "You walked into a wall, dumbass!\n");
        }
    }
    void attack(Floor*& floor, Enemy enemyArray[50])
    {
        move(44, 0);

        //assert(false); //test to see if game header is handling the attack input
        char buffer[50];
        int randomChance = (rand() % 100);
        int atkUpX = currentX - 1;
        int atkUpY = currentY;
        int atkLeftX = currentX;
        int atkLeftY = currentY - 1;
        int atkRightX = currentX;
        int atkRightY = currentY + 1;
        int atkDownX = currentX + 1;
        int atkDownY = currentY;
        //if there is an enemy above the player
        if (floor -> tileArray[atkUpX][atkUpY].hasEnemy() == 1)
        {
            //take health from enemy above player
            for (int q = 0; q < 50; q++)
            {
                if ((enemyArray[q].getCurrentX() == atkUpX) &&
                   (enemyArray[q].getCurrentY() == atkUpY) &&
                   (enemyArray[q].getHealth() > 0))
                {
                    enemyArray[q].takeMeleeDamage(damage, CritHit());

                    sprintf(buffer, "%i", enemyArray[q].getDamageTkn());
                    printw("You did ");
                    printw(buffer);
                    printw(" damage to the enemy! \n");
                    if (enemyArray[q].getHealth() < 1)
                    {
                        printw("You killed the enemy! \n");
                        gainExperience(enemyArray[q].getLevel());
                        sprintf(buffer, "%i", getXPgained());
                        printw("You gained ");
                        printw(buffer);
                        printw("XP! \n");
                        floor -> tileArray[atkUpX][atkUpY].setEnemy(0);
                    }
                    else
                    {
                        if (evade() == false)
                        {
                            takeMeleeDamage(enemyArray[q].getDamage());
                            sprintf(buffer, "%i", getDamageTkn());
                            printw("The enemy attacked you back for ");
                            printw(buffer);
                            printw(" damage! \n");
                        }
                        else
                        {
                            printw("You evaded the enemy counter!");
                        }
                    }
                }
            }
        }
        // else if there is an enemy to the left of the player
        else if (floor -> tileArray[atkLeftX][atkLeftY].hasEnemy() == 1)
        {
            //take health from enemy to the left of player
            for (int q = 0; q < 50; q++)
            {
                if ((enemyArray[q].getCurrentX() == atkLeftX) &&
                   (enemyArray[q].getCurrentY() == atkLeftY) &&
                   (enemyArray[q].getHealth() > 0))
                {
                    enemyArray[q].takeMeleeDamage(damage, CritHit());
                    char buffer[50];
                    sprintf(buffer, "%i", enemyArray[q].getDamageTkn());
                    printw("You did ");
                    printw(buffer);
                    printw(" damage to the enemy! \n");
                    if (enemyArray[q].getHealth() < 1)
                    {
                        printw("You killed the enemy! \n");
                        gainExperience(enemyArray[q].getLevel());
                        sprintf(buffer, "%i", getXPgained());
                        printw("You gained ");
                        printw(buffer);
                        printw("XP! \n");
                        floor -> tileArray[atkLeftX][atkLeftY].setEnemy(0);
                    }
                    else
                    {
                        if (evade() == false)
                        {
                            takeMeleeDamage(enemyArray[q].getDamage());
                            sprintf(buffer, "%i", getDamageTkn());
                            printw("The enemy attacked you back for ");
                            printw(buffer);
                            printw(" damage! \n");
                        }
                        else
                        {
                            printw("You evaded the enemy counter!");
                        }
                    }
                }
            }
        }
        // else if there is an enemy to the right of the player
        else if (floor -> tileArray[atkRightX][atkRightY].hasEnemy() == 1)
        {
            //take health from enemy to the right of the player
            for (int q = 0; q < 50; q++)
            {
                if ((enemyArray[q].getCurrentX() == atkRightX) &&
                   (enemyArray[q].getCurrentY() == atkRightY) &&
                   (enemyArray[q].getHealth() > 0))
                {
                    enemyArray[q].takeMeleeDamage(damage, CritHit());
                    char buffer[50];
                    sprintf(buffer, "%i", enemyArray[q].getDamageTkn());
                    printw("You did ");
                    printw(buffer);
                    printw(" damage to the enemy! \n");
                    if (enemyArray[q].getHealth() < 1)
                    {
                        printw("You killed the enemy! \n");
                        gainExperience(enemyArray[q].getLevel());
                        sprintf(buffer, "%i", getXPgained());
                        printw("You gained ");
                        printw(buffer);
                        printw("XP! \n");
                        floor -> tileArray[atkRightX][atkRightY].setEnemy(0);
                    }
                    else
                    {
                        if (evade() == false)
                        {
                            takeMeleeDamage(enemyArray[q].getDamage());
                            sprintf(buffer, "%i", getDamageTkn());
                            printw("The enemy attacked you back for ");
                            printw(buffer);
                            printw(" damage! \n");
                        }
                        else
                        {
                            printw("You evaded the enemy counter!\n");
                        }
                    }
                }
            }
        }
        // else if there is an enemy under the player
        else if (floor -> tileArray[atkDownX][atkDownY].hasEnemy() == 1)
        {
            //take health from enemy under player
            for (int q = 0; q < 55; q++)
            {
                if ((enemyArray[q].getCurrentX() == atkDownX) &&
                   (enemyArray[q].getCurrentY() == atkDownY) &&
                   (enemyArray[q].getHealth() > 0))
                {
                    enemyArray[q].takeMeleeDamage(damage, CritHit());                    char buffer[50];
                    sprintf(buffer, "%i", enemyArray[q].getDamageTkn());
                    printw("You did ");
                    printw(buffer);
                    printw(" damage to the enemy! \n");
                    if (enemyArray[q].getHealth() < 1)
                    {
                        printw("You killed the enemy! \n");
                        gainExperience(enemyArray[q].getLevel());
                        sprintf(buffer, "%i", getXPgained());
                        printw("You gained ");
                        printw(buffer);
                        printw("XP! \n");
                        floor -> tileArray[atkDownX][atkDownY].setEnemy(0);
                    }
                    else
                    {
                        if (evade() == false)
                        {
                            takeMeleeDamage(enemyArray[q].getDamage());
                            sprintf(buffer, "%i", getDamageTkn());
                            printw("The enemy attacked you back for ");
                            printw(buffer);
                            printw(" damage! \n");
                        }
                        else
                        {
                            printw("You evaded the enemy counter!");
                        }
                    }
                }
            }
        }
    }
    void directionalMagic(Floor*& floor, Enemy enemyArray[50])
    {
        move(44, 0);
        if (magicAmount >= 10)
        {
            char buffer[50];
            int randomChance = (rand() % 100);
            int atkUpX = currentX - 1;
            int atkUpY = currentY;
            int atkLeftX = currentX;
            int atkLeftY = currentY - 1;
            int atkRightX = currentX;
            int atkRightY = currentY + 1;
            int atkDownX = currentX + 1;
            int atkDownY = currentY;
            //if there is an enemy above the player
            for (int counter = 0; counter < 4; counter++)
            {
                if (floor -> tileArray[atkUpX][atkUpY].hasEnemy() == 1)
                {
                    for (int q = 0; q < 50; q++)
                    {
                        if ((enemyArray[q].getCurrentX() == atkUpX) &&
                        (enemyArray[q].getCurrentY() == atkUpY) &&
                        (enemyArray[q].getHealth() > 0))
                        {
                            enemyArray[q].takeMagicDam(getMagicPower());
                            if (enemyArray[q].getHealth() < 1)
                            {
                                gainExperience(enemyArray[q].getLevel());
                                floor -> tileArray[atkUpX][atkUpY].setEnemy(0);
                            }
                        }
                    }
                }
                atkUpX = atkUpX - 1;
            }
            for (int counter = 0; counter < 4; counter++)
            {
                if (floor -> tileArray[atkLeftX][atkLeftY].hasEnemy() == 1)
                {
                    for (int q = 0; q < 50; q++)
                    {
                        if ((enemyArray[q].getCurrentX() == atkLeftX) &&
                        (enemyArray[q].getCurrentY() == atkLeftY) &&
                        (enemyArray[q].getHealth() > 0))
                        {
                            enemyArray[q].takeMagicDam(getMagicPower());
                            if (enemyArray[q].getHealth() < 1)
                            {
                                gainExperience(enemyArray[q].getLevel());
                                floor -> tileArray[atkLeftX][atkLeftY].setEnemy(0);
                            }
                        }
                    }
                }
                atkLeftY = atkLeftY - 1;
            }
            for (int counter = 0; counter < 4; counter++)
            {
                if (floor -> tileArray[atkRightX][atkRightY].hasEnemy() == 1)
                {
                    for (int q = 0; q < 50; q++)
                    {
                        if ((enemyArray[q].getCurrentX() == atkRightX) &&
                        (enemyArray[q].getCurrentY() == atkRightY) &&
                        (enemyArray[q].getHealth() > 0))
                        {
                            enemyArray[q].takeMagicDam(getMagicPower());
                            if (enemyArray[q].getHealth() < 1)
                            {
                                gainExperience(enemyArray[q].getLevel());
                                floor -> tileArray[atkRightX][atkRightY].setEnemy(0);
                            }
                        }
                    }
                }
                atkRightY = atkRightY + 1;
            }
            for (int counter = 0; counter < 4; counter++)
            {
                if (floor -> tileArray[atkDownX][atkDownY].hasEnemy() == 1)
                {
                    for (int q = 0; q < 50; q++)
                    {
                        if ((enemyArray[q].getCurrentX() == atkDownX) &&
                        (enemyArray[q].getCurrentY() == atkDownY) &&
                        (enemyArray[q].getHealth() > 0))
                        {
                            enemyArray[q].takeMagicDam(getMagicPower());
                            if (enemyArray[q].getHealth() < 1)
                            {
                                gainExperience(enemyArray[q].getLevel());
                                floor -> tileArray[atkDownX][atkDownY].setEnemy(0);
                            }
                        }
                    }
                }
                atkDownX = atkDownX + 1;
            }
            magicAmount = magicAmount - 10;
        }
        else
        {
            printw("You don't have enough MP!");
        }
    }
    void healMagic()
    {
        move(44, 0);
        if (health == health_cap)
        {
            printw("You already have full HP!");
        }
        else if (magicAmount >= 7)
        {
            magicAmount = magicAmount - 7;
            health = health + 20;
            if (health > health_cap)
            {
                health = health_cap;
            }
        }
        else
        {
            printw("You don't have enough MP!");
        }
    }
    void takeMeleeDamage(int inEnemyDamage)
    {
        char bell = 7;
        damageTkn = ((inEnemyDamage * 11) - (defense * 10));
        if (damageTkn < 0)
        {
            damageTkn = 0;
        }
        health = health - damageTkn;
        cout<<bell;
    }

    int getDamageTkn()
    {
        return damageTkn;
    }

    void equipItem(int newItem)
    {
        int oldItem = playerInventory.storage[newItem].getItemType();

        // If there is no item in the new item's slot.
        if (equipped[oldItem].getName() == "")
        {
            addStats(playerInventory.storage[newItem]);
            equipped[oldItem] = playerInventory.storage[newItem];
            playerInventory.storage.erase(playerInventory.storage.begin() + newItem);

        }
        // If we're switching items.
        else if (equipped[oldItem].getName() != "")
        {
            removeStats(equipped[oldItem]);
            playerInventory.storage.push_back(equipped[oldItem]);
            addStats(playerInventory.storage[newItem]);
            equipped[oldItem] = playerInventory.storage[newItem];
            playerInventory.storage.erase(playerInventory.storage.begin() + newItem);
        }


    }

    void removeStats(Item oldItem)
    {
        health_cap = health_cap - oldItem.getHealthBonus();
        magicAmount_Cap = magicAmount_Cap - oldItem.getMagicAmount_CapBonus();
        damage = damage - oldItem.getDamageBonus();
        magicPower = magicPower - oldItem.getMagicDamageBonus();
        defense = defense - oldItem.getDefenseBonus();
        magicDefense = magicDefense - oldItem.getMagicDefenseBonus();
        evasion = evasion - oldItem.getEvasionBonus();
        critical = critical - oldItem.getCriticalBonus();
    }

    void addStats(Item newItem)
    {
        health_cap = health_cap + newItem.getHealthBonus();
        magicAmount_Cap = magicAmount_Cap + newItem.getMagicAmount_CapBonus();
        damage = damage + newItem.getDamageBonus();
        magicPower = magicPower + newItem.getMagicDamageBonus();
        defense = defense + newItem.getDefenseBonus();
        magicDefense = magicDefense + newItem.getMagicDefenseBonus();
        evasion = evasion + newItem.getEvasionBonus();
        critical = critical + newItem.getCriticalBonus();
    }

        void printEquipped()
    {
        int counter = 0;
        int input;
        attron (COLOR_PAIR(6));
        for (int i = 2; i < 35 ; i += 10)
            for (int j = 10; j < 80; j += 18)
            {

                move(i-1, j-1);
                printw("--------------------");
                move(i, j-1);
                printw("-                  -");
                move(i+1, j-1);
                printw("-                  -");
                move(i+2, j-1);
                printw("-                  -");
                move(i+3, j-1);
                printw("-                  -");
                move(i+4, j-1);
                printw("-                  -");
                move(i+5, j-1);
                printw("-                  -");
                move(i+6, j-1);
                printw("-                  -");
                move(i+7, j-1);
                printw("--------------------");

                move(i,j);
                printw(" %i. ", counter);
                const char *itemName = equipped[counter].getName().c_str();
                printw(itemName);

                if (equipped[counter].getName() != "")
                {
                    if (equipped[counter].getItemType() == 0)
                    {
                        move(i+1,j);
                        printw(" Defense: +%i", equipped[counter].getDefenseBonus());
                        move(i+2,j);
                        printw(" Health: +%i", equipped[counter].getHealthBonus());
                        move(i+3,j);
                        printw(" M.Defense: +%i", equipped[counter].getMagicDefenseBonus());
                        move(i+4,j);
                        printw(" Evasion: +%i", equipped[counter].getEvasionBonus());
                    }
                    else if (equipped[counter].getItemType() == 1)
                    {
                        move(i+1,j);
                        printw(" Damage: +%i", equipped[counter].getDamageBonus());
                        move(i+2,j);
                        printw(" Magic Damage: +%i", equipped[counter].getMagicDamageBonus());
                        move(i+3,j);
                        printw(" Critical: +%i", equipped[counter].getCriticalBonus());
                    }

                }
                else
                {
                    move(i,j+3);
                    printw("EMPTY");
                }

                counter++;
                if (counter == 2)
                {
                    attron (COLOR_PAIR(2));
                    return;
                }

            }
    }

};


#endif
