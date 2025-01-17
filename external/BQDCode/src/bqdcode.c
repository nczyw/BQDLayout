#include "bqdcode.h"
int streaming = 0 ;
struct Barcode_Item *BQDBarcode_Create(char *text){
    return Barcode_Create(text);
}

int BQDBarcode_Delete(struct Barcode_Item *bc){
    return Barcode_Delete(bc);
}

int BQDBarcode_Encode(struct Barcode_Item *bc, int flags){
    return Barcode_Encode(bc, flags);
}

int BQDBarcode_Print(struct Barcode_Item *bc, FILE *f, int flags){
    return Barcode_Print(bc, f, flags);
}
int BQDBarcode_Position(struct Barcode_Item *bc, int wid, int hei,int xoff, int yoff, double scalef){
    return Barcode_Position(bc, wid, hei, xoff, yoff, scalef);
}
int BQDBarcode_Encode_and_Print(char *text, FILE *f, int wid, int hei,int xoff, int yoff, int flags){
    return Barcode_Encode_and_Print(text, f, wid, hei, xoff, yoff, flags);
}
int BQDBarcode_Version(char *versionname){
    return Barcode_Version(versionname);
}

/*
 * dmtx functions
*/
DmtxTime BQDdmtxTimeNow(void){
    return dmtxTimeNow();
}

DmtxTime BQDdmtxTimeAdd(DmtxTime t, long msec){
    return dmtxTimeAdd(t, msec);
}

int BQDdmtxTimeExceeded(DmtxTime timeout){
    return dmtxTimeExceeded(timeout);
}

DmtxEncode *BQDdmtxEncodeCreate(void){
    return dmtxEncodeCreate();
}

DmtxPassFail BQDdmtxEncodeDestroy(DmtxEncode **enc){
    return dmtxEncodeDestroy(enc);
}

DmtxPassFail BQDdmtxEncodeSetProp(DmtxEncode *enc, int prop, int value){
    return dmtxEncodeSetProp(enc, prop, value);
}

int BQDdmtxEncodeGetProp(DmtxEncode *enc, int prop){
    return dmtxEncodeGetProp(enc, prop);
}

DmtxPassFail BQDdmtxEncodeDataMatrix(DmtxEncode *enc, int n, unsigned char *s){
    return dmtxEncodeDataMatrix(enc, n, s);
}

DmtxPassFail BQDdmtxEncodeDataMosaic(DmtxEncode *enc, int n, unsigned char *s){
    return dmtxEncodeDataMosaic(enc, n, s);
}

DmtxDecode *BQDdmtxDecodeCreate(DmtxImage *img, int scale){
    return dmtxDecodeCreate(img, scale);
}

DmtxPassFail BQDdmtxDecodeDestroy(DmtxDecode **dec){
    return dmtxDecodeDestroy(dec);
}

DmtxPassFail BQDdmtxDecodeSetProp(DmtxDecode *dec, int prop, int value){
    return dmtxDecodeSetProp(dec, prop, value);
}

int BQDdmtxDecodeGetProp(DmtxDecode *dec, int prop){
    return dmtxDecodeGetProp(dec, prop);
}

unsigned char *BQDdmtxDecodeGetCache(DmtxDecode *dec, int x, int y){
    return dmtxDecodeGetCache(dec, x, y);
}

DmtxPassFail BQDdmtxDecodeGetPixelValue(DmtxDecode *dec, int x, int y, int channel, /*@out@*/ int *value){
    return dmtxDecodeGetPixelValue(dec, x, y, channel, value);
}

DmtxMessage *BQDdmtxDecodeMatrixRegion(DmtxDecode *dec, DmtxRegion *reg, int fix){
    return dmtxDecodeMatrixRegion(dec, reg, fix);
}

DmtxMessage *BQDdmtxDecodePopulatedArray(int sizeIdx, DmtxMessage *msg, int fix){
    return dmtxDecodePopulatedArray(sizeIdx, msg, fix);
}

DmtxMessage *BQDdmtxDecodeMosaicRegion(DmtxDecode *dec, DmtxRegion *reg, int fix){
    return dmtxDecodeMosaicRegion(dec, reg, fix);
}

