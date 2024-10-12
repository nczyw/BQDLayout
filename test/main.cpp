#include <iostream>
#include <windows.h>
#include <filesystem>

#ifdef _WIN32
#define MYAPI __cdecl
#else
#define MYAPI
#endif

enum BQDError{
    BQDOk,          //BQD Normal
    BQDConfigErr,   //BQD There is an error in the printer configuration: incorrect paper size and margins.
    BQDVARErr,      //BQD Variable format error.
    BQDDLLErr,      //BQD The dependent `BQDCode.dll` does not exist.
    BQDNFErr,       //BQD Failed to create the BQD file because the save path was not selected.
    BQDPDFPathErr,  //BQD The PDF file path is incorrect.
    BQDPDFOErr,     //BQD The print file is in use or printer configuration error.
    BQDOFErr,       //BQD Failed to open the BQDLayout configuration file.
    BQDCBCErr,      //BQD Failed to create the barcode file.
    BQDCTErr,       //BQD Failed to create the text file.
    BQDCRTErr,      //BQD Failed to create the rectangle file.
    BQDCLErr,       //BQD Failed to create the line file.
    BQDRRErr,       //BQD Failed to create the rounded rectangle file.
    BQDDMErr,       //BQD Failed to create the DataMatrix file.
    BQDQRCErr,      //BQD Failed to create the QRCode file.
    BQDELPErr,      //BQD Failed to create the circle file.
    BQDSETLAYErr    //Failed to set the layout file.
};
typedef BQDError  (MYAPI *createBQDLayoutFileFunc)();
typedef BQDError  (MYAPI *printfBQDCodeFunc)(const char * dbfile ,
                                      const char * printername ,
                                      int opf ,
                                      const char * var
                                      );

typedef const char * (*getVarlistFunc)(const char * dbfile);

typedef BQDError (MYAPI *settingsBQDLayout) (const char * dbfile);

namespace fs = std::filesystem ;

HMODULE loadLibraryIfExists(const std::string& libName) {
    if (fs::exists(libName)) {
        HMODULE hLib = LoadLibraryA(libName.c_str());
        if (hLib == NULL) {
            std::cerr << "Failed to load library: " << libName << ". Error code: " << GetLastError() << std::endl;
        } else {
            std::cout << "Successfully loaded library: " << libName << std::endl;
        }
        return hLib;
    }
    return NULL;
}


int main(int argc, char *argv[]){
    // Define the library names
    std::string primaryLib = "BQDLayout.dll";
    std::string secondaryLib = "libBQDLayout.dll";

    // Attempt to load the primary library first
    HMODULE hBQD = loadLibraryIfExists(primaryLib);

    // If the primary library is not loaded, try loading the secondary library
    if (hBQD == NULL) {
        hBQD = loadLibraryIfExists(secondaryLib);
    }

    if (hBQD == NULL) {
        std::cerr << "Both libraries are missing or failed to load." << std::endl;
        return 1; // Return with error code
    }

    createBQDLayoutFileFunc createBQDLayoutFile = (createBQDLayoutFileFunc) GetProcAddress(hBQD,"createBQDLayoutFile");
    printfBQDCodeFunc printfBQDCode = (printfBQDCodeFunc) GetProcAddress(hBQD,"printfBQDCode");
    getVarlistFunc getVarlist = (getVarlistFunc) GetProcAddress(hBQD,"getVarlist");
    if(createBQDLayoutFile == NULL || printfBQDCode == NULL || getVarlist == NULL){
        std::cerr << "function exp fail" << std::endl;
        return 2 ;
    }
    //   std::cout << createBQDLayoutFile() << std::endl;
    const char * tmp = "Var=1234567890";
    std::cout << printfBQDCode("C:/Users/Sublime/Desktop/pdftest/NewBQD.bqd","C:/Users/Sublime/Desktop/pdftest/NewBQD.pdf",1,nullptr) << std::endl;//Microsoft Print to PDF
    //std::cout << printfBQDCode("C:/Users/Sublime/Desktop/pdftest/NewBQD.bqd","Microsoft Print to PDF",0,tmp) << std::endl;
    const char * var = NULL;
    var = getVarlist("C:/Users/Sublime/Desktop/pdftest/BQDCode.bqd");
    std::string str = var;
    std::cout <<  var << std::endl;
    return 0;
}
