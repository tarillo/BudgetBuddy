#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void calcStateTax(const int userSalary, double &stateTaxRate, double &totalStateTax);
void calcFederalTax(const int userSalary, double &federalTaxRate, double &totalFederalTax);
void GetData(const int userSalary, const string userCity);
int ApartmentRent(const string userCity, const vector <string> &cities, const vector <int> &avgApartmentPrice);
void addDeductPayment(const double monthlyIncome, double& income);
void printMenu();
void printRealMenu();

int main()  {
    vector <string> cities;
    vector <int> avgApartmentPrice;
    int userSalary;
    double stateTaxRate = 0;
    double totalStateTax = 0;
    double federalTaxRate = 0;
    double totalFederalTax = 0;
    double netIncome;
    double payment;
    string cityName;
    unsigned int i;
    ifstream inFS;
    string City;
    double cityRent;  
    char userOption;
    bool found = false;
    string fileName;
    char choice;
    double debtAmount;

    cout << "Please enter the file name: " << endl;
    cin >> fileName;

    inFS.open(fileName);

    //Check if file is open
    if(!inFS.is_open())  {
        cout << "Error opening: " << fileName << endl;
    }

    //Get cities and their average rent and store into respective vectors
    while(getline(inFS, City))   {
        inFS >> cityRent;
        inFS.ignore();

        cities.push_back(City);
        avgApartmentPrice.push_back(cityRent); 
    }

    inFS.close();
    //Introduction
    cout << "Hello user! Welcome to your very own BudgetBuddy, here to help with most of your financial budget needs! ヾ(＠⌒▽⌒＠)ﾉ" << endl;
    cout << "The first menu will show you an ideal budget where it will show the estimated costs of your chosen city and will account your annual salary. Showing the range that is likely to be spent in certain categories from tax to also seeing your incomes" << endl;
    cout << "Then you will have the option to create a realistic budget, taking into account your monthly salary and monthly expenses to see whether your spending your money wisely ◑.◑" << endl;
    cout << "First we will begin with asking you some basic questions! ( ★^O^★ )" << endl;
    
    cout << "What is your annual salary: " << endl;
    cin >> userSalary;                              // get user salary
    cout << "Please choose a city in LA County: " << endl;
    cin.ignore();
    getline(cin, cityName);                                // get the city they want to estimate the cost of living in
    cout << endl;

    // Check if city is in LA county
    
    while(!found)   {
        for(i = 0; i < cities.size(); ++i)  {
            if(cities.at(i) == cityName)    {
                found = true;
            }
        }

        if(found)   {
            cout << "The city entered is in LA county. Projecting Menu:" << endl;
            cout << endl;
        }

        else{
            cout << "The city entered is not apart of LA county. Please enter a city in LA county: " << endl;
            cin >> cityName;
        }
    }

    //call functions    
    calcStateTax(userSalary, stateTaxRate, totalStateTax);
    calcFederalTax(userSalary, federalTaxRate, totalFederalTax);
    netIncome = userSalary - totalFederalTax - totalStateTax;
    
    //Menu and Options:
    cout << "Choose an option. Press f to exit." << endl;
    cout << endl;
    printMenu();
    cin >> userOption;
    
    while(userOption != 'f')    {

        cout << endl;

        if(userOption == 'a')   {
            cout << "Budget:" << endl;
            cout << "Utilities -- 5 to 10% of your budget -- $" << netIncome * 0.05 << " to $" << netIncome * 0.10 << endl;
            cout << "Food -- 5 to 15% of your budget -- $" << netIncome * 0.05 << " to $" << netIncome * 0.15 << endl;     
            cout << "Transportation -- 10 to 15% of your budget -- $" << netIncome * 0.10 << " to $" << netIncome * 0.15 << endl;
            cout << "Clothing -- 5 to 10% of your budget -- $" << netIncome * 0.05 << " to $" << netIncome * 0.10 << endl;
            cout << "Medical-- 5 to 10% of your budget -- $" << netIncome * 0.05 << " to $" << netIncome * 0.10 << endl;
            cout << "Savings/Investment -- 10 to 15% of your budget -- $" << netIncome * 0.1 << " to $" << netIncome * 0.15 << endl;
            cout << "Other --  5 to 10% of your budget -- $" << netIncome * 0.05 << " to $" << netIncome * 0.10 << endl;
            cout << "Housing -- 25 to 35% of your budget -- $" << netIncome * 0.25 << " to $" << netIncome * 0.35 << endl;
            cout << endl;
            cout << "Would you like to see the average house price in your area? (y/n)" << endl;
            cin >> choice;
            if (choice == 'y'){
                cout << "The average apartment rent in " << cityName << " is $" << ApartmentRent(cityName, cities, avgApartmentPrice) << endl;
            }
        }
        else if(userOption == 'b')   {
            cout << "Your tax deduction is:" << endl;
            
            cout << "State Tax rate: " << stateTaxRate << endl;
            cout << "Total State Tax: $" << totalStateTax << endl;
            
            cout << "Federal Tax rate: " << federalTaxRate << endl;
            cout << "Total Federal Tax: $" << totalFederalTax << endl;
            
            cout << "Total tax: $" << totalStateTax + totalFederalTax << endl;
            cout << "Budget after tax: $" << netIncome << endl;
        }
        else if(userOption == 'c')   {
            cout << "Net monthly income (monthly income - taxes): $" << netIncome / 12 << endl;
        }
        else if(userOption == 'd')   {
            cout << "Net yearly income (yearlyincome - taxes): $" << netIncome << endl;
        }
        else if(userOption == 'e')   {
            cout << "Based on your selected city, " << cityName << ", your average apartment rent is $" << ApartmentRent(cityName, cities, avgApartmentPrice) << "." << endl;
        }
        else {
            cout << "***Choice Invalid***" << endl;
        }
        cout << endl;
        cout << "If you would like to continue getting budget tips/information with your budget buddy, input a new letter. Press f to exit.";
        printMenu();
        cin >> userOption;
    }

    cout << endl;

    //Real Calculations
    double monthlyIncome = netIncome / 12.0;
    double income;
    
    cout << "Now that you have looked at potential costs and budgeting information, if you would like to calculate actual costs, press y, otherwise press n.";
    cin >> choice;
    cout << endl;

    while(choice != 'n')    {
        if (choice == 'y')
        {
            cout << endl;
            cout << "NOTE: Tax has already been deducted. Your net monthly salary is $" << netIncome / 12.0 << endl << endl;
            cout << "Before helping to calculate your budget, do you have any debt? If yes press y, if no press n.";
            cin >> choice;
            cout << endl;

            if(choice == 'y')    {
            cout << "Please enter the monthly debt amount. This debt is not housing debt. The housing debt will count as housing expenses.";
            cout << "The debt entered will be deducted from your salary before expense calculations." << endl;
            cout << "Please enter debt amount: " << endl;
            cin >> debtAmount;
            monthlyIncome -= debtAmount;
            
            cout << "Your remaining balance before paying expenses is $" << monthlyIncome << endl;
            }

            income = monthlyIncome;
            cout << "Generating Menu for real calculations: " << endl;
            cout << "Note: Please choose menu options for actual expenses you are currently paying or wish to pay." << endl << endl;
            
            printRealMenu();
            cout << "Choose a letter from a - f:" << endl;
            cin >> userOption;
            
            while(userOption != 'q')    {

                cout << endl;

                if (userOption == 'a'){
                    cout << "How much do you pay for housing?" << endl;
                    addDeductPayment(monthlyIncome, income);
                }
                else if (userOption == 'b'){
                    cout << "How much do you pay for utilities?" << endl;
                    addDeductPayment(monthlyIncome, income);
                }
                else if (userOption == 'c'){
                    cout << "How much do you pay for food?" << endl;
                    addDeductPayment(monthlyIncome, income);
                }
                else if (userOption == 'd'){
                    cout << "How much do you pay for health services?" << endl;
                    addDeductPayment(monthlyIncome, income);
                }
                else if (userOption == 'e'){
                    cout << "How much do you pay for transportation?" << endl;
                    addDeductPayment(monthlyIncome, income);
                }
                else if (userOption == 'f'){
                    cout << "How much do you pay for clothing?" << endl;
                    addDeductPayment(monthlyIncome, income);
                    
                }
                else  {
                    cout << "***Choice Invalid***" << endl;
                }

                cout << endl;
                cout << "Your remaining balance is $" << income << endl << endl;
                cout << "If you would like to continue calculating, input a new letter. Press q to exit." << endl;
                cin >> userOption;
            
            }

            cout << endl;
            cout << "The remaining balance is $" << income << ". You can add this to your savings or add it to personal spending!" << endl;
        }

        else    {
            cout << "***Choice Invalid***" << endl;
            cout << "Please press y if you wish to calculate actual costs or n for no." << endl;
            cin >> choice;
        }
    }

    cout << "Thank you for choosing Budget Buddy, we hope to see you again soon!" << endl;
}

