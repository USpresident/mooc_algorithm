#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Gmock最大只支持10个参数的函数mock

class IFileApi{
public:
    virtual int open(const char* path, int o_flag)=0;
    virtual int read(const char* path, char* buffer, int size, int &size_ret)=0;
    virtual int close(int fd)=0;
};

class FileDataLoad {
public:
    FileDataLoad(IFileApi *api) :
            m_fileApi(api),
            m_szFileData(NULL),         
            m_nDataSize(0){ }

    ~FileDataLoad() { if (m_szFileData != NULL) { delete [] m_szFileData; }}

    int LoadData(const char* path, int size)
{  
        int fd = m_fileApi->open(path, 0777);   // 打开文件
        if (fd <= 0) { return -1; } // 我们假设 fd > 0. (真实环境中可能=0) 
        m_szFileData = new char[size+1];
        m_szFileData[size] = '\0';
        int size_ret = 0;
        // 读文件，仅仅作为示例，所以忽略参数size
        int ret = m_fileApi->read(path, m_szFileData, size, size_ret);
        if (ret != 0) {
            delete [] m_szFileData;
            return ret;
        }
        if (size != size_ret) { // 暂时不考虑           
            return -1;          
        }
        m_nDataSize = ret;
        // 关闭文件
        ret = m_fileApi->close(fd);     
        return ret;
    }

    char    *GetFileData() { return m_szFileData; }
    int     GetDataSize() { return m_nDataSize; }
private:
    IFileApi*   m_fileApi;
    char*       m_szFileData;
    int         m_nDataSize;
};

class MockFileApi : public IFileApi{
public:
    MOCK_METHOD2(open, int(const char*, int));
    MOCK_METHOD4(read, int(const char*, char*, int, int &));
    MOCK_METHOD1(close, int(int));
};

TEST(FileDataLoadTest, LoadData) 
{
    MockFileApi *api = new MockFileApi;
    FileDataLoad fileLoad((IFileApi*)api);
    int file_load_size = 100;

    // 我们期望当调用api->open()函数的时候，总是返回11，且这个函数仅被调用1次
    EXPECT_CALL(*api, open(::testing::_, ::testing::_))
        .Times(1)   // 期望被调用1次
        .WillRepeatedly(::testing::Return(11)); // 总是返回11

    // 我们期望调用 api->read 时, 设置第3个参数为 file_load_size 且返回 0。这个函数只被调用1次。 
    EXPECT_CALL(*api, read(::testing::_, ::testing::_, ::testing::_, ::testing::_))
        .Times(1)
        .WillRepeatedly(
            ::testing::DoAll(
                ::testing::SetArgReferee<3>(file_load_size),
                ::testing::Return(0)
            )
        );

    // 我们期望调用 api->close 时, 返回0。 这个函数只被调用1次。
    EXPECT_CALL(*api, close(::testing::_))
        .Times(1)
        .WillRepeatedly(::testing::Return(0));

    int ret = fileLoad.LoadData("/home/test_file", file_load_size); 
    // 我们期望返回 0
    EXPECT_EQ(ret, 0);
    delete api;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}