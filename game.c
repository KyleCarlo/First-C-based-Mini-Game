/*
    Description:    This program simulates a simple trading game 
                    and the player must increase their points (Golden Dragons) as much as they can.
    Programmed by:  Kyle Carlo C. Lasala     Section: S17b
    Last modified:  February 5, 2022
    Acknowledgement: The mentioned websites helped in gaining in-depth knowledge for time.h,
                     string.h, conio.h, and dirent.h in this program respectively.
                     https://www.tutorialspoint.com/c_standard_library/time_h.htm
                     https://www.tutorialspoint.com/c_standard_library/string_h.htm
                     https://www.educative.io/edpresso/what-is-getchar-in-c
                     https://stackoverflow.com/questions/4204666/how-to-list-files-in-a-directory-in-a-c-program

                     Furthermore, https://ascii.co.uk/art is where most of the ascii art came from.
                     Others, came from my own idea and generated some ascii art using
                     https://manytools.org/hacker-tools/convert-images-to-ascii-art/ 
*/

#include <stdio.h>  //standard input output library
#include <stdlib.h> //where srand and random functions are defined 
#include <time.h>   //where time function is defined
#include <string.h> //where strlen and strcmp functions are defined
#include <conio.h>  //where getch function is defined
#include <windows.h> //where is clear screen is defined
#include <dirent.h> //where the directory function is defined

#define NORMRANGE 21 //range of price for normal items
#define NORMMIN 180 //minimum price for normal items
#define SPECRANGE 51 //range of price for special items
#define SPECMIN 100 //minimum price for special items

//DESIGN ONLY FUNCTIONS
/*
    UI function creates the common border for user interface design

    Precondition: input of the user in *cPart is a valid string within the conditions of the functions

    @param *cPart - is a pointer string that will determine the border structure to make
    @param nSpacing - is an integer that determines the length of the border
*/
void UI (char *cPart, int nSpacing);

/*
    delay function delays in executing the printf functions 

    @param nSecs - is an integer input on how many seconds will be the program delay
*/
void delay (int nSecs);

/*
    invalidinput function displays the printf statement if the user input is invalid within 
    the specific situation

    Precondition: input of the user in specific situation is known to be inalid
*/
void invalidinput ();

/*
    gameintro function displays the introductory part of the game which introduces the story
    and instructions for the game

    Precondition: the game intro should be displayed only once every program execution

    @return nReturn - determines if the game will start or if the user will exit
*/
int gameintro ();

/*
    acknowledgement function displays the acknowledgements indicated above 

    Precondition: the acknowledgement only prints after the player totally completes the 15 days of the game
*/
void acknowledgement();

//FUNCTIONS THAT ARE PART OF THE PROGRAM FLOW

/*
    ChoosingPartner function prints the user interface for selecting the trading partner and
    also prompts the user to choose a partner

    @param *cPartnerNames - array of strings that holds the partner names

    @return cChoice - the partner chosen by the player
*/
char ChoosingPartner (char *cPartnerNames[]);

/*
    SetPrice function sets the normal and special prices for every trading partner
    
    Precondition: There is already a chosen valid trading partner

    @param cPartner - the partner chosen by the player
    @param fPrice - array of floats that stores the prices per each item
*/
void SetPrice (char cPartner, float fPrice[]);

/*
    DayAction function prints the user interface for the day and prompts the user 
    to choose an action (buy, sell, ironbank, wheelhouse, or quit)

    Precondition: There is already a chosen valid trading partner and
                  the prices are already generated

    @param cPartner - the chosen partner of the player
    @param *cPartnerNames - array of strings that stores the names of the partners
    @param *cItemNames - array of strings that stores the names of the items
    @param fPrice - array of floats that stores the prices 
    @param nIntry - array of integers that stores the quantity per item
    @param nDays - days remaining in the game
    @param fGD - the golden dragons of the player
    @param fDebt - the accumulated debt of the user
    @param fSavings - the accumulated savings of the player inside of the bank
    @param nStored - the total quantity of all items
    @param nTCap - the total capacity available in the wheelhouse

    @return cChoice - the chosen action of the player
*/
char DayAction (char cPartner, char *cPartnerNames, char *cItemNames[], float fPrice[], int nIntry[], int nDays, float fGD, float fDebt, float fSavings, int nStored, int nTCap);

/*
    Buy function prints the user interface for the player and prompts the user to choose
    an action to buy an item

    Precondition: There is already a chosen valid trading partner and
                  the prices are already generated. Player also chose
                  to sell in the day action

    @param *cItemNames - array of strings that stores the names of the items
    @param fPrice - array of floats that stores the prices
    @param nIntry - array of integers that stores the quantity per item
    @param *fGD - pointer to the golden dragons of the player
    @param *nStored - pointer to the total quantity of all items
    @param nTCap - the total capacity available in the wheelhouse
    @param *cDayAction - the action of the user in the day 
*/
void Buy (char *cItemNames[], float fPrice[], int nIntry[], float *fGD, int *nStored, int nTCap, char *cDayAction);

/*
    Sell function prints the user interface for the player and prompts the user to choose
    an action to sell an item

    Precondition: There is already a chosen valid trading partner and
                  the prices are already generated. Player also chose 
                  to sell in the day action

    @param *cItemNames - array of strings that stores the names of the items
    @param fPrice - array of floats that stores the prices
    @param nIntry - array of integers that stores the quantity per item
    @param *fGD - pointer to the golden dragons of the player
    @param *nStored - pointer to the total quantity of all items
    @param nTCap - the total capacity available in the wheelhouse
    @param *cDayAction - the action of the player in the day
*/
void Sell (char *cItemNames[], float fPrice[], int nIntry[], float *fGD, int *nStored, int nTCap, char *cDayAction);

/*
    IronBank function prints the user interface for the player and prompts the user to choose
    an action to either deposit, withdraw, loan, or pay a loan 

    Precondition: There is already a chosen valid trading partner and
                  the prices are already generated

    @param *fGD - pointer to the golden dragons of the player
    @param *fSavings - pointer to the savings of the player
    @param *fDebt - pointer to the debts of the player
    @param fAccount - the savings capacity of the player
    @param fLoanable - the loanable amount for the day
    @param *nLoanMark - the identifier that determines if the user already loaned for the day
    @param *cDayAction - the action of the player in the day
*/
void IronBank (float *fGD, float *fSavings, float *fDebt, float fAccount, float fLoanable, int *nLoanMark, char *cDayAction);

/*
    Deposit function prints the user interface for the player and prompts the user to choose
    an action to deposit a golden dragon to their savings

    Precondition: Player chose iron bank in the day action

    @param *fGD - pointer to the golden dragons of the player
    @param *fSavings - pointer to the savings of the player
    @param fAccount - the savings capacity of the player
    @param *cDayAction - the action of the player in the day
*/
void Deposit (float *fGD, float *fSavings, float fAccount, char *cDayAction);

/*
    Withdraw function prints the user inteface for the player and prompts the user to choose
    an action to withdraw a golden dragon from their savings

    Precondition: Player should have greater than 0 golden dragons and 
                  player prompts in the iron bank to deposit

    @param *fGD - pointer to the golden dragons of the player
    @param *fSavings - pointer to the savings of the player
    @param *cDayAction - the action of the player in the day
*/
void Withdraw (float *fGD, float *fSavings, char *cDayAction);

/*
    Loan function prints the user interface for the player and prompts the user to choose
    an action to loan from the iron bank with 5% interest every day

    Precondition: Player should have greater than 0 savings and 
                  player prompts in the iron bank to withdraw

    @param *fGD - pointer to the golden dragons of the player
    @param *fDebt - pointer to the debts of the player
    @param fLoanable - loanable amount of the user for the day
    @param *nLoanMark - identifier that determines if the user already loaned for the day
*/
void Loan (float *fGD, float *fDebt, float fLoanable, int *nLoanMark, char *cDayAction);

/*
    PayLoan function prints the user interface for the player and prompts the user to choose 
    an action to pay loan to the ironbank

    Precondition: Player should greater than 0 loaned amount and
                  player prompts in the iron bank to pay loan

    @param *fGD - pointer to the golden dragons of the player
    @param *fDebt - pointer to the debts of the player
    @param *cDayAction - the action of the player in the day
*/
void PayLoan (float *fGD, float *fDebt, char *cDayAction);

/*
    WheelHouse function prints the loading interface for the player when chose wheelhouse

    Precondition: Player chose wheelhouse in the day action
*/
void WheelHouse ();

/*
    Merchant function prints the user interface for the player and prompts the user to choose
    either to accept the offered powerups 

    Precondition: Random number generated within the range of 0 - 9 is equals to 0 and
                  the user already chose wheelhouse in the day action
    
    @param *fGD - pointer to the golden dragons of the player
    @param *nTCap - pointer to the wheelhouse capacity of the player
    @param *fAccount - pointer to the savings capacity of the player
    @param *fLoanable - pointer to the loanable amount of the player for the next day
    @param nIntry - array of integer that stores the quantity per item
    @param *nChestMark - identifier that determines if the user already unlocked the chest
    @param *nStored - pointer to the total quantity of all items
*/
void Merchant (float *fGD, int *nTCap, float *fAccount, float *fLoanable, int nIntry[], int *nChestMark, int *nStored);

/*
    TreasureChest function prints the user interface of the player and prompts the user to 
    unlock the chest to get the reward

    Precondition: The user encountered the merchant

    @param *fGD - pointer to the golden dragons fo the player
    @param nIntry - array of integer that stores the quantity per item
    @param *nChestMark - identifier that determines if the user already unlocked the chest
    @param *nStored - pointer to the total quantity of all items
*/
void TreasureChest (float *fGD, int nIntry[], int *nChestMark, int *nStored); 

/*
    ExitGame function prints the player data for ending the game and prompts the user if
    he wants to save the game or not

    Precondition: The user chose quit in any part of the game

    @param nDays - remaining days of the player
    @param fGD - golden dragons of the player
    @param fDebt - debts accumulated in the ironbank
    @param fSavings - savings accumulated in the ironbank
    @param nStored - total quantity of all items
    @param nTCap - total capacity in the wheelhouse
    @param nIntry - array of integer that stores the quantity per item
    @param fPrice - array of float that stores the prices per item
    @param nProgressIdentifier - identifier where the user quit the game
    @param nLoanMark - identifier if the player already loaned for the day
    @param nChestMark - identifier if the player already unlocked the chest
    @param cPartner - chosen trading partner of the player
    @param *cItemNames - array of strings that stores the names of the items
*/
int ExitGame (int nDays, float fGD, float fDebt, float fSavings, int nStored, int nTCap, int nIntry[], float fPrice[], int nProgressIdentifier, int nLoanMark, int nChestMark, char cPartner, char *cItemNames[]);

/*
    SaveProgress function saves the progress of the player in the game if he prompted 
    to save the game

    Precondition: The player chose quit and prompted to save the game

    @param cName - string that stores the name of the player
    @param nDays - remaining days of the player
    @param fGD - golden dragons of the player
    @param fDebt - debts accumulated in the iron bank
    @param fSavings - savings accumulated in the iron bank
    @param nStored - total quantity of all items
    @param nTCap - wheelhouse capacity
    @param nIntry - array of integer that stores the quantity per item
    @param fPrice - array of float that stores the prices per item
    @param nProgressIdenfier - identifier that determines where the player quits
    @param nLoanMark - identifier if the player already loaned for the day
    @param nChestMark - identifier if the player already unlocked the chest
    @param cPartner - chosen trading partner of the player
*/
void SaveProgress (char cName[], int nDays, float fGD, float fDebt, float fSavings, int nStored, int nTCap, int nIntry[], float fPrice[], int nProgressIdentifier, int nLoanMark, int nChestMark, char cPartner);

/*
    LoadProgress function loads the saved file of the player created from 
    previous game

    Precondition: There is an existing saved file in the directory of the source code

    @param cName - string that stores the name of the player
    @param *nDays - pointer to remaining days of the player
    @param *fGD - pointer to golden dragons of the player
    @param *fDebt - pointer to debts accumulated in the iron bank
    @param *fSavings - pointer to savings accumulated in the iron bank
    @param *nStored - pointer to total quantity of all items
    @param *nTCap - pointer to wheelhouse capacity
    @param nIntry - array of integer that stores the quantity per item
    @param fPrice - array of float that stores the prices per item
    @param *nProgressIdenfier - identifier that determines where the player quits
    @param *nLoanMark - identifier if the player already loaned for the day
    @param *nChestMark - identifier if the player already unlocked the chest
    @param *cPartner - pointer to chosen trading partner of the player
    @param *cItemNames - array of strings that stores the names of the item
    @param *cPartnerNames - array of strings that stores the names of the trading partners
*/
void LoadProgress (char cName[], int *nDays, float *fGD, float *fDebt, float *fSavings, int *nStored, int *nTCap, int nIntry[], float fPrice[], int *nProgressIdentifier, int *nLoanMark, int *nChestMark, char *cPartner, char *cItemNames[], char *cPartnerNames[]);

