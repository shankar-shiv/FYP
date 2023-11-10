#include <stdint.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "heatshrink_encoder.h"
#include "heatshrink_decoder.h"
#include "greatest.h"

// write some data into the compression buffer
const uint8_t input[] = "9.739696383476257324e-01, 9.132320880889892578e-01, 8.655097484588623047e-01, 8.232104182243347168e-01, 7.462038993835449219e-01, 6.420824527740478516e-01, 5.477223396301269531e-01, 4.262472987174987793e-01, 3.253796100616455078e-01, 2.798264622688293457e-01, 2.288503199815750122e-01, 1.366594433784484863e-01, 4.772234335541725159e-02, 1.084598712623119354e-02, 1.008676812052726746e-01, 1.887201666831970215e-01, 2.277657240629196167e-01, 2.407809048891067505e-01, 2.570498883724212646e-01, 2.635574936866760254e-01, 2.939262390136718750e-01, 3.188720047473907471e-01, 3.492407798767089844e-01, 4.023861289024353027e-01, 4.392624795436859131e-01, 4.501084685325622559e-01, 4.620390534400939941e-01, 4.750542342662811279e-01, 4.891540110111236572e-01, 4.869848191738128662e-01, 5.075922012329101562e-01, 5.108459591865539551e-01, 5.303687453269958496e-01, 5.433839559555053711e-01, 5.694143176078796387e-01, 5.824295282363891602e-01, 6.084598898887634277e-01, 6.193058490753173828e-01, 6.420824527740478516e-01, 6.507592201232910156e-01, 6.583514213562011719e-01, 6.572667956352233887e-01, 6.550976037979125977e-01, 6.268980503082275391e-01, 6.214750409126281738e-01, 6.019522547721862793e-01, 5.824295282363891602e-01, 5.477223396301269531e-01, 5.227765440940856934e-01, 4.837310314178466797e-01, 4.707158207893371582e-01, 4.338394701480865479e-01, 4.175705015659332275e-01, 4.034707248210906982e-01, 3.926247358322143555e-01, 3.828633427619934082e-01, 3.828633427619934082e-01, 3.796095550060272217e-01, 3.839479386806488037e-01, 3.752711415290832520e-01, 3.687635660171508789e-01, 3.665943741798400879e-01, 3.676789700984954834e-01, 3.644251525402069092e-01, 3.698481619358062744e-01, 3.709327578544616699e-01, 3.698481619358062744e-01, 3.644251525402069092e-01, 3.752711415290832520e-01, 3.828633427619934082e-01, 3.872017264366149902e-01, 3.698481619358062744e-01, 3.861171305179595947e-01, 3.763557374477386475e-01, 3.796095550060272217e-01, 3.817787468433380127e-01, 3.839479386806488037e-01, 3.752711415290832520e-01, 3.817787468433380127e-01, 3.796095550060272217e-01, 3.731019496917724609e-01, 3.774403333663940430e-01, 3.861171305179595947e-01, 3.785249590873718262e-01, 3.882863223552703857e-01, 3.774403333663940430e-01, 3.828633427619934082e-01, 3.991323113441467285e-01, 3.969631195068359375e-01, 3.958785235881805420e-01, 4.305856823921203613e-01, 4.360086619853973389e-01, 4.479392766952514648e-01, 4.544468522071838379e-01, 4.598698616027832031e-01, 4.522776603698730469e-01, 4.642082452774047852e-01, 4.663774371147155762e-01, 4.587852358818054199e-01, 4.869848191738128662e-01, 7.809110879898071289e-01, 1.000000000000000000e+00, 9.598698616027832031e-01, 9.045553207397460938e-01, 8.427332043647766113e-01, 7.787418365478515625e-01, 7.071583271026611328e-01, 6.312364339828491211e-01, 5.260303616523742676e-01, 4.186550974845886230e-01, 3.145336210727691650e-01, 2.331887185573577881e-01, 2.049891501665115356e-01, 1.420824229717254639e-01, 6.399132311344146729e-02, 0.000000000000000000e+00, 9.978307783603668213e-02, 1.876355707645416260e-01, 2.386117130517959595e-01, 2.505423128604888916e-01, 2.678958773612976074e-01, 2.516269087791442871e-01, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 0.000000000000000000e+00, 4.000000000000000000e+00";

#if HEATSHRINK_DYNAMIC_ALLOC
#error HEATSHRINK_DYNAMIC_ALLOC must be false for static allocation test suite.
#endif

static void dump_buf(char *name, uint8_t *buf, uint16_t count)
{
    for (int i = 0; i < count; i++)
    {
        uint8_t c = (uint8_t)buf[i];
        printf("%s %d: 0x%02x ('%c')\n", name, i, c, isprint(c) ? c : '.');
    }
}

// Global variables
static heatshrink_encoder hse;
static heatshrink_decoder hsd;

