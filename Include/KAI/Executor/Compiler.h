#pragma once

// TODO: I don't like including heavy STL containers in main headers
#include <map>

#include <KAI/Core/Debug.h>
#include <KAI/Executor/Operation.h>
#include <KAI/Executor/Continuation.h>
#include <KAI/Language/Common/Language.h>

KAI_BEGIN

///
/// Compiler works for any language that conforms to the concept defined in
/// <KAI/Language/Common/TranslatorBase.h>
///
class Compiler : public Reflected<Compiler>
{
	typedef std::map<Operation, String> OperationToString;

	typedef std::map<String, Pointer<Operation>> StringToOperation;

private:
	OperationToString op_to_string;
	StringToOperation string_to_op;
	Language _language = Language::Pi;

#ifdef KAI_DEBUG
	int _traceLevel = 0;
#endif

public:
	void Create();
	bool Destroy();

	void SetLanguage(Language);
	Language GetLanguage() const;

	// TODO: put into private compilation moddule and specialise on each language added
	template <class Trans>
	Pointer<Continuation> Compile(const String &text, Structure st = Structure::Expression) const
	{
		if (text.empty())
			return Object();

		auto trans = std::make_shared<Trans>(Reg());
		trans->trace = _traceLevel;

		auto result = trans->Translate(text.c_str(), st);
		if (trans->Failed)
		{
			KAI_TRACE_ERROR_1(trans->Error);
			return Object();
		}

		return result;
	}

	Pointer<Continuation> Translate(const String &text, Structure st = Structure::Expression) const;
	Pointer<Continuation> CompileFile(const String &fileName, Structure st = Structure::Program) const;
	
#ifdef KAI_DEBUG
	void SetTraceLevel(int n) { _traceLevel = n; }
#endif

	static void Register(Registry &, const char * = "Compiler");

protected:
	void AddOperation(int N, const String &S);
};

// you can interact with a Compiler at runtime
KAI_TYPE_TRAITS(
	Compiler, 
	Number::Compiler, 
	Properties::Reflected);

KAI_END
