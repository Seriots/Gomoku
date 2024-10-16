#pragma once

#include <iostream>

#include "structs.hpp"


class Cell {
    private:
        e_cell _value;
    
    public:
        Cell(e_cell value = (e_cell)NONE);
        Cell(const Cell &c);
        ~Cell();
        
        void operator= (const Cell &c);
        
        e_cell get() const;
        void set(e_cell value);
};

std::ostream& operator<<(std::ostream &os, const Cell &c); 