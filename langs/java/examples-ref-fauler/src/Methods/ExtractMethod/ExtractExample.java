/**
	Think : _orders - что за тип?
*/
//import Vector?
package Methods.ExtractMethod;
import java.util.Vector;
import java.util.Enumeration;
class ExtractExample {
	void printOwing() { 
		Enumeration e = _orders.elements(); 
		double outstanding = 0.0;
		
		// вывод баннера
		System.out.println();
		System.out.println();
		System.out.println();

		// расчет задолжности
		while( e.hasMoreElements() ) {
			Order each = (Order)e.nextElement();
			outstanding += each.getAmount();
		}
		
		// вывод деталей
		System.out.println(" имя"+_name);
		System.out.println(" сумма "+outstanding);
	}
	private String _name;
	private Vector<Order> _orders;
	
	// ctr
	public ExtractExample() {
		_name = new String( "I" );
		_orders = new Vector<Order>();
	}
}