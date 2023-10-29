/*
 * Description: Example program to demonstrate the basic usage of the compress/decompress functions within lz4.c/lz4.h.
 *              The functions you'll likely want are LZ4_compress_default and LZ4_decompress_safe.
 *              Both of these are documented in the lz4.h header file; need to read them.
 */

/* Dependencies */
#include <stdio.h>                               // For printf()
#include <string.h>                              // For memcmp()
#include <stdlib.h>                              // For exit()
#include "../.libraries/lz4-1.9.4/lib/lz4file.h" // This is all that is required to expose the prototypes for basic compression and decompression.

/*
 * Simple show-error-and-bail function.
 */
void run_screaming(const char *message, const int code)
{
  printf("%s \n", message);
  exit(code);
}

int main(void)
{
  /* Introduction */
  // Below we will have a Compression and Decompression section to demonstrate.
  // There are a few important notes before we start:
  //   1) The return codes of LZ4_ functions are important.
  //      Read lz4.h if you're unsure what a given code means.
  //   2) LZ4 uses char* pointers in all LZ4_ functions.
  //      This is baked into the API and not going to change, for consistency.
  //      If your program uses different pointer types,
  //      you may need to do some casting or set the right -Wno compiler flags to ignore those warnings (e.g.: -Wno-pointer-sign).

  /* Compression */
  // We'll store some text into a variable pointed to by *src to be compressed later.
  const char *const src = "9.779411554336547852e-01,9.264705777168273926e-01,6.813725233078002930e-01,2.450980395078659058e-01,1.544117629528045654e-01,1.911764740943908691e-01,1.519607901573181152e-01,8.578431606292724609e-02,5.882352963089942932e-02,4.901960864663124084e-02,4.411764815449714661e-02,6.127450987696647644e-02,6.617647409439086914e-02,6.127450987696647644e-02,4.901960864663124084e-02,7.352941483259201050e-02,6.127450987696647644e-02,6.127450987696647644e-02,6.617647409439086914e-02,6.862745434045791626e-02,9.558823704719543457e-02,7.598039507865905762e-02,9.313725680112838745e-02,1.053921580314636230e-01,1.151960790157318115e-01,1.029411777853965759e-01,1.176470592617988586e-01,1.250000000000000000e-01,1.421568691730499268e-01,1.274509876966476440e-01,1.519607901573181152e-01,1.446078419685363770e-01,1.642156839370727539e-01,1.446078419685363770e-01,1.593137234449386597e-01,1.519607901573181152e-01,1.544117629528045654e-01,1.421568691730499268e-01,1.519607901573181152e-01,1.519607901573181152e-01,1.470588296651840210e-01,1.323529481887817383e-01,1.274509876966476440e-01,1.348039209842681885e-01,1.372549086809158325e-01,1.127450987696647644e-01,1.078431382775306702e-01,1.053921580314636230e-01,1.078431382775306702e-01,9.803921729326248169e-02,9.313725680112838745e-02,1.029411777853965759e-01,1.004901975393295288e-01,1.053921580314636230e-01,1.029411777853965759e-01,1.176470592617988586e-01,1.053921580314636230e-01,1.225490197539329529e-01,1.274509876966476440e-01,1.421568691730499268e-01,1.470588296651840210e-01,1.446078419685363770e-01,1.740196049213409424e-01,2.303921580314636230e-01,2.377450913190841675e-01,2.475490123033523560e-01,2.303921580314636230e-01,2.254901975393295288e-01,1.985294073820114136e-01,1.764705926179885864e-01,1.323529481887817383e-01,1.250000000000000000e-01,1.176470592617988586e-01,1.225490197539329529e-01,1.127450987696647644e-01,1.299019604921340942e-01,1.151960790157318115e-01,8.333333581686019897e-02,0.000000000000000000e+00,6.617647409439086914e-02,3.063725531101226807e-01,6.127451062202453613e-01,8.602941036224365234e-01,1.000000000000000000e+00,9.583333134651184082e-01,7.450980544090270996e-01,3.039215803146362305e-01,1.642156839370727539e-01,2.058823555707931519e-01,1.642156839370727539e-01,1.029411777853965759e-01,9.558823704719543457e-02,9.068627655506134033e-02,1.004901975393295288e-01,9.558823704719543457e-02,9.803921729326248169e-02,9.313725680112838745e-02,9.803921729326248169e-02,9.558823704719543457e-02,1.127450987696647644e-01,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00,0.000000000000000000e+00";
  // The compression function needs to know how many bytes exist.  Since we're using a string, we can use strlen() + 1 (for \0) (Null-terminated string)
  const int src_size = (int)(strlen(src) + 1);
  // LZ4 provides a function that will tell you the maximum size of compressed output based on input data via LZ4_compressBound().
  const int max_dst_size = LZ4_compressBound(src_size);
  // We will use that size for our destination boundary when allocating space.
  char *compressed_data = (char *)malloc((size_t)max_dst_size);
  if (compressed_data == NULL)
    run_screaming("Failed to allocate memory for *compressed_data.", 1);
  // That's all the information and preparation LZ4 needs to compress *src into* compressed_data.
  // Invoke LZ4_compress_default now with our size values and pointers to our memory locations.
  // Save the return value for error checking.
  const int compressed_data_size = LZ4_compress_default(src, compressed_data, src_size, max_dst_size);
  // Check return_value to determine what happened.
  if (compressed_data_size <= 0)
    run_screaming("A 0 or negative result from LZ4_compress_default() indicates a failure trying to compress the data. ", 1);
  if (compressed_data_size > 0)
    printf("We successfully compressed some data! Ratio: %.2f\n",
           (float)compressed_data_size / src_size);
  // Not only does a positive return_value mean success, the value returned == the number of bytes required.
  // You can use this to realloc() *compress_data to free up memory, if desired.  I'll do so just to demonstrate the concept.
  compressed_data = (char *)realloc(compressed_data, (size_t)compressed_data_size);
  if (compressed_data == NULL)
    run_screaming("Failed to re-alloc memory for compressed_data.  Sad :(", 1);

  /* Decompression */
  // Now that we've successfully compressed the information from *src to *compressed_data, let's do the opposite!
  // The decompression will need to know the compressed size, and an upper bound of the decompressed size.
  // In this example, we just re-use this information from previous section,
  // but in a real-world scenario, metadata must be transmitted to the decompression side.
  // Each implementation is in charge of this part. Oftentimes, it adds some header of its own.
  // Sometimes, the metadata can be extracted from the local context.

  // First, let's create a *new_src location of size src_size since we know that value.
  char *const regen_buffer = (char *)malloc(src_size);
  if (regen_buffer == NULL)
    run_screaming("Failed to allocate memory for *regen_buffer.", 1);
  // The LZ4_decompress_safe function needs to know where the compressed data is, how many bytes long it is,
  // where the regen_buffer memory location is, and how large regen_buffer (uncompressed) output will be.
  // Again, save the return_value.
  const int decompressed_size = LZ4_decompress_safe(compressed_data, regen_buffer, compressed_data_size, src_size);
  free(compressed_data); /* no longer useful */
  if (decompressed_size < 0)
    run_screaming("A negative result from LZ4_decompress_safe indicates a failure trying to decompress the data.  See exit code (echo $?) for value returned.", decompressed_size);
  if (decompressed_size >= 0)
    printf("We successfully decompressed some data!\n");
  // Not only does a positive return value mean success,
  // value returned == number of bytes regenerated from compressed_data stream.
  if (decompressed_size != src_size)
    run_screaming("Decompressed data is different from original! \n", 1);

  /* Validation */
  // We should be able to compare our original *src with our *new_src and be byte-for-byte identical.
  if (memcmp(src, regen_buffer, src_size) != 0)
    run_screaming("Validation failed.  *src and *new_src are not identical.", 1);
  printf("Validation done. The string we ended up with is:\n%s\n", regen_buffer);
  return 0;
}
