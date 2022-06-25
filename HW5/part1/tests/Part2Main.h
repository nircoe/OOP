#include <iostream>
#include "staff/Part2Examples.h"
#include "my/MyTest.h"
#include "partner/PartnerPartTwoMain.h"

void part2Main() {
    std::cout<<"part2Main"<<std::endl;
    MyTest().test();
    std::cout<<"MyTest PASSED"<<std::endl;
    Part2Examples().mainPart2Examples();
    std::cout<<"Part2Examples PASSED"<<std::endl;
    PartnerPartTwoMain().partnerPartTwoMain();
}
