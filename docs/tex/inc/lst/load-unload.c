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
