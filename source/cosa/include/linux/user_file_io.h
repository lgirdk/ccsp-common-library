/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2015 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

/**********************************************************************
   Copyright [2014] [Cisco Systems, Inc.]
 
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
 
       http://www.apache.org/licenses/LICENSE-2.0
 
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
**********************************************************************/


/**********************************************************************

    module:	kernel_file_io.h

        For Advanced Networking Service Container (ANSC),
        BroadWay Service Delivery System

    ---------------------------------------------------------------

    description:

        This wrapper file defines some basic data types and
        structures on a particular platform.

    ---------------------------------------------------------------

    environment:

        Linux kernel

    ---------------------------------------------------------------

    author:

        Xuechen Yang
        Geng Yang
        Ying Lou

    ---------------------------------------------------------------

    revision:

        01/19/01    initial revision.
        09/14/01    adapted to linux kernel by Geng Yang
        04/03/02    adapted to linux user by Ying Lou

**********************************************************************/


#ifndef  _USER_FILE_IO_
#define  _USER_FILE_IO_

#include <zlib.h>
/* prevent including zlib header from AL code */
#define  ZLIB_H

#include "user_time.h"
#include <time.h>
/*#include <direct.h> */
#include <dirent.h>
#include <sys/stat.h>

/***********************************************************
        DEFINITION OF BASIC DATA TYPE AND STRUCTURES
***********************************************************/

#define  USER_FILE_ATTRIBUTE_Normal                 0x00000000
#define  USER_FILE_ATTRIBUTE_Directory              0x00000001
#define  USER_FILE_ATTRIBUTE_Hidden                 0x00000002
#define  USER_FILE_ATTRIBUTE_ReadOnly               0x00000004
#define  USER_FILE_ATTRIBUTE_System                 0x00000008

/* this is also defined in slap_io_utils.c as _SIO_MAX_FNAME */
#define _LINUX_MAX_FNAME              260

typedef  struct
_FIND_CONTEXT
{
    char*                           DirName;
    char                            TarFileName[_LINUX_MAX_FNAME];
    DIR*                            pDir;
}
FIND_CONTEXT,  *PFIND_CONTEXT;

typedef  struct
_USER_FILE_PROPERTY
{
    ULONG                           Attributes;
    ULONG                           Size;
    USER_SYSTEM_TIME                AccessTime;
    USER_SYSTEM_TIME                ModificationTime;
    USER_SYSTEM_TIME                CreationTime;
}
USER_FILE_PROPERTY,  *PUSER_FILE_PROPERTY;

#define  USER_FILE_SEEK_SET                         SEEK_SET
#define  USER_FILE_SEEK_CUR                         SEEK_CUR
#define  USER_FILE_SEEK_END                         SEEK_END

#define  USER_FILE_O_APPEND                         O_APPEND
#define  USER_FILE_O_BINARY                         0
#define  USER_FILE_O_CREATE                         O_CREAT
#define  USER_FILE_O_SHORT_LIVED                    O_SHORT_LIVED
#define  USER_FILE_O_TEMPORARY                      O_TEMPORARY
#define  USER_FILE_O_EXCL                           O_EXCL
#define  USER_FILE_O_RANDOM                         O_RANDOM
#define  USER_FILE_O_RDONLY                         O_RDONLY
#define  USER_FILE_O_RDWR                           O_RDWR
#define  USER_FILE_O_SEQUENTIAL                     O_SEQUENTIAL
#define  USER_FILE_O_TEXT                           O_TEXT
#define  USER_FILE_O_TRUNC                          O_TRUNC
#define  USER_FILE_O_WRONLY                         O_WRONLY

#define  USER_FILE_S_IREAD                          S_IRUSR
#define  USER_FILE_S_IWRITE                         S_IWUSR
#define  USER_FILE_S_IRGO                           S_IRGRP | S_IROTH

#define  USER_GZIP_FILE_O_RDONLY                    "rb1"
#define  USER_GZIP_FILE_O_WRONLY                    "wb1"

#define  USER_FILE_PATH_SEP                         '/'

#define  user_open_file                             open
#define  user_close_file                            close
#define  user_read_file                             read
#define  user_write_file                            write
#define  user_seek_file                             lseek
/* using this or the following dependes on if using inline, also has parameter issue */
/*#define  user_rename_file                           rename*/
/*#define  user_create_directory                      mkdir*/

#define  user_open_gzip_file                             gzopen
#define  user_close_gzip_file                            gzclose
#define  user_read_gzip_file                             gzread
#define  user_write_gzip_file                            gzwrite
#define  user_seek_gzip_file                             gzseek

extern int user_rename_file(char* old_file_name, char* new_file_name);
extern int user_create_directory(char* dir_name);
extern int user_get_file_stat(char* file_name, void* h_file_property);
extern int user_move_file(char* srcFile, char* dstFile);
extern int user_copy_directory(char* srcDir, char* dstDir);
extern int user_delete_directory(char* dir);
extern int user_delete_file(char *filename);
extern int user_get_file_size(PVOID h);
extern int user_copy_file(char *src, char *dst, int fail_if_exists);

extern int user_find_first_file
    (
        char*                       dir_name,
        char*                       tar_file_name,
        void**                      ph_find_context,
        char*                       pb_directory,    /* 0 file, !0 dir */
        char*                       first_file_name
    );

extern int user_find_next_file
    (
        void*                       h_find_context,
        char*                       pb_directory,
        char*                       next_file_name
    );

extern void user_find_close
    (
        void*                      h_find_context
    );

#endif
