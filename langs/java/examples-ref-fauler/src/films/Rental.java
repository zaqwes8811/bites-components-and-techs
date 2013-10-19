// Rental.java
package films;
public class Rental {
	private Movie _movie;
	private int _daysRented;

	// get-set 
	public Rental(Movie movie, int daysRented) {
		_movie = movie;
		_daysRented = daysRented;
	}
	public int getDaysRented() {
		return _daysRented;
	}
	public Movie getMovie() {
		return _movie;
	}
	
	public double getCharge( ){
		double result = 0;
		switch( getMovie().getPriceCode() ) {
			case Movie.REGULAR:
				if(getDaysRented() > 2) 
					result += (getDaysRented()-2)*1.5;
			break;
			case Movie.NEW_RELEASE:
				result +=  getDaysRented() * 3;
			break;
			case Movie.CHILDRENS:
				if(getDaysRented() > 3) 
					result += (getDaysRented()-3)*1.5;
			break;
		}
		return result;
	}
	public int getFrequentRenterPoints() {
		// плюсуем в любом случае, разница в том насколько
		if((getMovie().getPriceCode() == Movie.NEW_RELEASE) && 
			(getDaysRented() > 1) ) 
			return 2;
		else
			return 1;
	}
}