unsigned char *BQDdmtxDecodeCreateDiagnostic(DmtxDecode *dec, /*@out@*/ int *totalBytes, /*@out@*/ int *headerBytes, int style){
    return dmtxDecodeCreateDiagnostic(dec, totalBytes, headerBytes, style);
}

DmtxRegion *BQDdmtxRegionCreate(DmtxRegion *reg){
    return dmtxRegionCreate(reg);
}

DmtxPassFail BQDdmtxRegionDestroy(DmtxRegion **reg){
    return dmtxRegionDestroy(reg);
}

DmtxRegion *BQDdmtxRegionFindNext(DmtxDecode *dec, DmtxTime *timeout){
    return dmtxRegionFindNext(dec, timeout);
}
DmtxRegion *BQDdmtxRegionScanPixel(DmtxDecode *dec, int x, int y){
    return dmtxRegionScanPixel(dec, x, y);
}

DmtxPassFail BQDdmtxRegionUpdateCorners(DmtxDecode *dec, DmtxRegion *reg, DmtxVector2 p00,
      DmtxVector2 p10, DmtxVector2 p11, DmtxVector2 p01){
        return dmtxRegionUpdateCorners(dec, reg, p00, p10, p11, p01);
}
DmtxPassFail BQDdmtxRegionUpdateXfrms(DmtxDecode *dec, DmtxRegion *reg){
    return dmtxRegionUpdateXfrms(dec, reg);
}
DmtxMessage *BQDdmtxMessageCreate(int sizeIdx, int symbolFormat){
    return dmtxMessageCreate(sizeIdx, symbolFormat);
}

DmtxPassFail BQDdmtxMessageDestroy(DmtxMessage **msg){
    return dmtxMessageDestroy(msg);
}

DmtxImage *BQDdmtxImageCreate(unsigned char *pxl, int width, int height, int pack){
    return dmtxImageCreate(pxl, width, height, pack);
}

DmtxPassFail BQDdmtxImageDestroy(DmtxImage **img){
    return dmtxImageDestroy(img);
}

DmtxPassFail BQDdmtxImageSetChannel(DmtxImage *img, int channelStart, int bitsPerChannel){
    return dmtxImageSetChannel(img, channelStart, bitsPerChannel);
}

DmtxPassFail BQDdmtxImageSetProp(DmtxImage *img, int prop, int value){
    return dmtxImageSetProp(img, prop, value);
}
int BQDdmtxImageGetProp(DmtxImage *img, int prop){
    return dmtxImageGetProp(img, prop);
}

int BQDdmtxImageGetByteOffset(DmtxImage *img, int x, int y){
    return dmtxImageGetByteOffset(img, x, y);
}

DmtxPassFail BQDdmtxImageGetPixelValue(DmtxImage *img, int x, int y, int channel, /*@out@*/ int *value){
    return dmtxImageGetPixelValue(img, x, y, channel, value);
}

DmtxPassFail BQDdmtxImageSetPixelValue(DmtxImage *img, int x, int y, int channel, int value){
    return dmtxImageSetPixelValue(img, x, y, channel, value);
}

DmtxBoolean BQDdmtxImageContainsInt(DmtxImage *img, int margin, int x, int y){
    return dmtxImageContainsInt(img, margin, x, y);
}

DmtxBoolean BQDdmtxImageContainsFloat(DmtxImage *img, double x, double y){
    return dmtxImageContainsFloat(img, x, y);
}

DmtxVector2 *BQDdmtxVector2AddTo(DmtxVector2 *v1, const DmtxVector2 *v2){
    return dmtxVector2AddTo(v1, v2);
}

DmtxVector2 *BQDdmtxVector2Add(/*@out@*/ DmtxVector2 *vOut, const DmtxVector2 *v1, const DmtxVector2 *v2){
    return dmtxVector2Add(vOut, v1, v2);
}

DmtxVector2 *BQDdmtxVector2SubFrom(DmtxVector2 *v1, const DmtxVector2 *v2){
    return dmtxVector2SubFrom(v1, v2);
}

