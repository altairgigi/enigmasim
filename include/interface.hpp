#ifndef INTERFACE_HPP
#define INTERFACE_HPP

//macro conditional to handle input across different systems
#ifdef _WIN32
    #include <curses.h>
#else
    #include <ncurses.h>
#endif
#include <string>
#include "enigma.hpp"

//strings for lampboard rows
const std::string row1 = "QWERTZUIO";
const std::string row2 = "ASDFGHJK";
const std::string row3 = "PYXCVBNML";

//class interface
class Interface {
    public:
        Interface();
        ~Interface();
        void DrawUI(const Enigma& machine, char model, char lamp);  //enigma passed as const to ensure is not accidentally modified
        char GetInput(const Enigma &machine, char lamp, char model); //manages player input
    private:
        WINDOW *enigmawin;
        void WindowManager(); //manages window creation and resize 
        void DrawEnigmaShield(WINDOW *win, int y, int x);
        void DrawRotorBox(WINDOW *win, char pos, int y, int x);
        void DrawLampboardRow(WINDOW *win, std::string keys, char lamp, int y, int x_offset);
        void DrawModelBox(WINDOW *win, char model, int y, int x);
};

//prototypes for the functions
void PrintUsage();
void PrintInstructions();
char GetModel();
void PrintText(std::vector<char> text);
char ConfirmSave(std::vector<char> textInput, std::vector<char> textOutput);

#endif