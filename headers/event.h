#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaration of functions
int selectLanguage();
int validatePin(int language);
int inflateMenu(int language); // returns the selection
float transact(float balance, int selection, int language);
int withdrawCash(float amount, float balance, float standingCharge, int language);
int deposit(float amount, float balance, int language);
void checkBalance(float balance, int language);
int transferCash(float balance, float standingCharge, float transferFee, float amount, int language);
void printMinistatement(int language);


// 1. Allowing users to select language of preference between English and Kiswahili.
int selectLanguage(){
    int language;
    int languageAvailable = 0;
    while(languageAvailable == 0)
    {
        printf("\nPlease select your language:\n\t1.English\n\t2.Kiswahili\n");
        printf("Your choice (1 or 2): ");
        scanf("%d", &language);
        // If language is not available on the list of options
        if(language == 1 || language == 2){
            languageAvailable = 1;
        }else{
            printf("Invalid choice. Please input 1 or 2.");
        }
    }
    return language;
}

// 2. Validating pin using a language of their choice.
int validatePin(int language){
    int pin = 2323;
    int enteredPin;
    int pinStatus = 0;
    int attempts = 3;
    do{
        attempts--;
        printf("%s", (language == 1)? "\nEnter your pin number: ": "\nWeka nambari yako ya siri: ");
        scanf("%d", &enteredPin);
        if(enteredPin == pin){
            pinStatus = 1;
        }else{
        if(attempts != 0){
            (language == 1)? printf("\nInvalid pin. You have %d more attempts.\n",attempts) : printf("\nNambari ya siri sio sahihi. Unaweza jaribu mara nyingine %d.\n", attempts);
        }else{
            (language == 1)? printf("\nYour card has been temporarily blocked. Please consult the bank. Goosebumps!") : printf("\nAccounti yako imezuiliwa. Tafadhali fika kwenye benki. Kwaheri.\nEeeh, nanii beba kadi yako!");
            exit(1);
        }
        }
    }while(pinStatus == 0);
return pinStatus;
}


// 3. Inflate a menu in a language of users choice. && 4. Get return the chosen transaction.
int inflateMenu(int language)
{
    // Get menu file in the language chosen.
    FILE *menuFile;
    if(language == 1)
    {
        printf("Welcome. Please Select a service.\n");
        menuFile = fopen("languages/englishMenu.txt", "r");
    }else{
        printf("Karibu. Tafadhali Chagua huduma.\n");
        menuFile = fopen("languages/kiswahiliMenu.txt", "r");
    }
    // Read menu items from file
    char menuItem[40];
    int menuItemsCount = 1;
    while(fgets(menuItem,sizeof(menuItem),menuFile))
    {
            printf("\t%d. %s",menuItemsCount,menuItem);
            menuItemsCount++;
    }

    // Get user's desired Transaction
    int transaction;
    (language == 1)? printf("\nTransaction: "): printf("Huduma: ");
    scanf("%d", &transaction);

    fclose(menuFile);
    return transaction;
}


// 5. Carry out the transaction that has been selected from menu.
float transact(float balance, int transaction, int language){
    float standingCharge = 500;
    float transferFee = 85;
    float amount;
    switch (transaction)
    {
        case 1:
            balance = withdrawCash(amount, balance, standingCharge, language);
            break;

        case 2:
            checkBalance(balance, language);
            break;

        case 3:
            balance = transferCash(balance, standingCharge, transferFee, amount, language);
            break;

        case 4:
            printMinistatement(language);
            break;

        case 5:
            balance = deposit(amount, balance,language);
            break;

        default:
            (language == 1)? printf("\nInvalid choice.\n") : printf("\nChaguo duni jamaa!\n");
            break;

    }

    return balance;
}

// 6. Transactions
// 6.1: Withdraw Cash
int withdrawCash(float amount, float balance, float standingCharge, int language){
            (language == 1)? printf("Enter amount to withdraw: ") :printf("Unatoa pesa ngapi: ");
            scanf("%f", &amount);
            if(amount < balance - standingCharge){
                balance -= amount;
                (language == 1)?  printf("Transaction Successful. Withdrawn %.2f. Balance is %.2f.",(float) amount, balance) : printf("Huduma imeidhinishwa. Umetoa %.2f. Baki ya akaunti ni: %.2f.",(float) amount, balance);
            }else{
                (language == 1)? printf("\nYou have insufficient balance.\n") : printf("\nHuna pesa za kutosha. Umesota Jamaa!\n");
            }

            return balance;
        }

// 6.2: Check Balance
void checkBalance(float balance, int language){
    (language == 1)? printf("\nBalance is: %.2f", balance): printf("Baki yako ni: %.2f",balance);
}

// 6.3: Transfer Cash
int transferCash(float balance, float standingCharge, float transferFee, float amount, int language){
        int accountNumber;
        if(language == 1){
            printf("Enter amount to transfer: ");
            scanf("%f", &amount);
            ENG:
            printf("\nEnter account recipient account number: ");
            scanf("%d", &accountNumber);
        }else{
            printf("Unatuma pesa ngapi?: ");
            scanf("%f", &amount);
            SWA:
            printf("\nWeka nambari ya akaunti ya unayetumia: ");
            scanf("%d", &accountNumber);
        }

        // Confirm that account number is valid.
        char strAccNumber[15];
        sprintf(strAccNumber, "%d", accountNumber);
        unsigned long int accNoLen = strlen(strAccNumber) + 1;
        printf("\n%lu\n", accNoLen);
        // Typical account numbers are always 11 digits long.
         if(accNoLen != 11){
             if(language == 1){
                 printf("\nInvalid Account number. A valid account number is 11 digits long.");
                 goto ENG;
             }else{
                 printf("\nNambari ya akaunti uliyoweka sio sahihi. Nambari sahihi huwa na urefu wa 11.");
                 goto SWA;
             }
         }else{
            if(amount < balance - (standingCharge + transferFee)){
                balance -= (float) amount;
                (language == 1)? printf("Transaction successful. You have transfered %.2f.", amount): printf("Huduma imeidhinishwa. Umetuma %.2f", amount );
            }else{
                (language == 1)? printf("\nYou have insufficient balance to complete this transaction.\n"): printf("\nHuna pesa za kutosha. Umesota Jamaa!\n");
            }
    }
    return balance;
}

// 6.4: Deposit some cash
int deposit(float amount, float balance, int language){
    (language == 1)? printf("Enter amount to deposit: ") :printf("Unaweka pesa ngapi: ");
    scanf("%f", &amount);
    balance += amount;
    (language == 1)?  printf("Transaction Successful. Deposited %.2f. Balance is %.2f.",(float) amount, balance) : printf("Huduma imeidhinishwa. Umeongeza %.2f. Baki ya akaunti ni: %.2f.",(float) amount, balance);

    return balance;
}

// 6.5: Print ministatement
void printMinistatement(int language){
    (language == 1)? printf("\nPlease collect your ministatement...\n"): printf("\nChukua ministatement yako jamaa!\n");;
}
