#ifndef __LCDEVENTARG__
#define __LCDEVENTARG__

 #include <typeinfo>


class LcdEventArg {
    private: 
        type_info srcType;
        double value;

    public:
        LcdEventArg(type_info srcType, double value) {
            this->srcType = srcType;
            this->value = value;
        }

        type_info getSrcType() {
            return srcType;
        }

        double getValue() {
            return value;
        }
};

#endif