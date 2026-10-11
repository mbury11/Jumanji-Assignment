/*
 * Program Name: Jumanji - The Jungle Escape Simulation
 * File Name: main.cpp
 * Description: An interactive text-based adventure game based on Jumanji: Welcome to the Jungle.
 *              The player selects a character avatar, manages lives/health, makes critical choices,
 *              solves interactive puzzles, and attempts to escape the jungle of Jumanji.
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function declarations for game organization
void printDivider();
void printHeader(const string& title);
int getValidChoice(int minOption, int maxOption);

int main() {
    // Seed random number generator for luck-based puzzle checks
    srand(static_cast<unsigned int>(time(0)));

    // Player State Variables
    string playerName = "";
    string avatarName = "";
    string specialAbility = "";
    int lives = 3;
    int health = 100;
    bool hasJaguarEye = false;
    bool hasMap = false;

    // --- GAME INTRO ---
    printHeader("JUMANJI: THE JUNGLE ESCAPE");
    cout << "You are browsing a dusty garage sale when you spot a strange, glowing video game console." << endl;
    cout << "As you plug it in, a loud drumbeat fills the room: DUM... DUM... DUM..." << endl;
    cout << "A swirl of green light pulls you inside the screen!" << endl;
    printDivider();

    cout << "Enter your real name, adventurer: ";
    getline(cin, playerName);

    if (playerName.empty()) {
        playerName = "Player 1";
    }

    cout << "\nWelcome to Jumanji, " << playerName << "! Choose your character avatar:" << endl;
    cout << "1. Dr. Smolder Bravestone (Strength & Speed)" << endl;
    cout << "2. Ruby Roundhouse (Agility & Martial Arts)" << endl;
    cout << "3. Mouse Finbar (Zoology & Inventory Specialist)" << endl;
    cout << "Select your avatar (1-3): ";

    int avatarChoice = getValidChoice(1, 3);

    switch (avatarChoice) {
    case 1:
        avatarName = "Dr. Smolder Bravestone";
        specialAbility = "Smoldering Intensity";
        break;
    case 2:
        avatarName = "Ruby Roundhouse";
        specialAbility = "Dance Fighting";
        break;
    case 3:
        avatarName = "Mouse Finbar";
        specialAbility = "Weapon Valet & Backpack Analysis";
        break;
    }

    printDivider();
    cout << "AVATAR CONFIRMED: " << avatarName << endl;
    cout << "SPECIAL ABILITY: " << specialAbility << endl;
    cout << "LIVES REMAINING: " << lives << " [|||]" << endl;
    printDivider();

    // --- STAGE 1: THE JUNGLE DROP ---
    printHeader("STAGE 1: THE DRUMBEAT CLEARING");
    cout << "You fall from the sky and land in a dense tropical jungle." << endl;
    cout << "In front of you is a wooden crate tied with thick vines, and to your right is a path leading toward river rapids." << endl;
    cout << "What do you want to do?" << endl;
    cout << "1. Use your force to smash open the wooden crate." << endl;
    cout << "2. Head straight down the path toward the river rapids." << endl;
    cout << "3. Examine the trees to scout the area." << endl;
    cout << "Choice (1-3): ";

    int stage1Choice = getValidChoice(1, 3);

    if (stage1Choice == 1) {
        cout << "\nYou break open the crate! Inside you find the Map of Jumanji and a health tonic." << endl;
        hasMap = true;
        health = 100;
        cout << "Items acquired! Health restored to 100%." << endl;
    }
    else if (stage1Choice == 2) {
        cout << "\nYou rush down the path without checking for traps." << endl;
        cout << "A hidden snare triggers, swinging a log into your chest!" << endl;
        health -= 30;
        cout << "Ouch! You took 30 damage. Current Health: " << health << "%" << endl;
    }
    else {
        cout << "\nYou climb a tall tree and spot Van Pelt's mercenaries patrolling nearby." << endl;
        cout << "You wait quietly until they pass, safely avoiding an ambush." << endl;
    }

    printDivider();

    // --- STAGE 2: THE CROCODILE RIVER ---
    printHeader("STAGE 2: THE CROCODILE RIVER");
    cout << "You arrive at a wide, roaring river. Dozens of hungry crocodiles swim in the water." << endl;
    cout << "A rickety rope bridge spans the river, but several wooden planks are missing." << endl;

    if (hasMap) {
        cout << "[MAP BONUS] Your map shows a secret ford with shallow stepping stones upstream!" << endl;
    }

    cout << "How do you cross?" << endl;
    cout << "1. Run across the broken rope bridge as fast as you can." << endl;
    cout << "2. Use your special ability (" << specialAbility << ") to clear a path." << endl;
    cout << "3. Swim across the river." << endl;
    if (hasMap) {
        cout << "4. Take the secret shallow stepping stones upstream." << endl;
    }

    int stage2Max = hasMap ? 4 : 3;
    cout << "Choice (1-" << stage2Max << "): ";
    int stage2Choice = getValidChoice(1, stage2Max);

    if (stage2Choice == 1) {
        cout << "\nAs you run, a plank snaps beneath your foot!" << endl;
        cout << "You plummet into the river and are attacked by crocodiles!" << endl;
        lives--;
        cout << "*** YOU DIED! ***" << endl;
        cout << "A loud BOOM echoes from the sky as you respawn back on the bank." << endl;
        cout << "Lives remaining: " << lives << endl;
    }
    else if (stage2Choice == 2) {
        cout << "\nYou activate " << specialAbility << "!" << endl;
        cout << "You pull off an incredible combination move, leaping across the gap and landing safely on the far shore." << endl;
    }
    else if (stage2Choice == 3) {
        cout << "\nSwimming with hungry crocodiles was a terrible idea." << endl;
        lives--;
        cout << "*** YOU DIED! ***" << endl;
        cout << "A loud BOOM echoes from the sky as you respawn on the far bank." << endl;
        cout << "Lives remaining: " << lives << endl;
    }
    else if (stage2Choice == 4) {
        cout << "\nThanks to the map, you cross the shallow stepping stones safely without alerting a single crocodile!" << endl;
    }

    printDivider();

    // --- STAGE 3: THE ANCIENT TEMPLE PUZZLE ---
    printHeader("STAGE 3: THE JAGUAR TEMPLE PUZZLE");
    cout << "You reach the ruins of the Jaguar Temple. On a stone pedestal lies the glowing green 'Jaguar's Eye' jewel." << endl;
    cout << "To claim the jewel, you must enter the correct three-digit code into a stone dial mechanism." << endl;
    cout << "A inscription on the wall reads: 'The code is the sum of (7 x 8) + 12.'" << endl;

    int attempts = 0;
    bool puzzleSolved = false;

    while (attempts < 3 && !puzzleSolved) {
        cout << "\nEnter the code: ";
        int codeGuess;
        if (!(cin >> codeGuess)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Enter numbers only." << endl;
            continue;
        }

        if (codeGuess == 68) {
            cout << "\n*CLICK!* The stone mechanism unlocks! You retrieve the Jaguar's Eye jewel!" << endl;
            hasJaguarEye = true;
            puzzleSolved = true;
        }
        else {
            attempts++;
            cout << "Incorrect code! A dart shoots out from the temple wall!" << endl;
            health -= 25;
            if (health <= 0) {
                lives--;
                health = 100;
                cout << "*** YOU DIED FROM POISON DART! ***" << endl;
                cout << "Lives remaining: " << lives << endl;
            }
            else {
                cout << "Current Health: " << health << "%" << endl;
            }
        }
    }

    if (!puzzleSolved) {
        cout << "\nYou trigger the temple alarm! In a desperate dash, you snatch the jewel while dodging traps." << endl;
        hasJaguarEye = true;
    }

    printDivider();

    // --- FINAL STAGE: THE JAGUAR STATUE CLIMB ---
    printHeader("FINAL STAGE: THE JAGUAR STATUE");
    cout << "You stand before the massive Jaguar Statue at the highest peak of the jungle." << endl;
    cout << "Van Pelt's motorcycle mercenaries surround the base of the statue!" << endl;
    cout << "How will you reach the top to insert the jewel?" << endl;
    cout << "1. Charge through the center of the mercenary line." << endl;
    cout << "2. Scale the steep rocky cliff behind the statue." << endl;
    cout << "3. Create a distraction using an explosive fuel canister." << endl;
    cout << "Choice (1-3): ";

    int finalChoice = getValidChoice(1, 3);

    if (finalChoice == 1) {
        if (avatarChoice == 1) {
            cout << "\nUsing Dr. Smolder Bravestone's raw strength, you knock aside the bikers and charge up the path!" << endl;
        }
        else {
            cout << "\nYou try to brute force your way through, taking heavy gunfire." << endl;
            health -= 40;
        }
    }
    else if (finalChoice == 2) {
        if (avatarChoice == 2) {
            cout << "\nUsing Ruby Roundhouse's agility, you effortlessly scale the sheer cliff face to the top!" << endl;
        }
        else {
            cout << "\nYou manage to climb the cliff, but slip near the top, taking 20 damage." << endl;
            health -= 20;
        }
    }
    else if (finalChoice == 3) {
        cout << "\nYou ignite a fuel canister near the bikes, causing a massive explosion that clears the area!" << endl;
    }

    // --- GAME ENDING ---
    printDivider();
    if (lives > 0 && hasJaguarEye) {
        printHeader("VICTORY!");
        cout << "You reach the crown of the Jaguar Statue and place the Jaguar's Eye jewel into its socket!" << endl;
        cout << "A beam of light shoots into the sky, and the jungle curse is lifted!" << endl;
        cout << "\nYou take a deep breath and shout at the top of your lungs:" << endl;
        cout << "\n>>> \"JUMANJI!\" <<<\n" << endl;
        cout << "The green light surrounds you again, lifting you out of the game and back into the real world." << endl;
        cout << "Game Over - You Win!" << endl;
        cout << "Final Stats - Player: " << playerName << " (" << avatarName << ") | Remaining Lives: " << lives << endl;
    }
    else {
        printHeader("GAME OVER");
        cout << "You ran out of lives before lifting the curse." << endl;
        cout << "Your avatar remains trapped inside Jumanji forever..." << endl;
        cout << "Game Over - Better luck next time!" << endl;
    }

    return 0;
}

// Utility function to print a simple line divider
void printDivider() {
    cout << "\n======================================================================\n" << endl;
}

// Utility function to print section headers cleanly
void printHeader(const string& title) {
    cout << "----------------------------------------------------------------------" << endl;
    cout << "   " << title << endl;
    cout << "----------------------------------------------------------------------" << endl;
}

// Input validation function to prevent infinite loops on invalid entry
int getValidChoice(int minOption, int maxOption) {
    int choice;
    while (true) {
        if (cin >> choice && choice >= minOption && choice <= maxOption) {
            cin.ignore(10000, '\n'); // Clear remaining buffer
            return choice;
        }
        cout << "Invalid choice! Please enter a number between " << minOption << " and " << maxOption << ": ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}