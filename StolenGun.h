/*
	STOLEN GUN CLASS
*/

#ifndef STOLENGUN_H_INCLUDED
#define STOLENGUN_H_INCLUDED

#include <string>

using namespace std;

class StolenGun
{
private:
	string serial; //Primary and unique key
	string make;  //Colt, Remington, Winchester etc
	string model;  //Remington's 700, Winchester's 1887, H&K's HK416 etc
	string caliber; //9mm, 5.56mm, .50 BMG etc
	string phoneNum; //Secondary key. contact phone number.
public:

	//Constructor//
	StolenGun() {}
	StolenGun(string s, string b, string m, string c, string p)
	{
		serial = s; make = b; model = m; caliber = c; phoneNum = p;
	}
	///////////////

	//Accessors//
	string getSerial() { return serial; }
	string getMake() { return make; }
	string getModel() { return model; }
	string getCaliber() { return caliber; }
	string getPhoneNum() { return phoneNum; }
	//////////

	//Mutators//
	void setSerial(string s) { serial = s; }
	void setMake(string b) { make = b; }
	void setModel(string m) { model = m; }
	void setCaliber(string c) { caliber = c; }
	void setPhoneNum(string p) { phoneNum = p; }

	~StolenGun(){ }
};

#endif // STOLENGUN_H_INCLUDED
