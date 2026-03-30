#ifndef INPUTREADER_H
#define INPUTREADER_H

#include <string>

class InputReader {
public:
    int readMenuChoice(int minValue, int maxValue) const;

private:
    void clearInput() const;
    bool isChoiceValid(int value, int minValue, int maxValue) const;
};

#endif // INPUTREADER_H
