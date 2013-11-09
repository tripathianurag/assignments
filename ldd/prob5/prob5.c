#include<linux/module.h>
#include<linux/cdev.h>
/* because of cdev.h, 
 * we don't require kobject.h, kdev_t.h and list.h
 */
//#include<linux/kernel.h>

static int num_of_devices_to_associate_with_driver;
module_param_named( num_devs, num_of_devices_to_associate_with_driver, int, 0644 );

static int  __init prob_5_init( void ){
printk(KERN_ERR "Prob_5 initiated.");
//code below:

return 0;
}

static void __exit prob_5_exit( void ){


//nothing but printk after:
printk(KERN_ERR "Prob_5 exited.");
}

module_init( prob_5_init );
module_exit( prob_5_exit );

MODULE_LICENSE("GPL");
MODULE_AUTHOR ( "Anubhav Saini <IAmAnubhavSaini@GMail.com>" );
