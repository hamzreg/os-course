struct page {
	unsigned long flags;
	struct list_head lru;
	struct address_space *mapping;
	pgoff_t index;
	unsigned long private;
	...
	struct list_head slab_list;
	struct page *next;
	int pages;
	int pobjects;
	...
	void *freelist;
	...
	atomic_t _mapcount;
	unsigned int page_type;
	unsigned int active;
	int units;
	atomic_t _refcount;
	...
	void *virtual;
	...
};
