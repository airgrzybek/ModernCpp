/*
 * Chunk.h
 *
 *  Created on: 28 paü 2015
 *      Author: xxpowdaw
 */

#ifndef SMALLOBJECTALLOCATION_CHUNK_H_
#define SMALLOBJECTALLOCATION_CHUNK_H_

#include <cstdlib>

namespace Memory
{

    struct Chunk
    {
        void Init(std::size_t blockSize, unsigned char blocks);
        void* Allocate(std::size_t blockSize);
        void Deallocate(void* p, std::size_t blockSize);
        void Release();
        void Reset(std::size_t blockSize, unsigned char blocks );
        bool IsBlockAvailable( void * p, unsigned char numBlocks, std::size_t blockSize ) const;

        /// Returns true if block at address P is inside this Chunk.
        inline bool HasBlock( void * p, std::size_t chunkLength ) const
        {
            unsigned char * pc = static_cast< unsigned char * >( p );
            return ( pData <= pc ) && ( pc < pData + chunkLength );
        }

        inline bool HasAvailable( unsigned char numBlocks ) const
        {
            return ( blocksAvailable == numBlocks );
        }

        inline bool IsFilled( void ) const
        {
            return ( 0 == blocksAvailable );
        }
        /*!
         * Pointer holds chunk of data.
         */
        unsigned char* pData;

        /*!
         * Holds first chunk available for allocation in this chunk.
         */
        unsigned char firstAvailableBlock;

        /*!
         * Holds number of available chunks.
         */
        unsigned char blocksAvailable;
    };

}/* Memory*/


#endif /* SMALLOBJECTALLOCATION_CHUNK_H_ */
