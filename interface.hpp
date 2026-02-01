#ifndef INTERFACE_HPP
#define INTERFACE_HPP
//macro conditional to handle input across different systems
#ifdef _WIN32
    #include <conio.h>
    #define get_input key = _getch() //getch is handled through this definition
#else
    #include <termios.h>
    #include <unistd.h>
    //struct to save terminal configuration
    static struct termios cfgOrigin;
    //function to disable raw mode
    void DisableRawMode() {
      tcsetattr(STDIN_FILENO, TCSAFLUSH, &cfgOrigin); //enforce original configuration
    }
    //function to enable raw mode
    void EnableRawMode() {
        tcgetattr(STDIN_FILENO, &cfgOrigin); //save original configuration

        struct termios cfgRaw = cfgOrigin; //copy original configuration
        cfgRaw.c_lflag &= ~(ECHO | ICANON); //ignore enter and hide input to user
        cfgRaw.c_cc[VMIN] = 1; //wait for at least one character
        cfgRaw.c_cc[VTIME] = 0; //pass the input immediately

        tcsetattr(STDIN_FILENO, TCSAFLUSH, &cfgRaw); //enforce raw configuration
    }
    #define get_input EnableRawMode(); read(STDIN_FILENO, &key, 1); DisableRawMode();
#endif

//prototypes for the functions
void PrintUsage();
void PrintInstructions();
void PrintInterface();
char GetModel();
char GetKey();
void LightKey(char key);
void PrintText(std::vector<char> textCrypted);

#endif