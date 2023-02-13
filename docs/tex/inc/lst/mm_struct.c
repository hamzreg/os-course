struct mm_struct {
	struct vm_area_struct *mmap;
	struct rb_root mm_rb;
	...
	unsigned long mmap_base;
	...
	unsigned long task_size;
	unsigned long highest_vm_end;
	pgd_t * pgd;
	...
	atomic_t mm_users;
	atomic_t mm_count;
	...
	int map_count;
	spinlock_t page_table_lock;
	struct rw_semaphore mmap_lock;
	struct list_head mmlist;
	...
	unsigned long total_vm;
	unsigned long locked_vm;
	...
	unsigned long start_code, end_code, start_data, end_data;
	unsigned long start_brk, brk, start_stack;
	unsigned long arg_start, arg_end, env_start, env_end;
	...
	struct mm_rss_stat rss_stat;
	...
	unsigned long flags;
	...
};
