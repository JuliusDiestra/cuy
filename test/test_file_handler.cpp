#include "cuy/file_handler.h"

#include "gtest/gtest.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

TEST(FileHandler, FileDoesNotExist) {
    const char* file_path = "/tmp/foo.c";
    int fd = -1;
    StatusCode file_open_result = file_open(file_path, FILE_READ, &fd);
    EXPECT_EQ(file_open_result, CUY_ERROR_FILE_HANDLER_FILE_DOES_NOT_EXIST);
}

/*
// Test: file_open successfully opens an existing file in read mode
TEST(FileHandler, FileOpenReadSuccess) {
    // Create a temporary file
    const char* test_file = "/tmp/test_read.txt";
    int fd = open(test_file, O_CREAT | O_WRONLY, 0644);
    ASSERT_GE(fd, 0) << "Failed to create test file";
    close(fd);

    int result_fd = -1;
    StatusCode status = file_open(test_file, FILE_READ, &result_fd);

    EXPECT_EQ(status, CUY_SUCCESS);
    EXPECT_GE(result_fd, 0);

    if (result_fd >= 0) {
        close(result_fd);
    }
    unlink(test_file);
}

// Test: file_open fails with non-existent file
TEST(FileHandler, FileOpenNonExistent) {
    const char* test_file = "/tmp/nonexistent_file_12345.txt";
    int result_fd = -1;

    StatusCode status = file_open(test_file, FILE_READ, &result_fd);

    EXPECT_EQ(status, CUY_ERROR_FILE_HANDLER_FILE_DOES_NOT_EXIST);
    EXPECT_EQ(result_fd, -1);
}

// Test: file_open with invalid mode
TEST(FileHandler, FileOpenInvalidMode) {
    const char* test_file = "/tmp/test_invalid_mode.txt";
    int fd = open(test_file, O_CREAT | O_WRONLY, 0644);
    ASSERT_GE(fd, 0) << "Failed to create test file";
    close(fd);

    int result_fd = -1;
    StatusCode status = file_open(test_file, (FileOpenMode)999, &result_fd);

    EXPECT_EQ(status, CUY_ERROR_FILE_HANDLER_OPEN_MODE);

    unlink(test_file);
}

// Test: file_close returns success (currently just returns CUY_SUCCESS)
TEST(FileHandler, FileCloseSuccess) {
    int fd = 0;
    StatusCode status = file_close(&fd);

    EXPECT_EQ(status, CUY_SUCCESS);
}
*/
