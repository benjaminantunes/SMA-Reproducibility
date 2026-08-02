#ifndef __POSITION_HPP__
#define __POSITION_HPP__

class Position
{
    private:
        int x;
        int y;
    public:
        Position        (int ix, int iy);
        Position        (void);

        int    getX     (void);
        int    getY     (void);
        void   setX     (int newX);
        void   setY     (int newY);
};

#endif