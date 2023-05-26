#include <wmkc_bigNum.h>

WMKC_PRIVATE(wmkcErr_ctx) wmkcBigNum_ArrayReversal
WMKC_OF((wmkcChar *number_string, wmkcSize size))
{
    wmkcErr_ctx error;
    if(!number_string || !size) {
        wmkcErr_return(error, wmkcErr_ErrNULL,
            "wmkcBigNum_ArrayReversal: number_string or size is NULL.");
    }
    wmkcSize i;
    wmkcByte swap;

    for(i = 0; i < size >> 1; ++i) {
        swap = number_string[i];
        number_string[i] = number_string[size - i - 1];
        number_string[size - i - 1] = swap;
    }

    wmkcErr_return(error, wmkcErr_OK, "OK.");
}

WMKC_PUBLIC(wmkcErr_ctx) wmkcBigNum_add WMKC_OPEN_API
WMKC_OF((wmkcChar **dst, wmkcChar *src1, wmkcChar *src2))
{
    /**
     * larger  = "1234561092843327530284087432857309150242358"
     * smaller = "9583209419874982749813573892749837"
     * res = {}
     * 
     * blockSize = 8
     * 
     * larger  -> Reversal -> 8532420519037582347804820357233482901654321
     * smaller -> Reversal -> 7389472983753189472894789149023859
     * 
     * larger  -> Padding  -> 853242051903758234780482035723348290165432100000
     * smaller -> Padding  -> 738947298375318947289478914902385900000000000000
     * 
     * larger  -> Reversal -> 000001234561092843327530284087432857309150242358
     * smaller -> Reversal -> 000000000000009583209419874982749813573892749837
     * 
     * larger  -> block    -> {     123, 45610928, 43327530, 28408743, 28573091, 50242358}
     * smaller -> block    -> {       0,       95, 83209419, 87498274, 98135738, 92749837}
     * 
     * larger  -> Reversal -> {50242358, 28573091, 28408743, 43327530, 45610928,      123}
     * smaller -> Reversal -> {92749837, 98135738, 87498274, 83209419,       95,        0}
     * res -> init     -> {       0,        0,        0,        0,        0,        0}
     * 
     * for(i = 0; i < len(larger); ++i) {
     *     res[i] += (larger[i] + smaller[i]);
     *     if(res[i] >= 100000000) {
     *         res[i] %= res[i];
     *         res[i + 1] += 1;
     *     }
     * }
     * 
     * res ->             {42992195, 26708830, 15907018, 26536950, 45611024,      123}
     * res -> Reversal -> {     123, 45611024, 26536950, 15907018, 26708830, 42992195}
     * res -> String   -> "1234561102426536950159070182670883042992195"
    */
    wmkcErr_ctx error;
    if(!dst || !src1 || !src2) {
        wmkcErr_return(error, wmkcErr_ErrNULL,
            "wmkcBigNum_add: dst or src1 or src2 is NULL.");
    }

    wmkcSize src1Size = strlen(src1);
    wmkcSize src2Size = strlen(src2);
    if(!src1Size || !src2Size) {
        wmkcErr_return(error, wmkcErr_ErrNULL,
            "wmkcBigNum_add: src1Size or src2Size is NULL.");
    }

    wmkcErr_return(error, wmkcErr_OK, "OK.");
}

WMKC_PUBLIC(wmkcErr_ctx) wmkcBigNum_sub WMKC_OPEN_API
WMKC_OF((wmkcChar **dst, wmkcChar *src1, wmkcChar *src2))
{
    wmkcErr_ctx error;
    wmkcErr_return(error, wmkcErr_OK, "OK.");
}

WMKC_PUBLIC(wmkcErr_ctx) wmkcBigNum_mul WMKC_OPEN_API
WMKC_OF((wmkcChar **dst, wmkcChar *src1, wmkcChar *src2))
{
    /**
     * 可参考wmkcBigNum_add。
    */
    wmkcErr_ctx error;
    wmkcErr_return(error, wmkcErr_OK, "OK.");
}

WMKC_PUBLIC(wmkcErr_ctx) wmkcBigNum_div WMKC_OPEN_API
WMKC_OF((wmkcChar **dst, wmkcChar *src1, wmkcChar *src2))
{
    wmkcErr_ctx error;
    wmkcErr_return(error, wmkcErr_OK, "OK.");
}

WMKC_PUBLIC(wmkcErr_ctx) wmkcBigNum_mod WMKC_OPEN_API
WMKC_OF((wmkcChar **dst, wmkcChar *src1, wmkcChar *src2))
{
    wmkcErr_ctx error;
    wmkcErr_return(error, wmkcErr_OK, "OK.");
}

WMKC_PUBLIC(wmkcErr_ctx) wmkcBigNum_pow WMKC_OPEN_API
WMKC_OF((wmkcChar **dst, wmkcChar *src1, wmkcChar *src2))
{
    wmkcErr_ctx error;
    wmkcErr_return(error, wmkcErr_OK, "OK.");
}