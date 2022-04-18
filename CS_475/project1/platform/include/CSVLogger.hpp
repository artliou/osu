////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 475 - CSV Logger
//
// Jeremy Prater
//

class CSVLogger
{
public:
    static FILE * logFilePtr;
    static bool OpenLogFile(const char * logName);
    static void CloseLogFile();
    static void WriteLog(const char * format, ...);
};
