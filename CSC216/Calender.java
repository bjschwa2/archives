import java.io.*;
import java.util.*;


/**
 * Prints out a calendar dependent on the specified month and year
 * 
 * @author Bradley Schwarz
 */
 public class Calender{

	public static final int MINIMUM_YEAR = 1753;
	public static final String MONTHS[] =  {"bad","January", "Febuary", "March", "April", "May", "June", "July",
										"August","September","October","November","December"};
										
	public static final int ONE_HUNDRED = 100;
	public static final int FOUR_HUNDRED = 400;
	public static final int FOURTEEN = 14;
	public static final int TWELVE = 12;
	public static final int THIRTY_ONE = 31;
	public static final int TWO = 2;
	public static final int THREE = 3;
	public static final int FOUR = 4;
	public static final int FIVE = 5;
	public static final int SIX = 6;
	public static final int SEVEN = 7;
	public static final int EIGHT = 8;
	public static final int NINE = 9;
	public static final int TEN = 10;
	public static final int ELEVEN = 11;
	public static final int THIRTY = 30;
	public static final int TWENTY_EIGHT = 28;
	public static final int TWENTY_NINE = 29;
	
											
	
	/**
	* @param args command line arguments
	*
	*/ 
	public static void main(String[] args){


		
		int month = 0;
		try {
    		month = Integer.parseInt(args[0]);        
		}
		catch (NumberFormatException e) {
    		System.out.println("Invaild Input please try again");
    		System.out.println("Usage: java Calendar <month> <year>");
    		System.exit(1);

		}


		int year = 0;
		try {
    		year = Integer.parseInt(args[1]);        
		}
		catch (NumberFormatException e) {
    		System.out.println("Invaild Input please try again");
    		System.out.println("Usage: java Calendar <month> <year>");
    		System.exit(1);
		}


		if (month > 12 || month < 1){

			System.out.println("Month must be an integer between 1 and 12");
			System.out.println("Usage: java Calendar <month> <year>");
			System.exit(1);

		}	

		if (year < MINIMUM_YEAR){

			System.out.println("Year must be 1753 or later");
			System.out.println("Usage: java Calendar <month> <year>");
			System.exit(1);

		}

	displayCalendar(month, year, getCalendar(month, year));
	

	}


	/**
	* Returns true if the year is a leap year and false otherwise 
	* Throw an IllegalArgumentException if year < 1753
	*
	* @param year The users specified year
	*
	*/
	public static boolean isLeapYear(int year) {
		if (year%FOUR==0){

        		if(year%ONE_HUNDRED==0) {

             			if(year%FOUR_HUNDRED==0){

             				return true;

             			}
             			else{ 
             
             				return false;
             	
             			}
             		}
             		else{ 
         
         			return true;
         
     			}
     		}
     		else{ 
     
     			return false;
		}
	}


	/**
	* Returns 0 if the first day of the month falls on Sunday, 1 if it falls on Monday, 
	* 2 if it falls Tuesday, ...,  and 6 if it falls on Saturday.
	*
	* @param month The users specified month
	* @param year The users specified year
	*
	*/
	public static int getFirstDayOfMonth(int month, int year) {

		int y = year;
		int m = month;
		int d = 1;

		int w = y - (FOURTEEN - m) / TWELVE;

		int x = w + w / FOUR - w / ONE_HUNDRED + w / FOUR_HUNDRED;

		int z = m + TWELVE * ((FOURTEEN - m) / TWELVE) - TWO;

		int DayOfWeek = (d + x + (THIRTY_ONE * z) / TWELVE) % SEVEN;

		return DayOfWeek;

	}


	/**
	* Returns a 2D integer array with 6 rows and 7 columns that contains the calendar for the month with 
	* 0's in positions that should be blank in the actual calendar. 
	*
	* @param month The users specified month
	* @param year The users specified year
	*
	*/
	public static int[][] getCalendar(int month, int year) {

		int start = 0;
		start = getFirstDayOfMonth(month, year);
	
	
		int end = 0;
		if (month == 1){
			end = THIRTY_ONE;	

		} else if (month == TWO){
			if (isLeapYear(year) == true){
				end = TWENTY_NINE;
		
			}else {
				end = TWENTY_EIGHT;
			}
	
	
		} else if (month == THREE){
			end = THIRTY_ONE;
	
		}else if (month == FOUR){
			end = THIRTY;
	
		}else if (month == FIVE){
			end = THIRTY_ONE;
	
		}else if (month == SIX){
			end = THIRTY;
	
		}else if (month == SEVEN){
			end = THIRTY_ONE;
	
		}else if (month == EIGHT){
			end = THIRTY_ONE;
	
		}else if (month == NINE){
			end = THIRTY;
	
		}else if (month == TEN){
			end = THIRTY_ONE;
	
		}else if (month == ELEVEN){
			end = THIRTY;
	
		}else if (month == TWELVE){
			end = THIRTY_ONE;
	
		}
	
	
		int[][] calendar = new int[SIX][SEVEN];
		int incr = 0;

		for (int r = 0; r < calendar.length; r++){
            		for (int c = 0; c < calendar[0].length; c++) {
            			if (r == 0 && c == start){
            				calendar[r][c] = ++incr;
            			}else if(incr < end && incr != 0 ){ 
               				calendar[r][c] = ++incr;
              			}  
            		}
		}
		return calendar;
	} 


	/**
	* Displays the calendar for the month and year based on the 2D calendar array 
	* with 6 rows and 7 columns as shown above that is passed to the method. The
	* month and year should be centered at the top of the calendar as shown below.
	*
	* @param month The users specified month
	* @param year The users specified year
	* @param calendar The calendar found in the getCalendar method
	*/
	public static void displayCalendar(int month, int year, int[][] calendar) { 

		System.out.println("   "+MONTHS[month] +" "+ year);
		System.out.println("Su "+"Mo "+"Tu "+"We "+"Th "+"Fr "+"Sa");

		for (int r = 0; r < calendar.length; r++){
            		for (int c = 0; c < calendar[0].length; c++) {
            
            
            			if (calendar[r][c]==0){
            		//calendar[r][c] = ;
            			}
                			System.out.printf("%2d ",calendar[r][c]); 
            			}
            		System.out.println(" ");
			}
		}
 
}

