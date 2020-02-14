#pragma once
#include <iostream>
#include <vector>
#include <type_traits>

template<typename T = int, typename Comp = std::less<T> >
struct Facility
{
    template<typename Arg>                              static void Printer(Arg&& arg);
                                                        static void Printer(char arg);
    template<T ... Args>                                struct List { static void print(); };
    template<T Arg, T ... Args>                         struct Add;
    template<T Arg>                                     struct Add<Arg>;
    template<typename Arg1, typename Arg2, bool = true> struct DotProduct;
    template<T ... Args1, T ... Args2, bool boolean>    struct DotProduct<List<Args1...>, List<Args2...>, boolean>;
    template<bool boolean>                              struct DotProduct<List<>, List<>, boolean>;
    template<typename Arg1, typename Arg2>              struct Concat;
    template<T ... Args1, T ... Args2>                  struct Concat<List<Args1 ...>, List<Args2...> >;
    template<typename Arg>                              struct Min;
    template<T Arg1, T Arg2, T... Args>                 struct Min<List<Arg1, Arg2, Args...> >;
    template<T Arg1, T Arg2>                            struct Min<List<Arg1, Arg2> >;
    template<T Arg1, typename Arg2>                     struct RemoveFirst;
    template<T Arg1, T Arg2, T ... Args>                struct RemoveFirst<Arg1, List<Arg2, Args...> >;
    template<T Arg, T ... Args>                         struct RemoveFirst<Arg, List<Arg, Args...> >;
    template<T Arg>                                     struct RemoveFirst<Arg, List<Arg> >;
    template<T Arg>                                     struct RemoveFirst<Arg, List<> >;
    template<typename Arg>                              struct Sort;
    template<T ... Args>                                struct Sort<List<Args...> >;
    template<T Arg>                                     struct Sort<List<Arg> >;
    template<T Arg1, T Arg2, bool = Comp()(Arg1, Arg2)> struct Result;
    template<T Arg1, T Arg2>                            struct Result<Arg1, Arg2, false>;
    template<typename Arg>                              struct Partition;
    template<T Arg1, T Arg2, T ... Args>                struct Partition<List<Arg1, Arg2, Args...> >;
    template<T Arg>                                     struct Partition<List<Arg> >;
    template<typename Arg, bool = false>                struct QuickSort;
    template<T Arg, T ... Args>                         struct QuickSort<List<Arg, Args...> >;
    template<bool boolean>                              struct QuickSort<List<>, boolean>;