/*
    MAIN FUNCTION
*/
int main()
{
    char cPartner, //stores which partner is chosen for the day
         cDayAction, // stores which action is chosen for the day
         cName[128], // stores the name of the player
         cFileName[128], // stores the name of the file created to print the score
         *cPartnerNames[] = {"Winterfell",  //stores the string names of partner choices
                             "Lys",
                             "Myr",
                             "Pentos",
                             "Qohor",
                             "Volantis"},
         *cItemNames[] = {"Sweet Beet",     //stores the string names of items
                          "Timber", 
                          "Intricate Lace", 
                          "Intoxicating Perfume", 
                          "Pale Amber Wine", 
                          "Myrish Eye", 
                          "Qohorik Tapestry", 
                          "Valyrian Steel"};
    int i,              //for loop variable
        nDays = 15,     //days remaining
        nIntry[8] = {0,0,0,0,0,0,0,0}, /* 1D array to store the items
                            1 - sweetbeet
                            2 - timber
                            3 - intricate lace
                            4 - intoxicating perfume
                            5 - pale amber wine
                            6 - myrish eye
                            7 - qohorik tapestry
                            8 - valyrian steel */
        nStored = 0,      //stored items in wheelhouse
        nTCap = 50,       //total capacity of wheelhouse
        nLoanMark = 0,    //identifier if the user already loaned for the day
        nChestMark = 0,   //identifier if the user already unlocked the chest
        nProgressIdentifier = 0;  //variable that identifies where does the user stop
    float fGD = 2000.0,     //number of dragon coins
          fDebt = 0.0,      //debt in the iron bank
          fSavings = 0.0,   //savings in the ironbank
          fAccount = 2000.0, //savings capacity;
          fLoanable = 1000.0, //loanable amount per day;
          fPrice[8] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0}, // 1D array to store the prices of items same order as inventory
          fScore = 0; //stores the over all score of the player

    srand(time(NULL)); //seed of the randomizer

    system("cls");
    nDays = gameintro();
    LoadProgress(cName, &nDays, &fGD, &fDebt, &fSavings, &nStored, &nTCap, nIntry, fPrice, &nProgressIdentifier, &nLoanMark, &nChestMark, &cPartner, cItemNames, cPartnerNames);
    // loads the progress of the player
    system("cls");
    
    while (nDays > 0) //initial loop - while remaining days is not equal to 0
    {
        if (nProgressIdentifier == 0) //progress identifier if there is a saved file
            cPartner = ChoosingPartner(cPartnerNames);
        if (cPartner != '9') 
        {
            if (nProgressIdentifier == 0) //progress identifier if there is a saved file
            {   
                printf("%s", cPartnerNames[cPartner - '0' - 1]); 
                SetPrice(cPartner, fPrice); //generates the prices
            }
            do
            {
                cDayAction = DayAction(cPartner, cPartnerNames[cPartner - '0' - 1], cItemNames, fPrice, nIntry, nDays, fGD, fDebt, fSavings, nStored, nTCap);
                //choose trading partner and printed UI already checked within the range of valid inputs
                switch (cDayAction)
                {
                case 'b':
                case 'B':
                    Buy(cItemNames, fPrice, nIntry, &fGD, &nStored, nTCap, &cDayAction);           
                    //buying function
                    break;
                case 's':
                case 'S':
                    Sell(cItemNames, fPrice, nIntry, &fGD, &nStored, nTCap, &cDayAction);
                    //selling function
                    break;
                case 'i':
                case 'I':
                    IronBank(&fGD, &fSavings, &fDebt, fAccount, fLoanable, &nLoanMark, &cDayAction);
                    //ironbank function 
                    break;
                case 'w':
                case 'W':
                    nProgressIdentifier = 0;
                    Merchant(&fGD, &nTCap, &fAccount, &fLoanable, nIntry, &nChestMark, &nStored);
                    WheelHouse();
                    //day ends
                    break;
                }
                
                if (cDayAction == 'Q' || cDayAction == 'q') // if the user quits
                {
                    nProgressIdentifier = 1; //changes the progress identifier
                    nDays = ExitGame(nDays, fGD, fDebt, fSavings, nStored, nTCap, nIntry, fPrice, nProgressIdentifier, nLoanMark, nChestMark, cPartner, cItemNames);
                    //ending process if the user exits the games
                }
            } while (!(cDayAction == 'q' || cDayAction == 'Q' || cDayAction == 'w' || cDayAction == 'W'));   
        }
        else //nTradingPartner == 9
        {
            nDays = ExitGame(nDays, fGD, fDebt, fSavings, nStored, nTCap, nIntry, fPrice, nProgressIdentifier, nLoanMark, nChestMark, cPartner, cItemNames);    
        }

        if (nDays != 0 && nProgressIdentifier == 0) //processes before the end of the day
        {
            nDays--; 
            nLoanMark = 0;
            if (nDays == 0) // ending actions if the user completed the 15 days
            {
                fScore = (((((fGD - fDebt) * 2.0) + fSavings + (fDebt * -4.0) + (nTCap - nStored))/4050.0) - 1.0) * 100.0;
                if(fScore >= 0)
                    printf("\n        You increased the economy of the Six Kingdoms by %.2f%%\n\n", fScore);
                else
                    printf("\n        You decreased the economy of the Six Kingdoms by %.2f%%\n\n", fScore);
                printf("         ___ _  _ ___     ___  ___    ___   _   __  __ ___ \n");
                printf("        | __| \\| |   \\   / _ \\| __|  / __| /_\\ |  \\/  | __| \n");
                printf("        | _|| .` | |) | | (_) | _|  | (_ |/ _ \\| |\\/| | _|      \n");
                printf("        |___|_|\\_|___/   \\___/|_|    \\___/_/ \\_\\_|  |_|___| \n\n\n");

                printf("            Enter your short name: ");
                scanf("%123s", cName);

                //creating a file name
                for (i = 0; i < strlen(cName); i++)
                {
                    cFileName[i] = cName[i];
                }
                cFileName[strlen(cName)] = '.';
                cFileName[strlen(cName) + 1] = 't';
                cFileName[strlen(cName) + 2] = 'x';
                cFileName[strlen(cName) + 3] = 't';
                cFileName[strlen(cName) + 4] = '\0';

                //score report for the user printed in a file
                FILE * fscorereport = fopen(cFileName, "w");
                fprintf(fscorereport, "Player: %s\n\n", cName);
                fprintf(fscorereport, "SCORE ITEMS       EQUIVALENT\n");
                fprintf(fscorereport, "Golden Dragons:    %.2f x 2\n", fGD - fDebt);
                fprintf(fscorereport, "Savings:           %.2f x 1\n", fSavings);
                fprintf(fscorereport, "Debt:              %.2f x-4\n", fDebt);
                fprintf(fscorereport, "Unused Storage:    %d x 1\n", nTCap - nStored);
                fprintf(fscorereport, "TOTAL SCORE:       %.0f", (((fGD - fDebt) * 2.0) + fSavings + (fDebt * -4.0) + (float)(nTCap - nStored)) - 4050.0);
                fclose(fscorereport);

                //acknowledgement as indicated above
                acknowledgement();
            }
            else 
            {
                //another processses before the day totally ends
                fSavings += fSavings * 0.10;
                fDebt += fDebt * 0.05;
            }
        }
    }
    return 0;
}

void UI (char *cPart, int nSpacing)
{
    int i; //for loop variable
    if (strcmp(cPart, "top") == 0)
    {
        for (i = 0; i < nSpacing; i++) // first border
        {
            if (i == 0)
                printf("%c", 201);
            else if (i == nSpacing - 1)
                printf("%c", 187);
            else
                printf("%c", 205);
        }
    }
    else if (strcmp(cPart, "middle") == 0)
    {
        for (i = 0; i < nSpacing; i++) // middle border
        {
            if (i == 0)
                printf("%c", 186);
            else if (i == nSpacing - 1)
                printf("%c", 186);
            else
                printf(" ");
        }
    }
    else if (strcmp(cPart, "middle2") == 0) // middle border 2
    {
        for (i = 0; i < nSpacing; i++)
        {
            if (i == 0)
                printf("%c", 204);
            else if (i == nSpacing - 1)
                printf("%c", 185);
            else 
                printf("%c", 205);
        }
    }
    else if (strcmp(cPart, "bottom") == 0)
    {
        for (i = 0; i < nSpacing; i++) // bottom border
        {
            if (i == 0)
                printf("%c", 200);
            else if (i == nSpacing - 1)
                printf("%c", 188);
            else
                printf("%c", 205);
        }
    }
    else if (strcmp(cPart, "space") == 0)
    {
        for (i = 0; i < nSpacing; i++) // spacing only
        {
            printf(" ");
        }
    }
}

void delay(int nSecs)
{
    int nMSecs = 1000 * nSecs;
    clock_t start_time = clock(); //in ms
    while (clock() < start_time + nMSecs);
}

void invalidinput()
{
    printf("Invalid Choice. Try Again.");
    delay(1);
    system("cls");
}

