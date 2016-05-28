#include "Main.h"
#include "KAI/Core/Registry.h"
#include "Tau/TauLexer.h"

#include <array>
#include <fstream>
#include <Tau/TauParser.h>

using namespace std;
using namespace kai;
using namespace kai::tau;

struct TauTest : ::testing::Test
{
	virtual void SetUp() override
	{
	}

	virtual void TearDown() override
	{
	}
};

typedef TauTokenEnumType Tok;

//template <class Cont, class Fun>
//std::vector<typename Cont::value_type> filter(Cont const &t, Fun f)
//{
//	std::vector<typename Cont::value_type> result;
//	for (const auto &x : t)
//		result.emplace_back(f(x));
//	return std::move(result);
//}

TEST_F(TauTest, TestLex1)
{
	auto input = "namespace Foo\n\tclass Bar\n\t\tint Method()\n";
	Registry r;
	TauLexer l(input, r);
	l.Process();
	if (l.Failed)
		cerr << l.Error << endl;
	ASSERT_FALSE(l.Failed);

	TauTokenEnumType::Enum res[] = {
		Tok::Namespace, Tok::Whitespace, Tok::Ident, Tok::NewLine,
		Tok::Tab, Tok::Class, Tok::Whitespace, Tok::Ident, Tok::NewLine,
		Tok::Tab, Tok::Tab, Tok::Ident, Tok::Whitespace, Tok::Ident, Tok::OpenParan,Tok::CloseParan, Tok::NewLine };
	int n = 0;
	for (auto t : l.GetTokens())
	{
		ASSERT_EQ(t.type, res[n++]);
	}
}

TEST_F(TauTest, TestParse1)
{
	ifstream file("First.tau");
	ASSERT_TRUE(file);
	string str((istreambuf_iterator<char>(file)),
	           istreambuf_iterator<char>());
	Registry r;
	auto l = make_shared<TauLexer>(str.c_str(), r);
	cout << str << endl;
	TauParser p(r);
	p.Process(l, Structure::Namespace);
}

