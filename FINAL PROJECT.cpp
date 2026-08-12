#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

// Function Declarations
bool cafeID(string userID, string password); // Function for staff login verification
string generateTransactionID(int seed);     // Function to generate a transaction ID
int calculateLoyaltyPoints(double total);    // Function to calculate loyalty points
void customerPage(string coupons[][2], int couponCount, string menuItems[], double prices[], int MENU_SIZE, int& transactionSeed); // Handles customer interactions
void staffPage(string coupons[][2], int& couponCount, string menuItems[], double prices[], int MENU_SIZE); // Handles staff management


// Main Function
int main()
{
    const int MENU_SIZE = 20; // Number of menu items
    string menuItems[MENU_SIZE] =
	{
        "Espresso\t\t\t", "Americano\t\t\t", "Cappuccino\t\t\t", "Latte\t\t\t", "Mocha\t\t\t", // Coffee
        "Black Tea\t\t\t", "Chamomile Tea\t\t", "Green Tea\t\t\t", "Jasmine Tea\t\t\t", "Butterfly Pea Tea\t\t", // Tea
        "Chocolate Milkshake\t\t", "Vanilla Milkshake\t\t", "Strawberry Milkshake\t", "Banana Milkshake\t\t", "Mango Milkshake\t\t", // Milkshakes
        "Apple Strudel\t\t", "Egg Tart\t\t\t", "Bomboloni\t\t\t", "Pain au Chocolat\t\t", "Danish\t\t\t" // Desserts
    };

    double prices[MENU_SIZE] =
	{
        4.20, 6.90, 10.20, 9.90, 13.90, // Coffee prices
        5.90, 5.90, 6.90, 6.90, 8.90,   // Tea prices
        14.50, 14.50, 17.50, 14.50, 14.50, // Milkshakes prices
        6.90, 4.90, 6.50, 10.90, 7.90    // Desserts prices
    };

    // Initialize coupons as a 2D array (up to 10 coupons)
    string coupons[10][2];
    int couponCount = 0;

    int transactionSeed = 123456; 		// Seed for generating transaction IDs


    int role;
    do 
	{
        cout << "\nWelcome to the Beryl's Cafe System!\n1. Customer\n2. Staff\n3. Exit\nSelect your role: ";
        cin >> role;

        if (role == 1)
		{
            customerPage(coupons, couponCount, menuItems, prices, MENU_SIZE, transactionSeed);
        }
		else if (role == 2)
		{
            staffPage(coupons, couponCount, menuItems, prices, MENU_SIZE);
        }
    } while (role != 3);

    cout << "Thank you for using the Beryl's Patisserie Cafe System!\n";
    return 0;
}


// Function Definitions

// Function to verify staff login
bool cafeID(string userID, string password)
{
    const string savedUserID = "user123";
    const string savedPassword = "pass123";

    bool verified = false;
    
    do
	{
        cout << "\nEnter User ID : ";
        cin >> userID;
        
        cout << "Enter password : ";
        cin >> password;
        
        if (userID == savedUserID && password == savedPassword)
		{
            verified = true; // Set verified flag
            break; // Exit loop on successful login
        }
        
        else
		{
        	cout << "Invalid user ID or password. Please try again." << endl;
		}

    } while (!verified); // Continue until verified
    
    return verified; // Return verification status after exiting loop
}

// Function to generate a unique transaction ID
string generateTransactionID(int seed)
{
    string transactionID = "TXN";
    for (int i = 0; i < 6; i++)
	{
        transactionID += to_string((seed + i) % 10); // Generates a deterministic "random" 6-digit number
    }
    return transactionID;
}

// Function to calculate loyalty points (1 point for every RM10 spent)
int calculateLoyaltyPoints (double total)
{
    int points;
    points = total / 10; 	// Calculate points
    return points;       	// Return the calculated points
}

