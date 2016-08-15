#include <gtest/gtest.h>

#include <data/Preferences.h>
#include <platform/Bridge.h>
#include <Poco/Path.h>

class PreferencesTest : public ::testing::Test
{
protected:
	// Per-test-case set-up.
	// Called before the first test in this test case.
	// Can be omitted if not needed.
	static void SetUpTestCase()
	{
		writablePath = std::unique_ptr<CrossMobile::Platform::Bridge>(
				CrossMobile::Platform::Bridge::create())->getWritablePath();
	}

	// Per-test-case tear-down.
	// Called after the last test in this test case.
	// Can be omitted if not needed.
	static void TearDownTestCase()
	{
	}

	// You can define per-test set-up and tear-down logic as usual.
	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
	}

	static std::string writablePath;
};

std::string PreferencesTest::writablePath;

TEST_F(PreferencesTest, defaultValues)
{

	Preferences testPrefs(Poco::Path(writablePath, "test_default.db").toString());
	testPrefs.clean();

	EXPECT_EQ("aa", testPrefs.getValue("testA", "aa"));
	EXPECT_EQ("aa", testPrefs.getValue("testA", "bb"));
	EXPECT_EQ("caa", testPrefs.getValue("testB", "caa"));
	EXPECT_EQ("caa", testPrefs.getValue("testB", ""));
}

TEST_F(PreferencesTest, empty)
{
	Preferences testPrefs(Poco::Path(writablePath, "test_empty.db").toString());
	testPrefs.clean();

	EXPECT_EQ("", testPrefs.getValue("testA", ""));
	testPrefs.setValue("testA", "aa");
	EXPECT_EQ("aa", testPrefs.getValue("testA", ""));

	EXPECT_EQ("", testPrefs.getValue("testB", ""));
	testPrefs.setValue("testA", "");
	EXPECT_EQ("", testPrefs.getValue("testA", "ZZ"));

	EXPECT_EQ("", testPrefs.getValue("", ""));
	testPrefs.setValue("", "a");
	EXPECT_EQ("a", testPrefs.getValue("", ""));
}

TEST_F(PreferencesTest, oddChars)
{
	Preferences testPrefs(Poco::Path(writablePath, "test_oddChars.db").toString());
	testPrefs.clean();

	EXPECT_EQ("~!@#$%^&*((()", testPrefs.getValue("testA", "~!@#$%^&*((()"));
	testPrefs.setValue("testA", "~!@#$%^&*((()");
	EXPECT_EQ("~!@#$%^&*((()", testPrefs.getValue("testA", ""));

	EXPECT_EQ("'", testPrefs.getValue("testB", "'"));
	testPrefs.setValue("testA", "'");
	EXPECT_EQ("'", testPrefs.getValue("testA", "ZZ"));

	EXPECT_EQ("/", testPrefs.getValue("\\", "/"));
	testPrefs.setValue("\\", "\\");
	EXPECT_EQ("\\", testPrefs.getValue("\\", ""));
}

TEST_F(PreferencesTest, readWrite)
{
	Preferences testPrefs(Poco::Path(writablePath, "test_readWrite.db").toString());
	testPrefs.clean();

	EXPECT_EQ("aa", testPrefs.getValue("testA", "aa"));
	testPrefs.setValue("testA", "bb");
	EXPECT_EQ("bb", testPrefs.getValue("testA", "cc"));
	testPrefs.setValue("testA", "cc");
	EXPECT_EQ("cc", testPrefs.getValue("testA", "cc"));

	EXPECT_EQ("aa", testPrefs.getValue("testB", "aa"));
	testPrefs.setValue("testB", "bb");
	EXPECT_EQ("bb", testPrefs.getValue("testB", "cc"));
	testPrefs.setValue("testB", "cc");
	EXPECT_EQ("cc", testPrefs.getValue("testB", "cc"));

	EXPECT_EQ("zz", testPrefs.getValue("testC", "zz"));
	testPrefs.setValue("testC", "zz");
	testPrefs.setValue("testC", "ccA");
	EXPECT_EQ("ccA", testPrefs.getValue("testC", "ccZ"));

	EXPECT_EQ("cc", testPrefs.getValue("testA", ""));
	EXPECT_EQ("cc", testPrefs.getValue("testB", ""));
	EXPECT_EQ("ccA", testPrefs.getValue("testC", ""));
}

