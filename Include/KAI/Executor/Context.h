#pragma once

#include <KAI/Core/Continuation.h>

KAI_BEGIN

// Context for an Executor
class Context
{
	Pointer<Continuation> _continuation;
	Object _scope;
	int _ip;

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

