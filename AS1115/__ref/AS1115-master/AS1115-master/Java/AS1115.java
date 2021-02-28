// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// AS1115
// This code is designed to work with the AS1115_I2CL_3CE I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/LED-Display?sku=AS1115_I2CL_3CE#tabs-0-product_tabset-2

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class AS1115
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus Bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, AS1115 I2C address is 0x00(00)
		I2CDevice device = Bus.getDevice(0x00);

		// Select Shutdown register, 0x0C(12)
		// Normal Operation, Reset Feature Register to Default Settings
		device.write(0x0C,(byte)0x01);
		// Select Intensity Control Register, 0x0A(10)
		// Duty cycle = 1/16
		device.write(0x0A,(byte)0x80);
		// Select Feature Register, 0x0E(14)
		// Enable HEX decoding
		device.write(0x0E,(byte)0x04);
		// Select Scan-limit Register, 0x0B(11)
		// Display digits 0-2
		device.write(0x0B,(byte)0x02);
		// Select Decode-enable Register, 0x09(09)
		// Set all digits to font decode
		device.write(0x09,(byte)0x07);
		Thread.sleep(500);
		
		for (int data = 0; data < 16; data++)
		{
			for (int digit = 0; digit < 2; digit++)
			{
				// Write data on the digits
				device.write(digit + 1, (byte)data);
			}
			// Output to screen
			System.out.printf("Display on 7-Segment : %s %n", Integer.toHexString(data));
			Thread.sleep(800);
		}
	}
}