/*
 *
 *      "Marcy's Nice Libs" v1.0.0
 *
 *      A friendly file library. Easy and simple!
 *
 */

#ifndef NL_FILE_H
#define NL_FILE_H

#define NL_BUFSIZ 4096

/*
 * Read contents of fd into buf. Automatically resizes the buffer
 * to fit the contents of the file.
 */
char *nl_readfile(int fd);

#endif // NL_FILE_H
