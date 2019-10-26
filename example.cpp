#include <iostream>
#include "reactive.h"

/* 
  How to use "reactive.h"

    1.  Make all classes you want to apply reactive programming inherit from rct::observer.

    2.  Inside the constructor of each class, use this->learn("event_name", [this](void*){...}).

    3. Create an instance of rct::subject.

    4. Use the attach function of rct::subject to add new observers. For this, use inside the function caller: "name", std::make_shared<class>(constructor args);

    5. Use trigger function of rct::subject followed by the name of the event and &args. This will execute the function of each observer, if defined.  

*/

//1.
class entity_A: public rct::observer{
  public:
  //2.
  entity_A(){
    this->learn("On_event_X", [this](void* args = nullptr){
      std::cout<<"A did response to event X"<<std::endl;
    });
  }
};

class entity_B: public rct::observer{
  public:
  entity_B(){
    this->learn("On_event_Y", [this](void* args = nullptr){
      int casted_args = *(static_cast<int*>(args));
      std::cout<<"B did response to event Y, which sent: "<<casted_args<<std::endl;
    });
  }
};



int main() {
  //3.
  rct::subject universe;


  //4.
  universe.attach("example_A_1", 
    std::make_shared<entity_A>()
  );

  universe.attach("example_A_1", 
    std::make_shared<entity_A>()
  );

  universe.attach("example_B_1", 
    std::make_shared<entity_B>()
  );


  //5.
  universe.trigger("On_event_X");

  int _arg = 18;
  universe.trigger("On_event_Y", (void*) &_arg);

}
