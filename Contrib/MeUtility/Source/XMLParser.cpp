#include "XMLParser.h"
#include "MediaPathManager.h"

/*
#ifdef DATA_LAUNCHER
#include "Cipher/cipher_factory.h"
#include "Launcher/DataLauncher.h"
#endif*/
#include "../filepacket/packet_interface.h"
template <class T>
inline T Clamp(T x, T min, T max)
{ 
	return (x < min) ? min : (x > max) ? max : x;
}
char cNULL = NULL;
// char *nullChar = new char(NULL);
char *nullChar = &cNULL;

RawData::RawData()
{
  data       = NULL;
  byteCount  = 0;
  skipDelete = false;
}
 
RawData::RawData(const RawData &copy)
{
  data       = NULL;
  byteCount  = 0;
  skipDelete = false;
  this->operator =(copy);
}

RawData &RawData::operator=(const RawData &copy)
{
  if(this != &copy)
  {
    destroy();
    byteCount  = copy.byteCount;
    skipDelete = false;

    if(byteCount > 0 && copy.data)
    {
      data = new char[byteCount];
      memcpy(data, copy.data, byteCount);
    }
  }
  return *this;
}

RawData::~RawData()
{
  destroy();
}

void RawData::destroy()
{
  if(data && !skipDelete)
  {
    deleteArray(data);
    byteCount = 0;
  }
} 

XMLTree::~XMLTree()
{
  flush();
}

XMLElement *XMLTree::getChildByName(const char *name)
{
  if(!name) return NULL;

  for(size_t i = 0; i < children.size(); i++)
    if(children[i]->getName() == name)
      return  children[i];
  return NULL;
}

XMLElement *XMLTree::getChild(size_t index)
{
  return index >= children.size() ? NULL : children[index];
}

size_t XMLTree::getChildrenCount()
{
  return children.size();
}

void XMLTree::flush()
{
  for(size_t t = 0; t < children.size(); t++)
    deleteObject(children[t]);
  children.clear();
}

void XMLTree::print()
{
  for(size_t t = 0; t < children.size(); t++)
    children[t]->print();
}

void XMLTree::addChild(XMLElement *child)
{
  if(!child) return;
  children.push_back(child);
}

XMLElement::XMLElement()
{
  value   = "NA";
  name    = "NA";
};

XMLElement::XMLElement(const XMLElement &copy)
{
  this->operator=(copy);
}

XMLElement &XMLElement::operator =(const XMLElement &copy)
{
  if(this != &copy)
  {
    flush();
    for(size_t i = 0; i < copy.children.size(); i++)
    {
      XMLElement *elem = new XMLElement();
      *elem = *copy.children[i];
      children.push_back(elem);
    }

    rawData = copy.rawData;
    value   = copy.value;
    name    = copy.name;
  }
  return *this;
}