    /****************************************************************************/
    /*!
      \brief
        Auxiliary struct of DotProduct(). Helps unpack too.
    */
    /****************************************************************************/
    template<T Arg, T ... Args>
    struct Add
    {
        // Adding the current head and the rest
        static constexpr T result = Arg + Add<Args...>::result;
    };
    /****************************************************************************/
    /*!
      \brief
        Auxiliary struct of DotProduct().
    */
    /****************************************************************************/
    template<T Arg>
    struct Add<Arg>
    {
        // The last element
        static constexpr T result = Arg;
    };
    /****************************************************************************/
    /*!
      \brief
        The name suggests itself. DotProduct is a metafunction that in the end
        computes the dot product of two lists of the same type.
        The plain old struct template.
    */
    /****************************************************************************/
    template<typename Arg1, typename Arg2, bool>
    struct DotProduct
    {};
    /****************************************************************************/
    /*!
      \brief
        The name suggests itself. DotProduct is a metafunction that in the end
        computes the dot product of two lists of the same type.
        Template specialization for 2 List as parameters.
    */
    /****************************************************************************/
    template<T ... Args1, T ... Args2, bool boolean>
    struct DotProduct<List<Args1...>, List<Args2...>, boolean>
    {
        // Multiplying both heads and add the rest
        static constexpr T result = Add<(Args1 * Args2)...>::result;
    };
    /****************************************************************************/
    /*!
      \brief
        The name suggests itself. DotProduct is a metafunction that in the end
        computes the dot product of two lists of the same type.
        Template specialization for 2 empty List.
    */
    /****************************************************************************/
    template<bool boolean>
    struct DotProduct<List<>, List<>, boolean>
    {
        // No elements
        static constexpr T result = 0;
    };
    /****************************************************************************/
    /*!
      \brief
        Concat is a metafunction that takes in two lists and return a list that's
        the concatenation of the two.
        The plain old struct template.
    */
    /****************************************************************************/
    template<typename Arg1, typename Arg2>
    struct Concat
    {};
    /****************************************************************************/
    /*!
      \brief
        Concat is a metafunction that takes in two lists and return a list that's
        the concatenation of the two.
        Template specialization for 2 List as parameters.
    */
    /****************************************************************************/
    template<T ... Args1, T ... Args2>
    struct Concat<List<Args1 ...>, List<Args2...> >
    {
        // Combine both pack into one list
        using result = List<Args1..., Args2...>;
    };
    /****************************************************************************/
    /*!
      \brief
        Min is a metafunction that takes a list and returns the smallest item on
        the list. The specific definition of smaller" depends on the type of
        Comp,which is defaulted to std::less<T>.
        The plain old struct template.
    */
    /****************************************************************************/
    template<typename Arg>
    struct Min;
    /****************************************************************************/
    /*!
      \brief
        Min is a metafunction that takes a list and returns the smallest item on
        the list. The specific definition of smaller" depends on the type of
        Comp,which is defaulted to std::less<T>.
        Template specialization for 1 List with first and second parameters
        unpacked.
    */
    /****************************************************************************/
    template<T Arg1, T Arg2, T... Args>
    struct Min<List<Arg1, Arg2, Args...> >
    {
        // Comparing first and second elements and continue to compare with the
        // rest the elements
        static constexpr T result = Comp()(Arg1, Arg2) ?
            Min<List<Arg1, Args...> >::result :
            Min<List<Arg2, Args...> >::result;
    };
    /****************************************************************************/
    /*!
      \brief
        Min is a metafunction that takes a list and returns the smallest item on
        the list. The specific definition of smaller" depends on the type of
        Comp,which is defaulted to std::less<T>.
        Template specialization for only first and second parameters.
    */
    /****************************************************************************/
    template<T Arg1, T Arg2>
    struct Min<List<Arg1, Arg2> >
    {
        // Comparing the last 2 elements in the list
        static constexpr T result = Comp()(Arg1, Arg2) ? Arg1 : Arg2;
    };
    /****************************************************************************/
    /*!
      \brief
        RemoveFirst is a metafunction that takes a list and an item. It removes
        the first occurence of the item on the list. If the item is not found,
        then the list remains as what it ought to be.
        The plain old struct template.
    */
    /****************************************************************************/
    template<T Arg1, typename Arg2>
    struct RemoveFirst;
    /****************************************************************************/
    /*!
      \brief
        RemoveFirst is a metafunction that takes a list and an item. It removes
        the first occurence of the item on the list. If the item is not found,
        then the list remains as what it ought to be.
        Template specialization for 1 List with first and second parameters
        unpacked.
    */
    /****************************************************************************/
    template<T Arg1, T Arg2, T ... Args>
    struct RemoveFirst<Arg1, List<Arg2, Args...> >
    {
        // Merging the list with 2nd element and rest of the element
        using result = typename Concat<List<Arg2>,
            typename RemoveFirst<Arg1, List<Args...> >::result >::result;
    };
    /****************************************************************************/
    /*!
      \brief
        RemoveFirst is a metafunction that takes a list and an item. It removes
        the first occurence of the item on the list. If the item is not found,
        then the list remains as what it ought to be.
        Template specialization for 1 List leftover.
    */
    /****************************************************************************/
    template<T Arg, T ... Args>
    struct RemoveFirst<Arg, List<Arg, Args...> >
    {
        // The first element is the one to be remove so we return the rest of the
        // list
        using result = List<Args...>;
    };
    /****************************************************************************/
    /*!
      \brief
        RemoveFirst is a metafunction that takes a list and an item. It removes
        the first occurence of the item on the list. If the item is not found,
        then the list remains as what it ought to be.
        Template specialization for 1 element left.
    */
    /****************************************************************************/
    template<T Arg>
    struct RemoveFirst<Arg, List<Arg> >
    {
        // The last element is the one to be remove so we return an empty list
        using result = List<>;
    };
    /****************************************************************************/
    /*!
      \brief
        RemoveFirst is a metafunction that takes a list and an item. It removes
        the first occurence of the item on the list. If the item is not found,
        then the list remains as what it ought to be.
        Template specialization for 1 empty List.
    */
    /****************************************************************************/
    template<T Arg>
    struct RemoveFirst<Arg, List<> >
    {
        // Empty list so we return empty list
        using result = List<>;
    };
    /****************************************************************************/
    /*!
      \brief
        Sort is a metafunction that takes a list and returns the sorted ascending
        order of the list. Again, the specific definition of smaller" depends on
        the type of Comp.
        The plain old struct template.
    */
    /****************************************************************************/
    template<typename Arg>
    struct Sort;
    /****************************************************************************/
    /*!
      \brief
        Sort is a metafunction that takes a list and returns the sorted ascending
        order of the list. Again, the specific definition of smaller" depends on
        the type of Comp.
        Template specialization for 1 List.
    */
    /****************************************************************************/
    template<T ... Args>
    struct Sort<List<Args...> >
    {
        // The smallest element
        constexpr static T smallest = Min<List<Args...> >::result;
        // Using the smalest element to remove the smallest element from the list
        using removed = typename RemoveFirst<smallest, List<Args...> >::result;
        // Merge the smallest at front and the rest of the elements at back
        using result = typename Concat< List<smallest >,
            typename Sort<removed>::result >::result;
    };
    /****************************************************************************/
    /*!
      \brief
        Sort is a metafunction that takes a list and returns the sorted ascending
        order of the list. Again, the specific definition of smaller" depends on
        the type of Comp.
        Template specialization for 1 List with only 1 element.
    */
    /****************************************************************************/
    template<T Arg>
    struct Sort<List<Arg> >
    {
        // Return the only element in the list
        using result = List<Arg>;
    };
    /****************************************************************************/
    /*!
      \brief
        Partition is a metafunction that splits a list into 2 halves using the
        first element as a pivot.
        Template specialization for only 2 elements.
    */
    /****************************************************************************/
    template<T Arg1, T Arg2, bool>
    struct Result
    {
        // Putting into 2nd list
        using FirstHalf = List<>;
        using SecondHalf = List<Arg2>;
    };
    /****************************************************************************/
    /*!
      \brief
        Partition is a metafunction that splits a list into 2 halves using the
        first element as a pivot.
        Template specialization for only 2 elements.
    */
    /****************************************************************************/
    template<T Arg1, T Arg2>
    struct Result<Arg1, Arg2, false>
    {
        // Putting into 1st list
        using FirstHalf = List<Arg2>;
        using SecondHalf = List<>;
    };
    /****************************************************************************/
    /*!
      \brief
        Partition is a metafunction that splits a list into 2 halves using the
        first element as a pivot.
        The plain old struct template.
    */
    /****************************************************************************/
    template<typename Arg>
    struct Partition;
    /****************************************************************************/
    /*!
      \brief
        Partition is a metafunction that splits a list into 2 halves using the
        first element as a pivot.
        Template specialization for 1 List with first and second parameters
        unpacked.
    */
    /****************************************************************************/
    template<T Arg1, T Arg2, T ... Args>
    struct Partition<List<Arg1, Arg2, Args...> >
    {
        // Storing the 1st list while do comparing
        using tmpfirsthalf = typename Result<Arg1, Arg2>::FirstHalf;
        // Storing the 2nd list while do comparing
        using tmpsecondhalf = typename Result<Arg1, Arg2>::SecondHalf;
        // The first list of the partition
        using FirstHalf = typename Concat<tmpfirsthalf,
            typename Partition<List<Arg1, Args...> >::FirstHalf
        >::result;
        // The second list of the partition
        using SecondHalf = typename Concat<tmpsecondhalf,
            typename Partition<List<Arg1, Args...> >::SecondHalf
        >::result;
    };
    /****************************************************************************/
    /*!
      \brief
        Partition is a metafunction that splits a list into 2 halves using the
        first element as a pivot.
        Template specialization for only 1 element.
    */
    /****************************************************************************/
    template<T Arg>
    struct Partition<List<Arg> >
    {
        // Returning empty lists
        using FirstHalf = List<>;
        using SecondHalf = List<>;
    };
    /****************************************************************************/
    /*!
      \brief
        QuickSort is a metafunction that sorts a list in an ascending order based
        on the Comp type. However, it differs from Sort in terms of the algorithm
        it employs. QuickSort is only allowed to use Partition to implement it's
        sorting capabilities.
        The plain old struct template.
    */
    /****************************************************************************/
    template<typename Arg, bool>
    struct QuickSort
    {};
    /****************************************************************************/
    /*!
      \brief
        QuickSort is a metafunction that sorts a list in an ascending order based
        on the Comp type. However, it differs from Sort in terms of the algorithm
        it employs. QuickSort is only allowed to use Partition to implement it's
        sorting capabilities.
        Template specialization for 1 List with first parameter unpacked.
    */
    /****************************************************************************/
    template<T Arg, T ... Args>
    struct QuickSort<List<Arg, Args...> >
    {
        // Storing the 1st list using partition
        using tmpfirsthalf = typename Partition<List<Arg, Args...> >::FirstHalf;
        // Storing the 2nd list using partition
        using tmpsecondhalf = typename Partition<List<Arg, Args...> >::SecondHalf;
        // Do quick sort on 1st list
        using list1 = typename QuickSort<tmpfirsthalf>::result;
        // Do quick sort on 2nd list
        using list2 = typename QuickSort<tmpsecondhalf>::result;
        // Merging 1st list, pivot and 2nd list together
        using result = typename Concat<typename Concat<list1, List<Arg> >::result,
            list2>::result;
    };
    /****************************************************************************/
    /*!
      \brief
        QuickSort is a metafunction that sorts a list in an ascending order based
        on the Comp type. However, it differs from Sort in terms of the algorithm
        it employs. QuickSort is only allowed to use Partition to implement it's
        sorting capabilities.
        Template specialization for empty List.
    */
    /****************************************************************************/
    template<bool boolean>
    struct QuickSort<List<>, boolean>
    {
        // Returning an empty list
        using result = List<>;
    };
};

