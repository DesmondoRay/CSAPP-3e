/**
 * homework 5.15
 */

/* Inner product. accumulate in temporary */
void inner_6x6(vec_ptr u, ver_ptr v, data_t *dest)
{
    long i;
    long length = vec_length(u);
    long limit = length - 6;
    data_t *udata = get_vec_start(u);
    data_t *vdata = get_vec_start(v);
    data_t sum0 = sum1 = sum2 = sum3 = sum4 = sum5 = (data_t) 0;
    
    // Combine 6 elements at a time
    for (i = 0; i < limit; i+=6) {
        sum0 = sum0 + udata[i] * vdata[i];
        sum1 = sum1 + udata[i+1] * vdata[i+1];
        sum2 = sum2 + udata[i+2] * vdata[i+2];
        sum3 = sum3 + udata[i+3] * vdata[i+3];
        sum4 = sum4 + udata[i+4] * vdata[i+4];
        sum5 = sum5 + udata[i+5] * vdata[i+5];
    }
    
    // Finish any remaining elements
    for (; i < length; i++) {
        sum0 = sum0 + udata[i] * vdata[i];
    }
    *dest = sum0 + sum1 + sum2 + sum3 + sum4 + sum5;
}