#include<linux/mm_types.h> //struct page
#include<linux/highmem.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anubhav Saini <IAmAnubhavSaini@GMail.com>");

static   unsigned long free_dma_page_addr;
static   unsigned long free_user_page_addr;
static   struct page * free_highmem_page;

static   unsigned long dma_pages[6];
static   unsigned long user_pages[6];
static   struct page * highmem_pages[6];

static   struct page * highmem_page;
   unsigned long highmem_page_address;
static   unsigned long highmem_page_addresses[8]; /* 2 ^ order(=3) */

static   int order_dma;
static   int order_user;
static   int order_highmem;

static int __init my_pager_init( void ){
  
  order_dma  = 0;
  order_user = 0;
  order_highmem = 0;
  int i = 0; //index for highmem kmap loop //ISO C90 forbids mixed declarations and code warning

  do{
    free_dma_page_addr = __get_free_pages( GFP_KERNEL | GFP_DMA, order_dma );
    if (! free_dma_page_addr ) break;
//we could do return -ENOMEM; 
//but we want to run the show further to user pages too.
    dma_pages[order_dma] = free_dma_page_addr;
    printk( KERN_ERR "Address for DMA page%c is : %lx. Order: %d.\n", 
            order_dma ? ' ' : 's', 
            free_dma_page_addr, 
            order_dma 
           );
  }while ( order_dma++ < 4 );

  do{
    free_user_page_addr = __get_free_pages( GFP_KERNEL | GFP_USER, order_user );
    if ( ! free_user_page_addr ) break;
    user_pages[order_user] = free_user_page_addr;
    printk( KERN_ERR "Address for user page%c is : %lx. Order: %d.\n", 
            order_user ? ' ' : 's', 
            free_user_page_addr,
            order_user
           );
  }while( order_user++ < 6 );
  
  highmem_page = alloc_pages( GFP_HIGHUSER, 3 ); /* order = 3 */
  if ( highmem_page == NULL ) printk(KERN_ERR "Couldn't allocate highmem page with order : 3\n" );
  else {
    for( i = 0; i < 8 /* 2^3 */; i++ ){
      highmem_page_addresses[i] = kmap( highmem_page + i);
      if ( ! highmem_page_addresses[i] ) printk( KERN_ERR "Couldn't map highmem pages.\n");
      else {
        printk( KERN_ERR "Address for highuser pages is : %lx. Order: %d.\n", 
                highmem_page_addresses[i],
                3
              );
       }
    }
  }
  
/*  do{
    free_highmem_page = alloc_pages( GFP_HIGHUSER, order_highmem );
    if ( ! free_highmem_page ) break;
    highmem_pages[order_highmem] = free_highmem_page;
    printk( KERN_ERR "Address for highmem page%c is : %lx. Order: %d.\n", 
            order_highmem ? ' ' : 's', 
            free_highmem_page,
            order_highmem
           );
  }while( order_highmem++ < 6 );
*/
  return 0;
}

static void __exit my_pager_exit( void ){
  int local_order = 0;
  int i = 0; // index for highmem unmap loop
  for( local_order = 0; local_order < order_dma; local_order++ )
    free_pages( dma_pages[local_order], local_order );
  for( local_order = 0; local_order < order_user; local_order++ )
    free_pages( user_pages[local_order], local_order );

//freeing highuser pages
  for( i = 0; i < 8 /* 2^3 */; i++ ){
    kunmap( highmem_page + i );
  }
  free_pages( highmem_page_addresses[0], 3 /* order */ );

  printk(KERN_ERR "Hihmem freed!\n");

/*  for( local_order = 0; local_order < order_highmem; local_order++ )
    free_pages( highmem_pages[local_order], local_order );
*/
}

module_init( my_pager_init );
module_exit( my_pager_exit );


