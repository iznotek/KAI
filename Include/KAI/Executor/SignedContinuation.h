#pragma once

#include <vector>

#include <KAI/Core/Config/Base.h>
#include <KAI/Core/Object/Label.h>
#include <KAI/Core/BuiltinTypes/Stack.h>
#include <KAI/Core/Type/Number.h>
#include <KAI/Executor/Continuation.h>

// TODO: this is not language-specific
#include <KAI/Language/Common/Process.h>

KAI_BEGIN

///
/// A SignedContinuation is just like a normal Continuation, except is knows what to
/// expect on the stack when it is executed, and what to return when leaving.
///
struct SignedContinuation : Language::Common::Process
{
	struct Parameter
	{
		Type::Number type;
		Label label;
		FormalParameter() { }
		FormalParameter(Label const &L) : label(L) { }
		FormalParameter(Type::Number T, Label const &L) : type(T), label(L) { }
	};

	typedef std::vector<Parameter> Parameters;
	typedef std::vector<Type::Number> ReturnTuple;

	void Create(
		Pointer<Array> params, 
		Pointer<Array> rtypes, 
		Pointer<Continuation> cont);

	Object GetContinuation() const { return cont; }
	bool Enter(Stack<Object> &);
	bool Leave(Stack<Object> &);
	static void Register(Registry &R);

private:
	Pointer<Continuation> cont;
	Parameters params;
	ReturnTuple return_tuple;
};

StringStream &operator<<(StringStream &, SignedContinuation const &);
BinaryStream &operator<<(StringStream &, SignedContinuation const &);
StringStream &operator>>(StringStream &, SignedContinuation &);

KAI_TYPE_TRAITS(
	SignedContinuation, 
	Number::SignedContinuation, 
	Properties::StringStreamInsert | Properties::BinaryStreaming
);

KAI_END
