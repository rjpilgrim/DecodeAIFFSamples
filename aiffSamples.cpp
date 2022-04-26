#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class int24
{
public:
	unsigned char dat[3];
    int24() {}
    int24(int val) {operator=(val);}
    int24& operator=(int val) {dat[0]=val;dat[1]=val>>8;dat[2]=val>>16;dat[2]|=val>>31<<7;return *this;}
    operator int() const {return (dat[0])|(dat[1]<<8)|(dat[2]<<16)|(dat[2]&0x80?-1<<24:0);}
    int24& operator++() {operator=(*this+1); return *this;}
    int24 operator++(int) {int24 t=*this;operator=(*this+1); return t;}
    int24& operator--() {operator=(*this+1); return *this;}
    int24 operator--(int) {int24 t=*this;operator=(*this-1); return t;}
    int24& operator+=(int rhs) {operator=(*this+rhs); return *this;}
    int24& operator-=(int rhs) {operator=(*this-rhs); return *this;}
    int24& operator*=(int rhs) {operator=(*this*rhs); return *this;}
    int24& operator/=(int rhs) {operator=(*this/rhs); return *this;}
    int24& operator%=(int rhs) {operator=(*this%rhs); return *this;}
    int24& operator>>=(int rhs) {operator=(*this>>rhs); return *this;}
    int24& operator<<=(int rhs) {operator=(*this<<rhs); return *this;}
    int24& operator|=(int rhs) {operator=(*this|rhs); return *this;}
    int24& operator&=(int rhs) {operator=(*this&rhs); return *this;}
    int24& operator^=(int rhs) {operator=(*this^rhs); return *this;}
    int24& operator|=(int24 rhs) {dat[0]|=rhs.dat[0]; dat[1]|=rhs.dat[1]; dat[2]|=rhs.dat[2]; return *this;}
    int24& operator&=(int24 rhs) {dat[0]&=rhs.dat[0]; dat[1]&=rhs.dat[1]; dat[2]&=rhs.dat[2]; return *this;}
    int24& operator^=(int24 rhs) {dat[0]^=rhs.dat[0]; dat[1]^=rhs.dat[1]; dat[2]^=rhs.dat[2]; return *this;}
};

int main(int argc, char * argv[]) {
	if (argc < 2) {
		return -1;
	}
	std::ifstream file;
	file.open(argv[1], std::ios::binary);
	if (!file.is_open()) {
		return -1;
	}
	int i = 0;
	int ssnd = 0;
	while (file && i < 256) {
		char output;
		file.read(&output, 1);
		if (output == 83) {
			if (ssnd == 0) {
				ssnd = 1;
			}
			else if (ssnd == 1) {
				ssnd = 2;
			}
			else {
				ssnd = 0;
			}
		}
		else if (output == 78) {
			if (ssnd == 2) {
				ssnd = 3;
			}
			else {
				ssnd = 0;
			}
		}
		else if (output == 68) {
			if (ssnd == 3) {
				ssnd = 4;
				break;
			}
			else {
				ssnd = 0;
			}
		}
		i++;
	}
	if (ssnd != 4) {
		return -1;
	}
	for (int i = 0; i < 12; i++) {
		char output;
		file.read(&output, 1);
	}
	i = 0;
	while (file && i < 256 ) {
		char output1;
		char output2;
		char output3;
		file.read(&output1, 1);
		file.read(&output2, 1);
		file.read(&output3, 1);
		int24 my24;
		my24.dat[2] = output1;
		my24.dat[1] = output2;
		my24.dat[0] = output3;
		std::cout << i << ": " << (int)my24 << std::endl;
		i++;
	}
	file.close();
	return 0;
}