#include <stdio.h>
#include <stdlib.h>

/*
 * This is module level documentation and is a one-liner for the whole program.
 *
 * Description:
 * This program allows the user to enter a month day and then year through args
 * input and allows the user to attain the day that specific date fell on.
 *
 * Inputs:
 * The program takes in the Month Day Year in that order. The month has to have
 * the first letter in upper case and the rest of the first three letters 
 * in lower case. 
 *
 * Outputs:
 * Once the correct input is entered the program would output the day on which
 * that day occured. If any other input is entered it would output "Input not valid"
 *
 * Caveats
 * The program only works for dates from 1900 to 2040
 */
 
char* monthName[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};  	/* Initialisation of a month of the year list*/
int monthNum[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};											/* Initialisation of a days in month list*/
int monthNumLeap[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};										/* Initialisation of a days in month list of a leap year*/
char* weekNames[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};										/* Initialisation of a days in week list*/


int numberLeapYear(int year)			/*This function calculates the number of leap years between the 1900 and the year entered*/
{
    int start = 1900;					/*Start of the programs date function*/
    int leap = (year-start)/4;			/*Leap years occur every 4 years from this date onward*/
    return(leap);
}

int isLeapYear(int year)				/*Algorithm checks to see if the year taken in is a leap year and outputs a zero or one depending if it is or is not*/
{
    int leapYear = (year % 4) || ((year % 100 == 0) &&(year % 400)) ? 0 : 1;		/*algorithm for leap year*/
    return leapYear;

}

int amountDays(char* month, int day, int year)	/*This function calculates the amount of days from the 1900's to the day specified*/
{
    int start = 1900;							/*year the program starts calculating from*/
    int btwnYear = year - start;				/*gets the number of years between the years*/
    int dayInYear = 365;						/*states how much days are in a year*/
    int totalDays = 0;							/*total days thus far is zero*/

    if (btwnYear>=1)							/*if the years between are more then 1 it has an added 356 days else it would just add the amount of days in the year*/
    {
        totalDays = numberLeapYear(year)+((btwnYear)*dayInYear);	/*algorithm to calculate days */
    }

    int i;										/*for loop in initialisation*/
    int count = 0;								/*count initialisation*/

    for (i = 0; i<12; i++)						/*for loop to check where the month in the year is*/
    {
        if(strcmp(monthName[i],month)==0)		/*using string compare to check if the months are equal*/
        {
            break;								/*if the months are equal break out of the loop*/
        }
        int num = monthNum[i];					/*initialising month to the number to add*/
        totalDays = totalDays + num;			/*adding the month number to the number of total days in a year*/
        count ++;								
    }
	if(strcmp(month,"Jan")==0&& isLeapYear(year)==0 ||strcmp(month,"Feb")==0&& isLeapYear(year)==0 )	/*this caters for the day lost before February when it is not a leap year*/
	{
		totalDays +=1;
	}
    totalDays += day;							/*total days + the day of the day of the month since we are not adding the entire days in the month just the day to which was entered*/

    return totalDays;

}


void invalid (int day, char* month, int year, char* day_string)	/*This function checks whether the input is valid*/
{
    int i;										/*declaration for for loop*/
    int count = 12;								/*count is 12 for the amount of months in a year*/

    if(year<1900 || year>2040)					/*if the year does not fall within the delimiter it will not be accepted*/
    {
        fprintf(stderr, "Input not valid\n");
        exit(1);
    }

    if(day<=0 || day>31)						/*if a day is a negative or more the 31 it is invalid*/
    {
        fprintf(stderr, "Input not valid\n");
        exit(1);
    }

    for (i = 0; i<12; i++)						/*if the day specified does not match the day in the month it is invalid*/
    {

        if(strcmp(month,monthName[i])!=0)		/*this count allows me to keep track of which months has passed*/
        {
            count = count -1;
        }
        if (strcmp(month,monthName[i])==0)		
        {
            if(isLeapYear(year)==1				
            {									/*checking to see if the year is a leap year and that the day matches month in the year in the leap year*/
                if(day<0 || day > monthNumLeap[i])
                {
                    fprintf(stderr, "Input not valid\n");
                    exit(1);
                }
            }

            if(isLeapYear(year)==0)				/*checking to see if the year is not a leap year and that the day matches month in the year in the leap year*/
            {
                if(day<0 || day > monthNum[i])
                {
                    fprintf(stderr, "Input not valid\n");
                    exit(1);
                }
            }
        }

        if (count == 0)							/*if no month was found that matches the months specified then invalid*/
        {
            fprintf(stderr, "Input not valid\n");
            exit(1);
        }
    }

}

int dayChecker(int totalDays, int day, char* month, int year)		/*Checks to see on which day the specified date falls*/
{
    int number = 28; 
    if(strcmp(month,"Jan")==0 || strcmp(month,"Feb")==0)			/*Caters for the day added previously*/
    {
        totalDays -= 1;
    }

    int weekDayNum = (totalDays)%7;									/*7 days in a week therefore if we mod the total days by 7 and use the remainder as a reference*/

    if (strcmp(month,"Feb")==0 && day == 29 && isLeapYear(year)==1)	/*if the month requested is feb and is is a leap year as well as requesting the 29th day*/
    {
        if(weekDayNum == -1)										/*it would automatically be a Sunday*/
        {
            weekDayNum = 6;
            printf("Sun");
        }
    }

   if (weekDayNum == 0)												/*if weekday is a zero it would automatically be a sunday*/
    {
        printf("Sun\n");
        exit(1);
    }
    char* dayName = weekNames[weekDayNum -1];						/*else the day would be the weekday number -1*/
    printf("%s\n",dayName);
    exit(1);
}

int main(int argc, char *argv[])
{
    if(argv[1] == NULL || argv[2] == NULL || argv[3] == NULL)		/*checks to see if all values are filled when entering a request*/
    {
		fprintf(stderr, "Input not valid\n");					
	}

    else
    {
        char* month = argv[1];										/*assigning the values to corresponding names*/
        int day = atoi(argv[2]);									/*assigning the values to corresponding names*/
        char* day_string = argv[2];									/*used day string to check if the number can be changed to a digit*/
        int year = atoi(argv[3]);									/*assigning the values to corresponding names*/

        invalid(day, month, year, day_string);						/*check to see if the values entered are valid*/

        int allDays = amountDays(month, day, year);					/*gets the total amount of days*/
        dayChecker(allDays, day, month, year);						/*checks to see what day it is*/
    }

    return 0;
}
