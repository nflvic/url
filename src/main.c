#include <stdio.h>
#include <assert.h>
#include "_string.h"
#include "utils.h"
#include "parser.h"

int main () {

    char *b =  "https://www.google.com/url?sa=i&url=https%3A%2F%2Fencrypted-tbn2.gstatic.com%2Flicensed-image%3Fq%3Dtbn%3AANd9GcSO9Xd_NJYU1FU2u886CDMp-pX-nffkmg_h0yhAKgLWCltFmAbQnt_nGdpEPgQZMZzw1k_pGxWjlD3U_Yk&psig=AOvVaw28MNkxJJUKU938AdiPt-28&ust=1704401304592000&source=images&cd=vfe&ved=0CBIQjRxqFwoTCIiV0MKLwoMDFQAAAAAdAAAAABAE";
    char *a = "https://www.google.com:/url/";
    url *out = url_parse(b);

    

    puts(out->address);

    map_print(out->params);

    assert(out->port == NULL);

    //assert(verify_url(a));

    return 0;
}