struct vm_area_struct {
	unsigned long vm_start;
	unsigned long vm_end;
	struct vm_area_struct *vm_next, *vm_prev;
	...
	struct mm_struct *vm_mm;
	...
	unsigned long vm_flags;
	...
	struct list_head anon_vma_chain;
	struct anon_vma *anon_vma;
	const struct vm_operations_struct *vm_ops;
	unsigned long vm_pgoff;
	struct file * vm_file;
	void * vm_private_data;
	...
};
