/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#include <ralink_i2c_drv.h>

////////////////////////////////////////////////////////////////////////////////
// I2C PROCESS
////////////////////////////////////////////////////////////////////////////////

static void show_usage(char *cmd)
{
	printf("Usage: %s DEV CHIP-ADDR R/W DATA-ADDR [VALUE] \n", cmd);
	printf("Set I2C registers\n\n");
	printf("            DEV     i2c dev name\n");
	printf("            ADDR    0x03 - 0x77\n");
	printf("            R/W     r or w\n");
}

int ralink_i2c_main(int argc, char **argv)
{
    char dev[64];
	int ret = 1, idx;
    int fd = -1;
    int rw = 0;
    unsigned int value = 0;
    unsigned int chipaddr, addr;

	if (argc < 5) {
		show_usage(argv[0]);
		return 1;
	}

	if (strlen(argv[1]) < 2) {
		show_usage(argv[0]);
		return 1;
	}
    if (argv[1][0] == '/') {
        snprintf(dev, sizeof(dev)-1, argv[1]);
    } else {
        snprintf(dev, sizeof(dev)-1, "/dev/%s", argv[1]);
    }
    fd = open(dev, O_RDWR);
    if (fd < 0) {
        printf("Could not open %s\n", dev);
        return -1;
    }

    chipaddr = (unsigned int)atoi(argv[2]);
    if (chipaddr < 0x3 || chipaddr > 0xfe) {
        printf("CHIP-ADDR is invalid!\n");
        goto error;
    }

    if (argv[3] && strlen(argv[3])) {
        if (argv[3][0] == 'r') {
            rw = 1;
        } else if (argv[3][0] == 'w') {
            rw = 2;
        }
    }
    if (! rw) {
        printf("RW must be r or w\n");
        goto error;
    }

    addr = (unsigned int)atoi(argv[4]);

    if (rw == 2) {
        if (!argv[5]) {
          printf("write data must be present!\n");
          goto error;
        }
        value = (unsigned int)atoi(argv[5]);
    }

    if (rw == 1) {          /* i2c read */
        ret  = ioctl(fd, RT2880_I2C_SET_ADDR_BYTES, 1);
        ret |= ioctl(fd, RT2880_I2C_SET_ADDR, chipaddr);
        ret |= ioctl(fd, RT2880_I2C_READ, addr);
        if (ret) {
          printf("i2c read error! ret = %u\n", ret);
        }
    } else if (rw == 2) {   /*  i2c write*/
        I2C_WRITE wdata;
        wdata.address = addr;
        wdata.value   = value;
        wdata.size    = 1;
        ret  = ioctl(fd, RT2880_I2C_SET_ADDR_BYTES, 1);
        ret |= ioctl(fd, RT2880_I2C_SET_ADDR, chipaddr);
        ret |= ioctl(fd, RT2880_I2C_WRITE, &wdata);
        if (ret) {
          printf("i2c write error! ret = %u\n", ret);
        }
    }

error:

    if ( fd > 0) {
        close(fd);
        fd = -1;
    }

	return ret;
}
