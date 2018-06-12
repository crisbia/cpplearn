
#include <iostream>
#include <memory>

class Data
{
public:

    static int i;

    Data()
    {
        id_ = i;
        std::cout << "Data() - id: " << id_ << "\n";
        ++i;
    }

    Data(const Data& other)
    {
        id_ = i;
        std::cout << "Data() - id: " << id_ << "\n";
        value_ = other.value_;
    }

    ~Data()
    {
        std::cout << "~Data() - id: " << id_ << "\n";
    }

    void print()
    {
        std::cout << value_ << "\n";
    }

    int value_;
    int id_;
};

int Data::i = 0;

class A
{
public:
    A()
    {
        data_ = std::unique_ptr<Data>(new Data());
        data_.get()->value_ = 1;

        std::cout << "A()\n";
    }

    ~A()
    {
        std::cout << "~A() - data: " << (data_ != nullptr ? std::to_string(data_.get()->value_) : "nullptr") << "\n";
    }

    A(const A& other)
    {
        data_ = std::unique_ptr<Data>(new Data(*(other.data_.get())));

        std::cout << "A(const A& other)\n";
    }

    A(A&& other)
    {
        data_ = std::move(other.data_);

        std::cout << "A(A&& other)\n";
    }

    void operator=(const A& other)
    {
        std::cout << "operator=(const A& other)\n";
    }

    void operator=(A&& other)
    {
        data_ = std::move(other.data_);

        std::cout << "operator=(A&& other)\n";
    }

    std::unique_ptr<Data> data_;
};

A create()
{
    A a;
    return a;
}

int main()
{
    A a1;
    A a2(std::move(a1));

//    A a = create();

    //A a1 = a;


    return 0;
}