void calcStateTax(const int userSalary, double &stateTaxRate, double &totalStateTax) {
    if(userSalary >= 698272)
    {
        stateTaxRate = 0.123;
        totalStateTax = 67876.49 + (stateTaxRate * userSalary) / 698271;
    }
    else if(userSalary >= 418962 && userSalary <= 298271)
    {
        stateTaxRate = .113;
        totalStateTax = 36314.46 + (stateTaxRate * userSalary) / 418961;

    }
    else if(userSalary >= 349138 && userSalary <= 418961)
    {
        stateTaxRate = .103;
        totalStateTax = 29122.59 + (stateTaxRate * userSalary) / 418961;
    }
    else if(userSalary >= 68351 && userSalary <= 349137)
    {
        stateTaxRate = .093;
        totalStateTax = 3009.40 + (stateTaxRate * userSalary) / 68350;
    }
    else if(userSalary >= 54082 && userSalary <= 68350)
    {
        stateTaxRate = .08;
        totalStateTax = 1867.88 + (stateTaxRate * userSalary) / 54081;

    }
    else if(userSalary >= 38960 && userSalary <= 54081)
    {
        stateTaxRate = .06;
        totalStateTax = 960.56 + (stateTaxRate * userSalary) / 38959;

    }
    else if(userSalary >= 24685 && userSalary <= 38959)
    {
        stateTaxRate = .04;
        totalStateTax = 389.56 + (stateTaxRate * userSalary) / 24684;

    }
    else if(userSalary >= 10413 && userSalary <= 24684)
    {
        stateTaxRate = .02;
        totalStateTax = 104.12 + (stateTaxRate * userSalary) / 10412;
    }
    else if(userSalary >= 0 && userSalary <= 10412)
    {
        stateTaxRate = .01;
        totalStateTax = stateTaxRate * userSalary;
    }
}

