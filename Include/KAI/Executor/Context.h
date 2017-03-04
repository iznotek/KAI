#pragma once

#include <KAI/Core/Continuation.h>

KAI_BEGIN

///
/// Context for an Executor.
///
/// This is analogous to a stack frame in C/ASM
///
class Context
{
	/// What we are currently executing
	Pointer<Continuation> _continuation;

	/// Object used for name lookps. Can be empty.
	Object _scope;
	
	/// The current 'instruction pointer' - or, index into the
	/// code of the Continuation
	int _ip;

	/// all scopes are mapped onto a folder in the local file system
	Pointer<FileSystem::Path> _path;

public:
	void Create(Pointer<Continuation>);
	void Create(Pointer<Continuation>, Object);

	Object NextInstruction();
	Object GetScope() const { return _scope; }
	void SetScope(Object const &Q) { _scope = Q; }

	static void Register(Registry &);

public:
	friend StringStream &operator<<(StringStream &, const Context&);
	friend StringStream &operator>>(StringStream &, Context&);

	friend StringStream &operator<<(StringStream &, const Context&);
	friend StringStream &operator>>(StringStream &, Context&);
};

KAI_TYPE_TRAITS(
	Contenxt,
	Number::Context,
	Properties::Streaming | Properties::Duplicate
)

KAI_END

