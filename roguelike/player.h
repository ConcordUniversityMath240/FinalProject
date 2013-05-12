#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cassert>
using namespace std;

/************************************************
Player.h

Handles the types of players, actions, and leveling.

    Player()                          Three different ones, for each player type. Sets stats.
    getLevel()                        Gets the Player level.
    getHealth()                       Gets the Player's health.
    getMagicAmount()                  Gets the Player's Mana Amount.
    getMagicAmount_Cap()              Gets the Player's max Mana Amount.
    getHealth_cap()                   Gets the Player's max health amount.
    getDamage()                       Gets the Player's damage amount.
    getDefense()                      Gets the Player's defense.
    getMagicPower()                   Gets the Player's Mana Power.
    getMagicDefense()                 Gets the Player's Magic Defense.
    getEvasion()                      Gets the Player's Evasion.
    getCritical()                     Gets the Player's Critical hit number.
    getExperience()                   Gets the Player's Experience amount.
    getExperience_Cap()               Gets the Player's Experience Cap.
    getType()                         Gets the type of Player (A, M, T).
    getArrows()                       Gets the amount of arrows the Player has.
    gainExperience(int inEnemyLevel)  Allows Player to gain experience when killing.
    getXPgained()                     Gets the Player's gained experience from killing.
    levelUp()                         Levels up the Player's stats when they get enough experience.
    CritHit()                         Determines whether the Player scores a critical hit.
    evade()                           Determines if the Player evades a hit.
    useStairs(Floor*& currentFloor)movePlayer(char input, Floor*& floor, Enemy enemyArray[50], Item itemArray[50])   Allows Player to go up/down stairs
    healMagic()                       Gives power to Mage automatically/others at level 4 to regain health with magic
    takeMeleeDamage(int inEnemyDamage, bool inEvade)    Determines the damage the player takes.
    getDamageTkn()                    Gets the damage taken.
    equipItem(int newItem)            Allows Equipping of items.
    removeStats(Item oldItem)         Removes excess stats when items dequipped.
    addStats(Item newItem)            Adds extra stats when items are equipped.
    printEquipped()                   Prints the equipped items.
    setArrowAmount(int inAmount)      Returns the arrow amount.
    getArrowAmount()                  Gets the arrow amount.
    Recover_Magic()                   Player has chance to recover magic with every step.



*************************************************/
class Player : public Character
{
public:
    int Type;
    Inventory playerInventory;
    //0 = armor
    //1 = weapon
    //2 = NYI
    //3 = NYI
    //4 = NYI
    //5 = NYI
    Item equipped[5];
    Player(char inType)
    {
        printw("HELLO");
        //Three constructors for stats for
        //each type of player, Fighter, Mage,
        //and Archer, respectively
        if(inType == 'F')
        {
            Type = 1;  //Numbers used for comparison of player types
            level = 1;
            health = 1200;
            magicAmount = 40;
            magicAmount_Cap = 40;
            health_cap = 1200;
            damage = 8;
            magicPower = 0;
            defense = 4;
            magicDefense = 2;
            evasion = 3;
            critical = 6;
            Experience = 0;
            //player reaches lvl 2 with 100 experience
            Experience_Cap = 100;
            arrows = 0;

            for (int i = 0; i < 5; i++)
                equipped[i].setName("");
        }
        //mage
        else if(inType == 'M')
        {
            Type = 2;
            level = 1;
            health = 100;
            magicAmount = 80;
            magicAmount_Cap = 80;
            health_cap = 100;
            damage = 2;
            magicPower = 8;
            defense = 4;
            magicDefense = 7;
            evasion = 4;
            critical = 4;
            Experience = 0;
            Experience_Cap = 100;
            arrows = 0;

            for (int i = 0; i < 5; i++)
                equipped[i].setName("");
        }
        //archer
        else if(inType == 'A')
        {
            Type = 3;
            level = 1;
            health = 110;
            magicAmount = 40;
            magicAmount_Cap = 40;
            health_cap = 110;
            damage = 6;
            magicPower = 4;
            defense = 2;
            magicDefense = 4;
            evasion = 8;
            critical = 8;
            Experience = 0;
            Experience_Cap = 100;
            arrows = 60;

            for (int i = 0; i < 5; i++)
                equipped[i].setName("");
        }
    }


