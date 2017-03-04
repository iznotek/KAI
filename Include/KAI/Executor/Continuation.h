#pragma once

#include <KAI/Core/Type.h>
#include <KAI/Core/BinaryStream.h>
#include <KAI/Core/BuiltinTypes/Array.h>
#include <KAI/Core/BuiltinTypes/String.h>
#include <KAI/Core/Registry.h>
#include <KAI/Core/Object/Reflected.h>

KAI_BEGIN

struct IDebugWrite
{
	virtual void WriteDebugInfo(StringStream&, IDebugDescription const &) = 0;
}

// A code block represented as a sequence of Objects.
struct Continuation : Reflected, IDebugWrite
{
	typedef Pointer<const Array> Code;
	typedef Pointer<const String> SourceCode;
	typedef Pointer<const Array> Arguments;

private:
	SourceCode _sourceCode;
	Arguments _args;
	Code _code;

public:
	void Create();
	bool Destroy();

	void Construct(Code, SourceCode = 0, Arguments = 0);

	bool HasCode() const { return _code.Exists(); }
	Code GetCode() const { return _code; }

	Pointer<String> GetSourceCode() const { return _sourceCode; }
	void SetSourceCode(Pointer<String>);

	String DebugDescription() const;

	friend StringStream &operator<<(StringStream &, const Continuation &);
	friend StringStream &operator>>(StringStream &, Continuation &);
	friend BinaryStream &operator<<(BinaryStream &, const Continuation &);
	friend BinaryStream &operator>>(BinaryStream &, Continuation &);

	static void Register(Registry &);

	void WriteDebugInfo(StringStream&, IDebugDescription const &) override;
};

KAI_TYPE_TRAITS(
	Continuation, 
	Number::Continuation, 
	Properties::Streaming | Properties::Reflected
	);

KAI_END
