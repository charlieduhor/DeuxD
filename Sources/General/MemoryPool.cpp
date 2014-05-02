
#include <DeuxD/DeuxD.h>

#include <algorithm>

DD_NS_USING

AutoreleasePool::AutoreleasePool() {
   mPrevious = stCurrent;
   stCurrent = this;
}

AutoreleasePool::~AutoreleasePool() {
   stCurrent = mPrevious;
   clear();
}

void AutoreleasePool::clear() {
   std::for_each(std::begin(mObjects), std::end(mObjects), [](PooledObject* o) {
      o->release();
   });

   mObjects.clear();
}

void AutoreleasePool::add(PooledObject* obj) {
   stCurrent->mObjects.push_back(obj);
}
