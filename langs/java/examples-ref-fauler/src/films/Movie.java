// Movie.java
package films;
public class Movie {
	public static final int CHILDRENS = 2;
	public static final int REGULAR = 0;
	public static final int NEW_RELEASE = 1;

	private String _title;
	private int _priceCode;  // выжные данные! в диаграмме они есть

	public Movie(String title, int priceCode) {
		_title = title;
		_priceCode = priceCode;
	}
	
	// за методы не считаются, это скорее добавка к 
	// свойствам
	public int getPriceCode() {
		return _priceCode;
	}
	public void setPriceCode(int arg) {  // переназначение
		_priceCode = arg;
	}
	public String getTitle() {
		return _title;
	}
}