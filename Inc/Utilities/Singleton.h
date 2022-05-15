/// \file Singleton.h
/// Klassisches Singleton-Entwurfsmuster ohne Verwendung dynamischen Speichers.

#ifndef guard_SINGLETON_H
# define guard_SINGLETON_H

# include <Compiler.h>
# include <Debug.h>

template<class CLASS>
class InstanceWrapper final
{ 
  public:
  
  InstanceWrapper() noexcept { ITM_PUTS(FUNC); STACK_CHECK(); }
  
  InstanceWrapper(InstanceWrapper const &) = delete;
  InstanceWrapper(InstanceWrapper      &&) = delete;

  ~InstanceWrapper() = default;

  InstanceWrapper & operator = (InstanceWrapper const &) = delete;
  InstanceWrapper & operator = (InstanceWrapper      &&) = delete;

  FORCE_INLINE CLASS & GetInstance() { return instance; }
  
  private:

  CLASS instance;
};

/// Klassisches Singleton-Entwurfsmuster.
/// \tparam CLASS ist der Datentyp, der als einzelstück implemeniert werden soll.
template<class CLASS>
class Singleton final
{ 
  public:
  
  Singleton() = delete;
  Singleton(Singleton const &) = delete;
  Singleton(Singleton      &&) = delete;

  ~Singleton() = default;

  Singleton & operator = (Singleton const &) = delete;
  Singleton & operator = (Singleton      &&) = delete;
  
  static FORCE_INLINE CLASS & Create() noexcept
  { 
    static InstanceWrapper<CLASS> wrapper;

    return wrapper.GetInstance(); 
  }

  static FORCE_INLINE CLASS & GetInstance() noexcept __attribute__((constructor))
  { 
    return Create(); 
  }
};

#endif
