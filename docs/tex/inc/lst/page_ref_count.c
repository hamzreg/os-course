#include <linux/atomic.h>
#include <linux/mm_types.h>
#include <linux/page-flags.h>

static inline int page_ref_count(const struct page *page)
{
	return atomic_read(&page->_refcount);
}
