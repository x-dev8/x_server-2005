//#include "lSupport.h"
#include <stdio.h>
#include <assert.h>
#include "jpegimage.h"


//////////////////////////////////////////////////////////////////////
// JPGDecode  : can out RGB/ALPHA type. 
//////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
	extern "C" {
#endif // __cplusplus
#undef FAR
#include "jpeglib.h"
#ifdef __cplusplus
	}
#endif // __cplusplus


/*
 * <setjmp.h> is used for the optional error recovery mechanism shown in
 * the second part of the example.
 */

#include <setjmp.h>
#include "myjpgcfg.h"

//
//	to handle fatal errors.
//	the original JPEG code will just exit(0). can't really
//	do that in Windows....
//
static void
my_error_exit (j_common_ptr cinfo)
{
	/* cinfo->err really points to a jpg_error_mgr struct, so coerce pointer */
	jpg_error_ptr myerr = (jpg_error_ptr) cinfo->err;

	char buffer[JMSG_LENGTH_MAX];

	/* Create the message */
	(*cinfo->err->format_message) (cinfo, buffer);

	/* Always display the message. */
	MessageBox(NULL,buffer,"JPEG Fatal Error",MB_ICONSTOP);


	/* Return control to the setjmp point */
	longjmp(myerr->setjmp_buffer, 1);
}
	
/*
 * Initialize source --- called by jpeg_read_header
 * before any data is actually read.
 */

static void
init_source (j_decompress_ptr cinfo)
{
  jpg_src_ptr src = (jpg_src_ptr) cinfo->src;

  /* We reset the empty-input-file flag for each image,
   * but we don't clear the input buffer.
   * This is correct behavior for reading a series of images from one source.
   */
  src->start_of_file = TRUE;
}


/*
 * Fill the input buffer --- called whenever buffer is emptied.
 * should never happen :)
 */

static boolean
fill_input_buffer (j_decompress_ptr cinfo)
{
  /* no-op */ (void)cinfo;
 return TRUE;
}


/*
 * Skip data --- used to skip over a potentially large amount of
 * uninteresting data (such as an APPn marker).
 */

static void
skip_input_data (j_decompress_ptr cinfo, long num_bytes)
{
  jpg_src_ptr src = (jpg_src_ptr) cinfo->src;

  if (num_bytes > 0) {
    src->pub.next_input_byte += (size_t) num_bytes;
    src->pub.bytes_in_buffer -= (size_t) num_bytes;
  }
}


/*
 * Terminate source --- called by jpeg_finish_decompress
 * after all data has been read.  Often a no-op.
 *
 * NB: *not* called by jpeg_abort or jpeg_destroy; surrounding
 * application must deal with any cleanup that should happen even
 * for error exit.
 */

static void
term_source (j_decompress_ptr cinfo)
{
  /* no work necessary here */ (void)cinfo;
}


/*
 * Prepare for input from mem buffer.
 * Leaves buffer untouched.
 */

static void
jpeg_memory_src (j_decompress_ptr cinfo, char * inbfr, int len)
{
  jpg_src_ptr src;

  /* The source object and input buffer are made permanent so that a series
   * of JPEG images can be read from the same file by calling jpeg_stdio_src
   * only before the first one.  (If we discarded the buffer at the end of
   * one image, we'd likely lose the start of the next one.)
   * This makes it unsafe to use this manager and a different source
   * manager serially with the same JPEG object.  Caveat programmer.
   */
  if (cinfo->src == NULL) {	/* first time for this JPEG object? */
    cinfo->src = (struct jpeg_source_mgr *)
      (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT,
				  (size_t)sizeof(jpg_source_mgr));
    src = (jpg_src_ptr) cinfo->src;
    src->buffer = (JOCTET *) inbfr;
  }

  src = (jpg_src_ptr) cinfo->src;
  src->pub.init_source = init_source;
  src->pub.fill_input_buffer = fill_input_buffer;
  src->pub.skip_input_data = skip_input_data;
  src->pub.resync_to_restart = jpeg_resync_to_restart; /* use default method */
  src->pub.term_source = term_source;
  src->infile = 0L;
  src->pub.bytes_in_buffer = len;		/*!!! sets to entire file len */
  src->pub.next_input_byte = (JOCTET *)inbfr;	/*!!! at start of buffer */
}


BOOL CJpgImage::LoadFromFile( const const char* pszFilename )
{
	FILE* fp = fopen( pszFilename, "rb" );
	if( fp == 0 )
		return false;
	fseek ( fp, 0, SEEK_END );
	DWORD dwFileSize = ftell( fp );
	if( dwFileSize == 0 )
	{
		fclose( fp );
		return false;
	}
	BYTE* pBuffer = new BYTE[dwFileSize];
	DWORD dwFileOffset = 0;
	rewind( fp );
	fread( pBuffer, dwFileSize, 1, fp );

	BOOL bOK = JPGDecode( pBuffer, dwFileSize );
	assert( bOK );
	delete []pBuffer;

	return TRUE;
}

