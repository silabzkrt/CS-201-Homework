#ifndef SHEEP_H
#define SHEEP_H

class Sheep{
    public:
    Sheep (const int id);
    Sheep ();
    Sheep (const Sheep& other);
    ~Sheep();
    Sheep& operator = (const Sheep& other);
    bool operator<(const Sheep& other) const;
    int getId();
    int setID(const int id);
    bool isInfected();
    void infect();
    void giveMedicine();

    private:
        int id;
        bool hasDisease;
};

#endif