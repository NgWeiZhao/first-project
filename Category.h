#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>

using namespace std;

class Category {
private:
    string name;

public:
    Category(string name) : name(name) {}
    string getName() const { return name; }
};

#endif
