//
// Created by pauca on 31/03/2022.
//

#include "TI.h"

TI::TI(string sym, long long start, long long end) {
    this->sym = sym;
    this->start = start;
    this->end = end;
}

ostream &operator<<(ostream &os, const TI &ti) {
    os << ti.sym << " " << ti.start << " " << ti.end;
    return os;
}

bool TI::operator==(const TI &rhs) const {
    return sym == rhs.sym &&
           start == rhs.start &&
           end == rhs.end;
}

bool TI::operator!=(const TI &rhs) const {
    return !(rhs == *this);
}

bool TI::operator<(const TI &rhs) const { //TODO comprovar que funcioni
    if (start < rhs.start)
        return true;
    if ( start == rhs.start) {
        if (end < rhs.end)
            return true;
        if (end == rhs.end)
            return sym < rhs.sym;
    }
    return false;
}

bool TI::operator>(const TI &rhs) const {
    return rhs < *this;
}

bool TI::operator<=(const TI &rhs) const {
    return !(rhs < *this);
}

bool TI::operator>=(const TI &rhs) const {
    return !(*this < rhs);
}


