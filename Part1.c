#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

/* This function is module entry point. */
int simple_init(void) {
	printk(KERN_INFO "Loading Example Module For CS 543 Assignment 2, Part I.\n");
	return 0;
}

/* This function is module exit point. */
void simple_exit(void) {
	printk(KERN_INFO "Removing Example Module For CS 543 Assignment 2, Part I.\n");
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

/* This part represents details about software licnse, module description, and author. */
MODULE_LICENSE("CS543");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SHANGQI WU");
