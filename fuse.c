#define FUSE_USE_VERSION 26
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <assert.h>

/* Command line options */
static struct options {
    /* points to malloc'ed memory. FUSE will call free() on them after usage */
    const char *filename; 
    const char *contents;
    /* To show usage. */
    int usage;
} options;

#define OPTION(t, p) { t, offsetof(struct options, p), 1 }

static const struct fuse_opt option_spec[] = {
    OPTION("--name=%s", filename),
    OPTION("--contents=%s", contents),
    OPTION("-h", usage),
    OPTION("--help", usage),
    FUSE_OPT_END
};

static void *dpy_init(struct fuse_conn_info *conn)
{
    return NULL;
}

static int dpy_getattr(const char *path, struct stat *stbuf)
{
    int res = 0;
    memset(stbuf, 0, sizeof(struct stat));
    if (strcmp(path, "/") == 0) {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
    } else if (strcmp(path+1, options.filename) == 0) {
        stbuf->st_mode = S_IFREG | 0444;
        stbuf->st_nlink = 1;
        stbuf->st_size = strlen(options.contents);
    } else
        res = -ENOENT;
    return res;
}
static int dpy_readdir(const char *path, void *buf, fuse_fill_dir_t filldir, off_t offset, struct fuse_file_info *fi)
{
    if (strcmp(path, "/") != 0)
        return -ENOENT;
    filldir(buf, ".", NULL, 0);
    filldir(buf, "..", NULL, 0);
    filldir(buf, options.filename, NULL, 0);
    return 0;
}

static int dpy_open(const char *path, struct fuse_file_info *fi)
{
    if (strcmp(path+1, options.filename) != 0)
        return -ENOENT;
    if ((fi->flags & O_ACCMODE) != O_RDONLY)
        return -EACCES;
    return 0;
}

static int dpy_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    size_t len;
    (void) fi;
    if(strcmp(path+1, options.filename) != 0)
        return -ENOENT;
    len = strlen(options.contents);
    if (offset < len) {
        if (offset + size > len)
            size = len - offset;
        memcpy(buf, options.contents + offset, size);
    } else
        size = 0;
    return size;
}

/* file system operations */
static struct fuse_operations ops = {
    .init    = dpy_init,
    .getattr = dpy_getattr,
    .readdir = dpy_readdir,
    .open    = dpy_open,
    .read    = dpy_read,
};

/* print how to use display file. */
static void usage(const char *progname)
{
    printf("usage: %s [options] <mountpoint>\n\n", progname);
    printf("File-system specific options:\n"
           "    --name=<s>          Name of the \"display\" file\n"
           "                        (default: \"display\")\n"
           "    --contents=<s>      Contents \"display\" file\n"
           "                        (default \"Hello, World!\\n\")\n"
           "\n");
}

/* file-system driver for displays. */
int main(int argc, char *argv[])
{
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);

    /* Set options */
    options.filename = strdup("dpy");
    options.contents = strdup("Hello World!\n");

    /* Parse options */
    if (fuse_opt_parse(&args, &options, option_spec, NULL) == -1)
        return 1;
    if (options.usage) {
        usage(argv[0]);
        assert(fuse_opt_add_arg(&args, "--help") == 0);
        args.argv[0] = (char*) "";
    }

    /* Drive user-space file system. */
    return fuse_main(args.argc, args.argv, &ops, NULL);
}
