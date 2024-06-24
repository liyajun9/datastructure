#ifndef DATASTRUCTURE_PLAYER_H
#define DATASTRUCTURE_PLAYER_H

struct player
{
    int id, key;
    operator int() const
    {
        return key;
    }
};

#endif //DATASTRUCTURE_PLAYER_H
