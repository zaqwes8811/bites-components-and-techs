/**
	Think : _orders - что за тип?
*/
//import Vector?
package Methods.ReplaceTempWithQuery;
class ReplaceTempWithQueryExample {
	double getPrice() { 
		int basePrice = _quantity * _itemPrice;
		double discountFactor;
		if( basePrice > 1000 ) discountFactor = 0.95;
		else discountFactor = 0.98;
		return basePrice * discountFactor;

	}
	private int _quantity, _itemPrice;
}