void XMLElement::setValue(string &val)
{
  bool valid = 0;
  for(size_t i = 0; i <val.size(); i++)
    if(val[i] != ' '  &&
       val[i] != '\t' &&
       val[i] != '\n')
    {
      valid = true;
      break;
    }
  if(valid)
    value = val;
}
const bool	  XMLElement::getValueb()
{
	if ( !strcmp( value.c_str(), "true" ) )
	{
		return true;
	}
	else
	{
		return false;
	}
}
const int     XMLElement::getValuei(){ return int(atoi(value.c_str()));   }
const char   *XMLElement::getValuec()
{
	if ( !strcmp( value.c_str(), "NULL" ) )
	{
		return "";
	}
	else
	{
		return value.c_str();
	}
}
string	XMLElement::getValues()
{
	if ( !strcmp( value.c_str(), "NULL" ) )
	{
		return "";
	}
	else
	{
		return value;
	}
}
const float   XMLElement::getValuef(){ return float(atof(value.c_str())); }
const double  XMLElement::getValued(){ return atof(value.c_str());        }
const string &XMLElement::getValue() { return value;}
/*
void XMLElement::loadRX_GY_BZ_AWi(XMLElement &element, Tuple4i &attributes)
{
  XMLElement *child    = NULL;

  if((child = element.getChildByName("x")) ||
     (child = element.getChildByName("r")) ||
     (child = element.getChildByName("R")) ||
     (child = element.getChildByName("X")))
    attributes.x = child->getValuei();

  if((child = element.getChildByName("y")) ||
     (child = element.getChildByName("g")) ||
     (child = element.getChildByName("G")) ||
     (child = element.getChildByName("Y")))
    attributes.y = child->getValuei();

  if((child = element.getChildByName("z")) ||
     (child = element.getChildByName("b")) ||
     (child = element.getChildByName("B")) ||
     (child = element.getChildByName("Z")))
    attributes.z = child->getValuei();

  if((child = element.getChildByName("w")) ||
     (child = element.getChildByName("a")) ||
     (child = element.getChildByName("A")) ||
     (child = element.getChildByName("W")))
    attributes.w = child->getValuei();
}

void XMLElement::loadRX_GY_BZ_AWf(XMLElement &element, Tuple4f &attributes)
{
  XMLElement *child    = NULL;

  if((child = element.getChildByName("x")) ||
     (child = element.getChildByName("r")) ||
     (child = element.getChildByName("R")) ||
     (child = element.getChildByName("X")))
    attributes.x = child->getValuef();

  if((child = element.getChildByName("y")) ||
     (child = element.getChildByName("g")) ||
     (child = element.getChildByName("G")) ||
     (child = element.getChildByName("Y")))
    attributes.y = child->getValuef();

  if((child = element.getChildByName("z")) ||
     (child = element.getChildByName("b")) ||
     (child = element.getChildByName("B")) ||
     (child = element.getChildByName("Z")))
    attributes.z = child->getValuef();

  if((child = element.getChildByName("w")) ||
     (child = element.getChildByName("a")) ||
     (child = element.getChildByName("A")) ||
     (child = element.getChildByName("W")))
    attributes.w = child->getValuef();
}

void XMLElement::loadRX_GY_BZi(XMLElement &element, Tuple3i &attributes)
{
  XMLElement *child    = NULL;

  if((child = element.getChildByName("x")) ||
     (child = element.getChildByName("r")) ||
     (child = element.getChildByName("R")) ||
     (child = element.getChildByName("X")))
    attributes.x = child->getValuei();

  if((child = element.getChildByName("y")) ||
     (child = element.getChildByName("g")) ||
     (child = element.getChildByName("G")) ||
     (child = element.getChildByName("Y")))
    attributes.y = child->getValuei();

  if((child = element.getChildByName("z")) ||
     (child = element.getChildByName("b")) ||
     (child = element.getChildByName("B")) ||
     (child = element.getChildByName("Z")))
    attributes.z = child->getValuei();
}

void XMLElement::loadRX_GY_BZf(XMLElement &element, Tuple3f &attributes)
{
  XMLElement *child    = NULL;

  if((child = element.getChildByName("x")) ||
     (child = element.getChildByName("r")) ||
     (child = element.getChildByName("R")) ||
     (child = element.getChildByName("X")))
    attributes.x = child->getValuef();

  if((child = element.getChildByName("y")) ||
     (child = element.getChildByName("g")) ||
     (child = element.getChildByName("G")) ||
     (child = element.getChildByName("Y")))
    attributes.y = child->getValuef();

  if((child = element.getChildByName("z")) ||
     (child = element.getChildByName("b")) ||
     (child = element.getChildByName("B")) ||
     (child = element.getChildByName("Z")))
    attributes.z = child->getValuef();
}

void XMLElement::loadRX_GYi(XMLElement &element,  Tuple2i &attributes)
{
  XMLElement *child    = NULL;

  if((child = element.getChildByName("x")) ||
     (child = element.getChildByName("r")) ||
     (child = element.getChildByName("R")) ||
     (child = element.getChildByName("X")))
    attributes.x = child->getValuei();

  if((child = element.getChildByName("y")) ||
     (child = element.getChildByName("g")) ||
     (child = element.getChildByName("G")) ||
     (child = element.getChildByName("Y")))
    attributes.y = child->getValuei();
}

void XMLElement::loadRX_GYf(XMLElement &element,  Tuple2f &attributes)
{
  XMLElement *child    = NULL;

  if((child = element.getChildByName("x")) ||
     (child = element.getChildByName("r")) ||
     (child = element.getChildByName("R")) ||
     (child = element.getChildByName("X")))
    attributes.x = child->getValuef();

  if((child = element.getChildByName("y")) ||
     (child = element.getChildByName("g")) ||
     (child = element.getChildByName("G")) ||
     (child = element.getChildByName("Y")))
    attributes.y = child->getValuef();
} 
*/
void XMLElement::print()
{
  cout << "Name: "    << name 
       << ", Value: " << value  <<". \n";
  XMLTree::print();
}

