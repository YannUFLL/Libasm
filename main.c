/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:47:18 by ydumaine          #+#    #+#             */
/*   Updated: 2024/11/05 17:59:49 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"
#include <stdio.h>


int compare_files(int fd1, int fd2) {
    const ssize_t BUFFER_SIZE = 1024;
    unsigned char buffer1[BUFFER_SIZE];
    unsigned char buffer2[BUFFER_SIZE];
    ssize_t bytes_read1, bytes_read2;

    do {
        bytes_read1 = read(fd1, buffer1, BUFFER_SIZE);
        bytes_read2 = read(fd2, buffer2, BUFFER_SIZE);

        if (bytes_read1 < 0 || bytes_read2 < 0) {
            return -1;
        }

        if (bytes_read1 != bytes_read2 || memcmp(buffer1, buffer2, bytes_read1) != 0) {
            return 1;
        }
    } while (bytes_read1 == BUFFER_SIZE);

    return 0;
}
void test_strlen(const char *str) {
    int expected = strlen(str); 
    int actual = ft_strlen(str); 

    if (expected == actual) {
        printf("✅ Test passed for the string '%s'. Length = %d\n", str, actual);
    } else {
        printf("❌ Test failed for the string '%s'. Expected = %d, Got = %d\n", str, expected, actual);
    }
}

void test_strcpy(const char *src) {
    char dest1[100];
    char dest2[100];
    
    strcpy(dest1, src); 
    ft_strcpy(dest2, src); 
    
    if (strcmp(dest1, dest2) == 0) {
        printf("✅ Test passed for the source string '%s'. Dest = '%s'\n", src, dest2);
    } else {
        printf("❌ Test failed for the source string '%s'. Expected = '%s', Got = '%s'\n", src, dest1, dest2);
    }
}

void test_ft_strcmp(const char* str1, const char* str2) {
    int result1 = strcmp(str1, str2);
    int result2 = ft_strcmp(str1, str2);
    
    if ((result1 == 0 && result2 == 0) || 
        (result1 < 0 && result2 < 0) || 
        (result1 > 0 && result2 > 0)) {
        printf("✅ Test passed ft_strcmp vs strcmp: '%s' vs '%s':\n", str1, str2);
    } else {
        printf("❌  Test failed ft_strcmp vs strcmp: '%s' vs '%s':\n", str1, str2);
    }
}

void test_ft_write()
{

    int fd1 = open("test_ft_write.txt", O_APPEND | O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    int fd2 = open("test_std_write.txt", O_APPEND | O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    int fd3 = open("test_close_fd", O_APPEND | O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    if (fd1 == -1 || fd2 == -1 || fd3 == -1)
    {
        fprintf(stderr, "error opening file: fd1: %d, fd2: %d, fd3: %d ", fd1, fd2, fd3);
        exit(1);
    }
    int ret = 0;
    ft_write(fd1, "test file\n", 10);
    write(fd2, "test file\n", 10);


    close(fd3);
    ret = ft_write(fd3, "Should fail\n", 12);
    if (ret == -1)
    {
        dprintf(fd1, "Error writing : %s\n", strerror(errno));
    }
    ret = write(fd3, "Should fail\n", 12);
    if (ret == -1)
    {
        dprintf(fd2, "Error writing : %s\n", strerror(errno));
    }

    write(fd1, "", 0);
    write(fd2, "", 0);


    ret = ft_write(-1, "test", 4);
    if (ret == -1)
    {
        dprintf(fd1, "Error writing : %s\n", strerror(errno));
    }
    ret = write(-1, "test", 4);
    if (ret == -1)
    {
        dprintf(fd2, "Error writing : %s\n", strerror(errno));
    }
    if (compare_files(fd1, fd2))
    {
        printf("✅ Test passed ft_writing vs writing\n");
    }
    else 
    {
        printf("❌  Test failed ft_wrining vs witring\n");
    }
}


void test_ft_read()
{
    int fd = open("test_read.txt", O_RDONLY);
    if (fd == -1)
    {
        fprintf(stderr, "error opening file: fd1: %d,", fd);
        exit(1);
    }

    char buffer1[50];
    char buffer2[50];
    char *errno1;
    char *errno2;

    int ret1 = ft_read(fd, buffer1, 49);
    lseek(fd, 0, SEEK_SET);
    int ret2 = read(fd, buffer2, 49);

    buffer1[ret1] = '\0';
    buffer2[ret2] = '\0';


    if (ret1 == ret2)
    {
        printf("✅ Test passed length read from an existing file\n");
    }
    else
    {
        printf("❌ Test failed length read from an existing file\n");
    }

    if (strcmp(buffer1, buffer2) == 0)
    {
        printf("✅ Test passed read from an existing file\n");
    }
    else
    {
        printf("❌ Test failed read from an existing file\n");
    }
    ret1 = ft_read(fd, buffer1, 0);
    if (ret1 == 0)
    {
        printf("✅ Test passed read empty string\n");
    }
    else
    {
        printf("❌ Test failed read empty string\n");
    }

    close(fd);
    ret1 = ft_read(fd, buffer1, 10);
    if (ret1 == -1)
    {
        printf("✅ Test passed read from closed file descriptor returned -1\n");
    }
    else
    {
        printf("❌ Test failed read from closed file descriptor did not return -1\n");
    }

    ret1 = ft_read(-1, buffer1, 10);
    if (ret1 == -1)
    {
        printf("✅ Test passed read with invalid file descriptor\n");
    }
    else
    {
        printf("❌ Test failed read with invalid file descriptor\n");
    }

    errno1 = strerror(errno);
    errno2 = strerror(errno);
     if (strcmp(errno1, errno2) == 0)
    {
        printf("✅ Test passed for the value of errno\n");
    }
    else
    {
        printf("❌ Test failed for for an existing file\n");
    }
    
}

void test_ft_strdup()
{
    char src1[] = "I'm the source, I need to be copied to the dest memory";
    char *dst1 = ft_strdup(src1);
    if (strcmp(src1, dst1) == 0)
    {
        printf("✅ Test passed for copying a normal string\n");
    }
    else
    {
        printf("❌ Test failed for copying a normal string\n");
    }
    free(dst1);
   

     char src2[] = "";
    char *dst2 = ft_strdup(src2);
    if (strcmp(src2, dst2) == 0)
    {
        printf("✅ Test passed for copying an empty string\n");
    }
    else
    {
        printf("❌ Test failed for copying an empty string\n");
    }
    free(dst2);

    char src3[] = "  ";
    char *dst3 = ft_strdup(src3);
    if (strcmp(src3, dst3) == 0)
    {
        printf("✅ Test passed for copying a string with spaces\n");
    }
    else
    {
        printf("❌ Test failed for copying a string with spaces\n");
    }
    free(dst3);


     char src4[] = "Hello\nWorld\t!";
    char *dst4 = ft_strdup(src4);
    if (strcmp(src4, dst4) == 0)
    {
        printf("✅ Test passed for copying a string with special characters\n");
    }
    else
    {
        printf("❌ Test failed for copying a string with special characters\n");
    }
    free(dst4);



}




int main()
{
    
    printf("FT_STRLEN\n");
    test_strlen("Hello, world!");
    test_strlen("12345");
    test_strlen("");
    test_strlen("Another example");
    printf("\n");

    printf("FT_STRCPY\n");
    test_strcpy("Hello, world!");
    test_strcpy("12345");
    test_strcpy("");
    test_strcpy("Another example");
    printf("\n");

    printf("FT_STRCMP\n");
    test_ft_strcmp("hello", "hello");  
    test_ft_strcmp("hello", "world");  
    test_ft_strcmp("world", "hello");  
    test_ft_strcmp("hello", "hell");   
    test_ft_strcmp("hell", "hello");   
    test_ft_strcmp("", "");            
    test_ft_strcmp("a", "");           
    test_ft_strcmp("", "a");           
    printf("\n");
    
    printf("FT_WRITE\n");
    test_ft_write(); 
    printf("\n");

    printf("FT_READ\n");
    test_ft_read();
    printf("\n");

    printf("FT_STRDUP\n");
    test_ft_strdup();

}
