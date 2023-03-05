#ifndef __MemoryAllocatorConfig_H__
#define __MemoryAllocatorConfig_H__

#include "MeAllocatedObject.h" 

/** \addtogroup Core
*  @{
*/
/** \addtogroup Memory
*  @{
*/
/** @file

This file configures Ogre's memory allocators. You can modify this
file to alter the allocation routines used for Ogre's main objects.

When customising memory allocation, all you need to do is provide one or
more custom allocation policy classes. These classes need to implement:

@code
// Allocate bytes - file/line/func information should be optional, 
// will be provided when available but not everywhere (e.g. release mode, STL allocations)
static inline void* allocateBytes(size_t count, const char* file = 0, int line = 0, const char* func = 0);
// Free bytes
static inline void deallocateBytes(void* ptr);
// Return the max number of bytes available to be allocated in a single allocation
static inline size_t getMaxAllocationSize();
@endcode

Policies are then used as implementations for the wrapper classes and macros 
which call them. AllocatedObject for example provides the hooks to override
the new and delete operators for a class and redirect the functionality to the
policy. STLAllocator is a class which is provided to STL containers in order
to hook up allocation of the containers members to the allocation policy.
@par
In addition to linking allocations to policies, this class also defines
a number of macros to allow debugging information to be passed along with
allocations, such as the file and line number they originate from. It's
important to realise that we do not redefine the 'new' and 'delete' symbols 
with macros, because that's very difficult to consistently do when other
libraries are also trying to do the same thing; instead we use dedicated
'ME_' prefixed macros. See ME_NEW and related items.
@par
The base macros you can use are listed below, in order of preference and 
with their conditions stated:
<ul>
<li>ME_NEW - use to allocate an object which have custom new/delete operators
to handle custom allocations, usually this means it's derived from AllocatedObject. 
Free the memory using ME_DELETE. You can in fact use the regular new/delete
for these classes but you won't get any line number debugging if you do.
The memory category is automatically derived for these classes; for all other
allocations you have to specify it.
</li>
<li>ME_NEW_T - use to allocate a single class / struct that does not have custom
new/delete operators, either because it is non-virtual (Vector3, Quaternion),
or because it is from an external library (e.g. STL). You must
deallocate with ME_DELETE_T if you expect the destructor to be called. 
You may free the memory using ME_FREE if you are absolutely sure there
is no destructor to be called. 
These macros ensure that constructors and destructors are called correctly 
even though the memory originates externally (via placement new). Also note 
that you have to specify the type and memory category so that the correct 
allocator can be derived, when both allocating
and freeing.
</li>
<li>ME_NEW_ARRAY_T - as ME_NEW_T except with an extra parameter to construct
multiple instances in contiguous memory. Again constructors and destructors
are called. Free with ME_DELETE_ARRAY_T.
</li>
<li>ME_ALLOC_T - use to allocate a set of primitive types conveniently with type safety. 
This <i>can</i> also be used for classes and structs but it is <b>imperative</b> that
you understand that neither the constructor nor the destructor will be called. 
Sometimes you want this because it's more efficient just to grab/free a chunk of
memory without having to iterate over each element constructing / destructing.
Free the memory with ME_FREE. </li>
<li>ME_MALLOC - the most raw form of allocation, just a set of bytes. 
Use ME_FREE to release.</li>
<li>_SIMD and _ALIGN variants - all of the above have variations which allow
aligned memory allocations. The _SIMD versions align automatically to the
SIMD requirements of your platform, the _ALIGN variants allow user-defined
alignment to be specified. </li>
</ul>
Here are some examples:
@code
/// AllocatedObject subclass, with custom operator new / delete
AllocatedClass* obj = ME_NEW AllocatedClass();
ME_DELETE obj;
AllocatedClass* array = ME_NEW AllocatedClass[10];
ME_DELETE [] obj;
/// Non-virtual or external class, constructors / destructors called
ExternalClass* obj = ME_NEW_T(ExternalClass, MEMCATEGORY_GENERAL)(constructorArgs);
ME_DELETE_T(obj, ExternalClass, MEMCATEGORY_GENERAL);
ExternalClass* obj = ME_NEW_ARRAY_T(ExternalClass, 10, MEMCATEGORY_GENERAL);
ME_DELETE_ARRAY_T(obj, NonVirtualClass, 10, MEMCATEGORY_GENERAL);
/// Primitive types
long* pLong = ME_ALLOC_T(long, 10, MEMCATEGORY_GENERAL);
ME_FREE(pLong, MEMCATEGORY_GENERAL);
/// Primitive type with constructor (you can mismatch ME_NEW_T and ME_FREE because no destructor)
long* pLong = ME_NEW_T(long, MEMCATEGORY_GENERAL)(0);
ME_FREE(pLong, MEMCATEGORY_GENERAL);
/// Raw memory
void* pVoid = ME_MALLOC(1024, MEMCATEGORY_GENERAL);
ME_FREE(pVoid, MEMCATEGORY_GENERAL);
@endcode
ME_ALLOC_T is also the route to go for allocating real primitive types like 
int & float. You free the memory using ME_FREE, and both variants have SIMD
and custom alignment variants.
*/
/** @} */
/** @} */

