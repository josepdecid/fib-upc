bool es_equilibrat(int n) {
	int eq = 0, ps = 1;
	while (n != 0) {
		if (ps%2 != 0) eq = eq + n%10;
		else eq = eq - n%10;
		n = n/10;
		++ps;
	}
	if (eq == 0) return true;
	else return false;
}