int gameintro ()
{
    int nReturn = 0;
    int nCountdown;
    char cSkip;
    for (nCountdown = 5; nCountdown >= 0; nCountdown--)//COUNTDOWN
    {
        system("cls");
        printf("\n\n\n\n\n                             PLEASE TOGGLE FULL SCREEN, BEFORE THE GAME STARTS\n");
        printf("                                          The game begins in %d...", nCountdown);
        delay(1);
    }
    //INTRODUCTION
    printf("\n\n\n                           press 's' to skip game intro or press Enter to read ");
    cSkip = getch();
    if(!(cSkip == 's' || cSkip == 'S'))
    {
        system("cls");
        printf("                                                                    o .,<>., o            \n");
        printf("                                                                    |\\/\\/\\/\\/|            \n");
        printf("                                                                    '========'            \n");
        printf("                                                                    (_ SSSSSSs            \n");
        printf("                                                                    )a'`SSSSSs            \n");
        printf("                                                                   /_   SSSSSS            \n");
        printf("                                                                   .=## SSSSS      \n");
        printf("                                                                   .####  SSSSs     \n");
        printf("                                                                   ###::::SSSSS     \n");
        printf("                                                                  .;:::""""SSS     \n");
        printf("                                                                 .:;:'  . .  \\\\     \n");
        printf("                                                                .::/  '     .'|     \n");
        printf("                                                               .::( .         |     \n");
        printf("                                                               :::)           \\     \n");
        printf("                                                               /\\(            /     \n");
        printf("                                                              /)            ( |     \n");
        printf("                                                            .'  \\  .       ./ /     \n");
        printf("                                                         _-'    |\\  .        |     \n");
        printf("                                       _..--..   .  /\"---\\      | ` |      . |     \n");
        printf("               -=====================,' _     \\=(*#(7.#####()   |  `/_..   , (     \n");
        printf("                           _.-''``';'-''-) ,.  \\ '  '+/// |   .'/   \\  ``-.) \\     \n");
        printf("                         ,'  _.-  ((    `-'  `._\\    `` \\_/_.'  )    /`-._  ) |     \n");
        printf("                       ,'\\ ,'  _.'.`:-.    \\.-'                 /   <_L   )\"  |     \n");
        printf("                     _/   `._,' ,')`;  `-'`'                    |     L  /    /     \n");
        printf("                    / `.   ,' ,|_/ / \\                          (    <_-'     \\     \n");
        printf("                    \\ / `./  '  / /,' \\                        /|`         `. |     \n");
        printf("                    )\\   /`._   ,'`._.-\\                       |)            \\'     \n");
        printf("                   /  `.'    )-'.-,' )__)                      |\\            `|     \n");
        printf("                  : /`. `.._(--.`':`':/ \\                      ) \\             \\     \n");
        printf("                  |::::\\     ,'/::;-))  /                      ( )`.            |     \n");
        printf("                  ||:::::  . .::':  :`-(                       |/    .          |     \n");
        printf("                  ||::::|  . :|  |==[]=:                       .        -       \\     \n");
        printf("                  |||:::|  : ||  :  |  |                      /\\           `     |     \n");
        printf("      ___ ___     '|;:::|  | |'   \\=[]=|                     /  \\                \\     \n");
        printf("     |   /_  ||``|||:::::  | ;    | |  |                     \\_.'\\_               `-.     \n");
        printf("     :   \\_``[]--[]|::::'\\_;'     )-'..`._                 .-'\\``:: ` .              \\     \n");
        printf("      \\___.>`''-.||:.__,'         |_______`>              <_____:::.         . . \\  _/     \n");
        delay(3);

        //STORY
        printf("\n\n\n        After being handed the Iron throne, "); delay(3); printf("King Bran of House Stark,\n"); delay(2);
        printf("        decided to devise a strategic plan "); delay(3); printf("to improve the economic  \n");
        printf("        growth of the Six Kingdoms. "); delay(3); printf("The Royal Treasury currently has \n");
        printf("        2,000 Golden Dragons only. "); delay(4); printf("To accomplish this task, he inst \n");
        printf("        -ructed YOU as his hand, Lord Tyrion Lannister, "); delay(4); printf("and his Master\n"); 
        printf("        of Coin, Lord Bronn of the Blackwater, to go to trade with\n"); delay(3);
        printf("        other kingdoms in Westeros and other free cities in Essos.\n\n"); delay(3);

        //INSTRUCTIONS
        printf("        You, Lord Tyrion, along with Lorn Bronn, have the respons\n"); delay(4);
        printf("        -ibility to improve the economy of the Six Kingdoms by \n");delay(4);
        printf("        TRADING ITEMS and EARNING GOLDEN DRAGONS.\n        You have 15 DAYS");delay(4);
        printf(" to accomplish the task, my Lord.\n\n"); delay(4);

        //SETUP
        printf("        You may select different trading partners, but you can only\n"); delay(4); 
        printf("        choose one partner a day. You can still visit other trading\n"); delay(4);
        printf("        partners after the day.\n"); delay (4);
        printf("        You can improve the economy better, the more items you sell.\n"); delay(4);
        printf("        Be aware of your DEBTS as it can increase your trading power,\n"); delay(4);
        printf("        but decrease the economy 4 times.\n"); delay(3);
        printf("        And you may end the day by selecting the wheelhouse.\n"); delay(4);
        printf("        AND ALSO, LOOK FOR THE MERCHANT, I think he can help you my Lord.\n"); delay(4); 
        }
        system("cls");

        printf("\n\n\n                                                                /\\\\           \n");
        printf("                                                                \\X\\\\\n");
        printf("                                                                 \\X\\\\ /\\\\\n");
        printf("                                                                  \\X\\/ //\n");
        printf("                                                                   \\X //\n");
        printf("                                                                   / .\\\\	\n");
        printf("           THE MAN WHO PASSES THE SENTENCE,                       / /\\.\\\\\n");	 	
        printf("                MUST SWING THE SWORD...                           \\// \\.\\\\\n");
        printf("                                                                       \\.\\\\\n");
        printf("                                                                        \\.\\\\\n");
        printf("                                                                         \\.\\\\\n");
        printf("                                                                          \\.\\\\\n");
        printf("                                                                           \\.\\\\\n");
        printf("                                                                            \\.\\\\\n");
        printf("                                                                             \\_|\n\n\n");
        delay(5);
        printf("                                   Press Enter to continue... ");
        getch();


    do
    {
        system("cls");
        printf("\n\n                                                           ,.=,,==. ,,_                 \n");
        printf("                                          _ ,====, _    |I|`` ||  `|I `|                \n");
        printf("                      _|\\_,              |`I|    || `==,|``   ^^   ``  |                \n");
        printf("              ,.--,   \\_ `a\\_            | ``    ^^    ||_,===TT`==,,_ |                \n");
        printf("         6^`--:_ ||  ,/  ,-,,\\           |,==Y``Y==,,__| \\L=_-`'   +J/`                 \n");
        printf("        / \\```\\ \\|\\_/ /-/\\\\  `            \\|=_  ' -=#J/..-|=_-     =|                   \n");
        printf("       /  \\.., | \\/  /-/  `                |=_   -;-='`. .|=_-     =|----T--,           \n");
        printf("      /   \\..,'|    /-|                    |=/\\  -|=_-. . |=_-/^\\  =||-|-|::|____       \n");
        printf("          \\__     \\_L-==,                  |=||  -|=_-. . |=_-| |  =|-|-||::\\____       \n");
        printf("          |  /   \\_.-..=                   |=LJ  -|=_-. . |=_-|_|  =||-|-|:::::::       \n");
        printf("          \\ /    /--_/\\                    |=_   -|=_-_.  |=_-     =|-|-||::::::        \n");
        printf("         _J`   .'-_,/\\_``=                 |=_   -|=//^\\. |=_-     =||-|-|:::::::       \n");
        printf("      `X`    \\/--_/    `-`             ,   |/&_,_-|=||  | |=_-     =|-|-||:::::::       \n");
        printf("      /   \\   |_/                   ,--``8%%,/    ',%%||  | |=_-     =||-|-|%%::::::       \n");
        printf("         _/  / /                ,---`_,888`  ,.'''''`-.,|,|/!,--,.&\\|&\\-,|&#:::::       \n");
        printf("      ./`; /`/`                |;:;K`__,...;=\\_____,=``           %%%%%%&     %%#,---       \n");
        printf("          \\\\\\\\                 |;::::::::::::|       `'.________+-------\\   ``          \n");
        printf("           w w           |    /8M%%;:::;;:::::|                  |        `-------       \n");
        printf("                         |   |`   88`V  /&8%%\\|_______,__,,      |                       \n");
        printf("                         |   /,  %%8,  ,/&888%% &,       ,  `-----`,--..../|--,,,,_       \n");
        printf("                        / \\/88%%  88%%  8888%%88%% &,       \\,     `\\      /     &,,        \n");
        printf("                        |,M8,  , `8%%   ,,8%% `8, `         , \\,        &\\     ,&##       \n");
        printf("                       /8888%%  888`    ```    `            `  `               ```       \n");
        printf("\n\n                           [S]TART                      [E]XIT");
        cSkip = getch();
        switch (cSkip)
        {
        case 's':
        case 'S':
            nReturn = 15;
        case 'e':
        case 'E':
            cSkip = 0;
            break;
        default:
            cSkip = 1;
            break;
        }
        system("cls");
    }while (cSkip);

    return nReturn;
}

char ChoosingPartner (char *cPartnerNames[])
{
    char cChoice;

    do
    {
        printf("\n\n");
        printf("                               ");  UI ("top", 30);     printf("                                %c\n", 30);
        printf("                               ");  UI ("middle", 30);  printf("                              %c %c %c\n", 17, 232, 16);
        printf("                               ");  printf("%c  %c%c%c TRADING PARTNERS %c%c%c  %c", 186, 232, 232, 232, 232, 232, 232, 186); printf("                                %c\n", 31);
        printf("          /\\                   "); UI ("middle", 30);  printf("\n");
        printf("         /  \\                  %c     [%d] %-18s %c\n", 186, 1, cPartnerNames[0], 186);
        printf("        /    \\   /\\            %c     [%d] %-18s %c\n", 186, 2, cPartnerNames[1], 186);
        printf("       /      \\ /  \\           %c     [%d] %-18s %c\n", 186, 3, cPartnerNames[2], 186);
        printf("      /  /\\    /    \\        /\\%c     [%d] %-18s %c    /\\  /\\      /\\            /\\/\\/\\  /\\\n",     186, 4, cPartnerNames[3], 186);
        printf("     /  /  \\  /      \\      /  %c     [%d] %-18s %c\\/\\/  \\/  \\  /\\/  \\/\\  /\\  /\\/ / /  \\/  \\\n", 186, 5, cPartnerNames[4], 186);
        printf("    /  /    \\/ /\\     \\    /   %c     [%d] %-18s %c \\ \\  /    \\/ /   /  \\/  \\/  \\  /    \\   \\\n",  186, 6, cPartnerNames[5], 186);
        printf("   /  /      \\/  \\/\\   \\  /    "); UI ("middle", 30);  printf("  \\    /   /    \\\n");
        printf("__/__/_______/___/__\\___\\_____ %c     [%d] %-18s %c", 186, 9, "Quit", 186); printf("_____________________________________________\n");
        printf("                               "); UI ("middle", 30);  printf("\n");
        printf("                               "); UI ("bottom", 30);  printf("\n");    
        printf("                               Choose your partner: ");
        cChoice = getch();
        if (cChoice < '1' || (cChoice > '6' && cChoice != '9'))
        {
            printf("\n                               ");
            invalidinput();
        }
    } while (cChoice < '1' || (cChoice > '6' && cChoice != '9'));
    
    return cChoice;
}

void SetPrice (char cPartner, float fPrice[])
{
    int i; // for loop variable
    for(i = 0; i < 8; i++)
    {
        fPrice[i] = (rand() % NORMRANGE) + (NORMMIN + 100*i);
    }

    switch (cPartner) //special prices of each partner
    {
        case '1': //winterfell
            fPrice[1] = (rand() % SPECRANGE) + (SPECMIN*2); //TIMBER
            break;
        case '2': //lys
            fPrice[3] = (rand() % SPECRANGE) + (SPECMIN*4); //INTOXICATING PERFUME
            break;
        case '3': //myr
            fPrice[2] = (rand() % SPECRANGE) + (SPECMIN*3); //INTRICATE LACE
            fPrice[5] = (rand() % SPECRANGE) + (SPECMIN*6); //MYRISH EYE
            break;
        case '4': //pentos
            fPrice[4] = (rand() % SPECRANGE) + (SPECMIN*5); //PALE AMBER WINE
            break;
        case '5': //qohor
            fPrice[6] = (rand() % SPECRANGE) + (SPECMIN*7); //QOHORIK TAPESTRY
            fPrice[7] = (rand() % SPECRANGE) + (SPECMIN*8); //VALYRIAN STEEL
            break;
        case '6': //volantis
            fPrice[0] = (rand() % SPECRANGE) + (SPECMIN*1); //SWEET BEET
            break;
    }
}

char DayAction (char cPartner, char *cPartnerNames, char *cItemNames[], float fPrice[], int nIntry[], int nDays, float fGD, float fDebt, float fSavings, int nStored, int nTCap)
{   
    int i; //for loop variable
    char cUPartnerName[11],
         cChoice;

    delay(1);
    system("cls");

    //CAPITALIZATION OF NAME
    for (i = 0; i <= strlen(cPartnerNames); i++)
    {
        if (i > 0)
            cUPartnerName[i] = cPartnerNames[i] - 32;
        else
            cUPartnerName[i] = cPartnerNames[i];
    }
    cUPartnerName[strlen(cPartnerNames)] = '\0';

    do
    {     
        UI("space", 47);
        UI("top", 76); printf("\n");
        UI("space", 9); printf("%c M A R K E T P L A C E %c", 175, 174);
        UI("space", 13);
        printf("%c", 186);
        UI("space", 33);
        printf("%-40s %c\n", cUPartnerName, 186);
        UI("space", 47);
        UI("middle2", 76); printf("\n");
        printf("    ++++      /++++     :++++`    -++++`       ");
        printf("%c ITEM        WARES AND GOODS        SELLING/BUYING PRICE        INVENTORY %c\n", 186, 186);
        printf("  dddddddd\\`:o-````o\\`:ydddddm+`-o:````+o`     ");
        UI("middle2", 76); printf("\n");
        for (i = 0; i < 8; i++)
        {
            switch (i)
            {
            case 0:
                printf(":ddddddddddy-       `sdddddddddh:        +o    ");
                break;
            case 1:
            case 2:
            case 3:
            case 4:
                printf("omddddddddd/         :ddddddddds         `m    ");
                break;
            case 5:
                printf("-sdddddddddy/`     `:ydddddddddh+.      -o:    ");
                break;
            case 6:
                printf("  ydddddds- ./`   /o- .odddddh: \\\\.   -oN`     ");
                break;
            case 7:
                printf("  y:-yys-     .ooo-     .+yy:     ./oo/`m`     ");
                break;
            }
            printf("%c [%d]         %-30s%-20.2f%7d%5c\n", 186, i + 1, cItemNames[i], fPrice[i], nIntry[i], 186);
        }
        printf("     y:                              m`        ");
        UI("middle2", 76); printf("\n");
        printf("     y:                              m`        ");
        printf("%c [B]uy        [S]ell        [W]heelhouse        [I]ronbank        [Q]uit  %c\n", 186, 186);
        printf("     y:                              m`        ");
        for (i = 0; i < 76; i++) //specific UI
        {
            switch (i)
            {
            case 0:
                printf("%c", 204);
                break;
            case 75:
                printf("%c", 185);
                break;
            case 50:
                printf("%c", 203);
                break;
            default:
                printf("%c", 205);
                break;
            }
        }
        printf("\n     y:_____________________________ m`        ");
        printf("%c    Days Remaining:      - %-21d %c", 186, nDays, 186);           
        printf("     SPECIAL ITEM:      %c\n", 186);
        printf("   //y:///////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\m`\\\\      ");
        printf("%c    Golden Dragons (GD): - %-21.2f %c                        %c\n", 186, fGD, 186, 186);
        printf("  y:++++++++++++++++++++++++++++++++++++m`     ");
        printf("%c    Debt:                - %-21.2f %c", 186, fDebt, 186);
        switch (cPartner)
        {
        case '1':
            printf("        %s          %c\n", cItemNames[1], 186);
            break;
        case '2':
            printf("  %s  %c\n", cItemNames[3], 186); 
            break;
        case '3':
            printf("    %s      %c\n", cItemNames[2], 186);
            break;
        case '4':
            printf("    %s     %c\n", cItemNames[4], 186);
            break;
        case '5':
            printf("   %s     %c\n", cItemNames[6], 186);
            break;
        case '6':
            printf("      %s        %c\n", cItemNames[0], 186);
            break;
        }
        printf("  y:====================================m`     ");
        
        printf("%c    Savings:             - %-21.2f %c", 186, fSavings, 186);   
        switch (cPartner)
        {
        case '3':
            printf("      %s        %c\n", cItemNames[5], 186);
            break;
        case '5':
            printf("    %s      %c\n", cItemNames[7], 186);
            break;
        default:
            printf("                        %c\n", 186);
            break;
        }
        printf("  y:====================================m`     ");   
        printf("%c    Capacity:            - %-3d/%-3d %15c                        %c\n", 186, nStored, nTCap, 186, 186); 
        printf("  :+++++++++++++++++++++++++++++++++++++:      ");
        for (i = 0; i < 76; i++) //specific UI
        {
            switch (i)
            {
            case 0:
                printf("%c", 200);
                break;
            case 75:
                printf("%c", 188);
                break;
            case 50:
                printf("%c", 202);
                break;
            default:
                printf("%c", 205);
                break;
            }
        }
        switch (cPartner)
        {
        case '1':
            printf("\n             %c Town Code: \"D\" %c", 237, 237);
            break;
        case '2':
            printf("\n             %c Town Code: \"R\" %c", 237, 237);
            break;
        case '3':
            printf("\n             %c Town Code: \"A\" %c", 237, 237);
            break;
        case '4':
            printf("\n             %c Town Code: \"G\" %c", 237, 237);
            break;
        case '5':
            printf("\n             %c Town Code: \"O\" %c", 237, 237);
            break;
        case '6':
            printf("\n             %c Town Code: \"N\" %c", 237, 237);
            break;
        }
        UI("space", 34);
        printf("Choose your action for the day: ");
        cChoice = getch();

        switch (cChoice)
        {
        case 'b':
        case 'B': 
            if (fGD > fPrice[0] && nTCap - nStored > 0)
            {
                printf("Buy");
                delay(1);
            }
            else if (nTCap - nStored <= 0)
            {
                printf("\n"); UI("space", 65);
                printf("You do not have enough wheelhouse capacity my Lord.");
                delay(2);
                cChoice = 0;
                system("cls");
            }
            else if (fGD < fPrice[0])
            {
                printf("\n"); UI("space", 65);
                printf("You do not have enough Golden Dragons my Lord.");
                delay(2);
                cChoice = 0;
                system("cls");
            }   
            break;
        case 's':
        case 'S':
            if (nStored > 0)
            {
                printf("Sell");
                delay(1);
            }
            else
            {
                printf("\n"); UI("space", 65);
                printf("You do not have item to sell my Lord.");
                delay(2);
                cChoice = 0;
                system("cls");
            }   
            break;
        case 'w':
        case 'W':
            printf("Wheelhouse");
            delay(1);
            break;
        case 'i':
        case 'I':
            printf("IronBank");
            delay(1);
            break;
        case 'q':
        case 'Q':
            printf("Quit");
            delay(1);
            break;
        default:
            printf("\n                     ");
            UI("space", 44);
            invalidinput();
            cChoice = 0;
            break;
        }
    } while (!cChoice);
    system("cls");
    return cChoice;
}

void Buy (char *cItemNames[], float fPrice[], int nIntry[], float *fGD, int *nStored, int nTCap, char *cDayAction)
{
    char cOrder = '*',    //stores the order number of the item
         cQuantity; //if the user selects the character '+' it adds one to the variable nQuantity
                    //if the user selects the character '-' it removes one to the variable nQuantity
    int nQuantity = 0, //quantity of the item to be bought
        nLoop = 1, //loop identifier
        i; // for loob variable
    
    do
    {
        UI("top", 76); printf("\n");
        printf("%c ITEM        WARES AND GOODS        SELLING/BUYING PRICE        INVENTORY %c\n", 186, 186);
        UI("middle2", 76); printf("\n");
        for (i = 0; i < 8; i++)
        {
            printf("%c [%d]         %-30s%-20.2f%7d%5c\n", 186, i + 1, cItemNames[i], fPrice[i], nIntry[i], 186);
        }
        UI("middle2", 76); printf("\n");
        printf("%c     Golden Dragons (GD): - %-25.2f                     %c\n", 186, *fGD, 186);
        printf("%c     Capacity:            - %-3d/ %-18d                       %c\n", 186, *nStored, nTCap, 186);
        UI("middle2", 76); printf("\n");
        printf("%c     [ 1 - 8 ] Item Order                   [B]ack         [Q]uit         %c\n", 186, 186);
        printf("%c     [+] Add Item      [-] Remove Item      [0]Cancel      [P]roceed      %c\n", 186, 186);
        UI("bottom", 76); printf("\n");
        printf("        Enter the item order first: ");
        if (cOrder == '*')
            cOrder = getch();
        if (cOrder >= '1' && cOrder <= '8')
        {
            printf("%s", cItemNames[cOrder - '0' - 1]);
            if (nQuantity == 0 && *fGD < fPrice[cOrder - '0' - 1])
            {
                printf("\n        You do not have enough Golden Dragon, my Lord.");
                cOrder = '*';
                delay(1);
                system("cls");
            }
            else
            {
                if (nQuantity > 0)
                {
                    printf("\n\n        TOTAL PRICE: %.2f GD", nQuantity * fPrice[cOrder - '0' - 1]);
                    printf("\n        How many %s do you want to buy: %d", cItemNames[cOrder - '0' - 1], nQuantity);
                }
                else 
                {
                    printf("\n\n        How many %s do you want to buy: ", cItemNames[cOrder - '0' - 1]);
                }
                cQuantity = getch();
                switch (cQuantity)
                {
                case '+':
                    if (*nStored + 1 <= nTCap && *fGD >= fPrice[cOrder - '0' - 1])
                    {
                        nQuantity++;
                        (*nStored)++;
                        nIntry[cOrder - '0' - 1]++;
                        *fGD -= fPrice[cOrder - '0' - 1];
                    }
                    else if (*nStored + 1 > nTCap && *fGD < fPrice[cOrder - '0' - 1])
                    {
                        printf("\n        Sorry my Lord, but you do not have enough GD and storage");
                        delay(1);
                    }
                    else if (*fGD < fPrice[cOrder - '0' - 1])
                    {
                        printf("\n        Sorry my Lord, but you do not have enough Golden Dragons.");
                        delay(1);
                    }
                    else if (*nStored + 1> nTCap)
                    {
                        printf("\n        Sorry my Lord, but you do not have enough Wheelhouse storage.");
                        delay(1);
                    }
                    break;
                case '-':
                    if (nQuantity > 0)
                    {
                        nQuantity--;
                        (*nStored)--;
                        nIntry[cOrder - '0' - 1]--;
                        *fGD += fPrice[cOrder - '0' - 1];
                    }
                    else
                    {
                        printf("\n        You are not buying %s yet my Lord.", cItemNames[cOrder - '0' - 1]);
                        delay(1);
                    }
                    break;
                case 'P':
                case 'p':
                    if (nQuantity > 0)
                    {
                        printf("\n        %d %s was delivered to your wheelhouse, my Lord.", nQuantity, cItemNames[cOrder - '0' - 1]);
                        nQuantity = 0;
                        cOrder = '*';
                        delay(1);
                        if (*fGD < fPrice[0])
                        {
                            nLoop = 0;
                        }
                    }
                    else
                    {
                        printf("\n        Buy some item first my Lord.");
                        delay(2);
                    }
                    break;
                case '0':
                    *nStored -= nQuantity;
                    nIntry[cOrder - '0' - 1] -= nQuantity;
                    *fGD += fPrice[cOrder - '0' - 1] * nQuantity;
                    nQuantity = 0;
                    cOrder = '*';
                    break;
                case 'q':
                case 'Q':
                    *cDayAction = 'q';
                case 'B':
                case 'b':
                    if (nQuantity > 0)
                    {
                        printf("\n        Do you want to cancel or proceed the payment?\n");
                        printf("        [C]ancel  or  [P]roceed: ");
                        cQuantity = getch();
                        switch (cQuantity)
                        {
                        case 'c':
                        case 'C':
                            *nStored -= nQuantity;
                            *fGD += fPrice[cOrder - '0' - 1] * nQuantity;
                            nQuantity = 0;
                            break;
                        case 'p':
                        case 'P':
                            printf("\n        %d %s was delivered to your wheelhouse, my Lord.", nQuantity, cItemNames[cOrder - '0' - 1]);
                            nQuantity = 0;
                            delay(2);
                            break;
                        default:
                            cQuantity = '+';
                            printf("\n        ");
                            invalidinput();
                            break;
                        }
                    }
                    else
                    {
                        printf("\n        Please come back again my Lord.");
                        delay(1);
                    }
                    nLoop = 0;
                    break;
                default:
                    cQuantity = '+';
                    printf("\n        ");
                    invalidinput();
                    break;
                }
            }
            system("cls");
        }
        else if (cOrder == 'P' || cOrder == 'p' || cOrder == '0' || cOrder == '+' || cOrder == '-')
        {
            printf("\n        Select an Item Order [ 1 - 8 ] first.");
            cOrder = '*';
            delay(1);
            system("cls");
        }
        else if (cOrder == 'B' || cOrder == 'b') 
        {
            printf("Back");
            printf("\n        Please come back again my Lord.");
            nLoop = 0;
            delay(1);
        }
        else if (cOrder == 'Q' || cOrder == 'q')
        {
            printf("Quit\n");
            *cDayAction = cOrder;
            nLoop = 0;
        }
        else
        {
            invalidinput();
            cOrder = '*';
        }
    } while (nLoop);
}

void Sell (char *cItemNames[], float fPrice[], int nIntry[], float *fGD, int *nStored, int nTCap, char *cDayAction)
{
    char cOrder = '*',    //stores the order number of the item
         cQuantity; //if the user selects the character '+' it adds one to the variable nQuantity
                    //if the user selects the character '-' it removes one to the variable nQuantity
    int nQuantity = 0, //quantity of the item to be bought
        nLoop = 1, //loop identifier
        i; // for loob variable
    
    do
    {
        UI("top", 76); printf("\n");
        printf("%c ITEM        WARES AND GOODS        SELLING/BUYING PRICE        INVENTORY %c\n", 186, 186);
        UI("middle2", 76); printf("\n");
        for (i = 0; i < 8; i++)
        {
            printf("%c [%d]         %-30s%-20.2f%7d%5c\n", 186, i + 1, cItemNames[i], fPrice[i], nIntry[i], 186);
        }
        UI("middle2", 76); printf("\n");
        printf("%c     Golden Dragons (GD): - %-25.2f                     %c\n", 186, *fGD, 186);
        printf("%c     Capacity:            - %-3d/ %-18d                       %c\n", 186, *nStored, nTCap, 186);
        UI("middle2", 76); printf("\n");
        printf("%c   [ 1 - 8 ] Item Order                       [B]ack        [Q]uit        %c\n", 186, 186);
        printf("%c   [+] Add to Sell    [-] Remove from Sell    [0] Cancel    [P] roceed    %c\n", 186, 186);
        UI("bottom", 76); printf("\n");
        printf("        Enter the item order first: ");
        if (cOrder == '*')
            cOrder = getch();
        if (cOrder >= '1' && cOrder <= '8')
        {
            printf("%s", cItemNames[cOrder - '0' - 1]);
            if (nQuantity == 0 && nIntry[cOrder - '0' - 1] == 0)
            {
                printf("\n        You do not have that %s, my Lord.", cItemNames[cOrder - '0' - 1]);
                cOrder = '*';
                delay(1);
                system("cls");
            }
            else
            {
                if (nQuantity > 0)
                {
                    printf("\n\n        TOTAL SELLING PRICE: %.2f GD", nQuantity * fPrice[cOrder - '0' - 1]);
                    printf("\n        How many %s do you want to sell: %d", cItemNames[cOrder - '0' - 1], nQuantity);
                }
                else 
                {
                    printf("\n\n        How many %s do you want to sell: ", cItemNames[cOrder - '0' - 1]);
                }
                cQuantity = getch();
                switch (cQuantity)
                {
                case '+':
                    if (nIntry[cOrder - '0' - 1] > 0)
                    {
                        nQuantity++;
                        (*nStored)--;
                        nIntry[cOrder - '0' - 1]--;
                        *fGD += fPrice[cOrder - '0' - 1];
                    }
                    else
                    {
                        printf("\n        Sorry my Lord, you can only sell %d %s.", nQuantity, cItemNames[cOrder - '0' - 1]);
                        delay(1);
                    }
                    break;
                case '-':
                    if (nQuantity > 0)
                    {
                        nQuantity--;
                        (*nStored)++;
                        nIntry[cOrder - '0' - 1]++;
                        *fGD -= fPrice[cOrder - '0' - 1];
                    }
                    else
                    {
                        printf("\n        You are not selling %s yet my Lord.", cItemNames[cOrder - '0' - 1]);
                        delay(1);
                    }
                    break;
                case 'P':
                case 'p':
                    if (nQuantity > 0)
                    {
                        printf("\n        %d %s was delivered to the market, my Lord.", nQuantity, cItemNames[cOrder - '0' - 1]);
                        nQuantity = 0;
                        cOrder = '*';
                        if (*nStored == 0)
                        {
                            nLoop = 0;
                        }
                        delay(1);
                    }
                    else
                    {
                        printf("\n        Sell some item first my Lord.");
                        delay(2);
                    }
                    break;
                case '0':
                    *nStored += nQuantity;
                    nIntry[cOrder - '0' - 1] += nQuantity;
                    *fGD -= fPrice[cOrder - '0' - 1] * nQuantity;
                    nQuantity = 0;
                    cOrder = '*';
                    break;
                case 'q':
                case 'Q':
                    *cDayAction = 'q';
                case 'B':
                case 'b':
                    if (nQuantity > 0)
                    {
                        printf("\n        Do you want to cancel or proceed to sell?\n");
                        printf("        [C]ancel  or  [P]roceed: ");
                        cQuantity = getch();
                        switch (cQuantity)
                        {
                        case 'c':
                        case 'C':
                            *nStored += nQuantity;
                            *fGD -= fPrice[cOrder - '0' - 1] * nQuantity;
                            nQuantity = 0;
                            break;
                        case 'p':
                        case 'P':
                            printf("\n        %d %s was delivered to the market, my Lord.", nQuantity, cItemNames[cOrder - '0' - 1]);
                            nQuantity = 0;
                            delay(2);
                            break;
                        default:
                            cQuantity = '+';
                            printf("\n        ");
                            invalidinput();
                            break;
                        }
                    }
                    else
                    {
                        printf("\n        Please come back again my Lord.");
                        delay(1);
                    }
                    nLoop = 0;
                    break;
                default:
                    cQuantity = '+';
                    printf("\n        ");
                    invalidinput();
                    break;
                }
            }
            system("cls");
        }
        else if (cOrder == 'P' || cOrder == 'p' || cOrder == '0' || cOrder == '+' || cOrder == '-')
        {
            printf("\n        Select an Item Order [ 1 - 8 ] first.");
            cOrder = '*';
            delay(1);
            system("cls");
        }
        else if (cOrder == 'B' || cOrder == 'b') 
        {
            printf("Back");
            printf("\n        Please come back again my Lord.");
            nLoop = 0;
            delay(1);
        }
        else if (cOrder == 'Q' || cOrder == 'q')
        {
            printf("Quit\n");
            *cDayAction = cOrder;
            nLoop = 0;
        }
        else
        {
            invalidinput();
            cOrder = '*';
        }
    } while (nLoop);
}

void IronBank (float *fGD, float *fSavings, float *fDebt, float fAccount, float fLoanable, int *nLoanMark, char *cDayAction)
{
    char cAction;
    int nLoop = 1;
    do
    {
        printf("\n"); UI("space", 60); UI("top", 51); printf("\n");
        printf("         _._._                       _._._                  ");   printf("%c BANK POLICIES                                   %c\n", 186, 186);    
        printf("        _|   |_                     _|   |_                 ");   printf("%c Savings earn 10%% every day.                     %c\n", 186, 186);
        printf("        | ... |_._._._._._._._._._._| ... |                 ");   printf("%c Loan interest is 5%% every day.                  %c\n", 186, 186);
        printf("        | ||| |  o   IRON BANK   o  | ||| |                 ");   UI("middle", 51); printf("\n");
        printf("        | \"\"\" |  \"\"\"    \"\"\"    \"\"\"  | \"\"\" |  ");   printf("               %c Current savings account capacity:  %8.2f GD  %c\n", 186, fAccount, 186);
        printf("   ())  |[-|-]| [-|-]  [-|-]  [-|-] |[-|-]|  ())            ");   printf("%c Current loanable amount every day: %8.2f GD  %c\n", 186, fLoanable, 186);
        printf("  (())) |     |---------------------|     | (()))           ");   UI("middle", 51); printf("\n");
        printf(" (())())| \"\"\" |  \"\"\"  BRAAVOS  \"\"\"  | \"\"\" |(())())"); printf("          %c You can only loan once a day.                   %c\n ", 186, 186);
        printf("(()))()|[-|-]|  :::   .-\"-.   :::  |[-|-]|(()))()          ");   UI("middle2", 51); printf("\n");
        printf(" ()))(()|     | |~|~|  |_|_|  |~|~| |     |()))(()          ");   printf("%c Golden Dragons (GD): %-27.2f%c\n", 186, *fGD, 186);
        printf("    ||  |_____|_|_|_|__|_|_|__|_|_|_|_____|  ||             ");   printf("%c Savings:             %-27.2f%c\n", 186, *fSavings, 186);
        printf(" ~ ~^^ @@@@@@@@@@@@@@/=======\\@@@@@@@@@@@@@@ ^^~ ~          ");  printf("%c Debt:                %-27.2f%c\n", 186, *fDebt, 186);
        printf("      ^~^~          /         \\           ~^~^              ");  UI("middle2", 51); printf("\n");
        printf("          ^~^~     /           \\      ~^~^                  ");  printf("%c [D]eposit    [W]ithdraw    [L]oan    [P]ay Loan %c\n", 186, 186);
        printf("^~^~              /             \\                 ~^~^      ");  printf("%c [B]ack       [Q]uit                             %c\n", 186, 186);
        printf(":::::::::::::::::::::::::::::::::::::::::::::::::::::::     ");   UI("bottom", 51); printf("\n");
        UI("space", 62); printf("Choose your action: "); cAction = getch();
        
        switch (cAction)
        {
        case 'd':
        case 'D':
            printf("Deposit");
            if(*fGD == 0 && *fSavings >= fAccount)
            {
                
                printf("\n");
                UI("space", 62);
                printf("You do not have any GD in your hands\n");
                UI("space", 62);
                printf("and not enough saving capacity, my Lord.");
                delay(2);
            }
            else if (*fGD == 0)
            {
                printf("\n");
                UI("space", 62);
                printf("You do not have any GD in your hands, my Lord.");
                delay(1);
            }
            else if(*fSavings >= fAccount)
            {
                printf("\n");
                UI("space", 62);
                printf("You do not have enough saving capacity, my Lord.");
                delay(1);
            }
            else
            {
                delay(1);
                Deposit(fGD, fSavings, fAccount, cDayAction);
                if(*cDayAction == 'q')
                {
                    nLoop = 0;
                }
            }            
            break;
        case 'w':
        case 'W':
            printf("Withdraw");
            if(*fSavings == 0)
            {
                printf("\n");
                UI("space", 62);
                printf("You do not have any GD in your savings, my Lord.");
            }
            else 
            {
                delay(1);
                Withdraw(fGD, fSavings, cDayAction);
                if(*cDayAction == 'q')
                {
                    nLoop = 0;
                }
            }  
            delay(1);
            break;
        case 'l':
        case 'L':
            printf("Loan");
            if(*nLoanMark)
            {
                printf("\n");
                UI("space", 62);
                printf("You already loaned for the day, my Lord.");
            }
            else
            {
                delay(1);
                Loan(fGD, fDebt, fLoanable, nLoanMark, cDayAction);
                if(*cDayAction == 'q')
                {
                    nLoop = 0;
                }
            }
            delay(1);
            break;
        case 'p':
        case 'P':
            printf("Pay Loan");
            if(*fDebt == 0.0)
            {
                printf("\n");
                UI("space", 62);
                printf("You don't have any debts, my Lord.");
            }
            else
            {
                delay(1);
                PayLoan(fGD, fDebt, cDayAction);
                if(*cDayAction == 'q')
                {
                    nLoop = 0;
                }
            }
            delay(1);
            break;
        case 'b':
        case 'B':
            printf("Back\n");
            UI("space", 62);
            printf("Please come back again, my Lord.");
            delay(1);
            nLoop = 0;
            break;
        case 'q':
        case 'Q':
            nLoop = 0;
            *cDayAction = 'q';
            break;
        default:
            invalidinput();
            break;
        }
        system("cls");
    } while (nLoop);
}

void Deposit (float *fGD, float *fSavings, float fAccount, char *cDayAction)
{
    int nLoop = 1;
    float fDeposit = 0,
          f10s[] = {0.01, 0.05, 
                    0.1,  0.5, 
                    1.0,  5.0, 
                    10.0, 50.0,
                    100.0, 500.0};
    char cDep = '*';
    system("cls");
    do
    {
        UI("space", 5); UI("top", 36); printf("\n");
        UI("space", 5); printf("%c             DEPOSIT              %c", 186, 186);     printf("     _....._                     \n"); 
        UI("space", 5); printf("%c     Welcome to the IronBank!     %c", 186, 186);     printf("    ';-.--';'                    "); UI("top", 40); printf("\n");
        UI("space", 5); printf("%c     You  may  deposit  your      %c", 186, 186);     printf("     }===={       _.---.._       ");  UI("middle", 40); printf("\n");                                                 
        UI("space", 5); printf("%c     Golden Dragons  here  my     %c", 186, 186);     printf("   .'  __  '.    ';-..--';       ");  printf("%c  Remaining Capacity:  %-15.2f%c\n", 186, fAccount - *fSavings, 186);
        UI("space", 5); printf("%c     Lord!                        %c", 186, 186);     printf("  /:: /  _`  \\    `}===={        "); UI("middle", 40); printf("\n");
        UI("space", 5); UI("middle2", 36);                                              printf(" |::  \\___/   |  .:  ___ '.      "); printf("%c  Golden Dragons (GD): %-15.2f%c\n", 186, *fGD, 186);
        UI("space", 5); printf("%c  [0] Add    0.01 [1] Add   0.05  %c", 186, 186);     printf(" \\::.         /_;:_ /  _`  \\     ");printf("%c  Amount to deposit:   %-15.2f%c\n", 186, fDeposit, 186);
        UI("space", 5); printf("%c  [2] Add    0.10 [3] Add   0.50  %c", 186, 186);     printf("  '::_     _-;'--.-';___/   |    ");  UI("middle", 40); printf("\n");
        UI("space", 5); printf("%c  [4] Add    1.00 [5] Add   5.00  %c", 186, 186);     printf("      `````  }====={        /    ");  printf("%c  Savings:             %-15.2f%c\n", 186, *fSavings, 186);
        UI("space", 5); printf("%c  [6] Add   10.00 [7] Add  50.00  %c", 186, 186);     printf("           .'  ___  '.   _.'     ");  UI("middle", 40); printf("\n");
        UI("space", 5); printf("%c  [8] Add  100.00 [9] Add 500.00  %c", 186, 186);     printf("          /:: /  _`   \\``        "); UI("bottom", 40); printf("\n");
        UI("space", 5); printf("%c  [+] Add 1000.00 [-] Erase       %c", 186, 186);     printf("         |::  \\___/    |         \n"); 
        UI("space", 5); printf("%c  [M]ax Amount    [D]eposit       %c", 186, 186);     printf("         \\::.          /         \n"); 
        UI("space", 5); printf("%c  [B]ack          [Q]uit          %c", 186, 186);     printf("          '::_      _.'          \n"); 
        UI("space", 5); UI("bottom", 36);                                               printf("              ``````             \n"); 
        UI("space", 5);
        printf("Enter amount to deposit: "); 
        cDep = getch();
        switch(cDep)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if(f10s[cDep - '0'] <= *fGD && fDeposit + f10s[cDep - '0'] <= fAccount)
            {                
                fDeposit += f10s[cDep - '0'];
                *fGD -= f10s[cDep - '0'];
                *fSavings += f10s[cDep - '0'];
            }
            else if (f10s[cDep - '0'] > *fGD)
            {
                printf("\n");
                UI("space", 5);
                printf("You do not have enough GD, my Lord.");
                delay(1);
            }
            else if (fDeposit + f10s[cDep - '0'] > fAccount)
            {
                printf("\n");
                UI("space", 5);
                printf("You savings capacity is full, my Lord.");
                delay(1);
            }
            break;
        case '+':
            if(1000.0 <= *fGD && fDeposit + 1000.0 <= fAccount)
            {                
                fDeposit += 1000.0;
                *fGD -= 1000.0;
                *fSavings += 1000.0;
            }
            else if (fDeposit + 1000.0 > *fGD)
            {
                printf("\n");
                UI("space", 5);
                printf("You do not have enough GD, my Lord.");
                delay(1);
            }
            else if (fDeposit + 1000.0 > fAccount)
            {
                printf("\n");
                UI("space", 5);
                printf("You don't have enough savings capacity, my Lord.");
                delay(1);
            }
            break;
        case '-':
            if(fDeposit != 0.0)
            {
                printf("Erase");
                *fGD += fDeposit;
                *fSavings -= fDeposit;
                fDeposit = 0.0;
                delay(1);
            }
            else 
            {
                printf("\n");
                UI("space", 5);
                printf("You don't have any deposit yet, my Lord.");
                delay(1);
            }
            break;
        case 'm':
        case 'M':
            if(*fGD != 0.0 && *fSavings < fAccount)
            {
                *fGD += fDeposit;
                *fSavings -= fDeposit;
                fDeposit = 0.0;

                if (*fGD <= fAccount && *fSavings <= fAccount)
                {
                    printf("%.2f GD", *fGD);
                    fDeposit = *fGD;
                    *fSavings += *fGD;
                    *fGD = 0.0;
                }
                else if (*fGD > fAccount)
                {
                    printf("%.2f GD", fAccount);
                    fDeposit = fAccount;
                    *fGD -= fAccount;
                    *fSavings += fAccount;
                }
            }
            else if (*fGD == 0.0)
            {
                printf("\n");
                UI("space", 5);
                printf("You don't have any GD left, my Lord.");
            }
            else if (*fSavings > fAccount)
            {
                printf("\n");
                UI("space", 5);
                printf("You don't have enough savings capacity, my Lord.");
            }
            delay(1);
            break;
        case 'B':
        case 'b':
            printf("Back");
            delay(1);
            nLoop = 0;
            break;
        case 'd':
        case 'D':
            if(fDeposit > 0)
            {
                printf("Deposit\n"); UI("space", 5);
                printf("You successfully deposited %.2f GD", fDeposit);
                delay(1);
                nLoop = 0;
            }
            else 
            {
                printf("Deposit\n"); UI("space", 5);
                printf("Deposit any amount first, my Lord.");
                delay(1);
            }
            break;
        case 'q':
        case 'Q':
            printf("Quit");
            nLoop = 0;
            *cDayAction = 'q';
            if(fDeposit > 0.0)
            {
                do
                {
                    printf("\n     Do you want to deposit %.2f GD before you quit?", fDeposit);
                    printf("\n     [C]ancel  or  [D]eposit: "); 
                    cDep = getch();                
                    switch (cDep)
                    {
                    case 'C':
                    case 'c':
                        *fGD += fDeposit;
                        *fSavings -= fDeposit;
                        fDeposit = 0.0;
                        nLoop = 0;
                        break;
                    case 'D':
                    case 'd':
                        printf("\n    You successfully deposited %.2f GD", fDeposit);
                        nLoop = 0;
                        break;
                    default:
                        invalidinput();
                        nLoop = 1;
                        break;
                    }
                } while (nLoop);
            }
            delay(1);
            break;
        default:
            printf("\n");
            UI("space", 5);
            invalidinput();
            break;
        }
        system("cls");
    } while (nLoop);
}

void Withdraw (float *fGD, float *fSavings, char *cDayAction)
{
    int nLoop = 1;
    float fWithdraw = 0,
          f10s[] = {0.01, 0.05, 
                    0.1,  0.5, 
                    1.0,  5.0, 
                    10.0, 50.0,
                    100.0, 500.0};
    char cDep = '*';
    system("cls");
    do
    {
        UI("space", 5); UI("top", 36); printf("\n");
        UI("space", 5); printf("%c             WITHDRAW             %c", 186, 186);     printf("     _....._                     \n"); 
        UI("space", 5); printf("%c     Welcome to the IronBank!     %c", 186, 186);     printf("    ';-.--';'                    \n"); 
        UI("space", 5); printf("%c     You  may  withdraw  your     %c", 186, 186);     printf("     }===={       _.---.._       ");  UI("top", 40); printf("\n");                                                   
        UI("space", 5); printf("%c     saved   Golden   Dragons     %c", 186, 186);     printf("   .'  __  '.    ';-..--';       ");  UI("middle", 40); printf("\n");
        UI("space", 5); printf("%c     here my Lord!                %c", 186, 186);     printf("  /:: /  _`  \\    `}===={        "); printf("%c  Savings:             %-15.2f%c\n", 186, *fSavings, 186);
        UI("space", 5); UI("middle2", 36);                                              printf(" |::  \\___/   |  .:  ___ '.      "); printf("%c  Amount to withdraw:  %-15.2f%c\n", 186, fWithdraw, 186);
        UI("space", 5); printf("%c  [0] Add    0.01 [1] Add   0.05  %c", 186, 186);     printf(" \\::.         /_;:_ /  _`  \\     ");UI("middle", 40); printf("\n");
        UI("space", 5); printf("%c  [2] Add    0.10 [3] Add   0.50  %c", 186, 186);     printf("  '::_     _-;'--.-';___/   |    ");  printf("%c  Golden Dragons (GD): %-15.2f%c\n", 186, *fGD, 186);
        UI("space", 5); printf("%c  [4] Add    1.00 [5] Add   5.00  %c", 186, 186);     printf("      `````  }====={        /    ");  UI("middle", 40); printf("\n");
        UI("space", 5); printf("%c  [6] Add   10.00 [7] Add  50.00  %c", 186, 186);     printf("           .'  ___  '.   _.'     ");  UI("bottom", 40); printf("\n");
        UI("space", 5); printf("%c  [8] Add  100.00 [9] Add 500.00  %c", 186, 186);     printf("          /:: /  _`   \\``        \n"); 
        UI("space", 5); printf("%c  [+] Add 1000.00 [-] Erase       %c", 186, 186);     printf("         |::  \\___/    |         \n"); 
        UI("space", 5); printf("%c  [M]ax Amount    [W]ithdraw      %c", 186, 186);     printf("         \\::.          /         \n"); 
        UI("space", 5); printf("%c  [B]ack          [Q]uit          %c", 186, 186);     printf("          '::_      _.'          \n"); 
        UI("space", 5); UI("bottom", 36);                                               printf("              ``````             \n"); 
        UI("space", 5);
        printf("Enter amount to withdraw: "); 
        cDep = getch();
        switch(cDep)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if(f10s[cDep - '0'] <= *fSavings)
            {                
                fWithdraw += f10s[cDep - '0'];
                *fGD += f10s[cDep - '0'];
                *fSavings -= f10s[cDep - '0'];
            }
            else
            {
                printf("\n");
                UI("space", 5);
                printf("You do not have enough savings, my Lord.");
                delay(1);
            }
            break;
        case '+':
            if(1000.0 <= *fSavings)
            {                
                fWithdraw += 1000.0;
                *fGD += 1000.0;
                *fSavings -= 1000.0;
            }
            else 
            {
                printf("\n");
                UI("space", 5);
                printf("You do not have enough savings, my Lord.");
                delay(1);
            }
            break;
        case '-':
            if(fWithdraw != 0.0)
            {
                printf("Erase");
                *fGD -= fWithdraw;
                *fSavings += fWithdraw;
                fWithdraw = 0.0;
            }
            else 
            {
                printf("\n");
                UI("space", 5);
                printf("You don't have any withdrawals yet, my Lord.");
            }
            delay(1);
            break;
        case 'm':
        case 'M':
            if(*fSavings > 0)
            {
                *fGD -= fWithdraw;
                *fSavings += fWithdraw;
                fWithdraw = 0.0;

                printf("%.2f", *fSavings);
                fWithdraw = *fSavings;
                *fGD += *fSavings;
                *fSavings = 0;
            }
            else
            {
                printf("\n");
                UI("space", 5);
                printf("You don't have any savings left, my Lord.");
            }
            delay(1);
            break;
        case 'B':
        case 'b':
            printf("Back");
            delay(1);
            nLoop = 0;
            break;
        case 'W':
        case 'w':
            printf("Withdraw\n"); 
            if(fWithdraw > 0)
            {
                UI("space", 5);
                printf("You successfully withdraw %.2f GD.", fWithdraw);
                nLoop = 0;
            }
            else
            {
                printf("Withdraw\n"); UI("space", 5);
                printf("Withdraw any amount first, my Lord.");
            }
            delay(1);
            break;
        case 'q':
        case 'Q':
            printf("Quit");
            nLoop = 0;
            *cDayAction = 'q';
            if (fWithdraw > 0.0)
            {
                do
                {
                    printf("\n     Do you want to withdraw %.2f GD before you quit?", fWithdraw);
                    printf("\n     [C]ancel  or  [W]ithdraw: ");
                    cDep = getch();
                    switch (cDep)
                    {
                    case 'C':
                    case 'c':
                        *fGD -= fWithdraw;
                        *fSavings += fWithdraw;
                        fWithdraw = 0.0;
                        nLoop = 0;
                        break;
                    case 'W':
                    case 'w':
                        printf("\n    You successfully withdraw %.2f GD.", fWithdraw);
                        nLoop = 0;
                        break;
                    default:
                        invalidinput();
                        nLoop = 1;
                        break;
                    }
                } while (nLoop);
            }
            delay(1);
            break;
        default:
            printf("\n");
            UI("space", 5);
            invalidinput();
            break;
        }
        system("cls");
    } while (nLoop);
}

void Loan (float *fGD, float *fDebt, float fLoanable, int *nLoanMark, char *cDayAction)
{
    int nLoop = 1;
    float fLoan = 0,
          f10s[] = {0.01, 0.05, 
                    0.1,  0.5, 
                    1.0,  5.0, 
                    10.0, 50.0,
                    100.0, 500.0};
    char cDep = '*';
    system("cls");
    do
    {
        UI("space", 5); UI("top", 36); printf("\n");
        UI("space", 5); printf("%c                LOAN              %c", 186, 186);     printf("     _....._                     \n"); 
        UI("space", 5); printf("%c     Welcome to the IronBank!     %c", 186, 186);     printf("    ';-.--';'                    \n"); 
        UI("space", 5); printf("%c     You   may  loan   Golden     %c", 186, 186);     printf("     }===={       _.---.._       ");  UI("top", 40); printf("\n");                                                   
        UI("space", 5); printf("%c     Dragons here my Lord  to     %c", 186, 186);     printf("   .'  __  '.    ';-..--';       ");  UI("middle", 40); printf("\n");
        UI("space", 5); printf("%c     boost trading power.         %c", 186, 186);     printf("  /:: /  _`  \\    `}===={        "); printf("%c  Loanable Amount:     %-15.2f%c\n", 186, fLoanable - fLoan, 186);
        UI("space", 5); UI("middle2", 36);                                              printf(" |::  \\___/   |  .:  ___ '.      "); printf("%c  Total Debt:          %-15.2f%c\n", 186, *fDebt, 186);
        UI("space", 5); printf("%c  [0] Add    0.01 [1] Add   0.05  %c", 186, 186);     printf(" \\::.         /_;:_ /  _`  \\     ");UI("middle", 40); printf("\n");
        UI("space", 5); printf("%c  [2] Add    0.10 [3] Add   0.50  %c", 186, 186);     printf("  '::_     _-;'--.-';___/   |    ");  printf("%c  Golden Dragons (GD): %-15.2f%c\n", 186, *fGD, 186);
        UI("space", 5); printf("%c  [4] Add    1.00 [5] Add   5.00  %c", 186, 186);     printf("      `````  }====={        /    ");  UI("middle", 40); printf("\n");
        UI("space", 5); printf("%c  [6] Add   10.00 [7] Add  50.00  %c", 186, 186);     printf("           .'  ___  '.   _.'     ");  UI("bottom", 40); printf("\n");
        UI("space", 5); printf("%c  [8] Add  100.00 [9] Add 500.00  %c", 186, 186);     printf("          /:: /  _`   \\``        \n"); 
        UI("space", 5); printf("%c  [+] Add 1000.00 [-] Erase       %c", 186, 186);     printf("         |::  \\___/    |         \n"); 
        UI("space", 5); printf("%c  [M]ax Amount    [L]oan          %c", 186, 186);     printf("         \\::.          /         \n"); 
        UI("space", 5); printf("%c  [B]ack          [Q]uit          %c", 186, 186);     printf("          '::_      _.'          \n"); 
        UI("space", 5); UI("bottom", 36);                                               printf("              ``````             \n"); 
        UI("space", 5);
        printf("Enter amount to loan: "); 
        cDep = getch();
        switch(cDep)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if(f10s[cDep - '0'] <= fLoanable - fLoan)
            {                
                fLoan += f10s[cDep - '0'];
                *fGD += f10s[cDep - '0'];
                *fDebt += f10s[cDep - '0'];
            }
            else
            {
                printf("\n");
                UI("space", 5);
                printf("You cannot loan beyond %.2f GD, my Lord.", fLoanable);
                delay(1);
            }
            break;
        case '+':
            if(1000.0 <= fLoanable - fLoan)
            {                
                fLoan += 1000.0;
                *fGD += 1000.0;
                *fDebt += 1000.0;
            }
            else 
            {
                printf("\n");
                UI("space", 5);
                printf("You cannot loan beyond %.2f GD, my Lord.", fLoanable);
                delay(1);
            }
            break;
        case '-':
            if(fLoan != 0.0)
            {
                printf("Erase");
                *fGD -= fLoan;
                *fDebt -= fLoan;
                fLoan = 0.0;
            }
            else 
            {
                printf("\n");
                UI("space", 5);
                printf("You don't have any loans yet, my Lord.");
            }
            delay(1);
            break;
        case 'm':
        case 'M':
            if(fLoan != fLoanable)
            {
                *fGD -= fLoan;
                *fDebt -= fLoan;
                fLoan = 0.0;

                printf("%.2f", fLoanable);
                fLoan += fLoanable;
                *fGD += fLoanable;
                *fDebt += fLoanable;
            }
            else 
            {
                printf("\n");
                UI("space", 5);
                printf("You already reached the maximum, my Lord.");
            }
            delay(1);
            break;
        case 'B':
        case 'b':
            printf("Back");
            delay(1);
            nLoop = 0;
            break;
        case 'L':
        case 'l':
            printf("Loan\n");
            if(fLoan > 0)
            {
                UI("space", 5);
                printf("You successfully loaned %.2f GD.", fLoan);  
                *nLoanMark = 1;      
                nLoop = 0;
            }
            else
            {
                UI("space", 5);
                printf("Loan any amount first, my Lord.");
            }
            delay(1);
            break;
        case 'q':
        case 'Q':
            printf("Quit");
            nLoop = 0;
            *cDayAction = 'q';
            if (fLoan > 0.0)
            {
                do
                {
                    printf("\n     Do you want to loan %.2f GD before you quit?", fLoan);
                    printf("\n     [C]ancel  or  [L]oan: ");
                    cDep = getch();
                    switch (cDep)
                    {
                    case 'C':
                    case 'c':
                        *fGD -= fLoan;
                        *fDebt -= fLoan;
                        fLoan = 0.0;
                        nLoop = 0;
                        break;
                    case 'L':
                    case 'l':
                        printf("\n    You successfully loaned %.2f GD.", fLoan);
                        *nLoanMark = 1;
                        nLoop = 0;
                        break;
                    default:
                        invalidinput();
                        nLoop = 1;
                        break;
                    }
                } while (nLoop);
            }
            delay(1);
            break;
        default:
            printf("\n");
            UI("space", 5);
            invalidinput();
            break;
        }
        system("cls");
    } while (nLoop);
}

void PayLoan (float *fGD, float *fDebt, char *cDayAction)
{
    int nLoop = 1;
    float fPay = 0,
          f10s[] = {0.01, 0.05, 
                    0.1,  0.5, 
                    1.0,  5.0, 
                    10.0, 50.0,
                    100.0, 500.0};
    char cDep = '*';
    system("cls");
    do
    {
        UI("space", 5); UI("top", 36); printf("\n");
        UI("space", 5); printf("%c             PAY LOAN             %c", 186, 186);     printf("     _....._                     \n"); 
        UI("space", 5); printf("%c     Welcome to the IronBank!     %c", 186, 186);     printf("    ';-.--';'                    \n"); 
        UI("space", 5); printf("%c     You  may pay  your loans     %c", 186, 186);     printf("     }===={       _.---.._       ");  UI("top", 40); printf("\n");                                                   
        UI("space", 5); printf("%c     here  my  Lord  to avoid     %c", 186, 186);     printf("   .'  __  '.    ';-..--';       ");  UI("middle", 40); printf("\n");
        UI("space", 5); printf("%c     any coonflicts.              %c", 186, 186);     printf("  /:: /  _`  \\    `}===={        "); printf("%c  Golden Dragons (GD): %-15.2f%c\n", 186, *fGD, 186);
        UI("space", 5); UI("middle2", 36);                                              printf(" |::  \\___/   |  .:  ___ '.      "); printf("%c  To Pay:              %-15.2f%c\n", 186, fPay, 186);
        UI("space", 5); printf("%c  [0] Add    0.01 [1] Add   0.05  %c", 186, 186);     printf(" \\::.         /_;:_ /  _`  \\     ");UI("middle", 40); printf("\n");
        UI("space", 5); printf("%c  [2] Add    0.10 [3] Add   0.50  %c", 186, 186);     printf("  '::_     _-;'--.-';___/   |    ");  printf("%c  Total Debt:          %-15.2f%c\n", 186, *fDebt, 186);
        UI("space", 5); printf("%c  [4] Add    1.00 [5] Add   5.00  %c", 186, 186);     printf("      `````  }====={        /    ");  UI("middle", 40); printf("\n");
        UI("space", 5); printf("%c  [6] Add   10.00 [7] Add  50.00  %c", 186, 186);     printf("           .'  ___  '.   _.'     ");  UI("bottom", 40); printf("\n");
        UI("space", 5); printf("%c  [8] Add  100.00 [9] Add 500.00  %c", 186, 186);     printf("          /:: /  _`   \\``        \n"); 
        UI("space", 5); printf("%c  [+] Add 1000.00 [-] Erase       %c", 186, 186);     printf("         |::  \\___/    |         \n"); 
        UI("space", 5); printf("%c  [M]ax Amount    [L]oan          %c", 186, 186);     printf("         \\::.          /         \n"); 
        UI("space", 5); printf("%c  [B]ack          [Q]uit          %c", 186, 186);     printf("          '::_      _.'          \n"); 
        UI("space", 5); UI("bottom", 36);                                               printf("              ``````             \n"); 
        UI("space", 5);
        printf("Enter amount to loan: "); 
        cDep = getch();
        switch(cDep)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if(f10s[cDep - '0'] <= *fDebt)
            {                
                fPay += f10s[cDep - '0'];
                *fGD -= f10s[cDep - '0'];
                *fDebt -= f10s[cDep - '0'];
            }
            else
            {
                printf("\n");
                UI("space", 5);
                printf("You pay only your debt, my Lord.");
                delay(1);
            }
            break;
        case '+':
            if(1000.0 <= *fDebt)
            {                
                fPay += 1000.0;
                *fGD -= 1000.0;
                *fDebt -= 1000.0;
            }
            else 
            {
                printf("\n");
                UI("space", 5);
                printf("You pay only your debt, my Lord.");
                delay(1);
            }
            break;
        case '-':
            if(fPay != 0.0)
            {
                printf("Erase");
                *fGD += fPay;
                *fDebt += fPay;
                fPay = 0.0;
            }
            else 
            {
                printf("\n");
                UI("space", 5);
                printf("You have to pay first, my Lord.");
            }
            delay(1);
            break;
        case 'm':
        case 'M':
            if(*fGD != 0 && fPay < *fDebt)
            {
                *fGD -= fPay;
                *fDebt -= fPay;
                fPay = 0.0;

                if (*fGD <= *fDebt)
                {
                    printf("%.2f GD", *fGD);
                    fPay += *fGD;
                    *fDebt -= *fGD;
                    *fGD = 0.0;
                    delay(1);
                }
                else if (*fGD > *fDebt)
                {
                    printf("%.2f GD", *fDebt);
                    fPay += *fDebt;
                    *fGD -= *fDebt;
                    *fDebt = 0.0;
                    delay(1);
                }
            }
            else if (*fGD == 0.0)
            {
                printf("\n");
                UI("space", 5);
                printf("You don't have any GD left, my Lord.");
                delay(1);
            }
            else if (fPay >= *fDebt)
            {
                printf("\n");
                UI("space", 5);
                printf("You may now pay your debt, my Lord.");
                delay(1);
            }
            
            break;
        case 'B':
        case 'b':
            printf("Back");
            delay(1);
            nLoop = 0;
            break;
        case 'P':
        case 'p':
            printf("Loan\n");
            if(fPay > 0.0)
            {
                UI("space", 5);
                printf("You successfully paid %.2f GD.", fPay);    
                nLoop = 0;
            }
            else
            {
                UI("space", 5);
                printf("Pay any amount first, my Lord.");
            }
            delay(1);
            break;
        case 'q':
        case 'Q':
            printf("Quit");
            nLoop = 0;
            *cDayAction = 'q';
            if (fPay > 0.0)
            {
                do
                {
                    printf("\n     Do you want to pay %.2f GD before you quit?", fPay);
                    printf("\n     [C]ancel  or  [L]oan: ");
                    cDep = getch();
                    switch (cDep)
                    {
                    case 'C':
                    case 'c':
                        *fGD += fPay;
                        *fDebt += fPay;
                        fPay = 0.0;
                        nLoop = 0;
                        break;
                    case 'L':
                    case 'l':
                        printf("\n    You successfully paid %.2f GD.", fPay);
                        nLoop = 0;
                        break;
                    default:
                        invalidinput();
                        nLoop = 1;
                        break;
                    }
                } while (nLoop);
            }
            delay(1);
            break;
        default:
            printf("\n");
            UI("space", 5);
            invalidinput();
            break;
        }
        system("cls");
    } while (nLoop);
}

void WheelHouse ()
{
    int i;
    printf("\n\n\n                          ... counting Golden Dragons ...                     \n\n\n");
    printf("                             ... checking inventory ...                       \n\n\n");
    printf("                                 ... sleeping ...                             \n\n\n");
    printf("                               ... end of the day ...                             \n\n\n                                      ");
    for (i = 0; i < 3; i++)
    {
        printf(".");
        delay(1);
    }
    printf("\n\n     o  _ o _|_ o ._   _     _. ._   _ _|_ |_   _  ._   ._   _. ._ _|_ ._   _  ._ \n");
    printf("  \\/ | _> |  |_ | | | (_|   (_| | | (_) |_ | | (/_ |    |_) (_| |   |_ | | (/_ |  \n");
    printf("                       _|                               |                         \n\n\n                                      ");
    for (i = 0; i < 3; i++)
    {
        printf(".");
        delay(1);
    }
    system("cls");
}

void Merchant (float *fGD, int *nTCap, float *fAccount, float *fLoanable, int nIntry[], int *nChestMark, int *nStored)
{
    int n = rand() % 10,
        i, nLoop = 0;
    char cChoice = '*';
    if (0 == 0 && *fGD > 900){
        do
        {
            printf("\n\n\n                     ___\n");
            printf("         .||,       /_ _\\\\           \n");                      
            printf("        \\.`',/      |'L'| |          \n");                             
            printf("        = ,. =      | -,| L          ");     printf("      "); UI("top", 74); printf("\n");        
            printf("        / || \\    ,-'\\\"/,'`.         ");  printf("      %c                                MERCHANT                                %c\n", 186, 186);                     
            printf("          ||     ,'   `,,. `.        ");     printf("      "); UI("middle2", 74); printf("\n");                                   
            printf("          ,|____,' , ,;' \\| |        ");    printf("      "); UI("middle", 74); printf("\n");                               
            printf("         (3|\\    _/|/'   _| |        ");    printf("      %c  Good Day my Lord!!! I am the MERCHANT and I am offering you my power  %c\n", 186, 186);                                 
            printf("          ||/,-''  | >-'' _,\\\\       ");   printf("      %c  to  increase your  wheelhouse storage by 50 units or tamper the bank  %c\n", 186, 186);                                 
            printf("          ||'      ==\\ ,-'  ,'       ");    printf("      %c  to increase your savings account capacity and loanable amount  every  %c\n", 186, 186);                                 
            printf("          ||       |  V \\ ,|         ");    printf("      %c  day. However, this will cost you GDs to pay.                          %c\n", 186, 186);                                      
            printf("          ||       |    |` |         ");     printf("      "); UI("middle", 74); printf("\n");                         
            printf("          ||       |    |   \\        ");    printf("      "); UI("bottom", 74); printf("\n");                         
            printf("          ||       |    \\    \\       \n");                                
            printf("          ||       |     |    \\      \n");                              
            printf("          ||       |      \\_,-'      \n");                            
            printf("          ||       |___,,--\")_\\      \n");                               
            printf("          ||         |_|   ccc/      \n");                              
            printf("          ||        ccc/             ");   
            printf("                          Press anything to continue "); 
            if (cChoice == '*') 
                getch();
            printf("\n"); 
            UI("space", 52); UI("top", 54); printf("\n");
            UI("space", 52); printf("%c                       MERCHANT                     %c\n", 186, 186);
            UI("space", 52);
            for (i = 0; i < 54; i++) //specific UI
            {
                switch (i)
                {
                case 0:
                    printf("%c", 204);
                    break;
                case 39:
                    printf("%c", 203);
                    break;
                case 53:
                    printf("%c\n", 185);
                    break;
                default:
                    printf("%c", 205);
                    break;
                }
            }
            UI("space", 52); printf("%c  POWERUP                             %c  COST       %c\n", 186, 186, 186); 
            UI("space", 52); printf("%c  [1]  Increase wheelhouse storage    %c  200.00 GD  %c\n", 186, 186, 186); 
            UI("space", 52); printf("%c  [2]  Increase savings capacity      %c  900.00 GD  %c\n", 186, 186, 186); 
            UI("space", 52); printf("%c  [3]  Increase loanable amount       %c  500.00 GD  %c\n", 186, 186, 186); 
            UI("space", 52);
            for (i = 0; i < 54; i++) //specific UI
            {
                switch (i)
                {
                case 0:
                    printf("%c", 204);
                    break;
                case 39:
                    printf("%c", 202);
                    break;
                case 53:
                    printf("%c\n", 185);
                    break;
                default:
                    printf("%c", 205);
                    break;
                }
            }
            UI("space", 52); printf("%c  [C]ancel                               [M]ystery  %c\n", 186, 186); 
            UI("space", 52); UI("bottom", 54); printf("\n");
            UI("space", 52); printf("   Choose a powerup: "); 
            cChoice = getch();
            switch (cChoice)
            {
            case '1':
                *fGD -= 200.0; 
                *nTCap += 50;
                nLoop = 0;
                break;
            case '2':
                *fGD -= 900.0;
                *fAccount *= 2.0;
                nLoop = 0;
                break;
            case '3':
                *fGD -= 500.0;
                *fLoanable *= 2.0;
                nLoop = 0;
                break;
            case 'm':
            case 'M':
                if(*nChestMark == 0)
                    TreasureChest(fGD, nIntry, nChestMark, nStored);
                else if (*nChestMark == 1)
                    printf("You already unlocked the chest my Lord.");
                if (*nStored > *nTCap)
                {
                    *nTCap += *nStored - *nTCap;
                }
                delay(1);
                nLoop = 1;
                break;
            case 'c':
            case 'C':
                printf("Until next time my Lord.");
                delay(1);
                nLoop = 0;
                break;
            default:
                invalidinput();
                cChoice = 0;
                nLoop = 1;
                break;
            }
            system("cls");
        } while (nLoop);
    }
    system("cls");
}

void TreasureChest (float *fGD, int nIntry[], int *nChestMark, int *nStored)
{
    char cChoice = '*',
         cAnswer[7],
         cToGuess[7] = "DRAGON";
    int i, nLoop = 0;
    do
    {
        system("cls");
        printf("*******************************************************************************  \n");
        printf("         |                   |                  |                     |          \n");
        printf("_________|________________.=\"\"_;=.______________|_____________________|_______   ");       UI("top", 52); printf("\n");
        printf("|                   |  ,-\"_,=\"\"     `\"=.|                  |                     ");     printf("%c You found a chest my Lord! However, you  cannot  %c\n",186,186);
        printf("|___________________|__\"=._o`\"-._        `\"=.______________|___________________  ");      printf("%c open it because it has a specific key  and only  %c\n",186,186);
        printf("         |                `\"=._o`\"=._      _`\"=._                     |          ");      printf("%c those  who  explored the  cities can unlock it.  %c\n",186,186);
        printf("_________|_____________________:=._o \"=._.\"_.-=\"'\"=.__________________|_______   ");     printf("%c You can only  found this  treasure chest  after  %c\n",186,186);
        printf("|                   |    __.--\" , ; `\"=._o.\" ,-\"\"\"-._ \".   |                     ");  printf("%c you met the merchant. Try to explore  different  %c\n",186,186);
        printf("|___________________|_._\"  ,. .` ` `` ,  `\"-._\"-._   \". '__|___________________  ");     printf("%c places and look for the key. If  you  know  the  %c\n",186,186);
        printf("         |           |o`\"=._` , \"` `; .\". ,  \"-._\"-._; ;              |          ");    printf("%c key now, you can unlock  the  chest, otherwise,  %c\n",186,186);
        printf("_________|___________| ;`-.o`\"=._; .\" ` '`.\"\\` . \"-._ /_______________|_______   ");    printf("%c return for another chance.                       %c\n",186,186);
        printf("|                   | |o;    `\"-.o`\"=._``  '` \" ,__.--o;   |                     ");      UI("middle2", 52); printf("\n");
        printf("|___________________|_| ;     (#) `-.o `\"=.`_.--\"_o.-; ;___|___________________  ");       printf("%c         [B]ack                 [U]nlock          %c\n",186,186);
        printf("____/______/______/___|o;._    \"      `\".o|o_.--\"    ;o;____/______/______/____  ");      UI("bottom", 52); printf("\n");
        printf("/______/______/______/_\"=._o--._        ; | ;        ; ;/______/______/______/_\n");
        printf("____/______/______/______/__\"=._o--._   ;o|o;     _._;o;____/______/______/____\n");
        printf("/______/______/______/______/____\"=._o._; | ;_.--\"o.--\"_/______/______/______/_\n");
        printf("____/______/______/______/______/_____\"=.o|o_.--\"\"___/______/______/______/____\n");
        printf("/______/______/______/______/______/______/______/______/______/______/______/_\n");
        printf("*******************************************************************************");         
        printf("           Choose your action: "); 
        cChoice = getch();
        switch (cChoice)
        {
        case 'u':
        case 'U':
            printf("Unlock\n");
            UI("space", 20);
            printf("Enter the key: ");
            scanf("%6s", cAnswer);
            UI("space", 20);
            for (i = 0; i < 5; i++)
            {
                printf(".");
                delay(1);
            }
            
            if (strcmp(strupr(cAnswer), cToGuess) == 0)
            {
                printf("YOU UNLOCKED THE CHEST!!!");
                *nChestMark = 1;
                nLoop = 0;
                delay(2);
                system("cls");
                printf("*******************************************************************************  \n");
                printf("         |                   |                  |                     |          \n");
                printf("_________|________________.=\"\"_;=.______________|_____________________|_______   ");       UI("top", 52); printf("\n");
                printf("|                   |  ,-\"_,=\"\"     `\"=.|                  |                     ");     printf("%c REWARD                                           %c\n",186,186);
                printf("|___________________|__\"=._o`\"-._        `\"=.______________|___________________  ");      printf("%c              5 pcs of Sweet Beet                 %c\n",186,186);
                printf("         |                `\"=._o`\"=._      _`\"=._                     |          ");      printf("%c              5 pcs of Timber                     %c\n",186,186);
                printf("_________|_____________________:=._o \"=._.\"_.-=\"'\"=.__________________|_______   ");     printf("%c              5 pcs of Intricate Lace             %c\n",186,186);
                printf("|                   |    __.--\" , ; `\"=._o.\" ,-\"\"\"-._ \".   |                     ");  printf("%c              5 pcs of Intoxicating Perfume       %c\n",186,186);
                printf("|___________________|_._\"  ,. .` ` `` ,  `\"-._\"-._   \". '__|___________________  ");     printf("%c              5 pcs of Pale Amber Wine            %c\n",186,186);
                printf("         |           |o`\"=._` , \"` `; .\". ,  \"-._\"-._; ;              |          ");    printf("%c              5 pcs of Myrish Eye                 %c\n",186,186);
                printf("_________|___________| ;`-.o`\"=._; .\" ` '`.\"\\` . \"-._ /_______________|_______   ");    printf("%c              5 pcs of Qohorik Tapestry           %c\n",186,186);
                printf("|                   | |o;    `\"-.o`\"=._``  '` \" ,__.--o;   |                     ");      printf("%c              5 pcs of Valyrian Steel             %c\n",186,186);
                printf("|___________________|_| ;     (#) `-.o `\"=.`_.--\"_o.-; ;___|___________________  ");       printf("%c              5000 Golden Dragons                 %c\n",186,186);
                printf("____/______/______/___|o;._    \"      `\".o|o_.--\"    ;o;____/______/______/____  ");      UI("bottom", 52); printf("\n");
                printf("/______/______/______/_\"=._o--._        ; | ;        ; ;/______/______/______/_\n");
                printf("____/______/______/______/__\"=._o--._   ;o|o;     _._;o;____/______/______/____\n");
                printf("/______/______/______/______/____\"=._o._; | ;_.--\"o.--\"_/______/______/______/_\n");
                printf("____/______/______/______/______/_____\"=.o|o_.--\"\"___/______/______/______/____\n");
                printf("/______/______/______/______/______/______/______/______/______/______/______/_\n");
                printf("*******************************************************************************  ");         printf("Press anything to continue ");getch();
                for (i = 0; i < 8; i++)
                {
                    nIntry[i] += 5;
                    *nStored += 5;
                }
                *fGD += 5000.0;               
            }
            else
            {
                printf("Incorrect Key.\n");
                nLoop = 1;
                delay(1);
            }
            break;
        case 'b':
        case 'B':
            nLoop = 0;
            break;
        default:
            invalidinput();
            nLoop = 1;
            break;
        }
    } while (nLoop);
    system("cls");
}

void acknowledgement ()
{
    system("cls");
    printf("Coded by: KYLE CARLO C. LASALA\n");
    printf("Student from: De La Salle University - Manila\n");
    printf("Date Finish: 02/05/2022\n\n");
    printf("Special thanks to:\n");
    printf("                     Sir Arren Matthew Antioquia\n\n");
    printf("Acknowledgement:\n");
    printf("                 The mentioned websites helped in gaining in-depth knowledge for time.h,\n");
    printf("                 string.h, and conio.h in this program respectively.\n");
    printf("                 https://www.tutorialspoint.com/c_standard_library/time_h.htm\n");
    printf("                 https://www.tutorialspoint.com/c_standard_library/string_h.htm\n");
    printf("                 https://www.educative.io/edpresso/what-is-getchar-in-c\n");
    printf("                 https://stackoverflow.com/questions/4204666/how-to-list-files-in-a-directory-in-a-c-program\n\n");
    printf("                 Furthermore, https://ascii.co.uk/art is where most of the ascii art came from.\n");
    printf("                 Others, came from my own idea and generated some ascii art using\n");
    printf("                 https://manytools.org/hacker-tools/convert-images-to-ascii-art/ \n\n\n");
    printf("                 THANK YOU FOR PLAYING THE GAME \n");
    printf("                 press anything to terminate the program ");
    getch();
}

void SaveProgress (char cName[], int nDays, float fGD, float fDebt, float fSavings, int nStored, int nTCap, int nIntry[], float fPrice[], int nProgressIdentifier, int nLoanMark, int nChestMark, char cPartner)
{
    char cFileName[128];
    int i,
        nGD = fGD * 10000,            //float to int GD
        nPrice[8],                  //float to int prices
        nSavings = fSavings * 10000,  //float to int savings
        nDebt = fDebt * 10000;        //float to int debt
    FILE * fsaved;

    for (i = 0; i < 8; i++)
    {
        nPrice[i] = fPrice[i] * 10000;
    }
    

    for (i = 0; i < strlen(cName) + 2; i++) //file name conversion - adds "``" to the name - mark as saved file
    {
        switch (i)
        {
        case 0:
        case 1:
            cFileName[i] = '`';
            break;
        default:
            cFileName[i] = cName[i-2];
            break;
        }
    }

    cFileName[strlen(cName) + 2] = '\0';
    printf("%s", cFileName);

    fsaved = fopen(cFileName, "w");

    fputs(cName, fsaved);       //line 1 in saved file - name of the player
    putw(nDays, fsaved);        //line 2 in saved file - days remaining of the player
    putw(nGD, fsaved);          //line 3 in saved file - gds of player
    putw(nDebt, fsaved);        //line 4 in saved file - debts in the bank
    putw(nSavings, fsaved);     //line 5 in saved file - savings in the bank
    putw(nStored, fsaved);      //line 6 in saved file - total inventory of the player
    putw(nTCap, fsaved);        //line 7 in saved file - total capacity in the wheelhouse

    for (i = 0; i < 8; i++)     //line 8 - 16 in saved file - inventory of the player
    {
        putw(nIntry[i], fsaved);
    }
    for (i = 0; i < 8; i++)     //line 17 - 25 in saved file - prices generated from randomizer
    {
        putw(nPrice[i], fsaved);
    }    
    putw(nProgressIdentifier, fsaved); //line 26 in saved file - progressidentifier identifies which part of the game does the user stopped
    putw(nLoanMark, fsaved);    //line 27 in saved file - loan identifier for the day
    putw(nChestMark, fsaved);   //line 28 in saved file - treasure chest identifier 
    putc(cPartner, fsaved);     //line 29 in saved file - partner choice for the day

    fclose(fsaved);
}

void LoadProgress (char cName[], int *nDays, float *fGD, float *fDebt, float *fSavings, int *nStored, int *nTCap, int nIntry[], float fPrice[], int *nProgressIdentifier, int *nLoanMark, int *nChestMark, char *cPartner, char *cItemNames[], char *cPartnerNames[])
{
    int i,                  //for loop variable
        nFileCounter = 0,   //file identifier and counter in the directory
        nGD,                //int to float GD
        nPrice[8],          //int to float prices
        nSavings,           //int to float savings
        nDebt;              //int to float debt
    char *cFileName,
         cIsLoad = 1,
         cChosenFile;
    FILE *fload;
    DIR *directory;

    do
    {
        i = 0;
        directory = opendir(".");
        struct dirent *entity;
        entity = readdir(directory);

        while (entity != NULL && i < 10)
        {
            if (entity->d_name[0] != '.' && entity->d_name[0] == '`' && entity->d_name[1] == '`')
            {
                printf("[%d] %s\n", i+1, entity->d_name);
                nFileCounter++;
                i++;
            }
            entity = readdir(directory);
        }

        if(nFileCounter > 0)
        {
            
            printf("Do you want to load your progress?\n");
            printf("[Y]es or [N]o: ");
            cIsLoad = getch();

            switch (cIsLoad)
            {
                case 'Y':
                case 'y':
                    printf("Yes\n");
                    printf("Choose the saved file you want to load: ");
                    cChosenFile = getch();
                    if (cChosenFile - '0' > 0 && cChosenFile - '0' <= nFileCounter)
                    {
                        i = 0;
                        directory = opendir(".");
                        entity = readdir(directory);
                        while (entity != NULL && i < 10)
                        {
                            if (entity->d_name[0] != '.' && entity->d_name[0] == '`' && entity->d_name[1] == '`')
                            {
                                if (i == cChosenFile - '0' - 1)
                                {
                                    cFileName = entity->d_name;
                                    entity = NULL;
                                }
                                i++;
                            }
                            entity = readdir(directory);
                        }

                        printf("%s\n", cFileName);

                        fload = fopen(cFileName, "r");

                        fgets(cName, strlen(cFileName) - 1, fload);           //loading data from line 1
                        *nDays = getw(fload);                                 //loading data from line 2
                        nGD = getw(fload); *fGD = nGD / 10000.0;                //loading data from line 3
                        nDebt = getw(fload); *fDebt = nDebt / 10000.0;          //loading data from line 4
                        nSavings = getw(fload); *fSavings = nSavings / 10000.0; //loading data from line 5
                        *nStored = getw(fload);                               //loading data from line 6 
                        *nTCap = getw(fload);                                 //loading data from line 7

                        for (i = 0; i < 8; i++) //loading data from line 8 - 16
                        {
                            nIntry[i] = getw(fload);
                        }
                        for (i = 0; i < 8; i++) //loading data from line 17 - 25
                        {
                            nPrice[i] = getw(fload);
                            fPrice[i] = nPrice[i] / 10000.0;
                        }

                        *nProgressIdentifier = getw(fload); //loading data from line 26
                        *nLoanMark = getw(fload); //loading data from line 27
                        *nChestMark = getw(fload); // loading data from line 28
                        *cPartner = getc(fload); //loading data from line 29

                        fclose(fload);
                        
                        //printing the loaded data
                        printf("\n    Days Remaining:      - %d\n", *nDays);
                        printf("    Golden Dragons (GD): - %.2f\n", *fGD);
                        printf("    Debt:                - %.2f\n", *fDebt);
                        printf("    Savings:             - %.2f\n", *fSavings);
                        printf("    Capacity:            - %d/%d\n", *nStored, *nTCap);
                        printf("    Inventory:\n");
                        for (i = 0; i < 8; i++)
                        {
                            printf("                %-20s - %d pcs\n", cItemNames[i], nIntry[i]);
                        }

                        printf("Successfully loaded.\n");
                        printf("Welcome back %s!\n", cName);

                        if (*cPartner != '9')
                        {
                            printf("We are in %s, %s\n", cPartnerNames[*cPartner - '0' - 1], cName);
                        }
                                                
                        printf("Press anything to continue ");
                        getch();
                    }
                    else
                    {
                        invalidinput();
                        cIsLoad = 0;
                    }
                break;
            
                case 'N':
                case 'n':
                    printf("No\n");
                    printf("You may now start your new game.\n");                    
                    printf("Press anything to continue ");
                    getch();
                break;

                default:
                    invalidinput();
                    cIsLoad = 0;
                break;
            }
        }
    } while (cIsLoad == 0);
    system("cls");
}

int ExitGame (int nDays, float fGD, float fDebt, float fSavings, int nStored, int nTCap, int nIntry[], float fPrice[], int nProgressIdentifier, int nLoanMark, int nChestMark, char cPartner, char *cItemNames[])
{
    int i,      //for loop variable
        nQuit = 0;  //return variable - determines if the game will exit
    char cChoice, //for user input
         cName[128];
    system("cls");
    do
    {
        printf("Do you want to quit the game?\n");
        printf("[Y]es or [N]o: ");
        cChoice = getch();
        switch (cChoice)
        {
        case 'y':
        case 'Y':
            printf("Yes");
            system("cls");
            printf("Do you want to save the game?\n");
            printf("[Y]es or [N]o: ");
            cChoice = getch();
            switch (cChoice)
            {
            case 'y':
            case 'Y':
                printf("Yes");
                cChoice = 1;
                break;
            case 'n':
            case 'N':
                printf("No");
                cChoice = 2;
                break;
            default:
                invalidinput();
                break;
            }
            break;
        case 'n':
        case 'N':
            printf("No");
            nQuit = nDays;
            break;
        default:
            invalidinput();
            break;
        }
            
    } while (!(cChoice == 1 || cChoice == 2 || cChoice == 'n' || cChoice == 'N'));
    system("cls");

    //print details for quitting the game
    switch (cChoice)
    {
    case 1:
        printf("Enter your name: ");
        scanf("%s", cName);
        SaveProgress(cName, nDays, fGD, fDebt, fSavings, nStored, nTCap, nIntry, fPrice, nProgressIdentifier, nLoanMark, nChestMark, cPartner);            
    case 2:
        printf("\n    Days Remaining:      - %d\n", nDays);
        printf("    Golden Dragons (GD): - %.2f\n", fGD);
        printf("    Debt:                - %.2f\n", fDebt);
        printf("    Savings:             - %.2f\n", fSavings);
        printf("    Capacity:            - %d/%d\n", nStored, nTCap);
        printf("    Inventory:\n");
        for (i = 0; i < 8; i++)
        {
            printf("                %-20s - %d pcs\n", cItemNames[i], nIntry[i]);
        }
        printf("\n\nPress anything to continue");
        getch();
        break;
    }
    return nQuit;
}