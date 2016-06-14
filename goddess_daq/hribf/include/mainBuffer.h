#ifndef MAINBUFFER_H
#define MAINBUFFER_H

#include <fstream>

#include <string>
#include <vector>

#include <Rtypes.h> //Basic ROOT types


///Class to handle main buffer in MAIN evt files.
class mainBuffer
{
	private:
		///Size of open file.
		unsigned long int fFileSize;
		///Buffer header size in words.
		unsigned int fHeaderSize;
		///Buffer header size in bytes.
		unsigned int fHeaderSizeBytes;
		///Buffer size in words.
		unsigned int fBufferSize;
		///Buffer size in bytes.
		unsigned int fBufferSizeBytes;

		///Current byte in buffer.
		UInt_t fCurrentByte;

		///Number of good words in buffer.
		ULong64_t fNumWords;
		///Number of good bytes in buffer
		ULong64_t fNumBytes;
		
		///Abstract declaration of Storage Manager initialization.
		virtual void InitializeStorageManager() {};

	protected:
		///File name of evt file.
		const char *fFileName;
		///Size of a word in the buffer.
		unsigned short int fWordSize;

		///File stream
		std::ifstream fFile;
		///Buffer contatiner.
		std::vector< char > fBuffer;
		///Position of beginning of buffer in bytes.
		unsigned int fBufferBeginPos;

		///Type of events in this buffer.
		ULong64_t fBufferType;
		///Checksum should evaluate to 0.
		ULong64_t fChecksum;
		///Current run number.
		ULong64_t fRunNum;
		///The current buffer number.
		ULong64_t fBufferNumber;
		///Current event number within the current buffer.
		ULong64_t fEventNumber;
		///The number of events in the current buffer.
		ULong64_t fNumOfEvents;

		///The run title
		std::string fRunTitle;
		///The runs tart time
		time_t fRunStartTime; 
		///The run end time
		time_t fRunEndTime; 
		///The elapsed run time.
		unsigned int fElapsedRunTime;

		///The portion of word read.
		unsigned short int fFractionalWordPos;
		///The last word position of written data in buffer.
		unsigned int fWritePosition;
	
		///Set the length of a data word in bytes.
		void SetWordSize(int numOfBytes) {fWordSize = numOfBytes;};
		///Set the number of good words in a buffer.
		void SetNumOfWords(ULong64_t numOfWords) 
			{SetNumOfBytes(numOfWords * GetWordSize());};
		///Set the number of good bytes in a buffer.
		void SetNumOfBytes(ULong64_t numOfBytess);

		///Get the run title
		std::string ReadString(unsigned int maxWords, bool verbose=false);
		std::string ReadStringBytes(unsigned int maxBytes, bool verbose=false);

		///Return the length of the current event in words.
		virtual UInt_t GetEventLength();
		///Validates event length and returns result.
		UInt_t ValidatedEventLength(UInt_t eventLength);

		///Set the buffer size in bytes.
		void SetBufferSize(ULong64_t bufferSizeBytes);
		///Set the header size in bytes.
		void SetHeaderSize(ULong64_t headerSizeBytes);

		///Switch whether word of size index is middle endian.
		std::vector<bool> fMiddleEndian;
		///Identify words of the specified length as middle endian.
		void SetMiddleEndian(unsigned int wordSize, bool middleEndian=true);
		///Check if word length was registered as middle endian.
		bool IsMiddleEndian(unsigned int wordSize) 
			{return fMiddleEndian[wordSize];};

	public:
		///Default constructor
		mainBuffer(unsigned int headerSize, unsigned int bufferSize, unsigned int wordSize);
		///Construct a buffer from a specific file
		mainBuffer(const char *filename);
		///Default destructor
		virtual ~mainBuffer();

		///Open evt file.
		bool OpenFile(const char *filename);
		///Close evt file.
		void CloseFile();

		///Clear the current values for the buffer.
		virtual void Clear();
		///Copy data into the current buffer.
		//void Copy(word *source, unsigned int length);
		///Output the values stored in the buffer header.
		virtual void PrintBufferHeader()=0;
		///Reads the next buffer.
		virtual int ReadNextBuffer();
		///Get a line from the file.
		std::string GetLine();

