#ifndef BQDLAYOUT_H
#define BQDLAYOUT_H

#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) \
|| defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define Q_DECL_EXPORT __declspec(dllexport)
#define Q_DECL_IMPORT __declspec(dllimport)
#else
#define Q_DECL_EXPORT __attribute__((visibility("default")))
#define Q_DECL_IMPORT __attribute__((visibility("default")))
#endif

#if defined(BQDLAYOUT_LIBRARY)
#define BQDLAYOUT_EXPORT Q_DECL_EXPORT
#else
#define BQDLAYOUT_EXPORT Q_DECL_IMPORT
#endif

#ifdef _WIN32
#define MYAPI __cdecl
#else
#define MYAPI
#endif

#ifdef __cplusplus
extern "C"{
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


/**
 * @brief createBQDLayoutFile   Create a BQD layout file.
 * @return BQDError
 */
BQDLAYOUT_EXPORT BQDError MYAPI createBQDLayoutFile(void);

/**
 * @brief printfBQDCode Print the file.
 * @param dbfile        Printer configuration file.
 * @param printername   Print the file name or printer name.
 * @param opf           Printer type
 *                          0: Standard printer
 *                          1: Generate PDF
 * @param var           Variable
 *                      var1=tmp1,var2=temp2,var3=temp3
 * @return  BQDError
 */
BQDLAYOUT_EXPORT BQDError MYAPI printfBQDCode(  const char * dbfile ,       //Printer configuration file.
                                                const char * printername ,  //Print the file name or printer name.
                                                int opf,                    //Printer type:0: Standard printer,1: Generate PDF
                                                const char * var );         //Var: var1=tmp1,var2=temp2,var3=temp3

/**
 * @brief getVarlist    Retrieve the list of variables.
 * @param dbfile        Print the configuration file.
 * @return              Varlist: name1,name2,name3,name4
 */
BQDLAYOUT_EXPORT const char * MYAPI getVarlist(const char * dbfile);

/**
 * @brief settingsBQDLayout     Adjust the layout.
 * @param dbfile                Print the configuration file.
 * @return BQDError
 */
BQDLAYOUT_EXPORT BQDError MYAPI settingsBQDLayout(const char * dbfile);
#ifdef __cplusplus
}
#endif


#endif // BQDLAYOUT_H
