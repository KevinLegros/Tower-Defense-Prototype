#ifndef _KEYS_HPP_
#define _KEYS_HPP_

class Keys {
    private:
        static bool eventClicked;

    public:
        Keys();

    public:
        static bool isEventClicked();

    public:
        static void setEventClicked(bool clicked);
};

#endif
