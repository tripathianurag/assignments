/* Anubhav Saini
 * --------------------------------------------------------------------------00
 * Problem: on multiple loading and unloading of this module, device entry 
 * still exists as cat /proc/devices shows:
 * ...
 * 226 drm
 * 247 mydev
 * 248 mydev
 * 249 mydev
 * 250 mydev
 * 251 mydev
 * 252 usbmon
 * ---
 */

#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/init.h>
//#include<linux/kdev_t.h> //fetched by cdev.h
#include<linux/module.h>
#include<linux/types.h>

/* because of cdev.h, 
 * we don't require kobject.h, kdev_t.h and list.h
 */
//#include<linux/kernel.h>

static int num_of_devices_to_associate_with_driver = 1;
module_param_named( num_devs, num_of_devices_to_associate_with_driver, int, 0644 );

static int  __init prob_5_init( void ){
printk(KERN_ALERT "Prob_5 initiated.\n");
//code below:
  dev_t dev = 101;
  int dev_reg_res = alloc_chrdev_region( &dev, 101, 1, "mydev" );
  if( dev_reg_res != 0 ){
    printk(KERN_ERR "Device registration failed.\n" );
    return -1;
  }
  printk(KERN_INFO "Device major # is %d and minor # is %d.\n",  MAJOR(dev), MINOR(dev) );
  printk(KERN_INFO "Returned dev value is %d.\n", dev );
return 0;
}

static void __exit prob_5_exit( void ){

  unregister_chrdev_region( 101, 1 );
//nothing but printk after:
printk(KERN_INFO "Prob_5 exited.\n");
}

module_init( prob_5_init );
module_exit( prob_5_exit );

MODULE_LICENSE("GPL");
MODULE_AUTHOR ( "Anubhav Saini <IAmAnubhavSaini@GMail.com>" );
