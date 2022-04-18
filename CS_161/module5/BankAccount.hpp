/*********************************************************************
** Author:       Jeremy Prater
** Date:         April 25, 2016
** Description:  Module 5.b assignment
*********************************************************************/

#ifndef BANKACCOUNT_HPP
#define BANKACCOUNT_HPP

#include <string>

/*********************************************************************
** Description: Assignment 5.a
**
** BankAccount header file and class declaration
**
*********************************************************************/

class BankAccount
{
  private:

    /////////////////////////////////////////////////////////////////
    //
    // Internal Variables
    //

    std::string customerName;
    std::string customerID;
    double      customerBalance;

  public:

    /////////////////////////////////////////////////////////////////
    //
    // Constructors
    //

    BankAccount (std::string Name, std::string ID, double Balance);

    /////////////////////////////////////////////////////////////////
    //
    // Functions
    //

    std::string getCustomerName    (void);
    std::string getCustomerID      (void);
    double      getCustomerBalance (void);
    void        withdraw           (double ammount);
    void        deposit            (double ammount);
};

#endif // BANKACCOUNT_HPP
