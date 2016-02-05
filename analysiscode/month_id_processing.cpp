int month_id (std::string month) {
	if (month.compare("Jan") == 0) {
		return 1;
	} else if (month.compare("Feb") == 0) {
		return 2;
	} else if (month.compare("Mar") == 0) {
		return 3;
	} else if (month.compare("Apr") == 0) {
		return 4;
	} else if (month.compare("May") == 0) {
		return 5;
	} else if (month.compare( "Jun") == 0) {
		return 6;
	} else if (month.compare("Jul") == 0) {
		return 7;
	} else if (month.compare("Aug") == 0) {
		return 8;
	} else if (month.compare("Sep") == 0) {
		return 9;
	} else if (month.compare("Oct") == 0) {
		return 10;
	} else if (month.compare("Nov") == 0) {
		return 11;
	} else if (month.compare("Dec") == 0) {
		return 12;
	} 
	return -1;
}
