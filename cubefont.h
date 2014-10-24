#ifndef CUBEFONT_H
#define CUBEFONT_H

#include <string>

using namespace std;

class CubeFont {
private:


public:
    CubeFont();
    ~CubeFont();

    bool loadFont(string input);
    bool loadFont(FILE input);

    bool getLetter(int x, int y, char letter);
};

#endif // CUBEFONT_H
