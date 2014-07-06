#ifdef KAI_HAVE_PRAGMA_ONCE
#	pragma once
#endif

#ifndef KAI_CONTINUATION_H
#	define KAI_CONTINUATION_H

KAI_BEGIN

struct Continuation
{
	typedef Array::const_iterator InstructionPointer;
	typedef Pointer</*const*/ Array> Code;

private:
	InstructionPointer ip;
	Object scope;
	Pointer<Array> code;
	String source_code;

public:
	void SetCode(Code);
	void SetCode(Code, String const &);

	Code &GetCode() { return code; }
	const Code &GetCode() const { return code; }

	String const &GetSourceCode() const { return source_code; }
	void SetSourceCode(String const &C) { source_code = C; }

	void SetScope(Object const &Q) { scope = Q; }
	Object GetScope() const { return scope; }
	bool HasScope() const { return scope.Exists(); }

	bool HasCode() const { return code.Exists(); }

	int InitialStackDepth;

	void Enter();

	InstructionPointer &Ip();
	InstructionPointer End() const;

	static void Register(Registry &);
};

StringStream &operator<<(StringStream &, const Continuation &);
StringStream &operator>>(StringStream &, Continuation &);
BinaryStream &operator<<(BinaryStream &, const Continuation &);
BinaryPacket &operator>>(BinaryPacket &, Continuation &);

KAI_TYPE_TRAITS(Continuation, Type::Number::Continuation, Type::Properties::Streaming);

KAI_END

#include KAI_TEST(Continuation)

#endif // KAI_CONTINUATION_H

//EOF
