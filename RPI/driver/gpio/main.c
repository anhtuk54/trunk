#include "main.h"

/***********************************************************************
 * 				Descriptions:	Global variables
 * 				
 * 
***********************************************************************/
// Decription of device in device tree.
static const struct of_device_id const_iodev_match[] = {
	{.compatible	=	"brcm,bcm2835-gpiomem"},
	{},
};

// Assign operations into platform driver for probing device driver in device tree.
static struct platform_driver 	g_platform_driver = {
	.driver	= {
		.owner 			= THIS_MODULE,
		.name			= DEF_IO_MODULE_NAME,
		.of_match_table	= of_match_ptr(const_iodev_match),
	},
	.remove	= __exit_p(iodev_remove_iomem)
};

// File operations with this module.
static struct file_operations g_fops = {
	.owner		= THIS_MODULE,
	.open 		= io_open,
	.release	= io_release,
	.read		= io_read,
	.write		= io_write
};

static dev_t					g_devno;							// major and minor number of this device
static struct io_stData 		g_io_stData[DEF_IO_MODULE_DEVNUM];	// private data structure of this device
static struct class 			*g_pxDevClass=NULL;					// for creating a class device


/***********************************************************************
 * 				Descriptions: Set up and clean up class of device
 * 
 * 
***********************************************************************/
int iodev_setup(struct io_stData *pxDev) {
	// Variables
	int _errno, _cnt, _devno, _major;
	
	// Initializing variables
	_errno	= 0;
	_cnt 	= 0;
	_devno 	= 0;
	_major 	= MAJOR(g_devno);
	
	// Creating device node
	g_pxDevClass = class_create(THIS_MODULE, DEF_IO_MODULE_NAME);
	if (NULL == g_pxDevClass) {
		LOG_ERRO();
		return -1;
	}
	
	for (_cnt=0; _cnt < DEF_IO_MODULE_DEVNUM; _cnt ++) {
		// get device no
		_devno = MKDEV(_major, DEF_IO_MODULE_FIRST_MINOR + _cnt);
		
		// initilizing
		cdev_init(&(pxDev[_cnt].m_cdev) ,&g_fops);
		pxDev[_cnt].m_cdev.owner	= THIS_MODULE;
		
		// adding device
		_errno = cdev_add(&(pxDev[_cnt].m_cdev), _devno, 1);
		if(_errno) {
			return _errno;
		}
		
		// adding into node
		pxDev[_cnt].m_pxDevice = device_create(g_pxDevClass \
												, NULL		\
												,_devno		\
												,NULL		\
												,DEF_IO_MODULE_NODE_NAME"%d"	\
												,DEF_IO_MODULE_FIRST_MINOR + _cnt);
		if (NULL == pxDev[_cnt].m_pxDevice) {
			LOG_ERRO();
			return -1;
		}
	}
	LOG_NOTI();
	return _errno;
}

int iodev_clean(struct io_stData *pxDev) {
	// Variables
	int _errno, _cnt, _devno, _major;
	
	// Initializing variables
	_errno	= 0;
	_cnt 	= 0;
	_devno 	= 0;
	_major 	= MAJOR(g_devno);
	
	for (_cnt=0; _cnt < DEF_IO_MODULE_DEVNUM; _cnt ++) {
		// get device no
		_devno = MKDEV(_major, DEF_IO_MODULE_FIRST_MINOR + _cnt);
		
		// deleting device
		cdev_del(&(pxDev[_cnt].m_cdev));
		
		// removing from node
		device_destroy(g_pxDevClass, _devno);
	}
	
	class_destroy(g_pxDevClass);
	
	return _errno;
}


/***********************************************************************
 * 
 * 
 * 
***********************************************************************/
int iodev_probe_iomem(struct platform_device * pxPlatfDev) {
	// Variables
	int _errno;

	// Initializing variables
	_errno = 0;

	// Finding address range in device tree
	_errno = of_address_to_resource(pxPlatfDev->dev.of_node,0,&(g_io_stData[0].m_res));
	if (_errno) {
		LOG_ERRO ("Cannot find out any device as description");
		unregister_chrdev_region(g_devno ,DEF_IO_MODULE_DEVNUM);
		return _errno;
	} else {
		LOG_NOTI("Found out device as description");
	}
	
	
	// Assign memory into this device
	g_io_stData[0].m_pvirt_base = NULL;
	g_io_stData[0].m_pvirt_base = of_iomap(pxPlatfDev->dev.of_node,0);
	
	if (NULL == g_io_stData[0].m_pvirt_base) {
		LOG_ERRO("Cannnot attack memory address");
		//release_mem_region(g_io_stData[0].m_res.start, resource_size(&(g_io_stData[0].m_res)));
		unregister_chrdev_region(g_devno ,DEF_IO_MODULE_DEVNUM);
		return -ENOMEM;
	} else {
		LOG_NOTI("virtual base address: %08x",(((unsigned long __iomem *)(g_io_stData[0].m_pvirt_base))));
		LOG_NOTI("Attacking memory address successful");
	}
	// Return
	return _errno;
}

