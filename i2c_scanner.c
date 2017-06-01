#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Lack of I2C device path as an argument. Example \"/dev/i2c-1\": \n");
        return 1;
    }
    else if (argc > 2)
    {
        fprintf(stderr, "Too many arguments, should be only one, I2C device path. Example \"/dev/i2c-1\": \n");
        return 2;
    }

    const char *i2c_dev_path = argv[1];
    int i2c_bus_file_hand = 0;
    i2c_bus_file_hand = open(i2c_dev_path, O_RDWR);
    if (i2c_bus_file_hand < 0 )
    {
        fprintf(stderr, "Can not open I2C Bus at: %s\n", i2c_dev_path);
        return 3;
    }
    else
    {
        printf("I2C Bus available at: %s\n", i2c_dev_path);
    }
    
    unsigned char slaves_counter = 0;
    for (unsigned char i = 0; i < 128; ++i)
    {
        const char slave_address = i;
	    if (ioctl(i2c_bus_file_hand, I2C_SLAVE, slave_address) >= 0 )
	    {
            if (write(i2c_bus_file_hand, NULL, 0) == 0)
            {
		        printf("I2C slave found under address: %#02x\n", slave_address);
                ++slaves_counter;
            }
	    }
    }
    
    printf("Number of I2C slaves found: %u\n", slaves_counter);
    return 0;
}