/****************************************************************************/
/*!
  \brief
    Auxiliary function of Print().
*/
/****************************************************************************/
template<typename T, typename Comp>
template<typename Arg>
static void Facility<T, Comp>::Printer(Arg&& arg)
{
    std::cout << std::forward<Arg>(arg) << " ";
}
/****************************************************************************/
/*!
  \brief
    Auxiliary function of Print(). For char only.
*/
/****************************************************************************/
template<typename T, typename Comp>
static void Facility<T, Comp>::Printer(char arg)
{
    std::cout << arg;
}
/**************************************************************************/
/*!
    \brief
    This is really a static member function of the function template List
    that prints out each element of the parameter pack in order.
*/
/**************************************************************************/
template<typename T, typename Comp>
template<T ... Args>
void Facility<T, Comp>::List<Args...>::print()
{
    std::cout << "\"";
    // Store parameters pack into vector
    std::vector < typename std::decay<T>::type > vector = { Args ... };
    // Print each elements
    for (typename std::vector< typename std::decay<T>::type >::iterator it =
        vector.begin(); it != vector.end(); ++it)
    {
        if (it != vector.end() - 1)
            // All element before last
            Printer(*it);
        else
            // Last element
            std::cout << *it;
    }
    // Empty parameters pack / vector
    if (vector.size() == 0)
        std::cout << "Empty List";
    std::cout << "\"\n";
}
