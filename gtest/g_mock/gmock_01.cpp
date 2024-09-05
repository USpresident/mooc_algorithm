#include <gmock/gmock.h>
#include <gtest/gtest.h>

class File {
public:
    virtual int open(const char *path_name) = 0;
    virtual int close() = 0;
    virtual int write(const char *buf, size_t size) = 0;
    virtual int read(char *buf, size_t size) = 0;
};

class Logger {
public:
    Logger(File *file) : m_file(file) {}

    bool init()
    {
        return m_file->open("test.txt") == 0;
    }

    bool write(const char *buf, size_t size)
    {
        return m_file->write(buf, size) == 0;
    }

private:
    File *m_file;
};

class MockFile : public File {
public:
    MOCK_METHOD(int, open, (const char *path_name), (override));
    MOCK_METHOD(int, close, (), (override));
    MOCK_METHOD(int, write, (const char *buf, size_t size), (override));
    MOCK_METHOD(int, read, (char *buf, size_t size), (override));
};

using ::testing::_;
using ::testing::Return;

TEST(MockDemo, initFailed)
{
    MockFile mockFile;
    EXPECT_CALL(mockFile, open(_))
        .WillOnce(Return(-1));

    Logger logger(&mockFile);

    EXPECT_FALSE(logger.init());
}

TEST(MockDemo, writeFailed)
{
    MockFile mockFile;
    EXPECT_CALL(mockFile, open(_))
        .WillOnce(Return(0));

    EXPECT_CALL(mockFile, write(_, 10))
        .Times(3)
        .WillOnce(Return(0))
        .WillOnce(Return(-1))
        .WillOnce(Return(5));

    Logger logger(&mockFile);

    EXPECT_TRUE(logger.init());

    // 需要调用3次, 与上边的返回结果一一对应
    EXPECT_TRUE(logger.write(nullptr, 10));
    EXPECT_FALSE(logger.write(nullptr, 10));
    EXPECT_FALSE(logger.write(nullptr, 10));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}