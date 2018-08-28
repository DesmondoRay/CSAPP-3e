/**
 * homework 9.18 -- mm.c
 *
 * 如596页所述，把前面块的分配/空闲位存放在当前块中多出来的低位中。
 */

// 修改处用 /*** xxx -- homework 9.18 ***/ 标注

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mm.h"
#include "memlib.h"

/* Basic constants and macros */
#define WSIZE       4       /* Word and header/footer size (bytes) */
#define DSIZE       8       /* Double word size (bytes) */
#define CHUNKSIZE  (1<<12)  /* Extend heap by this amount (bytes) */

#define MAX(x, y) ((x) > (y)? (x) : (y))  

/* Pack a size and allocated bit into a word */
// #define PACK(size, alloc)  ((size) | (alloc))
/*** 前面块的分配/空闲位放入当前块的低位中 										-- homework 9.18 ***/ 
#define PACK(size, alloc, prev_alloc) (((size) | (alloc)) | (prev_alloc << 1))

/* Read and write a word at address p */
#define GET(p)       (*(unsigned int *)(p))
#define PUT(p, val)  (*(unsigned int *)(p) = (val))

/* Read the size and allocated fields from address p */
#define GET_SIZE(p)  (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)
#define GET_PREV_ALLOC(p) ((GET(p) >> 1) & 0x1)  		/*** 前面块的分配/空闲位 -- homework 9.18 ***/ 

/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp)       ((char *)(bp) - WSIZE)
#define FTRP(bp)       ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp)  ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
#define PREV_BLKP(bp)  ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))

/* Global variables */
static char *heap_listp = 0;  /* Pointer to first block */  

/* Function prototypes for internal helper routines */
static void *extend_heap(size_t words);
static void place(void *bp, size_t asize);
static void *find_fit(size_t asize);
static void *coalesce(void *bp);

/* 
 * mm_init - Initialize the memory manager 
 */
int mm_init(void) 
{
	mem_init();
	
    /* Create the initial empty heap */
    if ((heap_listp = mem_sbrk(4*WSIZE)) == (void *)-1)
        return -1;
    PUT(heap_listp, 0);                          /* Alignment padding */
    PUT(heap_listp + (1*WSIZE), PACK(DSIZE, 1, 1)); /* Prologue header */	/*** homework 9.18 ***/
    PUT(heap_listp + (2*WSIZE), PACK(DSIZE, 1, 1)); /* Prologue footer */   /*** homework 9.18 ***/
    PUT(heap_listp + (3*WSIZE), PACK(0, 1, 1));     /* Epilogue header */   /*** homework 9.18 ***/
    heap_listp += (2*WSIZE);
	
	 /* Extend the empty heap with a free block of CHUNKSIZE bytes */
    if (extend_heap(CHUNKSIZE/WSIZE) == NULL) 
        return -1;
    return 0;
}

/* 
 * extend_heap - Extend heap with free block and return its block pointer
 */
static void *extend_heap(size_t words) 
{
    char *bp;
    size_t size;

    /* Allocate an even number of words to maintain alignment */
    size = (words % 2) ? (words+1) * WSIZE : words * WSIZE;
    if ((long)(bp = mem_sbrk(size)) == -1)
        return NULL;

    /* Initialize free block header/footer and the epilogue header */
    PUT(HDRP(bp), PACK(size, 0, GET_PREV_ALLOC(HDRP(bp))));					/*** homework 9.18 ***/
    PUT(FTRP(bp), PACK(size, 0, GET_PREV_ALLOC(HDRP(bp)))); 				/*** homework 9.18 ***/
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1, 0)); 								/*** homework 9.18 ***/

    /* Coalesce if the previous block was free */
    return coalesce(bp);
}

/* 
 * mm_free - Free a block 
 */