XMLElement::~XMLElement()
{
  flush();
}

void XMLElement::flush()
{
  XMLTree::flush();
  rawData.destroy(); 
}

XMLStack::XMLStack(char *xmlFilePath, bool isOn)
{
  XMLVersion = 1.0;
  loggerOn   = isOn;
  encoding   = "ISO-8859-1";
  state      = XML_READY;
  if(xmlFilePath)
    state = loadXMLFile(xmlFilePath);
  else
    state = XML_FILE_NOT_FOUND;    
};

XMLStack::XMLStack(const XMLStack &copy)
{
  this->operator=(copy);
}

XMLStack &XMLStack::operator =(const XMLStack &copy)
{
  if(this != &copy)
  {
    flush();
    for(size_t i = 0; i < copy.children.size(); i++)
    {
      XMLElement *element = new XMLElement();
                 *element = *copy.children[i];
      addChild(element);
    }
    XMLVersion = copy.XMLVersion;
    encoding   = copy.encoding;
    loggerOn   = copy.loggerOn;
    state      = copy.state;
  }
  return *this;
}

XMLStack::~XMLStack()
{
  flush();
}

void XMLStack::print()
{
  cout << "Version: " << XMLVersion
       << ", Encoding: " << encoding << endl;
  XMLTree::print();
}

int XMLStack::loadXMLBuffer( const char *pszBuffer, int nBufferSize )
{
	if( !pszBuffer )
	{
		return XML_FILE_NOT_FOUND;
	}
	char       *progress     = NULL,
				*stream       = NULL;

	bufferProgress = 0;
	bufferSize     = 0;

	flush();
	state        = XML_SUCCESS;
	stream      = new char[nBufferSize + 1];
	memset(stream, NULL, nBufferSize + 1);
	strncpy( stream, pszBuffer, nBufferSize );
	bufferSize = nBufferSize;
	
	progress    =  stream;
	do
	{
		XMLElement *parent = new XMLElement();
		progress = parseXMLStream(progress, parent);
		addChild(parent);
	}
	while(*progress && (state == XML_SUCCESS));
	deleteArray(stream);
	if(state != XML_SUCCESS) 
	{
		flush();
		return Logger::writeErrorLog(string("Failed to parse the XML File at <") + 
			"NULL" + ">");
	}

	return XML_SUCCESS;
}

#include "StringLanguageTranslator.h"

