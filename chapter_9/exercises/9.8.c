/**
 * exercise 9.8
 */

static void *find_fit(size_t asize)
{
	char *bp = (NEXT_BLKP(heap_listp));
	size_t next_size = GET_SIZE(bp);
	size_t next_alloc = GET_ALLOC(HDRP(bp));
	
	while (next_size > 0) {
		if (!next_alloc && next_size >= asize)
			return bp;
		bp = (NEXT_BLKP(bp));
		next_size = GET_SIZE(bp);
		next_alloc = GET_ALLOC(HDRP(bp));
	}
	return NULL;
}