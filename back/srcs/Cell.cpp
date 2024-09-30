#include "Cell.hpp"

Cell::Cell(e_cell value) {
    _value = value;
}

Cell::Cell(const Cell &c) {
    _value = c.get();
}

void Cell::operator= (const Cell &c) {
    _value = c.get();
}

Cell::~Cell() { }

e_cell Cell::get() const {
    return _value;
}

void Cell::set(e_cell value) {
    _value = value;
}