DmtxVector2 *BQDdmtxVector2Sub(/*@out@*/ DmtxVector2 *vOut, const DmtxVector2 *v1, const DmtxVector2 *v2){
    return dmtxVector2Sub(vOut, v1, v2);
}

DmtxVector2 *BQDdmtxVector2ScaleBy(DmtxVector2 *v, double s){
    return dmtxVector2ScaleBy(v, s);
}

DmtxVector2 *BQDdmtxVector2Scale(/*@out@*/ DmtxVector2 *vOut, const DmtxVector2 *v, double s){
    return dmtxVector2Scale(vOut, v, s);
}

double BQDdmtxVector2Cross(const DmtxVector2 *v1, const DmtxVector2 *v2){
    return dmtxVector2Cross(v1, v2);
}

double BQDdmtxVector2Norm(DmtxVector2 *v){
    return dmtxVector2Norm(v);
}

double BQDdmtxVector2Dot(const DmtxVector2 *v1, const DmtxVector2 *v2){
    return dmtxVector2Dot(v1, v2);
}

double BQDdmtxVector2Mag(const DmtxVector2 *v){
    return dmtxVector2Mag(v);
}

double BQDdmtxDistanceFromRay2(const DmtxRay2 *r, const DmtxVector2 *q){
    return dmtxDistanceFromRay2(r, q);
}

double BQDdmtxDistanceAlongRay2(const DmtxRay2 *r, const DmtxVector2 *q){
    return dmtxDistanceAlongRay2(r, q);
}

DmtxPassFail BQDdmtxRay2Intersect(/*@out@*/ DmtxVector2 *point, const DmtxRay2 *p0, const DmtxRay2 *p1){
    return dmtxRay2Intersect(point, p0, p1);
}

DmtxPassFail BQDdmtxPointAlongRay2(/*@out@*/ DmtxVector2 *point, const DmtxRay2 *r, double t){
    return dmtxPointAlongRay2(point, r, t);
}

void BQDdmtxMatrix3Copy(/*@out@*/ DmtxMatrix3 m0, DmtxMatrix3 m1){
    dmtxMatrix3Copy(m0, m1);
}

void BQDdmtxMatrix3Identity(/*@out@*/ DmtxMatrix3 m){
    dmtxMatrix3Identity(m);
}

void BQDdmtxMatrix3Translate(/*@out@*/ DmtxMatrix3 m, double tx, double ty){
    dmtxMatrix3Translate(m, tx, ty);
}

void BQDdmtxMatrix3Rotate(/*@out@*/ DmtxMatrix3 m, double angle){
    dmtxMatrix3Rotate(m, angle);
}

void BQDdmtxMatrix3Scale(/*@out@*/ DmtxMatrix3 m, double sx, double sy){
    dmtxMatrix3Scale(m, sx, sy);
}

void BQDdmtxMatrix3Shear(/*@out@*/ DmtxMatrix3 m, double shx, double shy){
    dmtxMatrix3Shear(m, shx, shy);
}

void BQDdmtxMatrix3LineSkewTop(/*@out@*/ DmtxMatrix3 m, double b0, double b1, double sz){
    dmtxMatrix3LineSkewTop(m, b0, b1, sz);
}

void BQDdmtxMatrix3LineSkewTopInv(/*@out@*/ DmtxMatrix3 m, double b0, double b1, double sz){
    dmtxMatrix3LineSkewTopInv(m, b0, b1, sz);
}

void BQDdmtxMatrix3LineSkewSide(/*@out@*/ DmtxMatrix3 m, double b0, double b1, double sz){
    dmtxMatrix3LineSkewSide(m, b0, b1, sz);
}

void BQDdmtxMatrix3LineSkewSideInv(/*@out@*/ DmtxMatrix3 m, double b0, double b1, double sz){
    dmtxMatrix3LineSkewSideInv(m, b0, b1, sz);
}

