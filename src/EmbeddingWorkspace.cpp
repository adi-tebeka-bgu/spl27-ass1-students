#include "MemoryBlock.h"

EmbeddingWorkspace::EmbeddingWorkspace(size_t size) : MemoryBlock(size) {}

IdleAction EmbeddingWorkspace::onLastRelease() const
{
    return IdleAction::Destroy;
}
MemoryBlock *EmbeddingWorkspace::clone() const
{
    return new EmbeddingWorkspace(*this);
}