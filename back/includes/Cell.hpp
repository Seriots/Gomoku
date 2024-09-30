#pragma once

enum e_cell {
    WHITE,
    BLACK,
    BLOCKED,
    NONE,
};

class Cell {
    private:
        e_cell _value;
    
    public:
        Cell(e_cell value = NONE);
        Cell(const Cell &c);
        ~Cell();
        
        void operator= (const Cell &c);
        
        e_cell get() const;
        void set(e_cell value);
};