class Account {
	// overdraft - перерасход - первышение кредита
	// сharge - плата
	// Overdrawn - овердрафта
	double overdraftCharge(){
		if(_type.isPremium() ){
			double result = 10;
			if( _daysOverdrawn > 7){ 
				result += (_daysOverdrawn - 7) * 0.85;
			}
			return result;
		}
		else return _daysOverdrawn * 1.75;
	}
	
	double dankCharge() {
		double result = 4.5;
		if(_daysOverdrawn > 0) {
			result += overdraftCharge();
		}
		return result;
	}
	private AccountType _type;
	private int _daysOverdrawn;
}