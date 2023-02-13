static void trace_pages(struct task_struct *task)
{
    struct mm_struct *mm = task->mm;
    struct vm_area_struct *vma = mm->mmap;

    unsigned long vaddr;
    int page_number = 0;

    for (; vma != NULL; vma = vma->vm_next)
    {
        for (vaddr = vma->vm_start; vaddr < vma->vm_end; vaddr += PAGE_SIZE)
        {
            printk(KERN_INFO "pagetracer: %d: page number is %d.\n",
                   process_id, page_number++);

            if (get_page(mm, vaddr) != 0)
            {
                printk(KERN_INFO "pagetracer: %d: page not mapped in page table.\n",
                       process_id); 
            }

        }
    }
}
