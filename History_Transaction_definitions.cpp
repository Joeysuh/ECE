#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TASK 1
//

Transaction::Transaction (std::string ticker_symbol, unsigned int day_date, unsigned int month_date,
unsigned year_date, bool buy_sell_trans, unsigned int number_shares, double trans_amount
) {

// copy all the declared variables and assign it as the function name based on the private variables part of the doc?
  symbol = ticker_symbol;
  day = day_date;
  month = month_date;
  year = year_date; 
  shares = number_shares;
  amount = trans_amount; 
  trans_id = assigned_trans_id;

  // 

  if ( buy_sell_trans == true ) {
    trans_type = "Buy"; 
  } else if ( buy_sell_trans == false ) {
    trans_type = "Sell"; 
  } 
  p_next = nullptr; 
  ++assigned_trans_id; 

  acb = 0; 
  acb_per_share = 0;
  share_balance = 0; 
  cgl = 0;

}


// Destructor
// TASK 1
//


// Leave it as is, no need for further action. 
Transaction::~Transaction(){}


// Overloaded < operator.
// TASK 2
//This overloaded operator implements the less-than operator for comparing Transactions, based on which
//Transaction occurred first chronologically. Returns true if and only if the transaction date for the left operand
//occurs prior to the transaction date of the right operand. If the transaction dates are equal for both left and
// right operands, returns true if and only if the transaction id of the left operand is *less greater than the
// transaction id of the right operand. 


bool Transaction::operator<( Transaction const &other ) {

if (year < other.year) {
  return true; 
} else if ( other.year < year) {
  return false; 
}


else {
  if ( month < other.month) { 
    return true; 
  }
  else if ( other.month < month) { 
    return false; 
  }


else {
  if ( day < other.day ) {
    return true; 
  } else if ( other.day < day) {
    return false; 
  } else {
    if (trans_id > other.trans_id) {
      return true;
    }
  }
  }
}

return false; 
}
// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " "
    << std::setw(4) << get_symbol() << " "
    << std::setw(4) << get_day() << " "
    << std::setw(4) << get_month() << " "
    << std::setw(4) << get_year() << " ";


  if ( get_trans_type() ) {
    std::cout << "  Buy  ";
  } else { std::cout << "  Sell "; }

  std::cout << std::setw(4) << get_shares() << " "
    << std::setw(10) << get_amount() << " "
    << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
    << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
    << std::setw(10) << std::setprecision(3) << get_cgl()
    << std::endl;
}


////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//



// Constructor
// TASK 3
//

History::History() { 
  p_head = nullptr; 
}

// Destructor
// TASK 3
//

History::~History(){
// delete the data bruh
  Transaction *temporary{nullptr};
  while (p_head != nullptr) {
    temporary = p_head;
    p_head = p_head ->get_next();
    delete temporary;
  }
  temporary = nullptr;
  p_head = nullptr;
}


// read_history(...): Read the transaction history from file.
// TASK 4
//

//open transaction history text and 

void History:: read_history(){

  // open the transaction file and be able to read it. 
ece150::open_file(); 
while ( ece150::next_trans_entry() == true ) {
  Transaction *recenttransaction = new Transaction (ece150::get_trans_symbol(), ece150::get_trans_day(), ece150::get_trans_month(), ece150::get_trans_year(), ece150::get_trans_type(), ece150::get_trans_shares(), ece150::get_trans_amount());
  insert(recenttransaction);
  }
  ece150::close_file(); 
}

// insert(...): Insert transaction into linked list.
// TASK 5 
//



void History:: insert(Transaction *p_new_trans){
  Transaction *newone {p_head};
  
  if ( p_head == nullptr) {
    p_head = p_new_trans; 
  } else {
    //get to end
    while ( newone -> get_next() != nullptr) {
      newone = newone -> get_next();
    }
    newone -> set_next(p_new_trans);
  }
  p_new_trans -> set_next(nullptr);
}


