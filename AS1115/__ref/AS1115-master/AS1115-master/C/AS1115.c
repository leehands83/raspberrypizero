// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// AS1115
// This code is designed to work with the AS1115_I2CL_3CE I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/LED-Display?sku=AS1115_I2CL_3CE#tabs-0-product_tabset-2

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main() 
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if ((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, PCA9536_BZ I2C address is 0x00(00)
	ioctl(file, I2C_SLAVE, 0x00);

	// Select Shutdown register(0x0C)
	// Normal Operation, Reset Feature Register to Default Settings(0x01)
	char config[2] = {0};
	config[0] = 0x0C;
	config[1] = 0x01;
	write(file, config, 2);
	// Select Intensity Control Register(0x0A)
	// Duty cycle = 1/16(0x04)
	config[0] = 0x0A;
	config[1] = 0x80;
	write(file, config, 2);
	// Select Feature Register(0x0E)
	// Enable HEX decoding(0x04)
	config[0] = 0x0E;
	config[1] = 0x04;
	write(file, config, 2);
	// Select Scan-limit Register(0x0B)
	// Display digits 0-2(0x02)
	config[0] = 0x0B;
	config[1] = 0x02;
	write(file, config, 2);
	// Select Decode-enable Register(0x09)
	// Set all digits to font decode(0x07)
	config[0] = 0x09;
	config[1] = 0x07;
	if(write(file, config, 2) !=2 )
	{
		printf("Erorr : Input/output Erorr \n");
		exit(1);
	}
	sleep(1);

	int data;
	int digit;
	for (data = 0; data < 16; data++)
	{
		for (digit = 0; digit < 2; digit++)
		{
			// Write data on the digits
			config[0] = digit + 1;
			config[1] = data;
			write(file, config, 2);
		}

		// Output to screen
		printf("Display on 7-Segment : %x \n", data);
		sleep(1);
	}
}
