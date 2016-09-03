#ifndef __MAIN_H__
#define __MAIN_H__

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

// For creating class device
#include <linux/device.h>

// For accessing device tree
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/platform_device.h>
#include <asm/io.h>


#include "logger.h"

MODULE_AUTHOR("tuna");
MODULE_LICENSE("GPL");

#define	DEF_MODULE_NAME			"tuna_i2c"
#define DEF_MODULE_CLASS_NAME	"tuna"
#define DEF_MODULE_1ST_MINOR	0
#define DEF_MODULE_DEVNUM		1

#define DEF_PERIPH_ADDR_BASE	0x3f000000
#define DEF_BSC0_ADDR_OFFSET	0x205000
#define DEF_BSC1_ADDR_OFFSET	0x804000
#define DEF_BSC2_ADDR_OFFSET	0x805000

// Mapulating bit
#define BIT_SET(reg, n)		*(reg) |= (1<<(n))	
#define BIT_CLR(reg, n)		*(reg) &= (~(1<<(n)))
#define BIT_TOG(reg, n)		*(reg) ^= (1<<(n))
#define BIT_TST(reg, n)		*(reg) &= (1<<n)

struct st_i2c_desc {
	void __iomem 	*m_pvBaseAddr;
	struct device 	*m_pxDevice;
	struct cdev		m_xCdev;
	struct resource	m_xResource;
	int 			m_iMinor;
	
	
};

int __init i2c_init(void);
void __exit i2c_exit(void);

int i2c_open(struct inode * pxInode, struct file * pxFile);
int i2c_close(struct inode * pxInode, struct file * pxFile);
ssize_t i2c_read(struct file *pxFile, char __user * pcBuf, size_t iSize, loff_t * plOfs);
ssize_t i2c_write(struct file *pxFile, const char __user * pcBuf, size_t iSize, loff_t * plOfs);

int i2c_cdev_setup(void);
int i2c_cdev_clean(void);
int iomem_probe(struct platform_device * pxDev);
int iomem_remove(struct platform_device * pxDev);



#endif
