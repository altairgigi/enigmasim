#include <iostream>
#include <vector>
#include "interface.hpp"

//constructor with window initialisation
Interface::Interface() {
    initscr();
    start_color();
    noecho();  //hides input from user
    raw(); //non blocking input
    curs_set(0); //hides cursor
    clear();

    if (COLORS >= 256) { //check if terminal supports color indexes, if yes creates color pairs
       init_pair(1, COLOR_WHITE, 236);
       init_pair(2, 137, 94);
    }

    enigmawin = newwin(20, 50, 0, 0);
}
//destructor with window deletion
Interface::~Interface() {
    delwin(enigmawin);
    endwin();
}
//public method to print the interface
void Interface::DrawUI(const Enigma& machine, char lamp, char model) {
    box(enigmawin, 0, 0);
    wbkgd(enigmawin, COLOR_PAIR(1)); //background color
    wattron(enigmawin, COLOR_PAIR(2)); //border color
    wborder(enigmawin, '#', '#', '#', '#', '#', '#', '#', '#');
    wattroff(enigmawin, COLOR_PAIR(2));

    std::vector<char> rotorsPositions = machine.GetRotorsPos();

    DrawEnigma(enigmawin, 1, 21);
    for(int i = 0; i < rotorsPositions.size(); i++) {
        if(i == 3) { //draw the fourth rotor if it exists
            DrawRotorBox(enigmawin, rotorsPositions[i], 5, 10);
        }
        else {
            DrawRotorBox(enigmawin, rotorsPositions[i], 5, (14 + (i * 4)));
        }
    }
    DrawLampboardRow(enigmawin, row1, lamp, 9, 7);
    DrawLampboardRow(enigmawin, row2, lamp, 11, 9);
    DrawLampboardRow(enigmawin, row3, lamp, 13, 7);
    DrawModel(enigmawin, model, 16, 22);

    refresh();
    wrefresh(enigmawin);
}
//private methods to print the interface parts
//this draws the enigma box in the upside center of the guy
void Interface::DrawEnigma(WINDOW *win, int y, int x) {
    mvwvline(win, y, x, ACS_ULCORNER, 1);
    mvwvline(win, y + 1, x, ACS_VLINE, 1);
    mvwvline(win, y + 2, x, ACS_LLCORNER, 1);
    mvwhline(win, y, x + 1, ACS_HLINE, 6);
    mvwhline(win, y + 2, x + 1, ACS_HLINE, 6);
    mvwvline(win, y, x + 7, ACS_URCORNER, 1);
    mvwvline(win, y + 1, x + 7, ACS_VLINE, 1);
    mvwvline(win, y + 2, x + 7, ACS_LRCORNER, 1);
    mvwprintw(win, y + 1, x + 1, "ENIGMA");
}
//this draws the rotor box
void Interface::DrawRotorBox(WINDOW *win, char pos, int y, int x) {
    mvwvline(win, y, x, ACS_ULCORNER, 1);
    mvwvline(win, y + 1, x, ACS_VLINE, 1);
    mvwvline(win, y + 2, x, ACS_LLCORNER, 1);
    mvwhline(win, y, x + 1, ACS_HLINE, 1);
    mvwhline(win, y + 2, x + 1, ACS_HLINE, 1);
    mvwvline(win, y, x + 2, ACS_URCORNER, 1);
    mvwvline(win, y + 1, x + 2, ACS_VLINE, 1);
    mvwvline(win, y + 2, x + 2, ACS_LRCORNER, 1);
    mvwprintw(win, y + 1, x + 1, "%c", pos);
}
//this draws the lampboard and highlights the encrypted key
void Interface::DrawLampboardRow(WINDOW *win, std::string keys, char lamp, int y, int x_offset) {
    for (int i = 0; i < keys.size(); ++i) {
        int x = x_offset + (i * 4);
        //check which lamp the encrypted key corresponds to
        if(toupper(lamp) == keys[i]) {
            wattron(win, A_STANDOUT); //'lights' it
            mvwprintw(win, y, x, "( )");
            mvwprintw(win, y, x + 1, "%c", keys[i]);
            wattroff(win, A_STANDOUT);
        }
        else { //otherwise prints normally
            mvwprintw(win, y, x, "( )");
            mvwprintw(win, y, x + 1, "%c", keys[i]);
        }
    }
}
//this draws the model with the model selected in the bottom center of the gui
void Interface::DrawModel(WINDOW *win, char model, int y, int x) {
    mvwvline(win, y, x, ACS_ULCORNER, 1);
    mvwvline(win, y + 1, x, ACS_VLINE, 1);
    mvwvline(win, y + 2, x, ACS_LLCORNER, 1);
    mvwhline(win, y, x + 1, ACS_HLINE, 4);
    mvwhline(win, y + 2, x + 1, ACS_HLINE, 4);
    mvwvline(win, y, x + 5, ACS_URCORNER, 1);
    mvwvline(win, y + 1, x + 5, ACS_VLINE, 1);
    mvwvline(win, y + 2, x + 5, ACS_LRCORNER, 1);
    mvwprintw(win, y + 1, x + 2, "M%c", model);
}
//prints informations on arguments and options
void PrintUsage() {
    std::cerr << "Usage: enigma.exe [<command>]\n"
              << "List of available commands:\n"
              << "-info\tShow instructions before running\n"
              << "-skip [<option>]\tSkip setup and load default settings\n"
              << "List of available options:\n"
              << "-m3\tUse the standard(M3) model\n"
              << "-m4\tuse the uboat(M4) model\n";
}
//function to print instructions on how the simulator will work
void PrintInstructions() {
    std::cout << "Welcome to EnigmaSim! This is a simple yet historically accurate Enigma machine simulator.\n"
              << "\nOperators who were tasked with managing the machine had to follow a strict sequence of operations:\n"
              << "1) Consult the cipher for the Enigma key to be used that day;\n"
              << "2) Take the three rotors indicated;\n"
              << "3) Set the programming of each individual rotor to the triplet of letters indicated (Ringstellung);\n"
              << "4) Insert them into the machine in the indicated order (Walzenlage);\n"
              << "5) Adjust the initial position of the rotor rings to the triplet of letters indicated (Grundstellung);\n"
              << "6) Configure the letter exchange plugs as determined by the Enigma key for that day (Steckerverbindungen).\n"
              << "\nLuckily, through a guided procedure, you will be able to setup the machine easily.\n"
              << "Then, you'll be able to input letters and get the encrypted result.\n";
}
//function to choose the model
char GetModel() {
    char m;
    do{
    std::cout << "Select the model you want to use: '3' for M3 (Standard) and '4' for M4 (Uboat)\n";
    std::cin >> m;
    std::cin.ignore(1000, '\n'); //cleans buffer
    }while(m != '3' && m != '4');
    return m;
}
//function to get the input key
char GetKey() {
    char key;
    key = getch();
    if(islower(key)) { //check if letter is lowercase
        key = toupper(key); //converts to uppercase
    }
    return key;
}
//function to print the key once the input is taken or after the encryption
void PrintKey(char key) {
    std::cout << key << "\n";
}
//function to print the before or text after the encryption
void PrintText(std::vector<char> text) {
    for(int i = 1; i <= text.size(); i++){ //count starts from 1 to handle % 4
        std::cout << text[i-1];
        if(i % 4 == 0) { //original enigma encrypted text was recorded in groups of four letters
            std::cout << " ";
        }
    }
    std::cout << "\n";
}
//this function asks if user wants to save the text and returns the choice
char AskSave(std::vector<char> textInput, std::vector<char> textOutput) {
    char choice{};

    std::cout << "Your text: \n";
    PrintText(textInput); //print input text
    std::cout << "Your encrypted text: \n";
    PrintText(textOutput); //prints final text
    //asks if the user wants to save the encrypted text
    std::cout << "Do you want to save your encrypted text? (y/n)\n";
    std::cin >> choice;

    return choice;
}