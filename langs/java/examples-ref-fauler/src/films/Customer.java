// Customer.java
/*
	1. поиск локальный переменных - выделение метода
	2. что использует метод? - перемещение метода
		выделенные метод не удалять!, но как протестили можно удалить
	3. переменная стала избыточной( лок. пер. дост. пробл., их нуж. сокр.
		) - замена перем. вызовом метода
	4. бизнес-правила начисления
	5. еще заменяем переменны вызовом метода
*/
package films;
import java.util.*;
public class Customer {
	public static final String ACCOUNTING_FOR = "Accounting for lease ";
	public static final String THE_AMOUNT =  "The amount of debts is ";
	public static final String YOU_HAVE_EARNED = "You have earned ";
	public static final String POINTS_FOR = " points for the activity";
	private String _name;
	private Vector _rentals = new Vector();	// replace to ArrayList

	// get-set 
	public Customer(String name) {
		_name = name; 
	}
	public void addRental(Rental arg) {
		_rentals.addElement(arg); 
	}
	public String getName() {
		return _name; 
	}

	// Methods
	public String statement() {
		double totalAmount = 0;
		int frequentRenterPoints = 0 ;
		Enumeration rentals = _rentals.elements();
		String result = ACCOUNTING_FOR +getName() + "\n";
		
		// For each rentals for customer
		while ( rentals.hasMoreElements() ) {
			double thisAmount = 0;
			Rental each = (Rental) rentals.nextElement();

			// добавить очки для активного арендатора
			frequentRenterPoints +=  each.getFrequentRenterPoints();

			// показать результаты для этой аренды
			result += "\t"+each.getMovie().getTitle()+"\t"+
				String.valueOf( each.getCharge())+"\n";
			totalAmount +=  each.getCharge();
		}

		// добавить нижний колонтитул
		result += THE_AMOUNT + String.valueOf(totalAmount) + "\n";
		result += YOU_HAVE_EARNED +String.valueOf(frequentRenterPoints)+ POINTS_FOR;
		return result;
	}
}