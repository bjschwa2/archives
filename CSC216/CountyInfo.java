import java.io.*;
import java.util.*;

/**
 * Alows the user to search the file counties.txt
 * The user can either Display the counties with different specifications
 * or search the file for a county or a state
 *
 * @author Bradley Schwarz
 */
 public class CountyInfo{
 	public static final String[] STATES = {"AL", "AK", "AZ", "AR", "CA", "CO", "CT", "DE", "DC", "FL",
                                       "GA", "HI", "ID", "IL", "IN", "IA", "KS", "KY", "LA", "ME",
                                       "MD", "MA", "MI", "MN", "MS", "MO", "MT", "NE", "NV", "NH",
                                       "NJ", "NM", "NY", "NC", "ND", "OH", "OK", "OR", "PA", "RI",
                                       "SC", "SD", "TN", "TX", "UT", "VT", "VA", "WA", "WV", "WI", "WY"};

        public static final int TWO = 2;
        

       /**
	* @param args command line arguments
        *
	*/
	public static void main(String[] args){
      
		Scanner console = new Scanner(System.in);
                Scanner scan = null;
                Scanner linecount = null;
                	try {
				scan = new Scanner(new File("counties.txt"));
				linecount= new Scanner(new File("counties.txt"));
				scan.useDelimiter(",");
			} catch (FileNotFoundException e) {
				System.out.println("File not found. "
							+ "Please try again.");
			}
                     
                
                int counter = 0;
                linecount.nextLine();
                while (linecount.hasNextLine()){
			linecount.nextLine();
			counter++;
		}
		
		//declare arrays at counter size
		String[] county = new String[counter];
		String[] state = new String[counter];
		int[] population = new int[counter];
		double[] area = new double[counter];
		double[] populationDensity = new double[counter];
		
	
		
		 scan.nextLine();
		//fill arrays with data at line i
		for(int i = 0; i < counter; i++){
			county[i] = scan.next();
			state[i] = scan.next();
			population[i] = scan.nextInt();
			scan.next();
			area[i] = scan.nextDouble();
			scan.next();
			scan.next();
			populationDensity[i] = scan.nextDouble();
			scan.nextLine();
			
		
		
		}
		
              
                while(true) {

                    System.out.println("County Info - Please enter an option below.");
                    System.out.println("D - Display counties with highest/lowest population, area, population density");
                    System.out.println("L - List all counties in a given state");
                    System.out.println("S - Search for county");
                    System.out.println("Q - Quit the program");

                    System.out.print("Option: ");

                    String process = console.next();

                    if (process.equalsIgnoreCase("D")){
                        
                        displayCounties(county, state, population, area, populationDensity); 

                    }else if (process.equalsIgnoreCase("l")){
                        
                        listCountiesInState(console, county, state, population, area, populationDensity); 

                    }else if (process.equalsIgnoreCase("S")){
                        
                        search(console, county, state, population, area, populationDensity); 

                    }else if (process.equalsIgnoreCase("Q")){
                    	System.out.println("Goodbye!");
                        System.exit(1);

                    }else{
                        System.out.println("invalid option");

                    }
                    System.out.println("  ");
        }

    }
    
	/**
	* Display counties with highest/lowest population, area, and population density
	* as shown above.
	*
	* @param county The array containing all of the counties
	* @param state The array containing all of the states
	* @param population The array containing all of the populations
	* @param area The array containing all of the areas
	* @param populationDensity The array containing all of the population densities
	*
	*/
	public static void displayCounties(String[] county, String[] state, 
	int[] population, double[] area, double[] populationDensity) {

		int highestPopulation = population[0];
		int locationHighestPopulation = 0;
			for(int i=0; i<population.length; i++){
				if(population[i]>highestPopulation){
				highestPopulation = population[i]; 
				locationHighestPopulation = i;
				}
			}
		int lowestPopulation = population[0];
		int locationLowestPopulation = 0;
			for(int x=0; x<population.length; x++){
				if(population[x]<lowestPopulation){
				lowestPopulation = population[x]; 
				locationLowestPopulation = x;
				}
			}
		
		double highestArea = area[0];
		int locationHighestArea = 0;
			for(int y=0; y<area.length; y++){
				if(area[y]>highestArea){
				highestArea = area[y]; 
				locationHighestArea = y;
				}
			}
		double lowestArea = area[0];
		int  locationLowestArea = 0;
			for(int z=0; z<area.length; z++){
				if(area[z]<lowestArea){
				lowestArea = area[z]; 
				locationLowestArea = z;
				}
			}
		
		double highestPopulationDensity = populationDensity[0];
		int locationHighestPopulationDensity = 0;
			for(int q=0; q<populationDensity.length; q++){
				if(populationDensity[q]>highestPopulationDensity){
				highestPopulationDensity = populationDensity[q]; 
				locationHighestPopulationDensity = q;
				}
			}
		double lowestPopulationDensity = populationDensity[0];
		int locationLowestPopulationDensity = 0;
			for(int v=0; v<populationDensity.length; v++){
				if(populationDensity[v]<lowestPopulationDensity){
				lowestPopulationDensity = populationDensity[v]; 
				locationLowestPopulationDensity = v;
				}
			}
	
	
		System.out.println(" ");
		
		System.out.println("Highest Population: " + highestPopulation);
	
		System.out.println(county[locationHighestPopulation] + "," + state[locationHighestPopulation] );
	
		System.out.println(" ");
	
		System.out.println("Lowest Population: " + lowestPopulation);
	
		System.out.println(county[locationLowestPopulation] + "," + state[locationLowestPopulation] );
	
		System.out.println(" ");
	
		System.out.println("Highest Area(sq mi): " + highestArea);
	
		System.out.println(county[locationHighestArea] + "," + state[locationHighestArea] );
	
		System.out.println(" ");
	
		System.out.println("Lowest Area(sq mi): " + lowestArea);
	
		System.out.println(county[locationLowestArea] + "," + state[locationLowestArea] );
	
		System.out.println(" ");
	
		System.out.println("Highest Population Density(people/sq mi land): " + highestPopulationDensity);
	
		System.out.println(county[locationHighestPopulationDensity] + "," + state[locationHighestPopulationDensity] );
	
		System.out.println(" ");
	
		System.out.println("Lowest Population Density(people/sq mi land): " + lowestPopulationDensity);
	
		System.out.println(county[locationLowestPopulationDensity] + "," + state[locationLowestPopulationDensity] );
	
		
	
	

	}
	
	
	/**
	* Prompt the user for a state or DC and list all counties in the state/DC and population, area,
	* and population density
	*
	* @scanner console The programs scanner
	* @param county The array containing all of the counties
	* @param state The array containing all of the states
	* @param population The array containing all of the populations
	* @param area The array containing all of the areas
	* @param populationDensity The array containing all of the population densities
	*
	*/
	public static void listCountiesInState(Scanner console, String[] county, String[] state, 
	int[] population, double[] area, double[] populationDensity) {


	//while(true) {
		System.out.print("State: ");
		String input = console.next();
	
		boolean isState = false;
	
		for (int i = 0 ; i<STATES.length ; i++){
			if (input.equalsIgnoreCase(STATES[i])){
				isState = true;
				break;
		
		
			} 
			
		
		}
		
		for (int j=0; j<state.length; j++){
			if (state[j].equalsIgnoreCase(input)){
				System.out.println( county[j] +", " + state[j]+"  "+ " Pop: " + population[j] + "   Area(sq mi): "+ area[j] 
									+ "    Pop Dens(people/sq mi land): " + populationDensity[j]);
			
			}
		
		}
	
	}

	

	/**
	* Prompt the user for part or all of a county name and list all counties 
	* whose name contains the string, ignoring case, and their state,
	* population, area, and population density
	*
	* @scanner console The programs scanner
	* @param county The array containing all of the counties
	* @param state The array containing all of the states
	* @param population The array containing all of the populations
	* @param area The array containing all of the areas
	* @param populationDensity The array containing all of the population densities
	*
	*/
	public static void search(Scanner console, String[] county, String[] state, 
	int[] population, double[] area, double[] populationDensity) {

		System.out.println("County (is/contains):");
		String countyInput = console.next();
	

			
		for (int j=0; j<county.length; j++){
			if (county[j].equalsIgnoreCase(countyInput) || county[j].contains(countyInput)){
				System.out.println( county[j] +", " + state[j]+"  "+ " Pop: " + population[j] + "   Area(sq mi): "+ area[j] 
									+ "    Pop Dens(people/sq mi land): " + populationDensity[j]);
			
			}
		
		}
	
	
	}


}
