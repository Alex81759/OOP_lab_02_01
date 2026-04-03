#ifndef INPUTREADER_H
#define INPUTREADER_H

class InputReader {
    private:
        void clearInput() const;
        bool isChoiceValid(int value, int minValue, int maxValue) const;
    public:
        int readMenuChoice(int minValue, int maxValue) const;
};

#endif // INPUTREADER_H
