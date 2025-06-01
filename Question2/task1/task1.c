#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

// =============================
// == BEGIN TinySHA2 (SHA-256) ==
// =============================
typedef struct {
    uint64_t total[2];
    uint32_t state[8];
    uint8_t buffer[64];
} SHA256_CTX;

void sha256_init(SHA256_CTX* ctx);
void sha256_update(SHA256_CTX* ctx, const uint8_t* data, size_t len);
void sha256_final(SHA256_CTX* ctx, uint8_t digest[32]);

static void sha256_transform(SHA256_CTX* ctx, const uint8_t data[64]) {
    uint32_t a, b, c, d, e, f, g, h;
    uint32_t w[64], i;

    for (i = 0; i < 16; ++i)
        w[i] = (uint32_t)data[i * 4] << 24 | (uint32_t)data[i * 4 + 1] << 16 |
               (uint32_t)data[i * 4 + 2] << 8 | (uint32_t)data[i * 4 + 3];

    for (; i < 64; ++i)
        w[i] = 0;

    a = ctx->state[0]; b = ctx->state[1]; c = ctx->state[2]; d = ctx->state[3];
    e = ctx->state[4]; f = ctx->state[5]; g = ctx->state[6]; h = ctx->state[7];

    #define S(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
    #define R(x, n) ((x) >> (n))
    #define Ch(x, y, z) ((x & y) ^ (~x & z))
    #define Maj(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
    #define Sigma0(x) (S(x, 2) ^ S(x,13) ^ S(x,22))
    #define Sigma1(x) (S(x, 6) ^ S(x,11) ^ S(x,25))
    #define sigma0(x) (S(x, 7) ^ S(x,18) ^ R(x, 3))
    #define sigma1(x) (S(x,17) ^ S(x,19) ^ R(x,10))

    for (i = 0; i < 64; ++i) {
        uint32_t t1 = h + Sigma1(e) + Ch(e, f, g) + 0x428a2f98 + w[i];
        uint32_t t2 = Sigma0(a) + Maj(a, b, c);
        h = g; g = f; f = e; e = d + t1;
        d = c; c = b; b = a; a = t1 + t2;
    }

    ctx->state[0] += a; ctx->state[1] += b; ctx->state[2] += c;
    ctx->state[3] += d; ctx->state[4] += e; ctx->state[5] += f;
    ctx->state[6] += g; ctx->state[7] += h;
}

void sha256_init(SHA256_CTX* ctx) {
    static const uint32_t iv[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };
    memcpy(ctx->state, iv, 32);
    memset(ctx->buffer, 0, 64);
    ctx->total[0] = ctx->total[1] = 0;
}

void sha256_update(SHA256_CTX* ctx, const uint8_t* data, size_t len) {
    size_t left = ctx->total[0] & 63;
    ctx->total[0] += len;
    if (ctx->total[0] < len) ctx->total[1]++;

    while (left && len) {
        ctx->buffer[left--] = *data++;
        len--;
    }

    while (len >= 64) {
        sha256_transform(ctx, data);
        data += 64;
        len -= 64;
    }

    if (len) {
        memcpy(ctx->buffer, data, len);
    }
}

void sha256_final(SHA256_CTX* ctx, uint8_t digest[32]) {
    uint8_t pad[64];
    size_t i, len = ctx->total[0] & 63;
    uint64_t bitlen = (ctx->total[0] + ctx->total[1] * 0x100000000ULL) * 8;

    pad[0] = 0x80;
    for (i = 1; i < 64; ++i) pad[i] = 0;

    if (len < 56) {
        sha256_update(ctx, pad, 56 - len);
    } else {
        sha256_update(ctx, pad, 64 - len + 56);
    }

    for (i = 0; i < 8; ++i)
        pad[i] = (uint8_t)(bitlen >> (56 - i * 8));
    sha256_update(ctx, pad, 8);

    for (i = 0; i < 32; ++i)
        digest[i] = (uint8_t)(ctx->state[i >> 2] >> (24 - (i & 3) * 8));
}
// =============================
// == END TinySHA2 (SHA-256) ==
// =============================

#define HASH_SIZE 32
#define MAX_TRANSACTIONS 10
#define TRANSACTION_SIZE 100

// Convert hash bytes to hex string
void hash_to_hex(const uint8_t* hash, size_t len, char* output) {
    for (size_t i = 0; i < len; ++i) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[len * 2] = '\0';
}

// Define Block structure
typedef struct {
    int index;
    time_t timestamp;
    char transactions[MAX_TRANSACTIONS][TRANSACTION_SIZE];
    char previous_hash[HASH_SIZE * 2 + 1]; // Hex encoded
    int nonce;
} Block;

// Calculate the hash of a block
void calculate_block_hash(const Block* block, char* output_hash) {
    char data[1024];

    snprintf(data, sizeof(data),
             "%d%ld%s%s%d",
             block->index,
             block->timestamp,
             block->transactions[0],
             block->previous_hash,
             block->nonce);

    uint8_t hash[HASH_SIZE];
    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, (uint8_t*)data, strlen(data));
    sha256_final(&ctx, hash);

    hash_to_hex(hash, HASH_SIZE, output_hash);
}

// Create genesis block
void create_genesis_block(Block* block) {
    block->index = 0;
    block->timestamp = time(NULL);
    strcpy(block->transactions[0], "Genesis Transaction");
    strcpy(block->previous_hash, "0");
    block->nonce = 0;

    char hash[HASH_SIZE * 2 + 1];
    calculate_block_hash(block, hash);
    printf("Genesis Block Hash: %s\n", hash);
}

int main() {
    Block genesis;
    create_genesis_block(&genesis);

    return 0;
}
