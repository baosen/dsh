#pragma once
class Kb {
public:
    Kb();
    ~Kb();
    int getkbcode();
private:
   input_event read();

    int fd;
};
