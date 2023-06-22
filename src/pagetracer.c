#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/pid.h>
#include <linux/page_ref.h>
#include <linux/page-flags.h>
#include <linux/atomic.h>
#include <asm/page.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Khamzina Regina");
MODULE_DESCRIPTION("Module for monitoring the state of pages allocated to a process");


static int process_id;
module_param(process_id, int, 0);


static void log_page(struct page *page)
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

static int walk_page_table(struct mm_struct *mm, unsigned long vaddr)
{
    pgd_t *pgd;
    p4d_t* p4d;
    pud_t *pud;
    pmd_t *pmd;
    pte_t *ptep, pte;

    struct page *page = NULL;

    pgd = pgd_offset(mm, vaddr);

    if (pgd_none(*pgd) || pgd_bad(*pgd))
        return 1;

    p4d = p4d_offset(pgd, vaddr);

    if (p4d_none(*p4d) || p4d_bad(*p4d))
        return 1;

    pud = pud_offset(p4d, vaddr);

    if (pud_none(*pud) || pud_bad(*pud))
        return 1;

    pmd = pmd_offset(pud, vaddr);

    if (pmd_none(*pmd) || pmd_bad(*pmd))
        return 1;

    ptep = pte_offset_map(pmd, vaddr);

    if (!ptep)
        return 1;

    pte = *ptep;
    page = pte_page(pte);

    if (page)
        log_page(page);

    pte_unmap(ptep);
    return 0;
}

static void scan_virtual_pages(struct task_struct *task)
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

            if (walk_page_table(mm, vaddr) != 0)
            {
                printk(KERN_INFO "pagetracer: %d: page not mapped in page table.\n",
                       process_id); 
            }
        }
    }
}

static int __init md_init(void)
{
    printk(KERN_INFO "pagetracer: module loaded.\n");

    if (process_id != 0)
    {
        struct task_struct *task = pid_task(find_vpid(process_id), PIDTYPE_PID);
        printk(KERN_INFO "pagetracer: %d: process name is %s.\n",
               process_id, task->comm);

        scan_virtual_pages(task);
    }
    else
    {
        printk(KERN_ERR "pagetracer: process id was not set.\n");
    }

    return 0;
}

static void __exit md_exit(void)
{
    printk(KERN_INFO "pagetracer: module unloaded.\n");
}

module_init(md_init);
module_exit(md_exit);
