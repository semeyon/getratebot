#include <iostream>
#include <vector>
#include <algorithm>

/**
  Example showing the function programming ideas in
  C++ 11. Features used here are part of standard language.  
**/

namespace lambda {

    template<typename Collection, typename unop>
    void for_each(Collection col, unop op) {
        std::for_each(col.begin(), col.end(), op);
    }

    template<typename Collection, typename unop>
    Collection map(Collection col, unop op) {
        std::transform(col.begin(), col.end(), col.begin(), op);
        return col;
    }

    template<typename Collection, typename binop>
    Collection zip(Collection fc, Collection sc, binop op) {
        std::transform(fc.begin(), fc.end(), sc.begin(), fc.begin(), op);
        return fc;
    }

    template<typename Collection, typename Condition>
    bool exists(Collection col, Condition con) {
        auto exist = std::find_if(col.begin(), col.end(), con);
        return exist != col.end();
    }


    template<typename Collection, typename Predicate>
    Collection filterNot(Collection col, Predicate predicate) {
        auto returnIterator = std::remove_if(col.begin(), col.end(), predicate);
        col.erase(returnIterator, std::end(col));
        return col;
    }

    template<typename Collection, typename Predicate>
    Collection filter(Collection col, Predicate predicate) {
        auto fnCol = filterNot(col, [predicate](typename Collection::value_type i) { return !predicate(i); });
        return fnCol;
    }

}