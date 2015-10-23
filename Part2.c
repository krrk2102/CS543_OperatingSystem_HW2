#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/slab.h>

/* This is the struct of birthday list, described on the book. */
struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
};

/* Declare the head of birthday list. */
static LIST_HEAD(birthday_list);

/* This function is module entry point. */
int birthday_init(void) {
	// Declare pointers for data insersion and traversing.
	struct birthday *person, *pointer;
	// Variants for birthday list construction. 
	int i = 0, dd = 1, mm = 1, yyyy = 1970, counter = 0;
	// Output this module is loaded to kernel log. 
	printk(KERN_INFO "Loading Example Module For CS 543 Assignment 2, Part II.\n");
	// Create a birthday list of 5 elements by a for loop. 
	for (i = 0; i < 5; i++) {
		// Allocate pointer with memory for elements in birthday list. 
		person = kmalloc(sizeof(*person), GFP_KERNEL);
		person->day = dd;
		person->month = mm;
		person->year = yyyy;
		// Initialize pointers in list_head of the new element. 
		INIT_LIST_HEAD(&person->list);
		// Add new element to the end of birthday list.
		list_add_tail(&person->list, &birthday_list);
		dd += 5; // Days will be 1, 6, 11, 16, 21.
		mm += 2; // Months will be 1, 3, 5, 7, 9.
		yyyy += 7; // Years will be 1970, 1977, 1984, 1991, 1998.
	}
	person = NULL;
	// Traverse birthday list and output each element to kernel log.
	list_for_each_entry(pointer, &birthday_list, list) {
		counter++; // This counter represents the number of element in the list.
		// Print information to kernel log.
		printk(KERN_INFO "Birthday %d:\nDAY: %d, MONTH: %d, YEAR: %d\n", counter, pointer->day, pointer->month, pointer->year);
	}
	pointer = NULL;
	return 0;
}

/* This function is module exit point. */
void birthday_exit(void) {
	// Declare pointers for deleting birthday list.
	struct birthday *pointer, *next;
	// Traversing the list meawhile deleting element just visited.
	list_for_each_entry_safe(pointer, next, &birthday_list, list) {
		// Remove the element from the list.
		list_del(&pointer->list);
		// Delete the element from memory
		kfree(pointer);
	}
	pointer = NULL;
	next = NULL;
	// Print announce for removing module before exit.
	printk(KERN_INFO "Removing Example Module For CS 543 Assignment 2, Part II.\n");
}

/* Macros for registering module entry and exit points. */
module_init(birthday_init);
module_exit(birthday_exit);

/* This part represents details about software licnse, module description, and author. */
MODULE_LICENSE("CS543 Operating System");
MODULE_DESCRIPTION("Automatically generate 5 birthday information and add them to one birthday list, traverse and print them to kernel log. Delete all birthday information before quit.");
MODULE_AUTHOR("SHANGQI WU");