// sort_by_date(): Sort the linked list by trade date.
// TASK 6
//


void History:: sort_by_date(){

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
    new_phead.insert(least);
  }
// removing lowest value from linked list

 
  // send the data from the new sorted linked list to p_head. 
  p_head = new_phead.get_p_head(); 
  new_phead.p_head = nullptr;
}

// removing lowest value from linked list

 
  // send the data from the new sorted linked list to p_head. 






// update_acb_cgl(): Updates the ACB and CGL values.
// TASK 7
//

void History:: update_acb_cgl(){
// acb is amount paid + acb
// acb per share/ per share
// share balance is number of shares you possess
// capital gains/lose

// Logic: set first and second parts of the pointers to the front and back end
Transaction *first{p_head -> get_next()};
Transaction *second{p_head};

second -> set_acb(second -> get_amount()); 
second -> set_share_balance(second -> get_shares());
second -> set_acb_per_share(second -> get_acb() / second -> get_share_balance()); 

// USE ACB COMPUTATION LOGIC! Sell, buy, # of shares
// Logic commented so i dont forget LUL
// for ACB, amount + previous ACB = new ACB
// for shares, get all shared + how many shares u got 

    while (first != nullptr) {
      if ( first -> get_trans_type()) {
        first -> set_acb(first -> get_amount() + second -> get_acb()); 
        first -> set_share_balance(first -> get_shares() + second -> get_share_balance());
   
      }
      // Logic 2: if shares are not being added (bought) he is selling shares, so the same operations, except -, but it needs to be total shares - my shares x acb_per_share
     // first -> set_acb(first -> get_acb() - first -> get_shares() * second -> get_acb_per_share());
     //cgl 
     //share balance
     //find if buy or find if sell 
      else {
        
        first -> set_acb(second -> get_acb() - first -> get_shares() * second -> get_acb_per_share()); 
        first -> set_cgl( first -> get_amount() - first -> get_shares() * second -> get_acb_per_share());
        first -> set_share_balance(second -> get_share_balance() - first -> get_shares());
      } 
      first -> set_acb_per_share(first -> get_acb() / first -> get_share_balance()); 
      second = second->get_next();
      first = first->get_next(); // NEED TO ITERATE FIRST. HOW COULD I FORGET TO NOT DO IT
  }
  
}

//unsigned int day_date, unsigned int month_date,
//unsigned year_date, bool buy_sell_trans, unsigned int number_shares, double trans_amount
//) {

// compute_cgl(): )Compute the ACB, and CGL.
// TASK 8

double History:: compute_cgl ( unsigned int year){

// calculate gains or losses using ACB
// return the total capital gains or losses
// sort the years, compare it. 


//logic: initiliaze a total variable for the CGL
// iterate thru the linked list and calculate the cgl again
// compare/sort the year and add to get cgl. 
// set the new pointer to the get next for the next cgl calculation
// iterate thru the linked list and calculate the cgl values. 
// while linked list is not nullptr, calculate cgl and then if statement to compare year
// if year is == total cgl is just the first get cgl
// return the summed cgl bru


double totalcgl{};

Transaction *first{p_head};

while ( first != nullptr) {
  if ( first -> get_year() == year) {
    totalcgl += first -> get_cgl();
  }
  first = first -> get_next(); 
} 
  return totalcgl;
} 

// print() Print the transaction history.
//TASK 9
//

// transaction history begins 
void History::  print(){
  std::cout << "========== BEGIN TRANSACTION HISTORY ============" << std::endl;
    Transaction *penultimate{p_head};
    while (penultimate != nullptr) {
      penultimate -> print();
      penultimate = penultimate -> get_next();
    }
    std::cout <<"========== END TRANSACTION HISTORY ============" << std::endl;
}


// GIVEN
// get_p_head(): Full access to the linked list.
//
Transaction *History::get_p_head() { return p_head; }