void mm_free(void *bp)
{
	if (bp == 0)
		return;
	
    size_t size = GET_SIZE(HDRP(bp));
	
	if (heap_listp == 0)
		mm_init();

	/*** 修改当前块的头部和脚部													-- homework 9.18 ***/
    PUT(HDRP(bp), PACK(size, 0, GET_PREV_ALLOC(HDRP(bp))));
    PUT(FTRP(bp), PACK(size, 0, GET_PREV_ALLOC(HDRP(bp))));
	
	/*** 修改后面一个块的头部或脚部													-- homework 9.18 ***/
	if (GET_ALLOC(HDRP(NEXT_BLKP(bp)))) 					 /*** 后面一个块已分配	-- homework 9.18 ***/
		PUT(HDRP(NEXT_BLKP(bp)), PACK(GET_SIZE(HDRP(NEXT_BLKP(bp))), 1, 0));
	else  /*** 后面一个块为空闲 													-- homework 9.18 ***/
	{
		PUT(HDRP(NEXT_BLKP(bp)), PACK(GET_SIZE(HDRP(NEXT_BLKP(bp))), 0, 0));
		PUT(FTRP(NEXT_BLKP(bp)), PACK(GET_SIZE(HDRP(NEXT_BLKP(bp))), 0, 0));
	}
    coalesce(bp);
}

/*
 * coalesce - Boundary tag coalescing. Return ptr to coalesced block
 */
static void *coalesce(void *bp) 
{
    // size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
	size_t prev_alloc = GET_PREV_ALLOC(HDRP(bp));  							/*** homework 9.18 ***/
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    if (prev_alloc && next_alloc) {            /* Case 1 */
        return bp;
    }

    else if (prev_alloc && !next_alloc) {      /* Case 2 */
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size, 0, 1)); 								 	/*** homework 9.18 ***/
        PUT(FTRP(bp), PACK(size, 0, 1));  									/*** homework 9.18 ***/
    }

    else if (!prev_alloc && next_alloc) {      /* Case 3 */
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(bp), PACK(size, 0, 1));  									/*** homework 9.18 ***/
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0, 1));  						/*** homework 9.18 ***/
        bp = PREV_BLKP(bp);
    }

    else {                                     /* Case 4 */
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + 
            GET_SIZE(FTRP(NEXT_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0, 1));  						/*** homework 9.18 ***/
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0, 1));  						/*** homework 9.18 ***/
        bp = PREV_BLKP(bp);
    }
    return bp;
}

/* 
 * mm_malloc - Allocate a block with at least size bytes of payload 
 */
void *mm_malloc(size_t size) 
{
    size_t asize;      /* Adjusted block size */
    size_t extendsize; /* Amount to extend heap if no fit */
    char *bp;      

	if (heap_listp == 0)
		mm_init();
	
    /* Ignore spurious requests */
    if (size == 0)
        return NULL;

    /* Adjust block size to include overhead and alignment reqs. */
    if (size <= WSIZE)  													/*** homework 9.18 ***/
        asize = DSIZE;
    else
        asize = DSIZE * ((size + (WSIZE) + (DSIZE-1)) / DSIZE);  			/*** homework 9.18 ***/

    /* Search the free list for a fit */
    if ((bp = find_fit(asize)) != NULL) {
        place(bp, asize);
        return bp;
    }

    /* No fit found. Get more memory and place the block */
    extendsize = MAX(asize,CHUNKSIZE);
    if ((bp = extend_heap(extendsize/WSIZE)) == NULL)
        return NULL;
    place(bp, asize);
    return bp;
} 

/* 
 * place - Place block of asize bytes at start of free block bp 
 *         and split if remainder would be at least minimum block size
 */
static void place(void *bp, size_t asize)
{
    size_t csize = GET_SIZE(HDRP(bp));   

    if ((csize - asize) >= (2*DSIZE)) { 
        // PUT(HDRP(bp), PACK(asize, 1));
        // PUT(FTRP(bp), PACK(asize, 1));
		PUT(HDRP(bp), PACK(asize, 1, 1));  									/*** homework 9.18 ***/
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(csize-asize, 0, 1));								/*** homework 9.18 ***/
        PUT(FTRP(bp), PACK(csize-asize, 0, 1));								/*** homework 9.18 ***/
    }
    else { 
        PUT(HDRP(bp), PACK(csize, 1, 1));									/*** homework 9.18 ***/
        PUT(HDRP(NEXT_BLKP(bp)), PACK(csize, 1, 1));						/*** homework 9.18 ***/
    }
}

/* 
 * find_fit - Find a fit for a block with asize bytes 
 */
static void *find_fit(size_t asize)
{
	/* First-fit search */
    void *bp;

    for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
        if (!GET_ALLOC(HDRP(bp)) && (asize <= GET_SIZE(HDRP(bp)))) {
            return bp;
        }
    }
    return NULL; /* No fit */
}