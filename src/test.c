#include <linux/init_task.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/pid.h>
#include <linux/page_ref.h>
#include <linux/page-flags.h>
#include <linux/atomic.h>
#include <asm/page.h>

MODULE_LICENSE("GPL");

static struct page *walk_page_table(struct mm_struct *mm, unsigned long addr)
{
    pgd_t *pgd;
    p4d_t* p4d;
    pte_t *ptep, pte;
    pud_t *pud;
    pmd_t *pmd;

    struct page *page = NULL;

    pgd = pgd_offset(mm, addr);
    if (pgd_none(*pgd) || pgd_bad(*pgd))
        goto out;
    printk(KERN_NOTICE "TEST_MD: Valid pgd");

    p4d = p4d_offset(pgd, addr);
    if (p4d_none(*p4d) || p4d_bad(*p4d))
        goto out;

    pud = pud_offset(p4d, addr);
    if (pud_none(*pud) || pud_bad(*pud))
        goto out;
    printk(KERN_NOTICE "TEST_MD: Valid pud");

    pmd = pmd_offset(pud, addr);
    if (pmd_none(*pmd) || pmd_bad(*pmd))
        goto out;
    printk(KERN_NOTICE "TEST_MD: Valid pmd");

    ptep = pte_offset_map(pmd, addr);
    if (!ptep)
        goto out;
    pte = *ptep;

    page = pte_page(pte);
    if (page)
    {
        printk(KERN_INFO "TEST_MD: page frame struct is @ %p", page);
        printk(KERN_INFO "TEST_MD: flags - %lu\n", page->flags);
        int ref_count = page_ref_count(page);
        printk(KERN_INFO "TEST_MD: refcount - %d\n", ref_count);
        int map_count = atomic_read(&page->_mapcount);
        printk(KERN_INFO "TEST_MD: mapcount - %d\n", map_count);
        int page_type1 = (int)page->page_type;
        printk(KERN_INFO "TEST_MD: page_type1 - %d\n", page_type1);
    }

    pte_unmap(ptep);

 out:
    return page;
}

static int __init md_init(void)
{
    int process_id = 5371;
    struct task_struct *task = pid_task(find_vpid(process_id), PIDTYPE_PID);

    printk(KERN_INFO "TEST_MD: Module md loaded!\n");
    printk(KERN_INFO "TEST_MD: name - %s\n", task->comm);

    struct vm_area_struct *vma = 0;
    unsigned long vpage;
    struct page* page = NULL;
    int i = 0;
    
    if (task->mm && task->mm->mmap)
    {
         for (vma = task->mm->mmap; vma; vma = vma->vm_next)
         {
             for (vpage = vma->vm_start; vpage < vma->vm_end; vpage += PAGE_SIZE)
             {
                printk(KERN_INFO "TEST_MD: page number - %d\n", i++);
                page = walk_page_table(task->mm, vpage);
             }
         }
    }

    return 0;
}

static void __exit md_exit(void)
{
    printk(KERN_INFO "TEST_MD: Good by!\n");
}

module_init(md_init);
module_exit(md_exit);