/** \addtogroup Core
*  @{
*/
/** \addtogroup Memory
*  @{
*/

/** A set of categories that indicate the purpose of a chunk of memory
being allocated. 
These categories will be provided at allocation time in order to allow
the allocation policy to vary its behaviour if it wishes. This allows you
to use a single policy but still have variant behaviour. The level of 
control it gives you is at a higher level than assigning different 
policies to different classes, but is the only control you have over
general allocations that are primitive types.
*/
enum MemoryCategory
{
	/// General purpose
	MEMCATEGORY_GENERAL = 0,
	/// Geometry held in main memory
	MEMCATEGORY_GEOMETRY = 1, 
	/// Animation data like tracks, bone matrices
	MEMCATEGORY_ANIMATION = 2, 
	/// Nodes, control data
	MEMCATEGORY_SCENE_CONTROL = 3,
	/// Scene object instances
	MEMCATEGORY_SCENE_OBJECTS = 4,
	/// Other resources
	MEMCATEGORY_RESOURCE = 5,
	/// Scripting
	MEMCATEGORY_SCRIPTING = 6,
	/// Rendersystem structures
	MEMCATEGORY_RENDERSYS = 7,


	// sentinel value, do not use 
	MEMCATEGORY_COUNT = 8
};
/** @} */
/** @} */


#include "MeAllocatedObject.h"

#define ME_MEMORY_ALLOCATOR_STD 1
#define ME_MEMORY_ALLOCATOR_NED 2
#define ME_MEMORY_ALLOCATOR_USER 3
#define ME_MEMORY_ALLOCATOR_NEDPOOLING 4

#define ME_MEMORY_ALLOCATOR ME_MEMORY_ALLOCATOR_STD



#if ME_MEMORY_ALLOCATOR == ME_MEMORY_ALLOCATOR_NEDPOOLING
//#  include "MeMemoryNedPooling.h"
// configure default allocators based on the options above
// notice how we're not using the memory categories here but still roughing them out
// in your allocators you might choose to create different policies per category

// configurable category, for general malloc
// notice how we ignore the category here, you could specialise
//template <MemoryCategory Cat> class CategorisedAllocPolicy : public NedPoolingPolicy{};
//template <MemoryCategory Cat, size_t align = 0> class CategorisedAlignAllocPolicy : public NedPoolingAlignedPolicy<align>{};

#elif ME_MEMORY_ALLOCATOR == ME_MEMORY_ALLOCATOR_NED

//#  include "MeNedAllocation.h"
// configure default allocators based on the options above
// notice how we're not using the memory categories here but still roughing them out
// in your allocators you might choose to create different policies per category

// configurable category, for general malloc
// notice how we ignore the category here, you could specialise
//template <MemoryCategory Cat> class CategorisedAllocPolicy : public MeNedAllocation{};
//template <MemoryCategory Cat, size_t align = 0> class CategorisedAlignAllocPolicy : public NedAlignedAllocPolicy<align>{};
#elif ME_MEMORY_ALLOCATOR == ME_MEMORY_ALLOCATOR_STD

#  include "MeNedAllocation.h"	
template <MemoryCategory Cat> class CategorisedAllocPolicy : public MeStdAllocation{};

#else

// your allocators here?

#endif

// Useful shortcuts
typedef CategorisedAllocPolicy<MEMCATEGORY_GENERAL> GeneralAllocPolicy;
typedef CategorisedAllocPolicy<MEMCATEGORY_GEOMETRY> GeometryAllocPolicy;
typedef CategorisedAllocPolicy<MEMCATEGORY_ANIMATION> AnimationAllocPolicy;
typedef CategorisedAllocPolicy<MEMCATEGORY_SCENE_CONTROL> SceneCtlAllocPolicy;
typedef CategorisedAllocPolicy<MEMCATEGORY_SCENE_OBJECTS> SceneObjAllocPolicy;
typedef CategorisedAllocPolicy<MEMCATEGORY_RESOURCE> ResourceAllocPolicy;
typedef CategorisedAllocPolicy<MEMCATEGORY_SCRIPTING> ScriptingAllocPolicy;
typedef CategorisedAllocPolicy<MEMCATEGORY_RENDERSYS> RenderSysAllocPolicy;

#endif