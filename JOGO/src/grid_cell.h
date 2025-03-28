#pragma once

class Grid_Cell
{
public:
    int x;
    int y;
    Grid_Cell();
    void Draw() const;


private:
    
    int width;
    int height;
    bool falling;
};