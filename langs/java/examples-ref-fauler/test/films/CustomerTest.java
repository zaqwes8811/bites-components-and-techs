// CustomerTest.java
/**
	Questions and Troubles: 
		- Насколько полный тест
		- Создание тестовых надотров
		
	Warnings :
		- тест еще плохой
*/
package films;
import org.junit.*;
import junit.framework.*;
import junit.textui.TestRunner;
import static org.junit.Assert.*;
import java.util.*;

public class CustomerTest  extends TestCase {
	public CustomerTest(String testName) {
		super(testName);
	 }
	public static void testOneCustomer( ) { 
		// Create the movies name list
		List<String>  moveNames = new ArrayList<String>();
		moveNames.add("Child");
		moveNames.add("Regular");
		moveNames.add("New");

		// Packing movies
		List<Movie>  aMovies =  new ArrayList<Movie>();
		String testCustomerSummary = new String("");
		for(String item : moveNames) {
			Movie aMove = new Movie( item, Movie.CHILDRENS );
			aMovies.add( aMove );
			
			// Data collection for the test
			testCustomerSummary += "\t"+aMove.getTitle()+"\t"+"10.5\n";
		}

		// Rentals List
		List<Rental> aRentals = new ArrayList<Rental>();
		for( Movie item : aMovies ) {
			Rental aRental =  new Rental( item, 10 );
			aRentals.add( aRental );
		}

		// Create aCustomer
		String nameCustomer =  new String( "Salvador" );
		Customer aCustomer = new Customer( nameCustomer );
		for( Rental item : aRentals) {
			aCustomer.addRental( item );
		}

		// Collect the test results
		String ideal = new String(Customer.ACCOUNTING_FOR+ nameCustomer + "\n"+
				testCustomerSummary+
				Customer.THE_AMOUNT+"31.5\n"+
				Customer.YOU_HAVE_EARNED+"3"+Customer.POINTS_FOR
			);

		// Get the report and test it
		String result =  aCustomer.statement();
		assertEquals( result, ideal);
	}
	// Main()
	public static void main(String[] args) {
		TestRunner runner = new TestRunner();
		TestSuite suite = new TestSuite();
		suite.addTest(new CustomerTest("testOneCustomer"));
		runner.doRun(suite);
	}
}

/**
  1. выделение метода zz - локальные переменные
  2. в выделенном методе нет данных класса его содержещего
  3. замена переменной вызовом метода (thisAmount - избыточная), 
    но теряем в производительности
  4. с расчетом бонуса тоже самое, но не передаем, т.к. переменная неизм
*/