int main(int argc, char **argv)
{
    heatshrink_encoder_reset(&hse);
    heatshrink_decoder_reset(&hsd);
    uint32_t input_size = sizeof(input);

    size_t comp_sz = input_size + (input_size / 2) + 4;
    size_t decomp_sz = input_size + (input_size / 2) + 4;
    uint8_t *comp = malloc(comp_sz);
    uint8_t *decomp = malloc(decomp_sz);
    // uint8_t comp[comp_sz];
    // uint8_t decomp[decomp_sz];

    if (comp == NULL)
        printf("malloc fail");
    if (decomp == NULL)
        printf("malloc fail");
    memset(comp, 0, comp_sz);
    memset(decomp, 0, decomp_sz);

    size_t count = 0;

    printf("\n^^ COMPRESSING\n");

    uint32_t sunk = 0;
    uint32_t polled = 0;
    while (sunk < input_size)
    {
        if (heatshrink_encoder_sink(&hse, &input[sunk], input_size - sunk, &count) < 0)
            printf("Error in heatshrink_encoder_sink \n");
        sunk += count;
        printf("^^ sunk %zd bytes \n", count);
        if (sunk == input_size)
        {
            if (heatshrink_encoder_finish(&hse) != HSER_FINISH_MORE)
                printf("Error in heatshrink_encoder_finish \n");
        }
        HSE_poll_res pres;
        do
        { /* "turn the crank" */
            pres = heatshrink_encoder_poll(&hse, &comp[polled], comp_sz - polled, &count);
            // ASSERT(pres >= 0);
            if (pres < 0)
                printf("Error in heatshrink_encoder_poll \n");
            polled += count;
            printf("^^ polled %zd bytes \n", count);
        } while (pres == HSER_POLL_MORE);

        // ASSERT_EQ(HSER_POLL_EMPTY, pres);
        if (HSER_POLL_EMPTY != pres)
            printf("FAIL: HSER_POLL_EMPTY != pres \n");

        if (polled >= comp_sz)
            printf("compression should never expand that much \n");
        if (sunk == input_size)
        {
            // ASSERT_EQ(HSER_FINISH_DONE, heatshrink_encoder_finish(&hse));
            if (heatshrink_encoder_finish(&hse) != HSER_FINISH_DONE)
                printf("Error in heatshrink_encoder_finish \n");
            // heatshrink_encoder_finish(&hse);
        }
    }
    printf("\n in: %u compressed: %u \n", input_size, polled);

    // update the output size to the (smaller) compressed size
    uint32_t compressed_size = polled;
    sunk = 0;
    polled = 0;

    printf("\n^^ DECOMPRESSING\n");

    while (sunk < compressed_size)
    {
        // ASSERT(heatshrink_decoder_sink(&hsd, &comp[sunk], input_size - sunk, &count) >= 0);
        if (heatshrink_decoder_sink(&hsd, &comp[sunk], compressed_size - sunk, &count) < 0)
            printf("Error in heatshrink_decoder_sink \n");

        sunk += count;

        printf("^^ sunk %zd\n", count);

        if (sunk == compressed_size)
        {
            // ASSERT_EQ(HSDR_FINISH_MORE, heatshrink_decoder_finish(&hsd));
            if (heatshrink_decoder_finish(&hsd) != HSDR_FINISH_MORE)
                printf("Error in heatshrink_decoder_finish \n");
        }

        HSD_poll_res pres;

        do
        {
            pres = heatshrink_decoder_poll(&hsd, &decomp[polled],
                                           decomp_sz - polled, &count);

            if (pres < 0)
                printf("Error in heatshrink_decoder_poll \n");
            polled += count;

            printf("^^ polled %zd\n", count);

        } while (pres == HSDR_POLL_MORE);

        if (HSDR_POLL_EMPTY != pres)
            printf("FAIL: HSDR_POLL_EMPTY != pres \n");

        if (sunk == compressed_size)
        {
            HSD_finish_res fres = heatshrink_decoder_finish(&hsd);
            // ASSERT_EQ(HSDR_FINISH_DONE, fres);
            if (HSDR_FINISH_DONE != fres)
                printf("FAIL: HSDR_FINISH_DONE != fres \n");
        }

        // commented because the below if function doesnt make sense
        if (polled > input_size)
        {

            printf("Decompressed data is larger than original input");
        }
    }

    printf("decompressed: %u\n", polled);

    // commented because the below if function doesnt make sense
    if (polled != input_size)
    {
        printf("Decompressed length does not match original input length");
    }

    // print the compression ratio
    printf("Compression ratio: %f\n", (float)input_size / (float)compressed_size);

    // print the decompressed data
    printf("Decompressed Data (%u bytes):\n", polled);

    for (size_t i = 0; i < polled; i++)
    {
        printf("%c", decomp[i]);
    }
    printf("\n");

    free(comp);
    free(decomp);

    return 0;
}
