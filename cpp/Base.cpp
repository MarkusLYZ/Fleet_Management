#include "Base.h"

Base::Base(string id, string des, int t) {
	ID = id;
	Destination = des;
	time = t;
}

string Base::getID() {
	return ID;
}
string Base::getDestination() {
	return Destination;
}
int Base::getTime() {
	return time;
}
void Base::setID(string id) {
	ID = id;
}
void Base::setTime(int t) {
	time = t;
}
void Base::setDestination(string dest) {
	Destination = dest;
}