DWORD* CJpgImage::CreateARGBBuffer()
{
	DWORD* pARGBBuffer = new DWORD[m_Width*m_Height];
	BYTE* pbySrc = m_pData;
	BYTE* pbyDst = (BYTE*)pARGBBuffer;
	for( int y = 0; y < m_Height; y++ )
	{
		for( int x = 0; x < m_Width; x++ )
		{
			*pbyDst++ = pbySrc[3*x+2];
			*pbyDst++ = pbySrc[3*x+1];
			*pbyDst++ = pbySrc[3*x+0];
			*pbyDst++ = 255;
		}
		pbySrc += m_Pitch;
	}
	return pARGBBuffer;
}
BOOL CJpgImage::ConvertTo( int nType )
{
	WORD* dst = (WORD*)m_pData;
	BYTE* pbySrc = m_pData;
	for( int y = 0; y < m_Height; y++ )
	{
		for( int x = 0; x < m_Width; x++ )
		{
			DWORD b = pbySrc[3*x+2];
			DWORD g = pbySrc[3*x+1];
			DWORD r = pbySrc[3*x+0];
			DWORD a = 1<<15;
			r >>= 3;
			r <<= 10;
			g >>= 3;
			g <<= 5;
			b >>= 3;
			*dst++ = a|r|g|b;
		}
		pbySrc += m_Pitch;
	}
	return TRUE;
}
BOOL CJpgImage::JPGDecode(LPBYTE pMemIn, DWORD dwLength)
{
	DWORD			dwBytes;
	eImgFmt		Format;

	struct jpg_error_mgr jerr;
	struct jpeg_decompress_struct cinfo;

	/* Step 1: allocate and initialize JPEG decompression object */
	
	/* We set up the normal JPEG error routines, then override error_exit. */
	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = my_error_exit;

	/* Establish the setjmp return context for my_error_exit to use. */
	if (setjmp(jerr.setjmp_buffer)) {
		/* If we get here, the JPEG code has signaled an error.
		 * We need to clean up the JPEG object, close the input file, and return.
		 */
		jpeg_destroy_decompress(&cinfo);
		return FALSE;
	}

	/* Now we can initialize the JPEG decompression object. */
	int size = sizeof(jpeg_decompress_struct);
	jpeg_create_decompress(&cinfo);


	/* Step 2: specify data source (eg, a file) */
	jpeg_memory_src(&cinfo, (char *)pMemIn, dwLength);


	/* Step 3: read file parameters with jpeg_read_header() */
	(void) jpeg_read_header(&cinfo, TRUE);

	// how big is this thing ?
	switch(cinfo.num_components)
	{
	case 1:
		Format = eImgFmt_L8;
		break;
	case 3:
		Format = eImgFmt_R8G8B8;
		break;
	default:
		return FALSE;
		break;
	}
	
	// Alloc Memory for Out Buffer
	dwBytes = cinfo.image_width * cinfo.image_height * cinfo.num_components;
	m_pData = new BYTE[dwBytes]; 
	if(m_pData == NULL) 
	{
		//lOut->Insert("TGADecode:Couldn't alloc memory for output buffer.\n");
		return FALSE;
	}

	m_Width = cinfo.image_width;
	m_Height = cinfo.image_height;
	m_Bytes = dwBytes;
	m_Format = Format; 
	m_BytesPerPixel = cinfo.num_components;
	m_Pitch = m_Width * cinfo.num_components;
	m_nMipLevels= 1;


	/* Step 4: set parameters for decompression */

	/* In this example, we don't need to change any of the defaults set by
	* jpeg_read_header(), so we do nothing here.
	*/

/////////////////	cinfo.out_color_space = JCS_GRAYSCALE;

	// decompress  

	jpeg_start_decompress(&cinfo);

    int increment = cinfo.output_width * cinfo.output_components;
	
	char *line = (char *)m_pData;

	while (cinfo.output_scanline < cinfo.output_height)
	{
		if (jpeg_read_scanlines(&cinfo, (unsigned char**) &line, 1))
		{
			line += increment;
		}
		else 
			break;
	}

    jpeg_finish_decompress(&cinfo);

	/* Step 8: Release JPEG decompression object */
	/* This is an important step since it will release a good deal of memory. */
	jpeg_destroy_decompress(&cinfo);

	return TRUE;
}

void CJpgImage::Destroy()
{
	if( m_pData )
	{
		delete []m_pData;
		m_pData = NULL;
	}
}
