#include <EEPROM.h>
#include <string>
using namespace std;

class Eeprom {

   public:
     Eeprom(){
      EEPROM.begin(512);
     }
     string esid="";
     string epass="";
     void clearSettings(){
       for (int i = 0; i < 96; ++i) {
          EEPROM.write(i, 0);
       }
       EEPROM.commit();
     };
     void readSettings(){
        esid="";
        epass = "";
        for (int i = 0; i < 32; ++i)
        {
          esid += char(EEPROM.read(i));
        }       
        for (int i = 32; i < 96; ++i)
        {
          epass += char(EEPROM.read(i));
        }
      };
      bool saveSettings(string qsid, string qpass){
        if (qsid.length() > 0 && qpass.length() > 0) {
          this->clearSettings();
          for (int i = 0; i < qsid.length(); ++i)
          {
            EEPROM.write(i, qsid[i]);
          }
          for (int i = 0; i < qpass.length(); ++i)
          {
            EEPROM.write(32 + i, qpass[i]);
          }
          EEPROM.commit();
          return true;
        }
        else{
          return false;
        }
      };
};
