#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "sha3/sph_blake.h"
#include "sha3/sph_bmw.h"
#include "sha3/sph_groestl.h"
#include "sha3/sph_jh.h"
#include "sha3/sph_keccak.h"
#include "sha3/sph_skein.h"
#include "sha3/sph_luffa.h"
#include "sha3/sph_cubehash.h"
#include "sha3/sph_shavite.h"
#include "sha3/sph_simd.h"
#include "sha3/sph_echo.h"
#include "sha3/sph_hamsi.h"
#include "sha3/sph_fugue.h"
#include "sha3/sph_shabal.h"
#include "sha3/sph_whirlpool.h"
#include "sha3/sph_sha2.h"
#include "sha3/sph_haval.h"
#include "sha3/sph_gost.h"

void x22i_hash(const char* input, char* output)
{
    sph_blake512_context      ctx_blake;
    sph_bmw512_context        ctx_bmw;
    sph_groestl512_context    ctx_groestl;
    sph_jh512_context         ctx_jh;
    sph_keccak512_context     ctx_keccak;
    sph_skein512_context      ctx_skein;
    sph_luffa512_context      ctx_luffa;
    sph_cubehash512_context   ctx_cubehash;
    sph_shavite512_context    ctx_shavite;
    sph_simd512_context       ctx_simd;
    sph_echo512_context       ctx_echo;
    sph_hamsi512_context      ctx_hamsi;
    sph_fugue512_context      ctx_fugue;
    sph_shabal512_context     ctx_shabal;
    sph_whirlpool_context     ctx_whirlpool;
    sph_sha512_context        ctx_sha2;
    sph_haval256_5_context    ctx_haval;
    sph_tiger_context         ctx_tiger;
    sph_gost512_context       ctx_gost;
    sph_sha256_context        ctx_sha;

    uint8_t hash[21 * 64];

    sph_blake512_init(&ctx_blake);
    sph_blake512 (&ctx_blake, input, 80);
    sph_blake512_close(&ctx_blake, hash);

    sph_bmw512_init(&ctx_bmw);
    sph_bmw512 (&ctx_bmw, hash, 64);
    sph_bmw512_close(&ctx_bmw, hash + 1*64);

    sph_groestl512_init(&ctx_groestl);
    sph_groestl512 (&ctx_groestl, hash + 1*64, 64);
    sph_groestl512_close(&ctx_groestl, hash + 2*64);

    sph_skein512_init(&ctx_skein);
    sph_skein512 (&ctx_skein, hash + 2*64, 64);
    sph_skein512_close(&ctx_skein, hash + 3*64);

    sph_jh512_init(&ctx_jh);
    sph_jh512 (&ctx_jh, hash + 3*64, 64);
    sph_jh512_close(&ctx_jh, hash + 4*64);

    sph_keccak512_init(&ctx_keccak);
    sph_keccak512 (&ctx_keccak, hash + 4*64, 64);
    sph_keccak512_close(&ctx_keccak, hash + 5*64);

    sph_luffa512_init(&ctx_luffa);
    sph_luffa512 (&ctx_luffa, hash + 5*64, 64);
    sph_luffa512_close(&ctx_luffa, hash + 6*64);

    sph_cubehash512_init(&ctx_cubehash);
    sph_cubehash512 (&ctx_cubehash, hash + 6*64, 64);
    sph_cubehash512_close(&ctx_cubehash, hash + 7*64);

    sph_shavite512_init(&ctx_shavite);
    sph_shavite512(&ctx_shavite, hash + 7*64, 64);
    sph_shavite512_close(&ctx_shavite, hash + 8*64);

    sph_simd512_init(&ctx_simd);
    sph_simd512 (&ctx_simd, hash + 8*64, 64);
    sph_simd512_close(&ctx_simd, hash + 9*64);

    sph_echo512_init(&ctx_echo);
    sph_echo512 (&ctx_echo, hash + 9*64, 64);
    sph_echo512_close(&ctx_echo, hash + 10*64);

    sph_hamsi512_init(&ctx_hamsi);
    sph_hamsi512 (&ctx_hamsi, hash + 10*64, 64);
    sph_hamsi512_close(&ctx_hamsi, hash + 11*64);

    sph_fugue512_init(&ctx_fugue);
    sph_fugue512 (&ctx_fugue, hash + 11*64, 64);
    sph_fugue512_close(&ctx_fugue, hash + 12*64);

    sph_shabal512_init(&ctx_shabal);
    sph_shabal512 (&ctx_shabal, hash + 12*64, 64);
    sph_shabal512_close(&ctx_shabal, hash + 13*64);

    sph_whirlpool_init(&ctx_whirlpool);
    sph_whirlpool (&ctx_whirlpool, hash + 13*64, 64);
    sph_whirlpool_close(&ctx_whirlpool, hash + 14*64);

    sph_sha512_init(&ctx_sha2);
    sph_sha512 (&ctx_sha2, hash + 14*64, 64);
    sph_sha512_close(&ctx_sha2, hash + 15*64);

    unsigned char temp[SWIFFTX_OUTPUT_BLOCK_SIZE] = {0};
    InitializeSWIFFTX();
    ComputeSingleSWIFFTX(hash + 12*64, temp, false);

    memcpy(hash + 16*64, temp, 64);
    sph_haval256_5_init(&ctx_haval);
    sph_haval256_5 (&ctx_haval, hash + 16*64, 64);
    sph_haval256_5_close(&ctx_haval, hash + 17*64);

    sph_tiger_init(&ctx_tiger);
    sph_tiger (&ctx_tiger, hash + 17*64, 64);
    sph_tiger_close(&ctx_tiger, hash + 18*64);

    LYRA2(hash + 19*64, 32, hash + 18*64, 32, hash + 18*64, 32, 1, 4, 4);

    sph_gost512_init(&ctx_gost);
    sph_gost512 (&ctx_gost, hash + 19*64, 64);
    sph_gost512_close(&ctx_gost, hash + 20*64);

    sph_sha256_init(&ctx_sha);
    sph_sha256 (&ctx_sha, hash + 20*64, 64);
    sph_sha256_close(&ctx_sha, output);
}
