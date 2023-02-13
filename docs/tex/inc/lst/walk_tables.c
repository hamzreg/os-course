#define pte_offset_map(dir,addr)	pte_offset_kernel((dir),(addr))
#define pte_page(pte)           (mem_map+pte_pagenr(pte))
#define pte_pagenr(pte)         ((__pte_page(pte) - PAGE_OFFSET) >> PAGE_SHIFT)

pgd_t *pgd_offset(const struct mm_struct *mm, unsigned long address);
pmd_t *pmd_offset(pgd_t *dir, unsigned long address);
pte_t *pte_offset_kernel(pmd_t *dir, unsigned long address);
unsigned long __pte_page(pte_t pte);

