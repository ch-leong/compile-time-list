#include "List.h"

template<int ... intlist>
using IntList = typename Facility<int>::List<intlist...>;

int main()
{
    // Test List.
    using List1 = IntList<1, 2, 3, 4>;
    List1::print();

    // Test Dot Product.
    using List2 = IntList<2, 4, 6, 8>;
    std::cout << Facility<int>::DotProduct<List1, List2>::result << "\n";

    // Test concat.
    Facility<int>::Concat<List1, List2>::result::print();

    // Test min.
    std::cout << Facility<int>::Min<List2>::result << std::endl;

    // Test remove first.
    Facility<int>::RemoveFirst<3, List1>::result::print();

    // Test partition.
    using MyList = IntList<99, 2, 5, 100, 78, 120, 55, 129>;
    MyList::print();
    Facility<int>::Partition< MyList >::FirstHalf::print();
    Facility<int>::Partition< MyList >::SecondHalf::print();

    // Test sort.
    using List = IntList<-2, -10, -5, -7, -5, -2, -4>;
    Facility<int>::Sort< List >::result::print();

    // Test quick sort.
    using ShorterList = IntList<-2, -10, -5, -7, -5, -2, -4>;
    Facility<int>::QuickSort< ShorterList >::result::print();

    return 0;
}