// Function for customer interface
void customerPage(string coupons[][2], int couponCount, string menuItems[], double prices[], int MENU_SIZE, int& transactionSeed)
{
    int quantities[MENU_SIZE] = {0};
    int choice, quantity, coldDrinkQuantity, orderChoice;
    double subtotal = 0, coldAddOn;
    char continueOrdering, drinkTemp;
    string dineOption, discountCode;
    bool dineIn = false;
    const double SERVICE_TAX = 0.06;
    const double DINE_IN_SERVICE_CHARGE = 0.10; // 10% service charge for dine-in

    cout << "\nWelcome to the Beryl's Patisserie Cafe Ordering Kiosk!\n";
    	
    // Selecting dine-in or takeaway
    do
    {
    cout << "Are you dining in or taking away? (D - Dine / TA Take Away): ";
    cin >> dineOption;
    
    if  (dineOption == "d" || dineOption == "D" || dineOption == "TA" || dineOption == "ta")
    {
    	break;
	}
	
	if (dineOption != "d" || dineOption != "D" || dineOption != "TA" || dineOption != "ta")
	{
		cout << "Invalid Option. Please try Again. " << endl;
	}
	
	} while (dineOption != "d" || dineOption != "D" || dineOption != "TA" || dineOption != "ta");

    
    if (dineOption == "d" || dineOption == "D")
	{
        dineIn = true;
    }

	// Displaying menu
    cout << "\nMenu:\n";
    for (int i = 0; i < MENU_SIZE; i++)
	{
        cout << "\t\t" << i + 1 << ". " << menuItems[i] << " - RM" << prices[i] << endl;
    }
   
   	do
	{	
		cout << "\n[1] Order Now || [2] Back : ";
		cin >> orderChoice;
		
		if ( orderChoice == 2)
		{
			cout << "\nThank you for using Beryl's Patisserie Cafe Ordering Kiosk\n" << endl;
			return;
		}
		
		if ( orderChoice == 1 )
		{
			break;
		}
		
		if (orderChoice < 1 || orderChoice > 2 )
		{
			cout << "Invalid Choice. Please Try Again. " << endl;
		}
		
	} while (orderChoice < 1 || orderChoice > 2);
	
	
    // Taking orders
    do
	{
		do
		{
	        cout << "\nEnter the number of the item you want to order: ";
	        cin >> choice;
	        
	        if (choice <= 10)
	        {
		        do
		        {
		            cout << "H- Hot / C- Cold : ";
		            cin >> drinkTemp;
		            
		            if ( drinkTemp == 'H' || drinkTemp == 'h' || drinkTemp == 'c' ||drinkTemp == 'C')
		            {
		            	break;
					}
		            
		            if (drinkTemp != 'H' || drinkTemp != 'h' || drinkTemp != 'C' || drinkTemp != 'c')
		            {
		            	cout << "Invalid Option. Please Try Again. " << endl;
					}
		    	} while (drinkTemp != 'H' || drinkTemp != 'h' || drinkTemp != 'C' || drinkTemp != 'c');
	    	}
	    	
	        else
	        {
	        	if ( choice >=11 && choice <= 20)
	        	{
		        	drinkTemp = 'D';
		        	cout << "Choice : Default"<<endl;
		        }
		        
			}
	
	        if (choice < 1 || choice > MENU_SIZE)
			{
	            cout << "Invalid choice. Please try again.\n";
	        }
	        
	        
    	} while (choice <1 || choice > 20);
		
		do
		{
			
	        cout << "Enter quantity: ";
	        cin >> quantity;
	
	        if (drinkTemp == 'C' || drinkTemp == 'c')
			{
	            coldAddOn += (2 * quantity); // Additional charge for cold drinks
	            coldDrinkQuantity += quantity;
	        }
	        
	         if (quantity < 1)
			{
	            cout << "Invalid quantity. Please try again.\n";
	            continue;
	        }
	      	
	        quantities[choice - 1] += quantity;
        
    	} while ( quantity < 1);

		do
        {
        	cout << "Do you want to order another item? (y/n): ";
        	cin >> continueOrdering;
       		
       		
	       if ( continueOrdering == 'n' || continueOrdering == 'N' || continueOrdering == 'y' || continueOrdering == 'Y')
	        {
	        	break;
	    	}
	    	else
	    	{
	    		cout << "Wrong choice! Please try again." << endl;
	    		
			}
	        
		} while ( continueOrdering != 'n' && continueOrdering != 'N' && continueOrdering != 'y' && continueOrdering != 'Y');
		
    } while (continueOrdering == 'y' || continueOrdering == 'Y');

    // Applying discount code
    cout << "\nIf you have a discount code, enter it now (or type 'N' for none): ";
    cin >> discountCode;

    double discountRate = 0.0;
    bool discountApplied = false;
    for (int i = 0; i < couponCount; i++)
	{
        if (coupons[i][0] == discountCode)
		{
            discountApplied = true;
            discountRate = stod(coupons[i][1]);
            break;
        }
    }

    // Calculating subtotal
    for (int i = 0; i < MENU_SIZE; i++)
	{
        if (quantities[i] > 0)
		{
            subtotal += prices[i] * quantities[i];
        }
    }
	
	subtotal = subtotal + coldAddOn;
	
    // Calculating discount, service charge, tax, and final total
    double discountAmount = round ((subtotal * discountRate)* 10.00 ) / 10.00;
    double totalAfterDiscount = subtotal - discountAmount;
    double serviceCharge = round((dineIn ? totalAfterDiscount * DINE_IN_SERVICE_CHARGE : 0 ) * 10.00) /10.00 ;
    double serviceTax = round(((totalAfterDiscount + serviceCharge) * SERVICE_TAX ) * 10.00 ) /10.00 ;
    double finalTotal = round ((totalAfterDiscount + serviceCharge + serviceTax ) *100.00 ) / 100.00; 
    
    int loyaltyPoints = calculateLoyaltyPoints(finalTotal);

    // Payment process
    int paymentMethod;
    string PayMethod;
	
	do
	{
	    cout << "How would you like to pay? (1 - Cash / 2 - Debit Card / 3 - Credit Card): ";
	    cin >> paymentMethod;
	    
	    if (paymentMethod > 0  || paymentMethod < 4)
	    {
		    switch (paymentMethod)
		    {
		    	case 1 : PayMethod = "Cash"; break;
		    	
		    	case 2 : PayMethod = "Debit Card"; break;
		    	
		    	case 3 : PayMethod = "Credit Card"; break;
		    	
			}
			
		}
		
		if (paymentMethod <1 || paymentMethod >3)
		{
			cout << "Invalid Payment Method. Please Try Again." << endl;
		}
	
	} while (paymentMethod < 1 || paymentMethod > 3);
	
	

    if (paymentMethod == 1)
	{
    	cout << "\n\n-----------------------------------------------------"<<endl;
        cout << "\nPlease pay at the counter." << endl;
    } else {
    	cout << "\n\n-----------------------------------------------------"<<endl;
        cout << "\nPayment Successful !" << endl;
    }

    // Printing receipt
    cout << "\n=========\tRECEIPT\t\t=========\n\n";
    
    for (int i = 0; i < MENU_SIZE; i++)
	{
        if (quantities[i] > 0)
		{
            cout << menuItems[i] << " x" << quantities[i] << "\t\t\tRM" << fixed << setprecision(2) << prices[i] * quantities[i] << endl;
        }
    }
    
    if (coldDrinkQuantity > 0) cout << "(C) Add-On" << "  x" << coldDrinkQuantity << "\t\t\t" << "RM" <<coldAddOn<<endl;
    cout << "\n===========================================\n";
    cout << "Subtotal:\t\t\tRM" << subtotal << endl;
    if (discountApplied) cout << "Discount:\t\t\t-RM" << discountAmount << endl;
    if (dineIn) cout << "Service Charge:\t\t\tRM" << serviceCharge << endl;
    cout << "Service Tax:\t\t\tRM" << serviceTax << endl;
    cout << "Total:\t\t\t\tRM" << finalTotal << endl;
    cout << "\nPayment Method :\t\t" << PayMethod << endl;
    cout << "Loyalty Points:\t\t\t" << loyaltyPoints << endl;
    cout << "\n==========================================\n";
    
    cout << "\n-\tThank you for your order!\t-\n";

    // Displaying transaction ID
    cout << "\tTransaction ID: " << generateTransactionID(transactionSeed++) << endl<<endl;
   	cout << "-----------------------------------------"<<endl;
}

