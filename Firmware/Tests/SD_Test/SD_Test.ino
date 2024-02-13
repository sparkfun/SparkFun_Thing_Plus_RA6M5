/*
  Written for SparkFun Thing Plus RA6M5
  Just test to see if we can read/write to an SD card over SDHI
  
  This code is adapted from TestSDCARD in the ArduinoCore-renesas
  repo.

*/
#include <cstdint>
#include <vector>
#include <string>
// #include "ThingPlusSDCardBlockDevice.h"
#include "SDCardBlockDevice.h"
#include "FATFileSystem.h"

#define TEST_FS_NAME "fs"
#define TEST_FOLDER_NAME "TEST_FOLDER"
#define TEST_FILE "test.txt"
#define DELETE_FILE_DIMENSION 150

#define STORAGE_DEBUG
#define SDHI_DEBUG

SDCardBlockDevice block_device(PIN_SDHI_CLK, PIN_SDHI_CMD, PIN_SDHI_D0, PIN_SDHI_D1, PIN_SDHI_D2, PIN_SDHI_D3, PIN_SDHI_CD, PIN_SDHI_WP);
FATFileSystem fs(TEST_FS_NAME);

std::string root_folder = std::string("/") + std::string(TEST_FS_NAME);
std::string folder_test_name = root_folder + std::string("/") + std::string(TEST_FOLDER_NAME);
std::string file_test_name = folder_test_name + std::string("/") + std::string(TEST_FILE);

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);

  // Enable SD Card Power
  digitalWrite(SD_NEN, LOW);

  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);

  // Initialize Serial
  Serial.begin(115200);
  while(!Serial){};

  digitalWrite(LED_BUILTIN, LOW);

  // List to store all directory in the root
  std::vector<std::string> dir_list;

  Serial.println();
  Serial.println("##### TEST SD CARD WITH FATFS #####");
  Serial.println();

  // Mount SD Card as FatFS 
  Serial.println("Mounting SD Card...");

  int err = fs.mount(&block_device);
  if(err)
  {
    // If we can't mount the filesystem, reformat drive.
    // This should only happen on the first boot.
    Serial.println("No filesystem found, formatting...");
    err = fs.reformat(&block_device);
  }

  if(err)
  {
    Serial.println("Error formatting SD Card. Freezing...");
    while(1);
  }

  // Read root root_folder

  DIR *dir;
  struct dirent *ent;
  int dirIndex = 0;

  Serial.println("*** List SD Card contents: ");
  if ((dir = opendir(root_folder.c_str())) != NULL)
  {
    while ((ent = readdir(dir)) != NULL)
    {
      if(ent->d_type == DT_REG)
      {
        Serial.print("- [File]: ");
      }

      else if (ent->d_type == DT_DIR)
      {
        Serial.print("- [Dir]: ");
        dir_list.push_back(ent->d_name);
      }

      Serial.println(ent->d_name);
      dirIndex++;
    }
    closedir(dir);
  }
  else
  {
    Serial.println("Error opening SD Card.");
    while(1);
  }

  if(dirIndex == 0) 
  {
    Serial.println("Empty SD Card.");
  }

  bool found_test_folder = false;

  // List content of the first level folders
  if(dir_list.size())
  {
    Serial.println();
    Serial.println("Listing content of folders in root: ");
  }

  for(unsigned int i = 0; i < dir_list.size(); i++)
  {
    if(dir_list[i] == TEST_FOLDER_NAME)
    {
      found_test_folder = true;
    }

    Serial.print("- ");
    Serial.print(dir_list[i].c_str());
    Serial.println(":");

    std::string d = root_folder + std::string("/") + dir_list[i];
    if((dir = opendir(d.c_str())) != NULL)
    {
      while((ent = readdir(dir)) != NULL)
      {
        if(ent->d_type == DT_REG)
        {
          Serial.print("   - [File]: ");
        }
        else if(ent->d_type == DT_DIR)
        {
          Serial.print("   - [Dir]: ");
        }
        Serial.println(ent->d_name);
      }
      closedir(dir);
    }
    else
    {
      Serial.print("Error opening sub-folder");
      Serial.println(d.c_str());
    }
  }

  // Create TEST_FOLDER (if it doesn't already exist)
  err = 0;
  if(!found_test_folder)
  {
    Serial.println("Test folder not found... creating TEST_FOLDER");
    err = mkdir(folder_test_name.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
    if(err != 0)
    {
      Serial.print("Failed folder creation with error ");
      Serial.println(err);
    }
  }

  // Read test file content
  if(err == 0)
  {
    int file_dimension = 0;
    FILE* fp = fopen(file_test_name.c_str(), "r");
    if(fp != NULL)
    {
      Serial.print("Opened file: ");
      Serial.print(file_test_name.c_str());
      Serial.println(" for reading");

      fseek(fp, 0L, SEEK_END);
      int numbytes = ftell(fp);
      fseek(fp, 0L, SEEK_SET);

      Serial.print("Bytes in the file: ");
      Serial.println(numbytes);
      file_dimension = numbytes;

      if(numbytes > 0)
      {
        Serial.println();
        Serial.println("----- START FILE CONTENT -----");
      }

      for(int i = 0; i < numbytes; i++)
      {
        char ch;
        fread(&ch, sizeof(char), 1, fp);
        Serial.print(ch);
      }

      if(numbytes > 0)
      {
        Serial.println("----- END FILE CONTENT -----");
        Serial.println();
      }
      else
      {
        Serial.println("File is Empty!");
        Serial.println();
      }

      fclose(fp);
    }
    else
    {
      Serial.print("Failed to open file: ");
      Serial.println(file_test_name.c_str());
    }

    // Delete file if the file dimension is greater than 150 bytes
    if(file_dimension > DELETE_FILE_DIMENSION)
    {
      Serial.println("Test file reached the delete dimension... deleting it!");
      if(remove(file_test_name.c_str()) == 0)
      {
        Serial.println("Test file has been deleted!");
      }
    }

    // Append to the file.
    fp = fopen(file_test_name.c_str(), "a");
    if(fp != NULL)
    {
      Serial.print("Opened file: ");
      Serial.print(file_test_name.c_str());
      Serial.println(" for writing (append)");

      char text[] = "This line has been appended to file!\n";
      fwrite(text, sizeof(char), strlen(text), fp);
      fclose(fp);
    }
    else
    {
      Serial.print("Failed open file for appending ");
      Serial.println(file_test_name.c_str());
    }

    // Read file content again
    fp = fopen(file_test_name.c_str(), "r");
    if(fp != NULL)
    {
      Serial.print("Opened file: ");
      Serial.print(file_test_name.c_str());
      Serial.println(" for reading");

      fseek(fp, 0L, SEEK_END);
      int numbytes = ftell(fp);
      fseek(fp, 0L, SEEK_SET);

      Serial.print("Bytes in the file: ");
      Serial.println(numbytes);

      if(numbytes > 0)
      {
        Serial.println();
        Serial.println("----- START FILE CONTENT -----");
      }

      for(int i = 0; i < numbytes; i++)
      {
        char ch;
        fread(&ch, sizeof(char), 1, fp);
        Serial.print(ch);
      }

      if(numbytes > 0)
      {
        Serial.println("----- END FILE CONTENT -----");
        Serial.println();
      }
      else
      {
        Serial.println("File is EMPTY!");
        Serial.println();
      }

      fclose(fp);
    }
    else
    {
      Serial.print("Failed to open file for appending: ");
      Serial.println(file_test_name.c_str());
    }
  }
  Serial.println("This is the end. Goodbye.");

}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("[DEBUG] SD_Test.ino - LED On.");
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("[DEBUG] SD_Test.ino - LED Off.");
  delay(1000);
}
