/******************************************************
****Author: Dipankar Das (14/1/2021)*******************
*****   COMPILED BY TDM-GCC     ***********************
*******************************************************
to calculate the age of the user and store their name,*
DOB with age*******************************************
*/

#include <stdio.h>
#include <stdlib.h>


FILE *f1;   // the file pointer
static char name[20];   // store the name of user whose dob is calculated
struct date { /* to store the day,month,year */
    int dd;
    int mm;
    int yy;
};

void display_main(){ /* to display the first welcome screen */
    printf("\n\n\n\t\t\t*****************************************");
    printf("\n\t\t\t*\t\t\t\t\t*");
    printf("\n\t\t\t*\tWELCOME TO AGE CALCULATOR\t*");
    printf("\n\t\t\t*\t\t\t\t\t*");
    printf("\n\t\t\t*****************************************\n\n\n");

    printf("Press any key to continue");
    getchar();
}

void acessing_todays_date(struct date dt[]){
    /* to store the current time of sys */
    dt[1].yy = ((__DATE__[7]-'0')*1000 + (__DATE__[8]-'0')*100 + (__DATE__[9]-'0')*10 + (__DATE__[10]-'0'));
    dt[1].dd = ((__DATE__[4]-'0')*10 + __DATE__[5]-'0');
    if(__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n')
        dt[1].mm = 1;
    else if(__DATE__[0] == 'F')
        dt[1].mm = 2;
    else if(__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r')
        dt[1].mm = 3;
    else if(__DATE__[0] == 'A' && __DATE__[1] == 'p' && __DATE__[2] == 'r')
        dt[1].mm = 4;
    else if(__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y')
        dt[1].mm = 5;
    else if(__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n')
        dt[1].mm = 6;
    else if(__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l')
        dt[1].mm = 7;
    else if(__DATE__[0] == 'A' && __DATE__[1] == 'a' && __DATE__[2] == 'u')
        dt[1].mm = 8;
    else if(__DATE__[0] == 'S' && __DATE__[1] == 'e' && __DATE__[2] == 'p')
        dt[1].mm = 9;
    else if(__DATE__[0] == 'O' && __DATE__[1] == 'c' && __DATE__[2] == 't')
        dt[1].mm = 10;
    else if(__DATE__[0] == 'N' && __DATE__[1] == 'o' && __DATE__[2] == 'v')
        dt[1].mm = 11;
    else if(__DATE__[0] == 'D' && __DATE__[1] == 'e' && __DATE__[2] == 'c')
        dt[1].mm = 12;
}

int age_cal(struct date *dt) {
    /* to return the number of days from the USER's DOB wrt to system date */
    int d, m, y, mf;
    d = (dt+0)->dd;
    m = (dt+0)->mm;
    y = (dt+0)->yy;

    int no_days = 0; // return the no of days b/w the two years
    while(!(d == (dt+1)->dd && m == (dt+1)->mm && y == (dt+1)->yy)) {
        if ((y%4 == 0 && y%100 != 0)||(y%400 == 0)) // leap year
            mf = 29;
        else // not a leap year
            mf = 28;
        
        if (m == 2 && d == mf) { // february month
            m = 3;
            d = 1;
            no_days++;
        }
        else if (m == 12 && d == 31) { // december month
            m = d = 1;
            y++;
            no_days++;
        }
        else if ((m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10) && d == 31){ // months with 31 days
            m++;
            d = 1;
            no_days++;
        }
        else if ((m == 4 || m == 6 || m == 9 || m == 11) && d == 30){ // months with 30 days
            m++;
            d = 1;
            no_days++;
        }
        else {
            d++;
            no_days++;
        }
    }
    return no_days;
}


int main(){
    system("cls");
    display_main();
    
    f1 = fopen("log_age.csv","a+"); // opening the file log_age.csv
    start:
    system("cls");

    struct date dt[2];

    printf("enter your name: \n");
    scanf(" %[^\n]",name);

    printf("\nenter your DOB in dd/mm/yyyy\n");
    scanf("%d/%d/%d", &dt[0].dd, &dt[0].mm, &dt[0].yy);
    acessing_todays_date(dt);

    int difftime = age_cal(dt);
    printf("the diff (in days) = %d\n", difftime);
    struct date age;
    // converting the days into year, month, days
    age.yy = difftime/365;
    difftime = difftime%365;
    age.mm = difftime/30;
    difftime = difftime%30;
    age.dd = difftime;

    system("cls");
    printf("\n\n\t\t\t*************************************************\n");
    printf("\t\t\t*\t\t%s AGE IS\t\t*\n", name);
    printf("\t\t\t*\t%d day(s) %d month(s) and %d years\t*\n", age.dd, age.mm, age.yy);
    printf("\t\t\t*************************************************\n");

    fprintf(f1,"%s,%d-%d-%d,%d",name, dt[0].dd, dt[0].mm, dt[0].yy, age.yy);
    printf("\n Enter Y(yes) to continue and N(no) to exit\n\n");

    char choice;
    scanf(" %c",&choice);
    if(choice == 'Y' || choice == 'y'){
        fprintf(f1,"\n");
        goto start;
    }
    else if (choice == 'N' || choice == 'n'){
        fprintf(f1,"\n");
        fclose(f1);
        return 0;
    }
    else{
        fprintf(f1,"\n");
        fclose(f1);
        printf("\nERROR: wrong key\n\n\n");
        return 0;
    }
}