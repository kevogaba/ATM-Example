#define BANKNAME "Funny Bank Kenya"
#define SLOGAN "We delight in helping you grow"

// Structure of a normal account holder.
struct accountHolder{
    int accNo;
    char accName[50];
    int cardNum;
    int accountBal;
}accDetails[5]; // This has limited me to five account holders at the moment, for memory safety.