TEST_F(PreferencesTest, writeLongText)
{
	Preferences testPrefs(Poco::Path(writablePath, "test_writeLongText.db").toString());
	testPrefs.clean();

	std::string key;
	std::string value;
	for (int i = 0; i < 100; ++i)
	{
		key += "a";
		value += "b";
	}
	EXPECT_EQ(value, testPrefs.getValue(key, value));
	testPrefs.setValue(key, value);
	EXPECT_EQ(value, testPrefs.getValue(key, ""));

	key.clear();
	value.clear();
	for (int i = 0; i < 1024; ++i)
	{
		key += "a";
		value += "b";
	}
	EXPECT_EQ(value, testPrefs.getValue(key, value));
	testPrefs.setValue(key, value);
	EXPECT_EQ(value, testPrefs.getValue(key, ""));
}

TEST_F(PreferencesTest, recreateDatabase)
{
	{
		Preferences testClean(Poco::Path(writablePath, "test_recreate.db").toString());
		testClean.clean();
	}
	{
		Preferences testPrefs(Poco::Path(writablePath, "test_recreate.db").toString());

		EXPECT_EQ("aa", testPrefs.getValue("testA", "aa"));
		testPrefs.setValue("testA", "bb");
		EXPECT_EQ("bb", testPrefs.getValue("testA", "1"));
		testPrefs.setValue("testA", "cc");
		EXPECT_EQ("cc", testPrefs.getValue("testA", "1"));
	}
	{
		Preferences testPrefs(Poco::Path(writablePath, "test_recreate.db").toString());
		EXPECT_EQ("cc", testPrefs.getValue("testA", ""));
		EXPECT_EQ("cc", testPrefs.getValue("testA", ""));
		testPrefs.setValue("testA", "123");
	}
	{
		Preferences testPrefs(Poco::Path(writablePath, "test_recreate.db").toString());
		EXPECT_EQ("123", testPrefs.getValue("testA", ""));
	}
}

TEST_F(PreferencesTest, multipleWrites)
{
	Preferences testPrefs(Poco::Path(writablePath, "test_multipleWrites.db").toString());
	testPrefs.clean();

	for (int i = 0; i < 20; ++i)
	{
		EXPECT_EQ("aa", testPrefs.getValue("testA", "aa"));
	}
	for (int i = 0; i < 23; ++i)
	{
		testPrefs.setValue("testA", "bb");
		EXPECT_EQ("bb", testPrefs.getValue("testA", "1"));
	}
	for (int i = 0; i < 21; ++i)
	{
		testPrefs.setValue("testA", "gg");
	}

	EXPECT_EQ("gg", testPrefs.getValue("testA", "1"));
}

TEST_F(PreferencesTest, bigLetters)
{
	Preferences testPrefs(Poco::Path(writablePath, "test_bigLetters.db").toString());
	testPrefs.clean();

	EXPECT_EQ("aa", testPrefs.getValue("testA", "aa"));
	testPrefs.setValue("testA", "bb");
	EXPECT_EQ("bb", testPrefs.getValue("testA", "cc"));
	testPrefs.setValue("testA", "cc");
	EXPECT_EQ("cc", testPrefs.getValue("testA", "cc"));

	EXPECT_EQ("aa", testPrefs.getValue("testa", "aa"));
	testPrefs.setValue("testa", "bb");
	EXPECT_EQ("bb", testPrefs.getValue("testa", "cc"));
	testPrefs.setValue("testa", "cc");
	EXPECT_EQ("cc", testPrefs.getValue("testa", "cc"));

	EXPECT_EQ("zz", testPrefs.getValue("TestA", "zz"));
	testPrefs.setValue("TestA", "zz");
	testPrefs.setValue("TestA", "ccA");
	EXPECT_EQ("ccA", testPrefs.getValue("TestA", "ccZ"));

	EXPECT_EQ("cc", testPrefs.getValue("testA", ""));
	EXPECT_EQ("cc", testPrefs.getValue("testa", ""));
	EXPECT_EQ("ccA", testPrefs.getValue("TestA", ""));
}