void BQDdmtxMatrix3Multiply(/*@out@*/ DmtxMatrix3 mOut, DmtxMatrix3 m0, DmtxMatrix3 m1){
    dmtxMatrix3Multiply(mOut, m0, m1);
}

void BQDdmtxMatrix3MultiplyBy(DmtxMatrix3 m0, DmtxMatrix3 m1){
    dmtxMatrix3MultiplyBy(m0, m1);
}

int BQDdmtxMatrix3VMultiply(/*@out@*/ DmtxVector2 *vOut, DmtxVector2 *vIn, DmtxMatrix3 m){
    return dmtxMatrix3VMultiply(vOut, vIn, m);
}

int BQDdmtxMatrix3VMultiplyBy(DmtxVector2 *v, DmtxMatrix3 m){
    return dmtxMatrix3VMultiplyBy(v, m);
}

void BQDdmtxMatrix3Print(DmtxMatrix3 m){
    dmtxMatrix3Print(m);
}

int BQDdmtxSymbolModuleStatus(DmtxMessage *mapping, int sizeIdx, int row, int col){
    return dmtxSymbolModuleStatus(mapping, sizeIdx, row, col);
}

int BQDdmtxGetSymbolAttribute(int attribute, int sizeIdx){
    return dmtxGetSymbolAttribute(attribute, sizeIdx);
}

int BQDdmtxGetBlockDataSize(int sizeIdx, int blockIdx){
    return dmtxGetBlockDataSize(sizeIdx, blockIdx);
}

int BQDgetSizeIdxFromSymbolDimension(int rows, int cols){
    return getSizeIdxFromSymbolDimension(rows, cols);
}

DmtxByteList BQDdmtxByteListBuild(DmtxByte *storage, int capacity){
    return dmtxByteListBuild(storage, capacity);
}

void BQDdmtxByteListInit(DmtxByteList *list, int length, DmtxByte value, DmtxPassFail *passFail){
    dmtxByteListInit(list, length, value, passFail);
}

void BQDdmtxByteListClear(DmtxByteList *list){
    dmtxByteListClear(list);
}

DmtxBoolean BQDdmtxByteListHasCapacity(DmtxByteList *list){
    return dmtxByteListHasCapacity(list);
}

void BQDdmtxByteListCopy(DmtxByteList *dst, const DmtxByteList *src, DmtxPassFail *passFail){
    dmtxByteListCopy(dst, src, passFail);
}

void BQDdmtxByteListPush(DmtxByteList *list, DmtxByte value, DmtxPassFail *passFail){
    dmtxByteListPush(list, value, passFail);
}

DmtxByte BQDdmtxByteListPop(DmtxByteList *list, DmtxPassFail *passFail){
    return dmtxByteListPop(list, passFail);
}

void BQDdmtxByteListPrint(DmtxByteList *list, char *prefix){
    dmtxByteListPrint(list, prefix);
}

char *BQDdmtxVersion(void){
    return dmtxVersion();
}

/*
 * QREncode functions
*/
QRinput *BQDQRinput_new(void){
    return QRinput_new();
}

QRinput *BQDQRinput_new2(int version, QRecLevel level){
    return QRinput_new2(version, level);
}

QRinput *BQDQRinput_newMQR(int version, QRecLevel level){
    return QRinput_newMQR(version, level);
}

int BQDQRinput_append(QRinput *input, QRencodeMode mode, int size, const unsigned char *data){
    return QRinput_append(input, mode, size, data);
}

int BQDQRinput_appendECIheader(QRinput *input, unsigned int ecinum){
    return QRinput_appendECIheader(input, ecinum);
}

int BQDQRinput_getVersion(QRinput *input){
    return QRinput_getVersion(input);
}

int BQDQRinput_setVersion(QRinput *input, int version){
    return QRinput_setVersion(input, version);
}

QRecLevel BQDQRinput_getErrorCorrectionLevel(QRinput *input){
    return QRinput_getErrorCorrectionLevel(input);
}

int BQDQRinput_setErrorCorrectionLevel(QRinput *input, QRecLevel level){
    return QRinput_setErrorCorrectionLevel(input, level);
}