void calcFederalTax(const int userSalary, double &federalTax, double& totalFederalTax){
    if(userSalary >= 578126)
    {
        federalTax = 0.37;
    }
    else if(userSalary >= 231251 && userSalary <= 578125)
    {
        federalTax = .35;
    }
    else if(userSalary >= 182101  && userSalary <= 231250)
    {
        federalTax = .32;
    }
    else if(userSalary >= 95376 && userSalary <= 182100)
    {
        federalTax = .24;
    }
    else if(userSalary >= 44726 && userSalary <= 95375)
    {
        federalTax = .22;
    }
    else if(userSalary >= 11001 && userSalary <= 44725)
    {
        federalTax = .12;
    }
    else if(userSalary >= 0 && userSalary <= 11000)
    {
        federalTax = .10;
    }
    totalFederalTax = federalTax * userSalary;
}

void printMenu()
{
    cout << endl;
    cout << "Menu: " << endl;
    cout << "a. Set up Budget" << endl;
    cout << "b. Show Tax Expenses" << endl;
    cout << "c. Net monthly income" << endl;
    cout << "d. Net yearly income" << endl;
    cout << "e. Average Apartment rent" << endl;
    cout << "f. Exit" << endl;
}

int ApartmentRent(const string userCity, const vector <string> &cities, const vector <int> &avgApartmentPrice)   {
    unsigned int i;

    for (i = 0; i < cities.size(); ++i) {
        if(userCity == cities.at(i)) {
            return avgApartmentPrice.at(i);
        }
    }

    cout << "City not in LA county" << endl;
    return 0;
}

void printRealMenu()
{
    cout << endl;
    cout << "Menu: " << endl;
    cout << "a. Housing" << endl;
    cout << "b. Utilities" << endl;
    cout << "c. Food" << endl;
    cout << "d. Medical health" << endl;
    cout << "e. Transportation" << endl;
    cout << "f. Clothing" << endl;
    cout << "q. Quit" << endl;
}

void addDeductPayment(const double monthlyIncome, double& income) {
    double payment;
    cin >> payment;
    cout << endl;
    income -= payment;
    if(income < 0) {
        cout << "Your costs have exceeded your budget. Budget Buddy is sad T^T" << endl;
        income = monthlyIncome;
        cout << "Budget buddy wanted to help you out so the expenses have all been reset. Please work through the Menu again :D" << endl;
    }
}