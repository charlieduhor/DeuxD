
#ifndef __DEUXD_MEMORYPOOL_H__
#define __DEUXD_MEMORYPOOL_H__

#include <atomic>
#include <cstddef>
#include <stdexcept>
#include <vector>

DD_NS_BEGIN

class PooledObject;

class DD_PUBLIC AutoreleasePool {
protected:
   static thread_local AutoreleasePool* stCurrent;

protected:
   AutoreleasePool* mPrevious;

public:
   AutoreleasePool();
   ~AutoreleasePool();

protected:
   std::vector<PooledObject*> mObjects;

public:
   void clear();

public:
   static void add(PooledObject*);
};

class DD_PUBLIC PooledObject {
   friend class AutoreleasePool;

private:
   std::atomic_uint32_t mRefCount;

   inline uint32_t retain() {
      return ++mRefCount;
   }

   inline uint32_t release() {
      uint32_t c = --mRefCount;

      if (c == 0) {
         delete this;
      }
       
      return c;
   }

   inline void autorelease() {
      AutoreleasePool::add(this);
   }

public:
   inline PooledObject() : mRefCount(1) {
      autorelease();
   }

   virtual ~PooledObject() {
#ifdef _DEBUG
      if (mRefCount != 0) {
         throw std::logic_error("Reference count is NOT zero");
      }
#endif
   }
};

template <typename T> class Pointer {
public:
   T* p;

public:
   inline Pointer() : p(nullptr) {
   }

   inline Pointer(std::nullptr_t) : p(nullptr) {
   }

   inline Pointer(T* ptr) : p(ptr) {
      if (ptr) {
         ptr->retain();
      }
   }

   inline Pointer(const Pointer<T>& ptr) : p(ptr.p) {
      if (p) {
         p->mRefCount++;
      }
   }

  inline  Pointer(Pointer<T>&& ptr) : p(ptr.p) {
      ptr.p = nullptr;
   }

   inline ~Pointer() {
      if (p) {
         p->release();
      }

#ifdef _DEBUG
      p = nullptr;
#endif
   }

   inline operator T*() const {
      return p;
   }

   inline Pointer<T>& operator = (T* ptr) {
      if (p == ptr) {
         return;
      }

      if (p) {
         p->release();
      }

      p = ptr;

      if (p) {
         p->retain();
      }

      return *this;
   }

   inline Pointer<T>& operator = (const Pointer<T>& ptr) {
      if (p == ptr.p) {
         return;
      }

      if (p) {
         p->release();
      }

      p = ptr.p;

      if (p) {
         p->retain();
      }

      return *this;
   }

   inline Pointer<T>& operator = (Pointer<T>&& ptr) {
      if (p) {
         p->release();
      }

      p     = ptr.p;
      ptr.p = nullptr;
      return *this;
   }

   inline Pointer<T>& operator = (std::nullptr_t) {
      if (p) {
         p->release();
         p = nullptr;
      }
   }
};

DD_NS_END

#endif
