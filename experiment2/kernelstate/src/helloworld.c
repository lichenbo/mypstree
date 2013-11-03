#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL")
static int hello_init(void){
	printk("<1>Hello World!\n");
	return 0;
}
static void hello_exit(void) {
	printk("<1>Goodbye!\n");
}

module_init(hello_init);
module_exit(hello_exit);