int XMLStack::loadXMLFile(const char *xmlFilePath)
{
//   const char *verifiedPath = MediaPathManager::lookUpMediaPath(xmlFilePath);
  const char *verifiedPath = (xmlFilePath);
  size_t      pathLength   =    0;
  char       *progress     = NULL,
             *stream       = NULL;

  bufferProgress = 0;
  bufferSize     = 0;

  flush();
  f_Handle* fp = NULL;

  /*
#ifdef DATA_LAUNCHER
  if (g_DirectReadInPackage)
  {
// 	  fp = fopen(verifiedPath,"rb");
	  fp = Cipher::CipherFactory::OpenCipherFile(verifiedPath);
	  if (!fp)
	  {
			return (state = XML_FILE_NOT_FOUND);
	  }
  }
  else
#endif
*/
  {
	  fp = packet_namespace::w_fopen(verifiedPath,"rb");
	  if (!fp)
	  {
// 		  fp = Cipher::CipherFactory::OpenCipherFile(verifiedPath);
// 		  if (!fp)
		  {
			  return (state = XML_FILE_NOT_FOUND);
		  }
	  }
  }
  packet_namespace::w_fseek ( fp, 0, SEEK_END );
  bufferSize =  packet_namespace::w_ftell( fp );
  packet_namespace::w_rewind( fp );
  stream      = new char[bufferSize + 1];
  memset(stream, NULL, bufferSize + 1);
  packet_namespace::w_fread(stream,sizeof(char),bufferSize,fp);
  packet_namespace::w_fclose(fp);
//   if (verifiedPath)
//   {
// 	  ifstream fileInputStream(verifiedPath, ifstream::in | ifstream::binary);
// 	  fileInputStream.seekg(0, ios::end);
// 
// 	  bufferSize  = fileInputStream.tellg();
// 	  stream      = new char[bufferSize + 1];
// 	  memset(stream, NULL, bufferSize + 1);
// 
// 	  fileInputStream.seekg(0, ios::beg);
// 	  fileInputStream.read(stream, bufferSize);
// 	  fileInputStream.close();
//   }
//   else
//   {
// 	  static char temp[1024];
// 	  sprintf(temp,"%sc",xmlFilePath);
// // 	  verifiedPath = MediaPathManager::lookUpMediaPath(temp);
// 	  verifiedPath = (temp);
// 	  if(!verifiedPath) 
// 		  return (state = XML_FILE_NOT_FOUND);
// 
// 	  ifstream fileInputStream(verifiedPath, ifstream::in | ifstream::binary);
// 	  fileInputStream.seekg(0, ios::end);
// 	  bufferSize  = fileInputStream.tellg();
// 	  char* buffer = new char[bufferSize];
// 	  fileInputStream.seekg(0, ios::beg);
// 	  fileInputStream.read(buffer, bufferSize);
// 	  fileInputStream.close();
// 
// 	  int outputSize = Cipher::g_Decoder->GetOutputLength( bufferSize ) + 1;
// 	  stream      = new char[outputSize];
// 	  memset(stream,0,outputSize);
// 
// // 	  try
// 	  {
// 		  bufferSize = Cipher::g_Decoder->Decode( (unsigned char*)stream, (unsigned char*)buffer, bufferSize );
// 	  }
// // 	  catch( Cipher::DecodeException& reason )
// 	  {
// 		  // 					SetError( TIXML_ERROR_OPENING_FILE, 0, 0, TIXML_ENCODING_UNKNOWN );
// 		  // 					std::cout << "decode exception and problem is " << reason.what() << std::endl;
// 	  }
// 
// 	  delete [] buffer;
// 
//   }

  pathLength = strlen(verifiedPath);

  for(size_t t = 0; t < pathLength; t++)
  {
    if(verifiedPath[t] == '.')
      break;
    logFilePath += verifiedPath[t];
  }

  logFilePath += ".err";

  state        = XML_SUCCESS;

  std::string strContent;
  if ((stream[0] == (char)0xef) && (stream[1] == (char)0xbb) && (stream[2] == (char)0xbf))//支持带文件头的utf-8格式
  {
	  progress = &stream[3];
//	  strContent= STN(&stream[3], bufferSize + 1 - 3);
  }
  else
  {
	  progress = stream;
// 	strContent= STN(stream, bufferSize + 1);
  }
//   delete[] stream;
// 
//   bufferSize  = strContent.size();
//   stream      = new char[bufferSize+1];
//   memset(stream, NULL, bufferSize+1);
//   strcpy_s( stream, bufferSize+1, strContent.c_str());

//   progress = stream;
  do
  {
    XMLElement *parent = new XMLElement();
    progress = parseXMLStream( progress, parent);
    addChild(parent);
  }
  while(*progress && (state == XML_SUCCESS));
 
 
  deleteArray(stream);
  if(state != XML_SUCCESS) 
  {
    flush();
    return Logger::writeErrorLog(string("Failed to parse the XML File at <") + 
                                 verifiedPath + ">");
  }
  return XML_SUCCESS;
}

void XMLStack::writeFatalLogInfo(const char* string)
{
  if(!loggerOn)  return;
  ofstream logFile(logFilePath.c_str());
  if(!logFile.is_open())   return;
  logFile << string;
  logFile << endl;
  logFile.close();
  state = XML_FAILED;
}

void XMLStack::writeFatalLogInfoList(const char* format,...)
{
  if(!loggerOn) 
    return;

  ofstream logFile(logFilePath.c_str() );

  if(!logFile.is_open()) 
     return;

  char stringBuffer[256] = {0};
  va_list  arguments;
  va_start(arguments, format);
  vsnprintf(stringBuffer, sizeof(stringBuffer)-1, format, arguments);
  va_end(arguments);
  logFile << stringBuffer;
  logFile << endl;
  logFile.close();
  state = XML_FAILED;
}

void XMLStack::flush()
{
  XMLTree::flush();
  state  = XML_READY;
}

bool XMLStack::moveAndCheckProgress(int jump)
{
  if((bufferProgress += jump) > bufferSize)
  {
    state = XML_BUFFER_OVERFLOW;
    return false;
  }

  return true;
}

int  XMLStack::getRemainingBytes()
{
  return Clamp(bufferSize - bufferProgress, 0, bufferSize);
}

