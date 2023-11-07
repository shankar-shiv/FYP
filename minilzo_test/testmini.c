/* testmini.c -- very simple test program for the miniLZO library

   This file is part of the LZO real-time data compression library.

   Copyright (C) 1996-2017 Markus Franz Xaver Johannes Oberhumer
   All Rights Reserved.

   The LZO library is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of
   the License, or (at your option) any later version.

   The LZO library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with the LZO library; see the file COPYING.
   If not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

   Markus F.X.J. Oberhumer
   <markus@oberhumer.com>
   http://www.oberhumer.com/opensource/lzo/
 */

#include <stdio.h>
#include <stdlib.h>

/*************************************************************************
// This program shows the basic usage of the LZO library.
// We will compress a block of data and decompress again.
//
// For more information, documentation, example programs and other support
// files (like Makefiles and build scripts) please download the full LZO
// package from
//    http://www.oberhumer.com/opensource/lzo/
**************************************************************************/

/* First let's include "minizo.h". */

#include "minilzo.h"

/* We want to compress the data block at 'in' with length 'IN_LEN' to
 * the block at 'out'. Because the input block may be incompressible,
 * we must provide a little more output space in case that compression
 * is not possible.
 */

char data[] = "9.739696383476257324e-01, 9.132320880889892578e-01, 8.655097484588623047e-01, 8.232104182243347168e-01, 7.462038993835449219e-01, 6.420824527740478516e-01, 5.477223396301269531e-01, 4.262472987174987793e-01, 3.253796100616455078e-01, 2.798264622688293457e-01, 2.288503199815750122e-01, 1.366594433784484863e-01, 4.772234335541725159e-02, 1.084598712623119354e-02, 1.008676812052726746e-01, 1.887201666831970215e-01, 2.277657240629196167e-01, 2.407809048891067505e-01, 2.570498883724212646e-01, 2.635574936866760254e-01, 2.939262390136718750e-01, 3.188720047473907471e-01, 3.492407798767089844e-01, 4.023861289024353027e-01, 4.392624795436859131e-01, 4.501084685325622559e-01, 4.620390534400939941e-01, 4.750542342662811279e-01, 4.891540110111236572e-01, 4.869848191738128662e-01, 5.075922012329101562e-01, 5.108459591865539551e-01, 5.303687453269958496e-01, 5.433839559555053711e-01, 5.694143176078796387e-01, 5.824295282363891602e-01, 6.084598898887634277e-01, 6.193058490753173828e-01, 6.420824527740478516e-01, 6.507592201232910156e-01, 6.583514213562011719e-01, 6.572667956352233887e-01, 6.550976037979125977e-01, 6.268980503082275391e-01, 6.214750409126281738e-01, 6.019522547721862793e-01, 5.824295282363891602e-01, 5.477223396301269531e-01, 5.227765440940856934e-01, 4.837310314178466797e-01, 4.707158207893371582e-01, 4.338394701480865479e-01, 4.175705015659332275e-01, 4.034707248210906982e-01, 3.926247358322143555e-01, 3.828633427619934082e-01, 3.828633427619934082e-01, 3.796095550060272217e-01, 3.839479386806488037e-01, 3.752711415290832520e-01, 3.687635660171508789e-01, 3.665943741798400879e-01, 3.676789700984954834e-01, 3.644251525402069092e-01, 3.698481619358062744e-01, 3.709327578544616699e-01, 3.698481619358062744e-01, 3.644251525402069092e-01, 3.752711415290832520e-01, 3.828633427619934082e-01, 3.872017264366149902e-01, 3.698481619358062744e-01, 3.861171305179595947e-01, 3.763557374477386475e-01, 3.796095550060272217e-01, 3.817787468433380127e-01, 3.839479386806488037e-01, 3.752711415290832520e-01, 3.817787468433380127e-01, 3.796095550060272217e-01, 3.731019496917724609e-01, 3.774403333663940430e-01, 3.861171305179595947e-01, 3.785249590873718262e-01, 3.882863223552703857e-01, 3.774403333663940430e-01, 3.828633427619934082e-01, 3.991323113441467285e-01, 3.969631195068359375e-01, 3.958785235881805420e-01, 4.305856823921203613e-01, 4.360086619853973389e-01, 4.479392766952514648e-01, 4.544468522071838379e-01, 4.598698616027832031e-01, 4.522776603698730469e-01, 4.642082452774047852e-01, 4.663774371147155762e-01, 4.587852358818054199e-01, 4.869848191738128662e-01, 7.809110879898071289e-01, 1.000000000000000000e+00, 9.598698616027832031e-01, 9.045553207397460938e-01, 8.427332043647766113e-01, 7.787418365478515625e-01, 7.071583271026611328e-01, 6.312364339828491211e-01, 5.260303616523742676e-01, 4.186550974845886230e-01, 3.145336210727691650e-01, 2.331887185573577881e-01, 2.049891501665115356e-01, 1.420824229717254639e-01, 6.399132311344146729e-02, 0.000000000000000000e+00, 9.978307783603668213e-02, 1.876355707645416260e-01, 2.386117130517959595e-01, 2.505423128604888916e-01, 2.678958773612976074e-01, 2.516269087791442871e-01, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 4.000000000000000000e+00";