// Function for staff management interface
void staffPage(string coupons[][2], int& couponCount, string menuItems[], double prices[], int MENU_SIZE)
{
    int option;
    bool verification;
    string userID, password;

    verification = cafeID(userID, password);

    if (verification)
	{
        do
		{
            cout << "\nStaff Panel:\n1. Add Coupon Code\n2. Adjust Inventory\n3. Exit to Main Menu\nChoice: ";
            cin >> option;

            if (option == 1)
			{ // Adding a coupon code
                string newCode;
                double discount;
                cout << "Enter new coupon code: ";
                cin >> newCode;
                
                cout << "Enter discount rate (e.g., 0.10 for 10%): ";
                cin >> discount;
                
                coupons[couponCount][0] = newCode;
                coupons[couponCount][1] = to_string(discount);
                couponCount++;
                cout << "Coupon added successfully!\n";
            }
            
			else if (option == 2)
			{ // Adjusting item prices
                int itemNum;
                double newPrice;
                cout << "\nCurrent Menu:\n";
                for (int i = 0; i < MENU_SIZE; i++)
				{
                    cout << i + 1 << ". " << menuItems[i] << " - RM" << fixed << setprecision(2) << prices[i] << endl;
                }
                
                do
                {
	                cout << "\nEnter the item number to adjust: ";
	                cin >> itemNum;
	                
	                if ( itemNum >=1 && itemNum <= 20)
	                {
	                	do
	                	{
		                	cout << "\nEnter new price (exp. 5.90 || 9.50): RM";
		                	cin >> newPrice;
		                	
		                	if ( newPrice > 0.00)
		                	{
		                		prices[itemNum - 1] = newPrice;
			                	cout << "\nPrice updated successfully!\n";
							}
							
							if ( newPrice < 0 )
							{
								cout << "Invalid amount entered. Please try again." << endl;
							}
	                	
	                	} while (newPrice < 0);
					}
					else
					{
	        			cout << "Invalid item number. Please Try again." << endl;
					}
					
            	} while (itemNum <1 || itemNum >20);
            	
				}  
        
		} while (option != 3);
    }
}