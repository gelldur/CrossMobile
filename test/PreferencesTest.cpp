#include <gtest/gtest.h>

#include <data/Preferences.h>
#include <platform/Bridge.h>

static std::string writablePath = std::unique_ptr<CrossMobile::Platform::Bridge>(
		CrossMobile::Platform::Bridge::create())->getWritablePath();

TEST(PreferencesTest, defaultValues)
{
	Preferences testPrefs(writablePath + "test_default.db");
	testPrefs.clean();

	EXPECT_EQ("aa", testPrefs.getValue("testA", "aa"));
	EXPECT_EQ("aa", testPrefs.getValue("testA", "bb"));
	EXPECT_EQ("caa", testPrefs.getValue("testB", "caa"));
	EXPECT_EQ("caa", testPrefs.getValue("testB", ""));
}

TEST(PreferencesTest, empty)
{
	Preferences testPrefs(writablePath + "test_empty.db");
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

TEST(PreferencesTest, oddChars)
{
	Preferences testPrefs(writablePath + "test_oddChars.db");
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

TEST(PreferencesTest, readWrite)
{
	Preferences testPrefs(writablePath + "test_readWrite.db");
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

TEST(PreferencesTest, writeLongText)
{
	Preferences testPrefs(writablePath + "test_writeLongText.db");
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

TEST(PreferencesTest, recreateDatabase)
{
	{
		Preferences testClean(writablePath + "test_recreate.db");
		testClean.clean();
	}
	{
		Preferences testPrefs(writablePath + "test_recreate.db");

		EXPECT_EQ("aa", testPrefs.getValue("testA", "aa"));
		testPrefs.setValue("testA", "bb");
		EXPECT_EQ("bb", testPrefs.getValue("testA", "1"));
		testPrefs.setValue("testA", "cc");
		EXPECT_EQ("cc", testPrefs.getValue("testA", "1"));
	}
	{
		Preferences testPrefs(writablePath + "test_recreate.db");
		EXPECT_EQ("cc", testPrefs.getValue("testA", ""));
		EXPECT_EQ("cc", testPrefs.getValue("testA", ""));
		testPrefs.setValue("testA", "123");
	}
	{
		Preferences testPrefs(writablePath + "test_recreate.db");
		EXPECT_EQ("123", testPrefs.getValue("testA", ""));
	}
}

TEST(PreferencesTest, multipleWrites)
{
	Preferences testPrefs(writablePath + "test_multipleWrites.db");
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

TEST(PreferencesTest, bigLetters)
{
	Preferences testPrefs(writablePath + "test_bigLetters.db");
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
