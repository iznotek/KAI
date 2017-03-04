#pragma once

KAI_BEGIN

struct StorageBase;

class Registry;

template <class T> struct Pointer;

struct StorageBase;

///
/// A Reflected object has access to the Registry that made it.
///
/// Refelected objects can overload Create() Destroy() and Delete() methods.
/// While any type can be added to a Registry, Reflected types have access
/// to the registry that made it, as well as the Object associated with the
/// stored value.
///
template <class T>
class Reflected
{
public:
	/// The KAI-space equivalence of 'this'.
	mutable StorageBase * const Self;

#ifdef KAI_DEBUG_REFLECTED_VALUE
	/// Enables us to see the value from a debugger.
	mutable const T * const Value;
#endif

	virtual ~Reflected() { }

	/// Called after object constructed, but before first use.
	virtual void Create() 
	{ 
#ifdef KAI_DEBUG_REFLECTED_VALUE
		Value = dynamic_cast<T const *>(this);
#endif
	}
	
	/// Called when object moved to deathrow, but before deleted.
	virtual void Destroy() { }

	/// Called immediately before resources are released.
	virtual void Delete() { }				

	/// Get the registry that created and owns this Object.
	Registry &Reg() const;
};

KAI_END
