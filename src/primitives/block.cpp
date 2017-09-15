// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "primitives/block.h"
#include "hash.h"
#include "tinyformat.h"
#include "utilstrencodings.h"
#include "crypto/common.h"
#include "compat/endian.h"
#include "dag_singleton.h"
<<<<<<< HEAD
=======

namespace
{
    #pragma pack(push, 1)
    /**
    *   The Keccak-256 hash of this structure is used as input for egihash
    *   It is a truncated block header with a deterministic encoding
    *   All integer values are little endian
    *   Hashes are the nul-terminated hex encoded representation as if ToString() was called
    */
    struct CBlockHeaderTruncatedLE
    {
        int32_t nVersion;
        char hashPrevBlock[65];
        char hashMerkleRoot[65];
        uint32_t nTime;
        uint32_t nBits;
        uint32_t nHeight;

        CBlockHeaderTruncatedLE(CBlockHeader const & h)
        : nVersion(htole32(h.nVersion))
        , hashPrevBlock{0}
        , hashMerkleRoot{0}
        , nTime(htole32(h.nTime))
        , nBits(htole32(h.nBits))
        , nHeight(htole32(h.nHeight))
        {
            auto prevHash = h.hashPrevBlock.ToString();
            memcpy(hashPrevBlock, prevHash.c_str(), (std::min)(prevHash.size(), sizeof(hashPrevBlock)));

            auto merkleRoot = h.hashMerkleRoot.ToString();
            memcpy(hashMerkleRoot, merkleRoot.c_str(), (std::min)(merkleRoot.size(), sizeof(hashMerkleRoot)));
        }
    };
    #pragma pack(pop)
}
>>>>>>> upstream/energi_v0

namespace
{
<<<<<<< HEAD
    #pragma pack(push, 1)
    /**
    *   The Keccak-256 hash of this structure is used as input for egihash
    *   It is a truncated block header with a deterministic encoding
    *   All integer values are little endian
    *   Hashes are the nul-terminated hex encoded representation as if ToString() was called
    */
    struct CBlockHeaderTruncatedLE
    {
        int32_t nVersion;
        char hashPrevBlock[65];
        char hashMerkleRoot[65];
        uint32_t nTime;
        uint32_t nBits;
        uint32_t nHeight;

        CBlockHeaderTruncatedLE(CBlockHeader const & h)
        : nVersion(htole32(h.nVersion))
        , hashPrevBlock{0}
        , hashMerkleRoot{0}
        , nTime(htole32(h.nTime))
        , nBits(htole32(h.nBits))
        , nHeight(htole32(h.nHeight))
        {
            auto prevHash = h.hashPrevBlock.ToString();
            memcpy(hashPrevBlock, prevHash.c_str(), (std::min)(prevHash.size(), sizeof(hashPrevBlock)));

            auto merkleRoot = h.hashMerkleRoot.ToString();
            memcpy(hashMerkleRoot, merkleRoot.c_str(), (std::min)(merkleRoot.size(), sizeof(hashMerkleRoot)));
        }
    };
    #pragma pack(pop)
}

uint256 CBlockHeader::GetHash(uint32_t blockHeight) const
{
<<<<<<< HEAD
    // BEGIN(a) = ((char*)&(a))
    // END(a)   = ((char*)&((&(a))[1]))
    auto egihash_result = egihash::full::hash(egihash::dag_t(blockHeight),
                                egihash::h256_t(&nVersion, sizeof(nVersion)), // TODO: this is not right, should be hash of serialized block header without mixhash + nonce
                                nNonce);
    std::vector<uint8_t> val(32, 0);
    std::memcpy(&val[0], &(egihash_result.value.b[0]), 32);
    return uint256(val);
=======
=======
>>>>>>> upstream/energi_v0
    CBlockHeaderTruncatedLE truncatedBlockHeader(*this);
    egihash::h256_t headerHash(&truncatedBlockHeader, sizeof(truncatedBlockHeader));
    egihash::result_t ret;
    // if we have a DAG loaded, use it
    auto const & dag = ActiveDAG();
    if (dag && ((nHeight / egihash::constants::EPOCH_LENGTH) == dag->epoch()))
    {
        ret = egihash::full::hash(*dag, headerHash, nNonce);
    }
    else // otherwise all we can do is generate a light hash
    {
        // TODO: pre-load caches and seed hashes
        ret = egihash::light::hash(egihash::cache_t(nHeight, egihash::get_seedhash(nHeight)), headerHash, nNonce);
    }

    hashMix = uint256(ret.mixhash);
    return uint256(ret.value);
<<<<<<< HEAD
>>>>>>> upstream/energi_v0
=======
>>>>>>> upstream/energi_v0
}

std::string CBlock::ToString(uint32_t blockHeight) const
{
    std::stringstream s;
<<<<<<< HEAD
<<<<<<< HEAD
    s << strprintf("CBlock(hash=%s, ver=%d, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%u, nBits=%08x, nNonce=%u, hashMix=%s, vtx=%u)\n",
        GetHash(blockHeight).ToString(),
        nVersion,
        hashPrevBlock.ToString(),
        hashMerkleRoot.ToString(),
        nTime, nBits, nNonce,
        hashMix.ToString(),
=======
    s << strprintf("CBlock(hash=%s, ver=%d, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%u, nBits=%08x, nHeight=%u, hashMix=%s, nNonce=%u, vtx=%u)\n",
        GetHash().ToString(),
        nVersion,
        hashPrevBlock.ToString(),
        hashMerkleRoot.ToString(),
        nTime, nBits, nHeight,
        hashMix.ToString(),
        nNonce,
>>>>>>> upstream/energi_v0
=======
    s << strprintf("CBlock(hash=%s, ver=%d, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%u, nBits=%08x, nHeight=%u, hashMix=%s, nNonce=%u, vtx=%u)\n",
        GetHash().ToString(),
        nVersion,
        hashPrevBlock.ToString(),
        hashMerkleRoot.ToString(),
        nTime, nBits, nHeight,
        hashMix.ToString(),
        nNonce,
>>>>>>> upstream/energi_v0
        vtx.size());
    for (unsigned int i = 0; i < vtx.size(); i++)
    {
        s << "  " << vtx[i].ToString() << "\n";
    }
    return s.str();
}