bool XMLStack::consumeWhiteSpaces(char **stream)
{
  while((**stream) != NULL && 
        (**stream  == ' ' || **stream == '\n' || 
         **stream  == '\t'|| **stream == '\r'))
  {
    (*stream)++;
    if(!moveAndCheckProgress()) return false;
  }
  return (**stream) != NULL;
}

bool XMLStack::consumeComment(char **stream)
{
  consumeWhiteSpaces(stream);
  if(*(*stream + 0) == '<' && *(*stream + 1) == '!' &&
     *(*stream + 2) == '-' && *(*stream + 3) == '-')
  {
    (*stream) = strstr((*stream) +=4, "-->") + 3;
    consumeWhiteSpaces(stream);
    return true;
  }
  return false;
}

void XMLStack::getIdentifier(char **stream, string& identifier)
{
  int    counter = 0;
  consumeWhiteSpaces(stream);

  while((**stream >= 'A'    &&
         **stream <= 'Z' )  ||

         **stream == '_'    ||
         **stream == '.'    ||
         **stream == ':'    ||
        (**stream >= 'a'   &&
         **stream <= 'z' ) ||

       (**stream >= '0'   &&
        **stream <= '9'))
  {
    counter++;
    (*stream)++;
    if(!moveAndCheckProgress()) return;
  }

  if(counter)
  {
//	  length = counter;
	  string szTemp = *stream-counter;
	  identifier = szTemp.substr( 0, counter );
  }
  //  identifier = ( (*stream) - counter );//, counter);

  consumeWhiteSpaces(stream); 
}

void XMLStack::getStreamedValue(char **stream, string& streamedVals)
{
  int    counter = 0;

  if(!consumeWhiteSpaces(stream)) return;

  while(**stream != '<' && **stream != NULL)
  {
    counter++;
    (*stream)++;
    if(!moveAndCheckProgress()) return;
  }

  if(counter)
  {
	  string szTemp = *stream-counter;
	  streamedVals = szTemp.substr( 0, counter );
  }

   // streamedVals = ((*stream) - counter);//, counter);

  if(**stream == NULL)
    state = XML_FAILED;
  else
    consumeWhiteSpaces(stream);
}

bool XMLStack::fillRawData(char **stream, RawData *dataStruct, int bytesCount)
{
  if(!dataStruct || !(*stream))
    return false;

  int  charCounter = 0;
  char *subStream  =  bytesCount > 0 ? new char[bytesCount + 1] : (*stream);

  if(bytesCount > 0)  
  {
    if(getRemainingBytes() <= bytesCount)
    {
      state = XML_BUFFER_OVERFLOW;
      return false;
    }
    dataStruct->byteCount = bytesCount;
    memset(subStream,      NULL, bytesCount + 1);
    memcpy(subStream, (*stream), bytesCount);
    (*stream) +=bytesCount;
    moveAndCheckProgress(bytesCount);
  }
  else
  {
    while(!(*(subStream + 0) == '<' && *(subStream + 1) == '/' &&
            *(subStream + 2) == 'R' && *(subStream + 3) == 'a' &&
            *(subStream + 4) == 'w' && *(subStream + 5) == 'D' &&
            *(subStream + 6) == 'a' && *(subStream + 7) == 't' &&
            *(subStream + 8) == 'a'))
    {
      charCounter++; subStream++;
      if(!moveAndCheckProgress()) 
        return false;
    }

    if(!charCounter)
      return false;

    subStream = new char[charCounter + 1];
    memset(subStream,      NULL, charCounter + 1);
    memcpy(subStream, (*stream), charCounter);
    (*stream)+=charCounter;
    dataStruct->byteCount = charCounter;
  }
  dataStruct->data = subStream; 
  return true;
}

void XMLStack::getStringValue(char **stream, string &value)
{
  int    counter = 0;

  if(!consumeWhiteSpaces(stream)) return;
  (*stream)++;
  if(!moveAndCheckProgress())     return;
  if(!consumeWhiteSpaces(stream)) return;
  (*stream)++;
  if(!moveAndCheckProgress())     return;

  while(**stream != '\"' && **stream != NULL)
  {
    counter++; (*stream)++;
    if(!moveAndCheckProgress())   return;
  }

  if(counter)
  {
	  string szTemp = *stream-counter;
	  value = szTemp.substr( 0, counter );
  }
 //   value = ((*stream) - counter );//, counter);

  if(**stream == NULL)
    state = XML_FAILED;
  else
  {
    (*stream)++;               //Get rid of the second quote sign
    if(!moveAndCheckProgress())     return;
    if(!consumeWhiteSpaces(stream)) return;
  }
}

