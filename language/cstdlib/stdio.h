#include <stdio.h>


/*-----------------------------------------------------------------------------------
 @stream
    Pointer to a FILE object that specifies the stream to be closed.
 @return
    If the stream is successfully closed, a zero value is returned. On failure, EOF -
    is returned.
    
 Closes the file associated with the stream and disassociates it. All internal buffe-
 rs associated with the stream are disassociated from it and flushed: the content  of 
 any unwritten output buffer is written and the content of any unread input buffer is 
 discarded.
 
 Even if the call fails, the stream passed as parameter will no longer be  associated 
 with the file nor its buffers.
 ----------------------------------------------------------------------------------*/
int fclose ( FILE * stream );









/*-----------------------------------------------------------------------------------
 Changes the name of the file or directory specified by @oldname to @newname. This is 
 an operation performed directly on a file; No streams are involved in the operation.
 If @oldname and @newname specify different paths and this is supported by the syste-
 m, the file is moved to the new location. If @newname names an existing file, the f-
 unction may either fail or override the existing file, depending on the specific sy-
 stem and library implementation. Proper file access shall be available.

 If the file is successfully renamed, a zero value is returned. On failure, a nonzer-
 o value is returned. On most library implementations, the errno variable is also set 
 to a system-specific error code on failure.
 ----------------------------------------------------------------------------------*/
int rename ( const char * oldname, const char * newname );




















































