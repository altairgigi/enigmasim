#ifndef REFLECTOR_HPP
#define REFLECTOR_HPP
//declaration of reflector class
class Reflector {
    public:
        Reflector(char reflectorCfg[]);
        void Reflect(int &index);
    private:
        char map[26];
};

#endif