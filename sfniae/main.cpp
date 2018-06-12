
#include <iostream>
#include <memory>

class Printable
{
public:
    void print() const
    {
        std::cout << "I am Printable!\n";
    }

};

class NonPrintable
{

};


template<typename T>
class Printer
{
public:

    template <class C>
    static std::true_type testSignature(void (C::*)() const);

    template <class C>
    static decltype(testSignature(&C::print)) test(std::nullptr_t);

    template <class C>
    static std::false_type test(...);

    using type = decltype(test<T>(nullptr));
    static const bool value = type::value;

    void printObject(const T& p)
    {
        InternalPrinter<T, value> pp;
        pp.internalPrint(p);
    }

    template <class C, bool V>
    class InternalPrinter
    {
    public:
        void internalPrint(const C& p)
        {
            std::cout << "Not printable\n";
        }
    };

    template <class C>
    class InternalPrinter<C, true>
    {
    public:
        void internalPrint(const C& p)
        {
            p.print();
        }
    };
};

int main()
{
    Printable p;
    NonPrintable np;

    Printer<Printable> p1;
    p1.printObject(p);

    Printer<NonPrintable> p2;
    p2.printObject(np);

    return 0;
}
