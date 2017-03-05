#pragma once

#include <KAI/Core/Process.h>
#include <KAI/Core/Registry.h>
#include <KAI/Language/Common/ParserCommon.h>

KAI_BEGIN

///
/// Common for all Languages in the sysyem, given a Translator Tr.
///
/// The common Translator Tr transforms raw text into a Continuation for an Executor.
/// This involves three main steps:
///
/// * Lexer. Convert text to stream of tokens.
/// * Parser. Parse tokes to a tree of nodes.
/// * AST Walker. Walk the nodes, generating code along the way.
///
/// I call this entire process a "Translator". This is not accurate terminology.
///
template <class Tr>
class Lang : public Process
{
public:
	/// The Translator. This has a lexer, parser and AST walker
	typedef Tr Translator;
	
	/// The lexer for the Translator
	typedef typename Tr::Lexer Lexer;
	
	/// The parser for the Translator. Redundant comments are redundant.
	typedef typename Tr::Parser Parser;

protected:
	Registry &reg;
	std::shared_ptr<Lexer> lex;
	std::shared_ptr<Parser> parse;
	std::shared_ptr<Translator> trans;

public:
	Lang(const Lang&) = delete;
	Lang(Registry &r) : reg(r) { }

	virtual Pointer<Continuation> Translate(const char *text, Structure st = Structure::Expression) = 0;
	virtual Pointer<Continuation> TranslateFile(const char *name, Structure st = Structure::Program) = 0;
};

KAI_END

