#ifndef __LOGGER_H__
#define __LOGGER_H__

#define LOG_NOTI(msg, ...)	printk(KERN_NOTICE 	"[NOTI]][%s][%s][%d]: " msg "\n",__FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOG_WARN(msg, ...)	printk(KERN_ALERT 	"[WARN]][%s][%s][%d]: " msg "\n",__FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOG_ERRO(msg, ...)	printk(KERN_ERR 	"[ERRO]][%s][%s][%d]: " msg "\n",__FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#endif	// LOGGER_H__