int iodev_remove_iomem(struct platform_device * pxPlatfDev) {
	// Variables
	int _errno;

	// Initializing variables
	_errno = 0;
	
	
	// Unassign memories
	if (NULL != g_io_stData[0].m_pvirt_base) {
		iounmap (g_io_stData[0].m_pvirt_base);
		//release_mem_region(g_io_stData[0].m_res.start, resource_size(&(g_io_stData[0].m_res)));
	}
	
	// Return
	return _errno;
}

int iodev_init_gpio(void) {
	// setup gpio port
	BIT_SET((unsigned long*)(g_io_stData[0].m_pvirt_base),12);
	return 0;
}

/***********************************************************************
 * 
 * 
 * 
***********************************************************************/
int io_open(struct inode *pxInode, struct file* pxFile) {	
	struct io_stData *_pDev;
	_pDev = container_of(pxInode->i_cdev, struct io_stData, m_cdev);
	pxFile->private_data = _pDev;
	return 0;
}

int io_release(struct inode *pxInode, struct file* pxFile) {
	return 0;
}

ssize_t io_read(struct file* pxFile, char __user *pcBuffer, size_t uLen, loff_t *plOfs) {
	return (ssize_t)1;
}

ssize_t io_write(struct file* pxFile, const char __user *pcBuffer, size_t uLen, loff_t *plOfs) {
	LOG_NOTI("cmd: %c", pcBuffer[0]);
	switch (pcBuffer[0]) {
		case '0': {
			LOG_NOTI("Clear gpio 4");
			BIT_SET((unsigned long*)(g_io_stData[0].m_pvirt_base)+10,4);
		}
		break;
		case '1': {
			LOG_NOTI("Set gpio 4");
			BIT_SET((unsigned long*)(g_io_stData[0].m_pvirt_base)+7,4);
		}
		break;
		default : {
			LOG_NOTI("Invalid command");
		}
		break;
	}
	return sizeof(pcBuffer);
}


/***********************************************************************
 * 
 * 
 * 
***********************************************************************/
int io_init(void) {
	
	// Variables
	int _errno;
	
	// Initializing variables
	_errno	= 0;
	
	// Injection
	LOG_NOTI("Injection.");
	
	// Regitering device 
	_errno = alloc_chrdev_region(\
								&g_devno\
								,DEF_IO_MODULE_FIRST_MINOR\
								,DEF_IO_MODULE_DEVNUM\
								,DEF_IO_MODULE_NAME);
	if (_errno) {
		LOG_ERRO();
		return _errno;
	} else {
		LOG_NOTI("Module no Major: %d - Minor: %d", MAJOR(g_devno), MINOR(g_devno));
	}
	
	// Setting up device
	_errno = iodev_setup(g_io_stData);
	
	if (_errno) {
		LOG_ERRO();
	}
	
	// Assign iomem address to device
	_errno = platform_driver_probe(&g_platform_driver, iodev_probe_iomem);
	if (_errno) {
		return -1;
	}
	// Initializing GPIO 
	iodev_init_gpio();
	
	// Ejection
	LOG_NOTI("Ejection");
	return _errno;
}

void io_clean(void) {
	// Variables
	int _errno;
	
	// Initializing variables
	_errno = 0;
	// Injection
	LOG_NOTI("Injection.");
	
	// Unassign iomem address to device
	platform_driver_unregister(&g_platform_driver);
	
	// Clean up device
	iodev_clean(g_io_stData);
	
	// Unregitering device
	unregister_chrdev_region(g_devno ,DEF_IO_MODULE_DEVNUM);
	
	// Ejection
	LOG_NOTI("Ejection");
}


/***********************************************************************
 * 
 * 
 * 
***********************************************************************/
module_init(io_init);
module_exit(io_clean);
