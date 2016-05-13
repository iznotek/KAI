#include "TestBase.h"
#include "KAI/Console.h"

using namespace kai;
using namespace std;

TEST(TestFunctionScripting, TestAssignment)
{
	Console console;

	console.Execute("a=1;");
	console.SetLanguage(Language::Rho);

	Object root = console.GetRoot();
	ASSERT_TRUE(root.HasChild("a"));
	ASSERT_EQ(Deref<int>(root.GetChild("a")), 3);
}

