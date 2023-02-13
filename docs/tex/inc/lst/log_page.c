static void lop_page(struct page *page)
{
    int page_type = (int)page->page_type;
    printk(KERN_INFO "pagetracer: %d: page type is %d.\n",
           process_id, page_type);

    int ref_count = page_ref_count(page);
    printk(KERN_INFO "pagetracer: %d: page usage count is %d.\n",
           process_id, ref_count);

    int map_count = atomic_read(&page->_mapcount);
    printk(KERN_INFO "pagetracer: %d: references count in page table is %d.\n",
           process_id, map_count);
}