int BQDQRinput_setVersionAndErrorCorrectionLevel(QRinput *input, int version, QRecLevel level){
    return QRinput_setVersionAndErrorCorrectionLevel(input, version, level);
}

void BQDQRinput_free(QRinput *input){
    QRinput_free(input);
}

int BQDQRinput_check(QRencodeMode mode, int size, const unsigned char *data){
    return QRinput_check(mode, size, data);
}

QRinput_Struct *BQDQRinput_Struct_new(void){
    return QRinput_Struct_new();
}

void BQDQRinput_Struct_setParity(QRinput_Struct *s, unsigned char parity){
    QRinput_Struct_setParity(s, parity);
}

int BQDQRinput_Struct_appendInput(QRinput_Struct *s, QRinput *input){
    return QRinput_Struct_appendInput(s, input);
}

void BQDQRinput_Struct_free(QRinput_Struct *s){
    QRinput_Struct_free(s);
}

QRinput_Struct *BQDQRinput_splitQRinputToStruct(QRinput *input){
    return QRinput_splitQRinputToStruct(input);
}

int BQDQRinput_Struct_insertStructuredAppendHeaders(QRinput_Struct *s){
    return QRinput_Struct_insertStructuredAppendHeaders(s);
}

int BQDQRinput_setFNC1First(QRinput *input){
    return QRinput_setFNC1First(input);
}

int BQDQRinput_setFNC1Second(QRinput *input, unsigned char appid){
    return QRinput_setFNC1Second(input, appid);
}

QRcode *BQDQRcode_encodeInput(QRinput *input) {
    return QRcode_encodeInput(input);
}

QRcode *BQDQRcode_encodeString(const char *string, int version, QRecLevel level, QRencodeMode hint, int casesensitive){
    return QRcode_encodeString(string, version, level, hint, casesensitive);
}

QRcode *BQDQRcode_encodeString8bit(const char *string, int version, QRecLevel level){
    return QRcode_encodeString8bit(string, version, level);
}

QRcode *BQDQRcode_encodeStringMQR(const char *string, int version, QRecLevel level, QRencodeMode hint, int casesensitive){
    return QRcode_encodeStringMQR(string, version, level, hint, casesensitive);
}

QRcode *BQDQRcode_encodeString8bitMQR(const char *string, int version, QRecLevel level){
    return QRcode_encodeString8bitMQR(string, version, level);
}

QRcode *BQDQRcode_encodeData(int size, const unsigned char *data, int version, QRecLevel level){
    return QRcode_encodeData(size, data, version, level);
}

QRcode *BQDQRcode_encodeDataMQR(int size, const unsigned char *data, int version, QRecLevel level){
    return QRcode_encodeDataMQR(size, data, version, level);
}

void BQDQRcode_free(QRcode *qrcode){
    QRcode_free(qrcode);
}

QRcode_List *BQDQRcode_encodeInputStructured(QRinput_Struct *s){
    return QRcode_encodeInputStructured(s);
}

QRcode_List *BQDQRcode_encodeStringStructured(const char *string, int version, QRecLevel level, QRencodeMode hint, int casesensitive){
    return QRcode_encodeStringStructured(string, version, level, hint, casesensitive);
}

QRcode_List *BQDQRcode_encodeString8bitStructured(const char *string, int version, QRecLevel level){
    return QRcode_encodeString8bitStructured(string, version, level);
}

QRcode_List *BQDQRcode_encodeDataStructured(int size, const unsigned char *data, int version, QRecLevel level){
    return QRcode_encodeDataStructured(size, data, version, level);
}

int BQDQRcode_List_size(QRcode_List *qrlist){
    return QRcode_List_size(qrlist);
}

void BQDQRcode_List_free(QRcode_List *qrlist){
    QRcode_List_free(qrlist);
}

void BQDQRcode_APIVersion(int *major_version, int *minor_version, int *micro_version){
    QRcode_APIVersion(major_version, minor_version, micro_version);
}

char *BQDQRcode_APIVersionString(void){
    return QRcode_APIVersionString();
}

void BQDQRcode_clearCache(void){
    return;
}