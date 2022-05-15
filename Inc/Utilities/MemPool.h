/// \file MemPool.h

#ifndef guard_MEM_POOL_H
# define guard_MEM_POOL_H

# include <Compiler.h>
# include <Debug.h>

template<unsigned SIZE, unsigned NUM>
class MemPool final
{
  public:
  
  MemPool() noexcept { }
  
  MemPool(MemPool const &) = delete;
  MemPool(MemPool      &&) = delete;

  ~MemPool() = default;
  
  MemPool & operator = (MemPool const &) = delete;
  MemPool & operator = (MemPool      &&) = delete;

  static constexpr unsigned const al = sizeof(WORD);
  static constexpr unsigned const size = ((SIZE + al - 1U) / al) * al;
  static constexpr unsigned const dim = NUM;

  void * Alloc() noexcept 
  {
    ASSERT(cntr < dim);
    
    return pool + cntr++;
  }

  private:

  using BufferType = BYTE[size];

  BufferType pool[dim];
  unsigned cntr = 0U;
};

#endif
