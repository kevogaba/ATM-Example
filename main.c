// Our bank acc structure.
#include "headers/bankStruct.h"
// Our ATM sequence of events
#include "headers/events.h"

int main(void)
{
    // Welcome user and prompt for choice of language of preference.
    printf("Welcome to %s ATM!\n%s.", BANKNAME,SLOGAN);

    // select Language
    int language = selectLanguage();

    // Input and validate PIN
    validatePin(language);

    // Start Active transaction session
    float balance = 2000;
    int transactionActive = 1;
    do{
        balance = transact(balance, inflateMenu(language), language);
        (language == 1)? printf("\nDo you wish to perform another transaction?.\n\t1. Yes\t2. No\nSelection: "):
        printf("\nJe, unataka kuzidi?.\n\t1. Ndio\t2. La\nChaguo: ");
        scanf("%d", &transactionActive);
    }while(transactionActive == 1);

    // Good bye after Transaction
    (language == 1)? printf("\nThank you for banking with us!\n") : printf("\nKwaheri!\n");

    return 0;
}
