#define LOG_TAG "creation_builder-main"
#include "Logger.h"

#include <string>
#include <memory>

class ProductBuilder;
class Product
{
    friend ProductBuilder;
    std::string mP1;
    int         mP2;
    double      mP3;
    char        mP4;
public:
    Product(const std::string &p1, const int &p2, const double &p3, const char &p4)
        :mP1(p1), mP2(p2), mP3(p3), mP4(p4)
    {
        LogInf() << "Create a product from :" << mP1 <<", "<< mP2 << ", " << mP3 << ", " << mP4;
    }
};

class ProductBuider
{
    std::string p1;
    int p2;
    double p3;
    char p4;
public:
    ProductBuider& setPart1(const std::string &p){ p1=p; return *this;}
    ProductBuider& setPart2(const int &p){ p2=p; return *this;}
    ProductBuider& setPart3(const double &p){ p3=p; return *this;}
    ProductBuider& setPart4(const char &p){ p4=p; return *this;}
    std::shared_ptr<Product> create()
    {
        return std::make_shared<Product>(p1,p2,p3,p4);
    }
};

int main(int argc, char**argv)
{
    auto p = ProductBuider().setPart1("Pd1").setPart2(1).setPart3(0.2).setPart4('H').create();
    return 0;
}
