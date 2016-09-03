#include "main.h"

static dev_t					g_devno;
static struct class				*g_px_class_dev=NULL;
static struct st_i2c_desc		g_i2c_desc[DEF_MODULE_DEVNUM];
static struct file_operations 	g_fops = {
	.owner		= THIS_MODULE,
	.open 		= i2c_open,
	.release	= i2c_close,
	.read		= i2c_read,
	.write		= i2c_write
};

static const struct of_device_id const_i2c_match_table[] = {
	{.compatible = "brcm,bcm2835-gpiomem"},
	{}
};

static struct platform_driver 	g_platform_driver = {
	.driver = {
		.owner 			= 	THIS_MODULE,
		.name			= 	DEF_MODULE_NAME,
		.of_match_table	=	const_i2c_match_table
	},
	.remove = __exit_p(iomem_remove)
};

module_init(i2c_init);
module_exit(i2c_exit);

int __init i2c_init(void) {
	
	int _errno, _cnt;
	
	_errno 	= 0;
	_cnt	= 0;
	
	LOG_NOTI();
								
	_errno = i2c_cdev_setup();
	_errno = platform_driver_probe(&g_platform_driver, iomem_probe);
	
	return _errno;
}

void __exit i2c_exit(void) {
	LOG_NOTI();
	platform_driver_unregister(&g_platform_driver);
	i2c_cdev_clean();
}

int i2c_open(struct inode * pxInode, struct file * pxFile) {
	return 0;
}

int i2c_close(struct inode * pxInode, struct file * pxFile) {
	return 0;
}

ssize_t i2c_read(struct file *pxFile, char __user * pcBuf, size_t iSize, loff_t * plOfs) {
	return 1;
}

ssize_t i2c_write(struct file *pxFile, const char __user * pcBuf, size_t iSize, loff_t * plOfs) {
	return 1;
}

int i2c_cdev_setup(void) {
	int _errno, _cnt;
	dev_t _devno;
	
	_errno 	= 0;
	_cnt	= 0;
	
	LOG_NOTI();
	
	_errno = alloc_chrdev_region(&g_devno
								,DEF_MODULE_1ST_MINOR
								,DEF_MODULE_DEVNUM
								,DEF_MODULE_NAME);
	if (_errno) {
		LOG_ERRO("Cannot allocate new device");
		return -1;
	} else {
		LOG_NOTI("%d - %d ", MAJOR(g_devno), MINOR(g_devno));
	}
	
	// creating classin file system
	g_px_class_dev = NULL;
	g_px_class_dev = class_create(THIS_MODULE, DEF_MODULE_CLASS_NAME);
	if (NULL == g_px_class_dev) {
		LOG_ERRO();
		unregister_chrdev_region(g_devno, DEF_MODULE_DEVNUM);
		return -1;
	}
	
	
	// Add devices into node
	for (_cnt=0; _cnt < DEF_MODULE_DEVNUM; _cnt++) {
		// make devno
		_devno = MKDEV(MAJOR(g_devno), DEF_MODULE_1ST_MINOR + _cnt);
		
		// initialize cdev		
		cdev_init(&(g_i2c_desc[_cnt].m_xCdev),&g_fops);
		g_i2c_desc[_cnt].m_xCdev.owner = THIS_MODULE;
		_errno = cdev_add(&(g_i2c_desc[_cnt].m_xCdev), _devno, 1);
		
		if (_errno) {
			LOG_ERRO();
			unregister_chrdev_region(g_devno, DEF_MODULE_DEVNUM);
			return -1;
		}
		
		// add to system node
		g_i2c_desc[_cnt].m_pxDevice = device_create(g_px_class_dev
													,NULL
													,_devno
													,NULL
													,DEF_MODULE_NAME"%d"
													,DEF_MODULE_1ST_MINOR+_cnt);
		if (NULL == g_i2c_desc[_cnt].m_pxDevice) {
			LOG_ERRO();
			unregister_chrdev_region(g_devno, DEF_MODULE_DEVNUM);
			return -1;
		}
	}
	
	return _errno;
}

int i2c_cdev_clean(void) {
	int _errno, _cnt;
	dev_t _devno;
	
	_errno 	= 0;
	_cnt	= 0;
	
	LOG_NOTI();
	
	for (_cnt=0; _cnt < DEF_MODULE_DEVNUM; _cnt++) {
		// make devno
		_devno = MKDEV(MAJOR(g_devno), DEF_MODULE_1ST_MINOR + _cnt);
		
		// remove device from class file system
		if (NULL != g_px_class_dev) {
			cdev_del(&(g_i2c_desc[_cnt].m_xCdev));
			device_destroy(g_px_class_dev, _devno);
		}
	}
	class_destroy(g_px_class_dev);
	unregister_chrdev_region(g_devno, DEF_MODULE_DEVNUM);
	return _errno;
}

int iomem_probe(struct platform_device * pxDev) {
	int _errno, _cnt;
	
	_errno 	= 0;
	_cnt	= 0;
	
	LOG_NOTI();
	
	// get resource
	_errno = of_address_to_resource(pxDev->dev.of_node, 0, &(g_i2c_desc[0].m_xResource));
	if (_errno) {
		LOG_ERRO("Cannot access resource");
		unregister_chrdev_region(g_devno, DEF_MODULE_DEVNUM);
		return -1;
	} else {
		LOG_NOTI("Matching device description");
	}
	
	// get iomem address
	g_i2c_desc[0].m_pvBaseAddr = NULL;
	g_i2c_desc[0].m_pvBaseAddr = of_iomap(pxDev->dev.of_node, 0);
	
	if (NULL == g_i2c_desc[0].m_pvBaseAddr) {
		LOG_ERRO("Cannot acces iomap");
		unregister_chrdev_region(g_devno, DEF_MODULE_DEVNUM);
		return -1;
	} else {
		LOG_NOTI("Attacked iomem");
	}
	
	return _errno;
}

int iomem_remove(struct platform_device * pxDev) {
	int _errno, _cnt;
	
	_errno 	= 0;
	_cnt	= 0;
	
	if (NULL != g_i2c_desc[0].m_pvBaseAddr) {
		iounmap(g_i2c_desc[0].m_pvBaseAddr);
	}
	
	return _errno;
}