    // Create a player with default attributes.
    Player(int inLevel, int inHealth, int inHealth_cap, int inMagicAmount, int inMagicAmount_cap,
           int inDamage, int inMagicPower, int inDefence, int inMagicDefence, int inEvasion,
           int inCritical, int inExperience, int inExperience_Cap, int inType, int inArrow)
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
        Type = inType;
        arrows = inArrow;
    }


    //getters for all stats
    int getLevel()
    {
        return level;
    }

    //Adds experience after killing an enemy
    int getHealth()
    {
        return health;
    }
    int getMagicAmount()
    {
        return magicAmount;
    }
    int getMagicAmount_Cap() {
        return magicAmount_Cap;
    }
    int getHealth_cap() {
        return health_cap;
    }
    int getDamage() {
        return damage;
    }
    int getDefense() {
        return defense;
    }
    int getMagicPower() {
        return magicPower;
    }
    int getMagicDefense() {
        return magicDefense;
    }
    int getEvasion() {
        return evasion;
    }
    int getCritical() {
        return critical;
    }
    int getExperience() {
        return Experience;
    }
    int getExperience_Cap() {
        return Experience_Cap;
    }
    int getType() {
        return Type;
    }
    int getArrows() {
        return arrows;
    }
    void gainExperience(int inEnemyLevel)
    {
        XPgained = inEnemyLevel * 10;
        Experience = Experience + XPgained;
        //tests if the player gained enough XP to level up
        if (Experience >= Experience_Cap)
        {
            levelUp();
        }
    }
    int getXPgained()
    {
        return XPgained;
    }
    //resets experience, initiates chances to increase stats
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
        //Experience_Cap = Experience_Cap * 1.2;
        Experience = 0;
        level++;
        //prints for when certain abilities are unlocked
        if ((level == 3) && ((Type == 1) || (Type == 3)))
        {
            printw("You can now use Directional magic attack! \n");
        }
        if ((level == 4) && ((Type == 1) || (Type == 3)))
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
    //allows player to go up or down stairs to different floors
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
    //handles all movement for the player
    void useStairs(Floor*& currentFloor)movePlayer(char input, Floor*& floor, Enemy enemyArray[50], Item itemArray[50])
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
            for (int q = 0; q < 50; q++)
            {
            //enemy damages player
                if ((enemyArray[q].getCurrentX() == destX) &&
                    (enemyArray[q].getCurrentY() == destY))
                {
                    takeMeleeDamage(enemyArray[q].getDamage(), evade());
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

    //simple healing magic function
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
    //allows player to take damage from enemies
    void takeMeleeDamage(int inEnemyDamage, bool inEvade)
    {
        if (inEvade == true)
        {
            printw("You dodged the enemy attack!");
        }
        else
        {
            damageTkn = ((inEnemyDamage * 11) - (defense * 10));
            if (damageTkn < 0)
            {
                damageTkn = 0;
            }
            health = health - damageTkn;
            char bell = 7;
            cout<<bell; //game beeps when you take damage!
        }
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
    //adds/removes stats of items when things are equipped/dequipped
    void  removeStats(Item oldItem)
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
        //printing for inventory screen
        void printEquipped()
    {
        int counter = 0;
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

    //sets the arrow starting amount
    void setArrowAmount(int inAmount)
    {
        arrows = inAmount;
    }
    int getArrowAmount()
    {
        return arrows;
    }

    //player has a 1:4 chance of recovering 10 mana
    void Recover_Magic()
    {
        int Recover = (rand() % 100);
        //check if mana is already full
        if(Recover < 25)
        {
            if(magicAmount != magicAmount_Cap)
            magicAmount = magicAmount + 10;
        }
    }
};



#endif