bool XMLStack::consumeXMLHeader(char **stream)
{  
  string token, value;

  if(*(*stream + 0) == '<' && *(*stream + 1) == '?' &&
     *(*stream + 2) == 'x' && *(*stream + 3) == 'm' &&
     *(*stream + 4) == 'l')
  {
    (*stream)+=5;
    if(!moveAndCheckProgress(5))  return false;

    while(**stream != '?')
    {
      getIdentifier(stream, token);
      getStringValue(stream, value);

      if((const string &)token == "version")
         XMLVersion = float(atof(value.c_str()));
      if((const string &)token == "encoding")
         encoding = value;
    }
  }
  else
    return false;
  (*stream)+=2;
  consumeWhiteSpaces(stream);
  return true;
}

char* XMLStack::parseXMLStream(char *stream, XMLElement *parent)
{
	if( nullChar == NULL )
		nullChar = new char(NULL);
  if(!stream || !parent) 
    return nullChar;

  string token;

  if(state == XML_FAILED || state == XML_BUFFER_OVERFLOW) 
    return nullChar;

  if(!consumeWhiteSpaces(&stream))
    return nullChar;

  if(*stream == '<'            &&
     (!consumeComment(&stream) &&
      !consumeXMLHeader(&stream)))
  {
    stream++;
    if(!moveAndCheckProgress())  return nullChar;
    getIdentifier(&stream, token);
    parent->setName(token);

    if(state == XML_FAILED || state == XML_BUFFER_OVERFLOW) 
      return nullChar;

    if(*stream == '>')
    {
      stream++;
      if(!moveAndCheckProgress())  return nullChar;
    }
    else
    {
      while((*stream != '/' && *(stream + 1) != '>') &&
            (*stream != '>'))
      {
        XMLElement *newTag = new XMLElement();
        getIdentifier(&stream, token);
        newTag->setName(token);

        if(state == XML_FAILED || state == XML_BUFFER_OVERFLOW) 
          return nullChar;

        token.clear();
        getStringValue(&stream, token);
        newTag->setValue(token);

        if(state == XML_FAILED || state == XML_BUFFER_OVERFLOW) 
           return nullChar;
        parent->addChild(newTag);
      }

      if(*stream == '/' && *(stream + 1) == '>')
      {
        stream +=2; 
        if(!moveAndCheckProgress(2))  return nullChar;
          return stream;
      }
      stream++;
    }

    if(parent->getName() != "RawData")
    { 
      getStreamedValue(&stream, token);
      parent->setValue(token);
    }
    else
    {
      XMLElement *info = parent->getChildByName("length");
      bool       sucess = (!info) ? fillRawData(&stream, &parent->rawData) :
                                    fillRawData(&stream, &parent->rawData, 
                                                          info->getValuei());
      if(!sucess)
        writeFatalLogInfo("\n<!>Failed to load raw data, check your XML file.\n");
      if(state == XML_FAILED || state == XML_BUFFER_OVERFLOW) 
        return nullChar;
    }
      
    if(!consumeWhiteSpaces(&stream))
      return nullChar;
    
    consumeComment(&stream);

    while(*stream == '<' && *(stream + 1) != '/')
    {
      XMLElement *newTag = new XMLElement();
      stream             = parseXMLStream(stream, newTag);

      if(!stream || !consumeWhiteSpaces(&stream))
        return nullChar;
      parent->addChild(newTag);
    }

    if(*stream == '<' && *(stream + 1)== '/')
    {
      stream+=2;
      if(!moveAndCheckProgress(2))  return nullChar;

      getIdentifier(&stream, token);
      if(state == XML_FAILED || state == XML_BUFFER_OVERFLOW) 
        return nullChar;
    }

    if(token != parent->getName() || *stream != '>')
    {
      writeFatalLogInfoList("\n<!>Start tag <%s> & End Tag <%s> do not match,"\
                            "check your XML file.\n", 
                            parent->getName().c_str(), token.c_str());
      return nullChar; 
    }
    stream++;
    if(!consumeWhiteSpaces(&stream)) return nullChar;

  }
  return (state == XML_SUCCESS) ? stream : nullChar;
}
