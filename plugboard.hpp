#ifndef PLUGBOARD_HPP
#define PLUGBOARD_HPP
//declaration of the plugboard class
class Plugboard {
    public:
        Plugboard(char plugWiring[]);
        void Swap(char &key, int &index);
    private:
        char plugs[26];
};

#endif