		///Return the number of good words in the current buffer.
		ULong64_t GetNumOfWords() {return fNumWords;};
		///Return the number of good bytes in the current buffer.
		unsigned int GetNumOfBytes() {return fNumBytes;};
		///Return the number of events in the current buffer.
		unsigned int GetNumOfEvents() {return fNumOfEvents;};
		///Return the size for each buffer.
		unsigned int GetBufferSize() {return fBufferSize;};
		///Return the size for each buffer.
		unsigned int GetBufferSizeBytes() {return fBufferSizeBytes;};
		///Return the size for each buffer in words.
		unsigned int GetHeaderSize() {return fHeaderSize;};
		///Return the size for each buffer in bytes.
		unsigned int GetHeaderSizeBytes() {return fHeaderSizeBytes;};
		///Return current buffer type.
		int GetBufferType() {return fBufferType;};
		///Returns the number of the current buffer.
		unsigned int GetBufferNumber();

		///Return the filename of the currently opened file.
		const char* GetFilename() {return fFileName;};
		///Return current file position in bytes.
		unsigned long int GetFilePosition();
		///Return current file position in percent.
		float GetFilePositionPercentage();
		///Returnt he open file size.
		unsigned long int GetFileSize() {return fFileSize;};

		///Return current buffer position in words.
		unsigned int GetBufferPosition() 
			{return GetBufferPositionBytes() / GetWordSize();};
		///Return current buffer position in bytes.
		unsigned int GetBufferPositionBytes() {return fCurrentByte;};
		
		///Return current buffer begin position in bytes.
		unsigned int GetBufferBeginPosition() {return fBufferBeginPos;}
		///Return the current writing position in the buffer, effectively the buffer size.
		unsigned int GetWritePosition() {return fWritePosition;}
		///Return the number of events remaining in the current buffer.
		unsigned int GetEventsRemaining() {return fNumOfEvents - fEventNumber;};
		///Return the current event number.
		unsigned int GetEventNumber() {return fEventNumber;}

		///Read out next word in the buffer.
		ULong64_t GetWord();
		///Read out next word in the buffer of a specified size in bytes.
		ULong64_t GetWord(unsigned int numOfBytes);
		///Read out next word in the buffer of a specified size in bytes and endianess.
		ULong64_t GetWord(unsigned int numOfBytes, bool middleEndian);
		///Read out next long word in the buffer.
		ULong64_t GetLongWord();
		///Read out next long word in the buffer with the specified endianess.
		ULong64_t GetLongWord(bool middleEndian);
		///Get current word in the buffer.
		ULong64_t GetCurrentWord();
		///Get current long word in the buffer.
		ULong64_t GetCurrentLongWord();

		///Get the size of a standard word.
		unsigned short int GetWordSize() {return fWordSize;}
		///Skip forward in the buffer by n words.
		void Seek(int numOfWords);
		///Skip forward in the buffer by n bytes.
		void SeekBytes(int numOfBytes);

		///Dump the current buffer header in hex.
		void DumpHeader();
		///Dump the current buffer in hex.
		void DumpBuffer();
		///Dumps the words in the current run begin/end buffer.
		virtual void DumpRunBuffer();
		///Dumps the words in the current event.
		void DumpEvent(); 
		///Dumps the words in the current scaler event.
		virtual void DumpScalers();

		///Get Run Title
		std::string GetRunTitle() {return fRunTitle;}
		///Get run start time.
		time_t GetRunStartTime() {return fRunStartTime;}
		///Get run end time.
		time_t GetRunEndTime() {return fRunEndTime;}
		///Get run value for current buffer.
		ULong64_t GetRunNumber() {return fRunNum;}
		///Get the elapsed run time.
		unsigned int GetElapsedRunTime() {return fElapsedRunTime;}

		///Indicate if the current buffer contains physics data.
		virtual bool IsDataType() = 0;
		///Indicate if the current buffer contains scalers.
		virtual bool IsScalerType() = 0;
		///Indicate if the current buffer is a run begin buffer.
		virtual bool IsRunBegin() = 0;
		///Indicate if the current buffer is a run end buffer.
		virtual bool IsRunEnd() = 0;

		///Unpack the current buffer
		/**Returns true while there is more content in the buffer to be unpacked.
 		 * \param[in] verbose Verbosity flag.
 		 */
		virtual void UnpackBuffer(bool verbose = false) = 0;
		///Reads current event and stores data.
		virtual int ReadEvent(bool verbose = false) = 0;
		///Reads current scaler event.
		virtual void ReadScalers(bool verbose = false) = 0;
		///Read the run start buffer.
		virtual void ReadRunBegin(bool verbose = false) = 0;
		///Read the run end buffer.
		virtual void ReadRunEnd(bool verbose = false) = 0;

		///Converts a binary word to a string.
		std::string ConvertToString(ULong64_t word);

};

#endif
