/*********************************************************************
** Author:       Jeremy Prater
** Date:         April 25, 2016
** Description:  Module 5.b assignment
*********************************************************************/

#include "BankAccount.hpp"

#ifdef Debug
#include <iostream>
#endif

/*********************************************************************
** Description: Assignment 5.b
**
** Create a BankAccount class to describe a BankAccount
**
*********************************************************************/

/*********************************************************************
** BankAccount Function Definitions
**
*********************************************************************/

/////////////////////////////////////////////////////////////////
//
// BankAccount Constructors
//
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//
// BankAccount (std::string Name, std::string ID, double Balance)
//
// Construct BankAccount with user supplied data
//

BankAccount::BankAccount (std::string Name, std::string ID, double Balance)
{
  this->customerName    = Name;
  this->customerID      = ID;
  this->customerBalance = Balance;
}

/////////////////////////////////////////////////////////////////
//
// BankAccount Functions
//
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//
// BankAccount::getCustomerName (void)
//
// Return customer name
//

std::string BankAccount::getCustomerName (void)
{
  return this->customerName;
}

/////////////////////////////////////////////////////////////////
//
// BankAccount::getCustomerID (void)
//
// Return customer ID
//

std::string BankAccount::getCustomerID (void)
{
  return this->customerID;
}

/////////////////////////////////////////////////////////////////
//
// BankAccount::getCustomerBalance (void)
//
// Return customer balance
//

double BankAccount::getCustomerBalance (void)
{
  return this->customerBalance;
}

/////////////////////////////////////////////////////////////////
//
// BankAccount::withdraw (void)
//
// withdraw from account
//

void BankAccount::withdraw (double ammount)
{
  this->customerBalance -= ammount;
}

/////////////////////////////////////////////////////////////////
//
// BankAccount::deposit (void)
//
// deposit to account
//

void BankAccount::deposit (double ammount)
{
  this->customerBalance += ammount;
}



#ifdef Debug
int main()
{
  BankAccount * account1 = new BankAccount ("Harry Potter", "K4637", 8032.78);
  std::cout << "customerName: " << account1->getCustomerName() << std::endl;
  std::cout << "customerID: " << account1->getCustomerID() << std::endl;
  std::cout << "customerBalance: " << account1->getCustomerBalance() << std::endl;

  account1->withdraw (244.0);
  account1->withdraw (3012.58);
  account1->deposit (37.54);
  account1->withdraw (1807.12);
  account1->deposit (500.00);

  double finalBalance = account1->getCustomerBalance();

  std::cout << "final customerBalance: " << finalBalance << std::endl;

  delete account1;
  return 0;
}
#endif
