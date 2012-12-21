/*
 * i2c.cpp
 *
 *  Created on: Dec 19, 2012
 *      Author: chris
 */

#include "i2c.h"
#include <iostream>

char *end;
int res, i2cbus, address, size, file;
int daddress;
char filename[20];

namespace std {

i2c::i2c(int i2cbus, int address) {
	size = I2C_SMBUS_BYTE;
	sprintf(filename, "/dev/i2c-%d", i2cbus);
//	cout << "filename" << endl;
	file = open(filename, O_RDWR);

	if (file < 0) {
		if (errno == ENOENT) {
			cout << "Error: Could not open file, ENOENT" << endl;
//			fprintf(stderr, "Error: Could not open file "
//					"/dev/i2c-%d: %s\n", i2cbus, strerror(ENOENT));
		} else {
			cout << "Error: Could not open file, errno" << endl;
//			fprintf(stderr, "Error: Could not open file "
//			"`%s': %s\n", filename, strerror(errno));
			if (errno == EACCES)
				fprintf(stderr, "Run as root?\n");
		}
		exit(1);
	}

	if (ioctl(file, I2C_SLAVE, address) < 0) {
		cout << "Error: Could not set address" << endl;
//		fprintf(stderr, "Error: Could not set address to 0x%02x: %s\n", address,
//				strerror(errno));
		return;
	}
	/*
	 res = i2c_smbus_write_byte(file, daddress);
	 if (res < 0) {
	 fprintf(stderr, "Warning - write failed, filename=%s, daddress=%d\n",
	 filename, daddress);
	 }
	 */
//
//	res = i2c_smbus_read_byte_data(file, daddress);
//
//	if (res < 0) {
//		fprintf(stderr, "Error: Read failed, res=%d\n", res);
//		exit(2);
//	}
//	printf("i2c0x%02x (%d)\n", res, res);
//	exit(0);
	return;
}

__u8 i2c::getByte(int dataAddress) {
	return i2c_smbus_read_byte_data(file, daddress);
}

i2c::~i2c() {
//	close(file);
}

} /* namespace std */
