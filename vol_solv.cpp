#include <iostream>
#include <cmath>
#include <string>

using namespace std;
double bs_price(double s0, double K, double time, double vol, double r, bool call);
void bisection(double &error, double opt_price, double &upper_bs, double &lower_bs, double &upper_bound, double &lower_bound, double s0, double K, double time, double r, bool call);
double normalCDF(double value);

int main() {
	double time, s0, vol, K, opt_price, r, upper_bs, lower_bs;
	double upper_bound = 1.00;
	double lower_bound = 0.001;
	double error_bound = 0.00001;
	double error;
	string type_opt;
	bool call = true;

	do {
		cout << "Call or put option: ";
		getline(cin, type_opt);
	} while (!(type_opt == "call" || type_opt == "put"));

	if (type_opt == "put") {
		call = false; //call is a boolean
	}

	cout << "Enter the option price: ";
	cin >> opt_price;

	cout << "Enter the stock price: ";
	cin >> s0;

	cout << "Enter the strike price: ";
	cin >> K;

	cout << "Enter the time: ";
	cin >> time;

	cout << "Enter the interest rate: ";
	cin >> r;

	upper_bs = bs_price(s0, K, time, upper_bound, r, call);
	lower_bs = bs_price(s0, K, time, lower_bound, r, call);

	do {
		bisection(error, opt_price, upper_bs, lower_bs, upper_bound,lower_bound, s0, K, time, r, call);
	} while (error >= error_bound);
	vol = (upper_bound + lower_bound) / 2;
	cout << "The implied volatility is "<< vol << endl;
	system("pause");
	return 0;
}

double bs_price(double s0, double K, double time, double vol, double r, bool call) {
	double d1, d2;
	d1 = (log(s0 / K) + (r + pow(vol, 2) / 2)*time) / (vol*sqrt(time));
	d2 = d1 - vol * sqrt(time);

	if (call == true) {
		return s0 * normalCDF(d1) - K * exp(-r * time)*normalCDF(d2);
	}
	else {
		return K * exp(-r * time)*normalCDF(-d2) - s0 * normalCDF(-d1);
	}
}

void bisection(double &error, double opt_price, double &upper_bs, double &lower_bs, double &upper_bound, double &lower_bound, double s0, double K, double time, double r, bool call) {
	double mid_point, mid_bs;
	mid_point = (upper_bound + lower_bound) / 2;
	mid_bs = bs_price(s0, K, time, mid_point, r, call);

	if (mid_bs - opt_price>0) {
		upper_bound = mid_point;
		upper_bs = mid_bs;
	}
	else {
		lower_bound = mid_point;
		lower_bs = mid_bs;
	}

	error = abs(mid_bs - opt_price);
}

double normalCDF(double value) {
	return 0.5 * erfc(-value * sqrt(0.5));
}
