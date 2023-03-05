
// error handler, to avoid those pesky exit(0)'s

struct jpg_error_mgr {
  struct jpeg_error_mgr pub;	/* "public" fields */

  jmp_buf setjmp_buffer;	/* for return to caller */
};

typedef struct jpg_error_mgr * jpg_error_ptr;

/* Expanded data source object for stdio input */

typedef struct {
  struct jpeg_source_mgr pub;	/* public fields */

  FILE * infile;		/* source stream */
  JOCTET * buffer;		/* start of buffer */
  boolean start_of_file;	/* have we gotten any data yet? */
} jpg_source_mgr;

typedef jpg_source_mgr * jpg_src_ptr;
