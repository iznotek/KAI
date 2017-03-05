#pragma once

#include <KAI/Core/Value.h>
#include <KAI/Executor/Continuation.h>
#include <KAI/Executor/Operation.h>
#include <KAI/Core/BuiltinTypes/Stack.h>
#include <KAI/Core/Object/Reflected.h>
#include <KAI/Core/Pathname.h>
#include <KAI/Core/Executor/ScopeResolution.h>

KAI_BEGIN

class Tree;

/// Executes code stored in Continuations via a stack of Contexts
class Executor;

// unsure why I forward reference the Executor class and its traits
// and at this point I am too scared to ask why.
KAI_TYPE_TRAITS(
	Executor, 
	Number::Executor, 
	Properties::Reflected); 

/// 
/// An Executor processes code provided by Continuations via Contexts.
///
/// Each thread can have multiple Executors. There are no globals used.
/// Executors themselves are Reflected Objects so can be read and written
/// to and from Binary and StringStreams, sent across a network, stored to
/// disk mid-execution and so on.
///
struct Executor : Reflected<Executor>, I
{
	///{@ Refleted methods
	void Create();
	bool Destroy();
	///@}

	void SetContinuation(Value<Continuation>);
	void Continue(Value<Continuation>);
	void ContinueOnly(Value<Continuation> C);
	void Continue();

	void Eval(Object const &Q);
	void Dump(Object const &Q);
	
	void PrintStack(StringStream &);

	template <class T>
	Value<T> New()
	{
		return Reg().New<T>();
	}

	template <class T>
	Value<T> New(T const & X)
	{
		return Reg().New(X);
	}

	void SetTree(Tree *T) { _tree = T; }
	Tree *GetTree() const { return _tree; }

	void SetTraceLevel(int);
	int GetTraceLevel() const;

	template <class T>
	void Push(const Value<T> &val)
	{
		Push(val.GetObject());
	}
	
	template <class Ident>
	void EvalIdent(Object const &Q)
	{
		Ident const &ident = ConstDeref<Ident>(Q);
		if (ident.Quoted())
		{
			Push(Q);
			return;
		}

		auto found = TryResolve(ident);
		if (found.Exists())
			Push(found);
		else
			KAI_THROW_1(ObjectNotFound, ident.ToString());
	}

	void Push(Object const &);
	void Push(const std::pair<Object, Object> &);
	Object Pop();
	Object Top() const;

	Value<Stack> GetDataStack();
	Value<const Stack> GetDataStack() const
	{
		return Value<const Stack>(_data.GetConstObject());
	}

	Value<const Stack> GetContextStack() const;

	/// This resets the entire process, other than static state stored
	/// in referenced objects
	void ClearStacks()
	{
		_data->Clear();
		_context->Clear();
	}

	static void Register(Registry &, const char * = "Executor");

	friend bool operator<(const Executor &A, const Executor &B);
	friend bool operator==(const Executor &A, const Executor &B);

	void ClearContext();
	
	Object ResolvePop(Object, bool ignoreQuote = false) const;
	Object Resolve(Object, bool ignoreQuote = false) const;
	Object Resolve(const Label &) const;
	Object Resolve(const Pathname &) const;

private:
	/// Pop top and convert it to a boolean value.
	bool PopBool();

	/// Perform an operation
	void Perform(Operation::Type op);

	void ToArray();
	void DropN();
	void GetChildren();
	void Expand();
	void MarkAndSweep();
	void MarkAndSweep(Object &root);

	void Push(Stack& L, Object const &Q);
	Object Pop(Stack &stack);
	void NextContinuation();
	
	void DumpStack(Stack const &);
	static void DumpContinuation(Continuation const &, int);

private:
	/// Iterate over each element in a Container.
	template <class C>
	Value<Array> ForEach(C const &, Object const &);

	/// Push all contents of any container onto the stack
	template <class Cont>
	void PushAll(const Cont &cont);

	// void TraceAll();
	// void Trace(const Object &);
	// void Trace(const Label &, const StorageBase&, StringStream &);
	// void Trace(const Object&, StringStream &);
	void ConditionalContextSwitch(Operation::Type);
	Value<Continuation> NewContinuation(Value<Continuation> P);

	Object TryResolve(Object const &) const;
	Object TryResolve(Label const &label) const;
	Object TryResolve(Pathname const &label) const;

private:
	/// The currently executing context
	Value<Context> CurrentContext() const { return _context->Top(); }
	
	/// The history of how we got here: A stack of Context objects.
	/// The _current context is always at the top of the Stack.
	Value<Stack> _context;
	
	/// The current data stack used by operations
	Value<Stack> _data;
	
	/// break out of current context on next loop iteration
	bool _break;
	
	/// used to resolve identifier lookups
	ScopeResolution _resolver;
	
	/// debugging
	int _traceLevel;
};

StringStream &operator<<(StringStream &, Executor const &);
BinaryStream &operator<<(BinaryStream &, Executor const &);
BinaryPacket &operator>>(BinaryPacket &, Executor &);

KAI_END
