/**
 * exercise 9.9
 */

static void place(void *bp, size_t asize)
{
	size_t size = GET_SIZE(bp);
	
	PUT(HDRP(bp), PACK(asize, 1));
	PUT(FTRP(bp), PACK(asize, 1));
	
	if ((size - asize) >= (2*DSIZE)) {
		bp = NEXT_BLKP(bp);
		PUT(HDRP(bp), PACK(size - asize, 0));
		PUT(FTRP(bp), PACK(size - asize, 0));
	}
}