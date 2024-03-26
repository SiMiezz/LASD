
#include "zlasdtest/test.hpp"
#include "zmytest/test.hpp"
#include <iostream>

void menuPrincipale(){
  int scelta;
  std::cout<<"Menu Principale-Scelta test\n1:LasdTest\n2:MyTest\n0:Exit"<<std::endl;
  std::cin>>scelta;

  switch(scelta){
    case 1:
      lasdtest();
      break;
    case 2:
      menu();
      break;
  }
}

int main() {
  std::cout << "Lasd Libraries 2022" << std::endl;
  menuPrincipale();
  return 0;
}