#define IN_LEN (sizeof(data))
#define OUT_LEN (IN_LEN + IN_LEN / 16 + 64 + 3)

static unsigned char __LZO_MMODEL in[IN_LEN];
static unsigned char __LZO_MMODEL out[OUT_LEN];

/* Work-memory needed for compression. Allocate memory in units
 * of 'lzo_align_t' (instead of 'char') to make sure it is properly aligned.
 */

#define HEAP_ALLOC(var, size) \
    lzo_align_t __LZO_MMODEL var[((size) + (sizeof(lzo_align_t) - 1)) / sizeof(lzo_align_t)]

// #define LZO1X_1_MEM_COMPRESS ((lzo_uint32_t) (16384L * lzo_sizeof_dict_t))
static HEAP_ALLOC(wrkmem, ((lzo_uint32_t)(16384L * lzo_sizeof_dict_t)));

/*************************************************************************
//
**************************************************************************/

int main(int argc, char *argv[])
{
    int r;
    lzo_uint in_len;
    lzo_uint out_len;
    lzo_uint new_len;

    if (argc < 0 && argv == NULL) /* avoid warning about unused args */
        return 0;

    printf("\nLZO real-time data compression library (v%s, %s).\n",
           lzo_version_string(), lzo_version_date());

    /*
     * Step 1: initialize the LZO library
     */
    if (lzo_init() != LZO_E_OK)
    {
        printf("internal error - lzo_init() failed !!!\n");
        printf("(this usually indicates a compiler bug - try recompiling\nwithout optimizations, and enable '-DLZO_DEBUG' for diagnostics)\n");
        return 3;
    }

    /*
     * Step 2: prepare the input block that will get compressed.
     *         We just fill it with zeros in this example program,
     *         but you would use your real-world data here.
     */

    in_len = IN_LEN;
    lzo_memset(in, 0, in_len);          // clear the buffer, you can use the code below. It will set all the blocks to zero.
    lzo_memcpy(in, data, sizeof(data)); // load the data

    /*
     * Step 3: compress from 'in' to 'out' with LZO1X-1
     */
    r = lzo1x_1_compress(in, in_len, out, &out_len, wrkmem);
    if (r == LZO_E_OK)
        printf("compressed %lu bytes into %lu bytes\n",
               (unsigned long)in_len, (unsigned long)out_len);
    else
    {
        /* this should NEVER happen */
        printf("internal error - compression failed: %d\n", r);
        return 2;
    }
    /* check for an incompressible block */
    if (out_len >= in_len)
    {
        printf("This block contains incompressible data.\n");
        return 0;
    }

    /*
     * Step 4: decompress again, now going from 'out' to 'in'
     */
    new_len = in_len;
    r = lzo1x_decompress(out, out_len, in, &new_len, NULL);
    if (r == LZO_E_OK && new_len == in_len)
        printf("decompressed %lu bytes back into %lu bytes\n",
               (unsigned long)out_len, (unsigned long)in_len);
    else
    {
        /* this should NEVER happen */
        printf("internal error - decompression failed: %d\n", r);
        return 1;
    }

    // print the contents of decompressed in array
    for (int i = 0; i < in_len; i++)
    {
        printf("%c", in[i]);
    }

    printf("\nminiLZO simple compression test passed.\n");
    printf("Compression ratio is %5.2f \n", (double)in_len / (double)out_len);

    return 0;
}

/* vim:set ts=4 sw=4 et: */
