#include "parse_common.h"

namespace parse_common {

Tree::Tree() {}

Tree::~Tree()
{
    for (unsigned i = 0; i < this->subTrees.size(); ++i)
        delete this->subTrees[i];
}

inline Tree* Tree::getSubTree(int i)
{
    return this->subTrees.at(i);
}

inline std::string Tree::getID()
{
    std::string id;
    switch (this->rule) {
        default: throw "Not a terminal symbol\n"; break;

        case Ftor_Exp_Id:       // fall-through
        case Ftor_Exp_Int:      // fall-through
        case Ftor_Exp_Char:     // fall-through
        case Lval_Exp_Id:
                 id = this->units[1];
                 break;
    }
    return id;
}

}
