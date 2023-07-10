#include <iostream>
#include "History.hpp"
#include "Transaction.hpp"


#ifndef MARMOSET_TESTING
unsigned int Transaction::assigned_trans_id = 0;
int main() {
  History trans_history{};
  trans_history.read_history();

  std::cout << "[Starting history]:" << std::endl;
  trans_history.print();
  trans_history.sort_by_date();

  std::cout << "[Sorted          ]:" << std::endl;
  trans_history.print();

  trans_history.update_acb_cgl();
  trans_history.print();

   std::cout << "[CGL for 2018    ]: " << trans_history.compute_cgl(2018) << std::endl;
   std::cout << "[CGL for 2019    ]: " << trans_history.compute_cgl(2019) << std::endl;

  return 0;
}
#endif
//1. sorting function only gives 3, maybe an if statement somewhere that sends it out

//2. compute_cgl runs forever, loops forever, probably your while loop condition is never met. while loop conditon is never met. 








/*void History:: sort_by_date(){

 // Logic:
// create a new linked list with a pointer for the transaction file
// new variable for something to go in the linked list
// variable to go thru linked list

  Transaction *counting{nullptr}; // iterating variable 
  Transaction *least{nullptr}; // insert into linked list LOL from the lowest value
  Transaction *counter_prev{nullptr};
  History new_phead{};  // new linked list for history


// iterate thru the linked list 
  while (p_head != nullptr) { 
    std::cout << "LOOP" << std::endl;
    least = p_head;
    counting = p_head; 
    counter_prev = p_head;

// find the smallest value
    while (counting != nullptr) { 
      if (*counting < *least) {
        least = counting;
      }
      counting = counting -> get_next();
    }
    // there is an edge case, where first node is the lowest value 
    if (least == p_head) {  
      p_head = p_head -> get_next();  
      least -> set_next(nullptr);
      new_phead.insert(least);
      continue;
    }

    // iterate thru the linked list until it is before c++ and assign counter to the getnext.
    while (counter_prev -> get_next() != least) {
      counter_prev = counter_prev->get_next();
    } 

    counter_prev -> set_next(least -> get_next()); 
    least -> set_next(nullptr);  
  }
// removing lowest value from linked list

 
  // send the data from the new sorted linked list to p_head. 
  p_head = new_phead.get_p_head(); 
  new_phead.p_head = nullptr;

}
*/