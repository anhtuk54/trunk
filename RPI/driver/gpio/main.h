// Kernel supports
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/uaccess.h>
#include <linux/ioport.h>			// For using iomem, ioport
#include <linux/interrupt.h>		// For using interrupt 
#include <linux/interrupt.h>		// For using interrupt 
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <asm/io.h>

// User definitions
#include "logger.h"					// Logger

// Module's information
MODULE_LICENSE("GPL");
MODULE_AUTHOR("tuna");

// Definitions
#define DEF_IO_MODULE_NAME			"io_dev"
#define DEF_IO_MODULE_NODE_NAME		"io_dev"
#define	DEF_IO_MODULE_FIRST_MINOR	0
#define	DEF_IO_MODULE_DEVNUM		1


#define DEF_BASE_PERIPH		(unsigned long)0x3f000000
#define DEF_BASE_GPIO		(DEF_BASE_PERIPH + (unsigned long)0x200000)
#define DEF_BLOCK_SIZE		4*(1024)

#define BIT_SET(reg, n)		*(reg) |= (1<<(n))	
#define BIT_CLR(reg, n)		*(reg) &= (~(1<<(n)))
#define BIT_TOG(reg, n)		*(reg) ^= (1<<(n))
#define BIT_TST(reg, n)		*(reg) &= (1<<n)

// Core struct device data
struct io_stData {
	struct cdev			m_cdev;			// for char device specifications
	struct resource 	m_res;			// for getting platform resouce
	struct device		*m_pxDevice;	// for creating device in its owner class
	void 				*m_pvirt_base;	// for memory manipulating
};

// Init/Deinit module
int io_init(void);
void io_clean(void);

// For file operations
int io_open(struct inode *pxInode, struct file* pxFile);
int io_release(struct inode *pxInode, struct file* pxFile);
ssize_t io_read(struct file* pxFile, char __user *pcBuffer, size_t uLen, loff_t *plOfs);
ssize_t io_write(struct file* pxFile, const char __user *pcBuffer, size_t uLen, loff_t *plOfs);

// For setting up character device
int iodev_setup(struct io_stData *pxDev);
int iodev_clean(struct io_stData *pxDev);

// For handling iomem
int iodev_probe_iomem(struct platform_device * pxPlatfDev);
int iodev_remove_iomem(struct platform_device * pxPlatfDev);
int iodev_init_gpio(void);



