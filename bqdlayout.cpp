#include "bqdlayout.h"
#include <bqdcode.h>
#include <QFileDialog>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QThread>
#include <QApplication>
#include <QByteArray>
#include <QPointF>
#include <QColor>
#include <QFont>
#include <QRectF>
#include <QObject>
#include <QColor>
#include <QFont>
#include <QCoreApplication>
#include <QPointF>
#include <QRect>
#include <QPainter>
#include <QPrinter>
#include <QGuiApplication>
#include <QScreen>
#include <QDateTime>
#include <QDebug>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/daily_file_sink.h>


//Printer and screen dpi
typedef struct typeDPI{
    qreal printerdpiX ;
    qreal printerdpiY ;
    qreal screendpiX  ;
    qreal screendpiY  ;
}typeDPI;


//barcode type
/*
enum {
    BARCODE_ANY = 0,    // choose best-fit
    BARCODE_EAN,
    BARCODE_UPC,        // upc == 12-digit ean
    BARCODE_ISBN,       // isbn numbers (still EAN13)
    BARCODE_39,         // code 39
    BARCODE_128,        // code 128 (a,b,c: autoselection)
    BARCODE_128C,       // code 128 (compact form for digits)
    BARCODE_128B,       // code 128, full printable ascii
    BARCODE_I25,        // interleaved 2 of 5 (only digits)
    BARCODE_128RAW,     // Raw code 128 (by Leonid A. Broukhis)
    BARCODE_CBR,        // Codabar (by Leonid A. Broukhis)
    BARCODE_MSI,        // MSI (by Leonid A. Broukhis)
    BARCODE_PLS,        // Plessey (by Leonid A. Broukhis)
    BARCODE_93,         // code 93 (by Nathan D. Holmes)
    BARCODE_11,         // code 11 (USD-8)
    BARCODE_39EXT       // code 39 extended (by Ian Ward)
};
*/

//Barcode type
typedef struct typeBarCode{
    int             layer               = 0 ;                           //Layer location.
    QByteArray      str                 = "BQDCode";                    //Content to display in the barcode.
    bool            var                 = false ;                       //Whether it is a variable.
    QByteArray      varName             = "";                           //Variable name.
    QPointF         postion             = QPointF(0,0);                 //Barcode position.
    QColor          bColor              = QColor(255,255,255,0);        //Barcode background color, default is transparent.
    QColor          fColor              = QColor(0,0,0,255);            //Barcode foreground color, default is black.
    QFont           font                = QFont("Arial",12);            //Default font for barcode text.
    int             type                = BARCODE_128;                  //Default barcode type.
    bool            disPlayText         = true;                         //Default text to display for the barcode.
    double          argin               = 0;                            //The barcode default setting leaves no margin.
    double          widthScalef         = 30;                           //Barcode width, default is 30mm.
    double          height              = 80;                           //Barcode height, default is 80mm.
    double          angle               = 0 ;                           //Barcode rotation angle, default is 0 degrees.
}typeBarCode;

//DataMatrix
typedef struct typeDataMatrix{
    int             layer               = 0 ;                           //Layer location.
    QByteArray      str                 = "DataMatrix";                 //Content to display in the DataMatrix.
    bool            var                 = false ;                       //Whether it is a variable.
    QByteArray      varName             = "";                           //Variable name.
    QPointF         postion             = QPointF(0,0);                 //DataMatrix position.
    QColor          bColor              = QColor(255,255,255,0);        //DataMatrix background color, default is transparent.
    QColor          fColor              = QColor(0,0,0,255);            //DataMatrix foreground color, default is black.
    double          argin               = 0;                            //The DataMatrix default setting leaves no margin.
    double          scalef              = 10;                           //DataMatrix length and width, default is 10mm.
    double          angle               = 0 ;                           //DataMatrix rotation angle, default is 0 degrees.
}typeDataMatrix;

//QR code
typedef struct typeQRCode{
    int             layer               = 0 ;                           //Layer location.
    QByteArray      str                 = "QRCode";                     //Content to display in the QRCode.
    bool            var                 = false ;                       //Whether it is a variable.
    QByteArray      varName             = "";                           //Variable name.
    QPointF         postion             = QPointF(0,0);                 //QRCode position.
    QColor          bColor              = QColor(255,255,255,0) ;       //QRCode background color, default is transparent.
    QColor          fColor              = QColor(0,0,0,255) ;           //QRCode foreground color, default is black.
    int             QRVersion           = 2 ;                           //Symbol version.
    QRecLevel       QRlevel             = QR_ECLEVEL_Q ;                //Error correction level.
    QRencodeMode    QRhint              = QR_MODE_8 ;                   //Encoding mode.
    bool            CaseSensitive       = true ;                        //Whether case-sensitive.
    double          scalef              = 10;                           //QRCode length and width, default is 10mm.
    double          angle               = 0 ;                           //QRCode rotation angle, default is 0 degrees.
}typeQRCode;


//Character type.
typedef struct typeStringText{
    int             layer               = 0 ;                           //Layer location.
    QByteArray      str                 = "String";                     //Content to display in the Character.
    bool            var                 = false ;                       //Whether it is a variable.
    QByteArray      varName             = "";                           //Variable name.
    QPointF         postion             = QPointF(0,0);                 //Character position.
    QColor          bColor              = QColor(255,255,255,0);        //Character background color, default is transparent.
    QColor          fColor              = QColor(0,0,0,255);            //Character foreground color, default is black.
    QFont           font                = QFont("Arial",12);            //Default font for Character text.
    double          angle               = 0 ;                           //Character rotation angle, default is 0 degrees.
}typeStringText;


//Rectangle type.
typedef struct typeRectangle{
    int             layer               = 0 ;                           //Layer location.
    QPointF         postion             = QPointF(0,0);                 //Rectangle position.
    QRectF          rect                = QRectF(0,0,1,1);              //Rectangle parameters.
    QColor          bColor              = QColor(255,255,255,0);        //Rectangle background color, default is transparent.
    QColor          fColor              = QColor(0,0,0,255);            //Rectangle foreground color, default is black.
    double          penWidth            = 0.1;                          //Rectangle pen width.
    double          angle               = 0 ;
}typeRectangle;

//Rounded rectangle type.
typedef struct typeRoundedRect{
    int             layer               = 0 ;                           //Layer location.
    QPointF         postion             = QPointF(0,0);                 //Rounded rectangle position.
    QRectF          rect                = QRectF(0,0,1,1);              //Rounded rectangle parameters.
    double          xRadius             = 0 ;                           //X radius of the rounded corner.
    double          yRadius             = 0 ;                           //Y radius of the rounded corner.
    QColor          bColor              = QColor(255,255,255,0);        //Rounded rectangle background color, default is transparent.
    QColor          fColor              = QColor(0,0,0,255);            //Rounded rectangle foreground color, default is black.
    double          penWidth            = 0.1;                          //Rounded rectangle pen width.
    double          angle               = 0 ;
}typeRoundedRect;

//Circle type.
typedef struct typeEllipse{
    int             layer               = 0 ;                           //Layer location.
    QPointF         postion             = QPointF(0,0);                 //Circle position.
    double          width               = 0 ;                           //Circle width
    double          height              = 0 ;                           //Circle height
    QColor          bColor              = QColor(255,255,255,0);        //Circle background color, default is transparent.
    QColor          fColor              = QColor(0,0,0,255);            //Circle foreground color, default is black.
    double          penWidth            = 0.1;                          //Circle pen width.
    double          angle               = 0 ;
}typeEllipse;

//Line type.
typedef struct typeLine{
    int             layer               = 0 ;                           //Layer location.
    QPointF         spostion            = QPointF(0,0);                 //Line starting coordinates.
    QPointF         epostion            = QPointF(0,0);                 //Line ending coordinates.
    QColor          fColor              = QColor(0,0,0,255);            //Line rounded rectangle background color, default is transparent.
    double          penWidth            = 0.1;                          //Line pen width.
    double          angle               = 0 ;
}typeLine;

//log
std::shared_ptr<spdlog::logger> BQDlogger = spdlog::daily_logger_format_mt("BQDLayout","logs/BQDLayout_" + QDateTime::currentDateTime().toString("yyyy-MM-dd").toStdString() + ".txt",0,0);      //日志记录器

static QApplication * app = nullptr;        //GUI dependencies.
static void appnew(void);                   //Create GUI dependencies.
static void appdel(void);                   //Delete GUI dependencies.

//All variables to be printed.
static QByteArray &getPrintVal(){
    static QByteArray printval;
    return printval;
}

static bool ptest = false ;                 //Test print.
static bool getconfig(const char *dbfile, QPageSize &pagesize ,  QMarginsF &marginsf);  //Read printing parameters.
//dpi
typeDPI dpi = {0};
static bool dllcheck(void); //Check if BQDDLL exists.
//Barcode list
static QVector <typeBarCode> & getbarcode(){
    static QVector <typeBarCode> barCode ;
    return barCode;
}
static int miniwidthBarCode = 0;                 //Minimum barcode width.
static int miniheightBarCode = 0;                //Minimum barcode height.
static int currentwidthBarCode = 0;              //Actual barcode width.
static int currentheightBarCode = 0;             //Actual barcode height.
static bool updatesizeBarCode(typeBarCode barcode ,struct Barcode_Item * bc);                   //Update barcode dimensions.
static bool renderBarCode(typeBarCode barcode , QPainter &painter ,struct Barcode_Item * bc);   //Draw the entire barcode.
static bool drawBarBarCode(typeBarCode barcode ,QPainter &painter , struct Barcode_Item * bc);  //Draw the barcode section of the barcode.
static bool drawtextBarCode(typeBarCode barcode , QPainter &painter);                           //Draw the character section of the barcode.
static bool createBarCode(QPainter &painter ,const QMap<QString,QString> var);                  //Create a barcode.
static bool readBarcode(QString dbfile, int page);                                              //Read the barcode from a specified page.

//DataMatrix list
static QVector<typeDataMatrix> & getdatamatrix(){
    static QVector<typeDataMatrix> datamatrix;
    return datamatrix;
}
static int widthDataMatrix = 0;                         //DataMatrix width.
static int heightDataMatrix = 0;                        //DataMatrix height.
static bool createDataMatrix(QPainter &painter, const QMap<QString, QString> var);  //Create a DataMatrix code.
static bool readDataMatrix(QString dbfile, int page);                               //Read DataMatrix from a specified page.

//QR Code list
static QVector<typeQRCode> & getqrcode(){
    static QVector<typeQRCode> qrcode;
    return qrcode;
}
static bool createQRCode(QPainter &painter , const QMap<QString, QString> var);     //Create a QR code.
static bool readQRCode(QString dbfile, int page);                                   //Read QR code from a specified page.


//StringText list
static QVector<typeStringText> & getstringtext(){
    static QVector<typeStringText> stringtext;
    return stringtext;
}
static bool createStringText(QPainter &painter , const QMap<QString,QString> var);  //Create a character.
static bool readStringText(QString dbfile, int page);                               //Read character from a specified page.

//Rectangle list
static QVector<typeRectangle> & getrectangle(){
    static QVector<typeRectangle> rectangle;
    return rectangle;
}
static bool createRectangle(QPainter &painter);        //Create a rectangle.
static bool readRectangle(QString dbfile, int page);   //Read rectangle from a specified page.

//Rounded rectangle list
static QVector<typeRoundedRect> & getroundedrect(){
    static QVector<typeRoundedRect> roundedrect;
    return roundedrect;
}
static bool createRoundedRect(QPainter &painter);      //Create a rounded rectangle.
static bool readRoundedRect(QString dbfile, int page); //Read rounded rectangle from a specified page.

//Line list
static QVector<typeLine> & getline(){
    static QVector<typeLine> line;
    return line;
}
static bool createLine(QPainter &painter);             //Create a line.
static bool readLine(QString dbfile, int page);        //Read line from a specified page.

//Circle list
static QVector<typeEllipse> & getellipse(){
    static QVector<typeEllipse> ellipse;
    return ellipse;
}
static bool createEllipse(QPainter &painter);           //Create a circle
static bool readEllipse(QString dbfile, int page);      //Read circle from a specified page.

static void addlog(QByteArray log , const bool &err = false );  //Add a log.

/**
 * @brief getconfig     Read printing parameters.
 * @param dbfile        Printer configuration file.
 * @param pagesize      Page size.
 * @param marginsf      Margins.
 * @return bool         Whether successful.
 */
static bool getconfig(const char * dbfile ,QPageSize &pagesize ,  QMarginsF &marginsf){
    bool ok = false;
    QString dbname = "BQDCodeDB_" + QStringLiteral("0x%1").arg(quintptr(QThread::currentThreadId()), 0, 16, QLatin1Char('0'));
    QSqlDatabase db;
    if(QSqlDatabase::contains(dbname)){
        db = QSqlDatabase::database(dbname);
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE",dbname);
    }
    //addlog(QString("BQDLayout name is %1").arg(dbname).toUtf8(),true);
    db.setDatabaseName(dbfile);
    if(!db.open()){
        addlog(QString("The BQDLayout file failed to open due to the following reason:%1,file:%2").arg(db.lastError().text(),QString(dbfile)).toUtf8(),true);
        return false;
    }
    //addlog(QString("The BQDLayout file was opened successfully.%1").arg(dbfile).toUtf8());

    QSqlQuery query(db);
    QString cmd = QString("select pagewidth,pageheight,margleft,margtop,margright,margbottom "
                          "from config"
                          );
    if(!query.exec(cmd)){
        addlog(QString("Configuration query failed due to the following reason:%1").arg(query.lastError().text()).toUtf8(),true);
        ok = false ;
    }else{
        query.first();
        pagesize = QPageSize(QSizeF(query.value(0).toDouble(),query.value(1).toDouble()),QPageSize::Millimeter);
        marginsf = QMarginsF(query.value(2).toDouble(),query.value(3).toDouble(),query.value(4).toDouble(),query.value(5).toDouble());
        ok =true ;
    }
    if(db.isOpen()) db.close();
    return ok;
}

/**
 * @brief appnew Create GUI dependencies.
 */
static void appnew(void){
    if(app){
        addlog(QString("The GUI dependencies have already been created by BQDCode and do not need to be created again.").toUtf8());
        return;
    }
    if(QApplication::instance() == nullptr){
        addlog(QString("GUI dependencies not found. Creating dependencies.").toUtf8());
        int argc = 0 ;
        app = new QApplication(argc,nullptr);
    }
    else {
        addlog(QString("GUI dependencies already exist. No need to create them.").toUtf8());
    }
}

static void appdel(void){
    return ;        //Cannot delete the GUI instance, return directly.
}

/**
 * @brief dllcheck  Check if BQDDLL exists.
 * @return bool     Whether it exists.
 */
static bool dllcheck(void){
    QDir dir(QCoreApplication::applicationDirPath());  // Get the current working directory of the program.
    QString fileName = "BQDCode.dll";
    QFile file(dir.filePath(fileName));
    bool Ndll = false ;
    Ndll = file.exists();
    if(!Ndll){
        addlog(dir.path().toUtf8());
        return false;
    }
    return true;
}

/**
 * @brief updatesizeBarCode     Update barcode dimensions.
 * @param barcode               Generate the data for the barcode.
 * @param bc                    Store the data after generating the barcode.
 * @return bool                 Was it successful.
 */
static bool updatesizeBarCode(typeBarCode barcode ,struct Barcode_Item * bc){
    if( !bc ) return false;

    if ( !bc->partial || !bc->textinfo )
    {
        bc->error = EINVAL;
        return false;
    }
    /* First, calculate barlen */
    int barlen = bc->partial[0] - '0';
    for (char * ptr = bc->partial + 1; *ptr; ptr++)
    {
        if ( isdigit(*ptr) )
        {
            barlen += (*ptr - '0');
        }
        else if ( islower(*ptr) )
        {
            barlen += (*ptr - 'a' + 1);
        }
    }


    /* The scale factor depends on bar length */
    if ( (fabs(bc->scalef) < 1e-6) )
    {
        if ( !bc->width )
        {
            bc->width = barlen  ; /* default */
        }
        bc->scalef = (double) bc->width / (double)barlen;

        //qDebug() << "fabs(bc->scalef) < 1e-6 , bc->width = " << bc->width << "bc->scalef = " << bc->scalef;
    }

    /* The width defaults to "just enough" */
    if ( !bc->width )
    {
        bc->width = barlen  * bc->scalef + 1;
    }

    /* But it can be too small, in this case enlarge and center the area */
    if (bc->width < barlen  * bc->scalef)
    {
        int wid = barlen  * bc->scalef + 1;
        bc->xoff -= (wid - bc->width) / 2 ;
        bc->width = wid;
        /* Can't extend too far on the left */
        if (bc->xoff < 0)
        {
            bc->width += -bc->xoff;
            bc->xoff = 0;
        }
    }

    /* The height defaults to 80 points (rescaled) */
    if ( !bc->height )
    {
        bc->height = 80 * bc->scalef;
    }

    /* If too small (5 + text), reduce the scale factor and center */
    int i = 5 + 10 * (( bc->flags & BARCODE_NO_ASCII) == 0 );
    if (bc->height < i * bc->scalef )
    {
        double scaleg = ((double) bc->height) / i;
        int wid = bc->width * scaleg / bc->scalef;
        bc->xoff += ( bc->width - wid ) / 2;
        bc->width = wid;
        bc->scalef = scaleg;
    }
    // int  m_margin = bc->margin;
    // qDebug() << "margin:" << m_margin;
    //  qDebug() << "bcwidht:" << bc->width;

    miniwidthBarCode  = bc->xoff + bc->width  + 2 * bc->margin;
    miniheightBarCode = bc->yoff + bc->height + 2 * bc->margin;
    //  qDebug() << "width:" << miniwidthBarCode << ",height:" << miniheightBarCode;

    //    currentwidthBarCode = barcode.widthScalef  * miniwidthBarCode;
    currentwidthBarCode = barcode.widthScalef;      //The current width requirement equals the set width.
    currentheightBarCode = miniheightBarCode ;

    //  qDebug() << "width:" << currentwidthBarCode << ",height:" << currentheightBarCode;

    return true;
}

/**
 * @brief renderBarCode     Draw the entire barcode.
 * @param barcode           Generate the data for the barcode.
 * @param painter           Drawing object.
 * @param bc                Store the data after generating the barcode.
 * @return bool             Was it successful.
 */
static bool renderBarCode(typeBarCode barcode , QPainter &painter ,struct Barcode_Item * bc){
    if( !bc ) return false;

    painter.translate(barcode.postion);     //Set the origin.
    painter.rotate(barcode.angle);          //Set the angle.

    int w = (bc->width + 2 * bc->margin) ;
    int h = (bc->height + 2 * bc->margin);
    painter.setBrush(barcode.bColor);
    painter.setPen(Qt::NoPen);
    painter.drawRect(QRect(0, 0, w, h));
    if ( !bc->partial || !bc->textinfo )
    {
        bc->error = EINVAL;
        return false;
    }
    if(!drawBarBarCode(barcode,painter,bc)){
        return false;
    }

    //    qDebug() << "bc->flags & BARCODE_NO_ASCII = " <<( bc->flags & BARCODE_NO_ASCII);
    if((bc->flags & BARCODE_NO_ASCII) )
    {
        drawtextBarCode(barcode,painter);
    }

    painter.translate(QPointF(0,0) - barcode.postion);     //Return to the origin before drawing.
    painter.rotate( 0);          //Restore the angle.
    return true;
}

/**
 * @brief drawBarBarCode    Draw the barcode section of the barcode.
 * @param barcode           Generate the data for the barcode.
 * @param painter           Drawing object.
 * @param bc                Store the data after generating the barcode.
 * @return bool             Was it successful.
 */
static bool drawBarBarCode(typeBarCode barcode ,QPainter &painter , struct Barcode_Item * bc){
    int mode = '-';
    int i; /* text below bars */
    char * ptr;
    double xpos = bc->margin + (bc->partial[0] - '0') * bc->scalef;
    for (ptr = bc->partial + 1, i = 1; *ptr; ptr++, i++)
    {
        /* special cases: '+' and '-' */
        if (*ptr == '+' || *ptr == '-')
        {
            mode = *ptr; /* don't count it */
            i++;
            continue;
        }
        /* j is the width of this bar/space */
        int j;
        if (isdigit (*ptr))   j = *ptr - '0';
        else                  j = *ptr - 'a' + 1;

        double x0, y0, yr;
        if (i % 2) /* bar */
        {

            //qDebug() << "bc->xoff = " << bc->xoff << ", xpos = " << xpos;
            x0 = bc->xoff + xpos;// + (j * scalef) / 2;
            y0 = bc->yoff + bc->margin;
            yr = bc->height;
            if ((bc->flags & BARCODE_NO_ASCII) )
            { /* leave space for text */
                if (mode == '-')
                {
                    /* text below bars: 10 points or five points */
                    //y0 += (isdigit(*ptr) ? 10 : 5) * scalef;
                    QFontMetrics metrics(barcode.font);     //Get the symbol width for setting coordinates.
                    int mH = metrics.height();              //Get the character height.
                    yr -= mH - 2 ;
                    // yr -= (isdigit(*ptr) ? 10 : 5) * bc->scalef;
                }
                else
                { /* '+' */
                    /* text above bars: 10 or 0 from bottom, and 10 from top */
                    y0 += (isdigit(*ptr) ? 10 : 0) * bc->scalef;
                    yr -= (isdigit(*ptr) ? 20 : 10) * bc->scalef;
                }
            }
            painter.fillRect(QRect(x0, y0, (j * bc->scalef), yr ), barcode.fColor);
            //    qDebug() << "fillRect: " <<  QRect(x0, y0, (j * bc->scalef), yr );
        }
        xpos += j * bc->scalef;
    }
    return true;
}

/**
 * @brief drawtextBarCode   Draw the character section of the barcode.
 * @param barcode           Generate the data for the barcode.
 * @param painter           Drawing object.
 * @return bool             Was it successful.
 */
static bool drawtextBarCode(typeBarCode barcode , QPainter &painter){
    painter.save();
    QFontMetrics metrics(barcode.font);    //Get the symbol width for setting coordinates.
    int mW = metrics.horizontalAdvance(barcode.str) * (dpi.printerdpiX / dpi.screendpiX);   //Calculate the character width.
    int mH = metrics.capHeight() * (dpi.printerdpiY / dpi.screendpiY);                      //Calculate the character height.

    painter.setBrush(barcode.bColor);
    painter.setPen(Qt::NoPen);
    painter.drawRect(QRect((currentwidthBarCode - mW)/2, currentheightBarCode, mW, mH));

    painter.setPen(barcode.fColor);
    painter.setFont(barcode.font);
    painter.drawText((currentwidthBarCode - mW)/2  ,currentheightBarCode + mH,barcode.str);
    painter.restore();
    return true;
}

/**
 * @brief createBarCode     Create a barcode.
 * @param painter           Drawing object.
 * @param var               Variable.
 * @return bool             Was it successful.
 */
static bool createBarCode(QPainter &painter, const QMap<QString, QString> var){
    for (auto & _barcode:getbarcode()) {
        if(!ptest){
            if(_barcode.var){
                QString tmp = var.value(_barcode.varName);
                addlog(QString("Barcode variable found. Variable name: %1, Variable value: %2").arg(_barcode.varName,tmp).toUtf8());
                _barcode.str = (tmp == "")?QString("ErrNoVar").toUtf8():tmp.toUtf8();
            }
        }
        struct Barcode_Item * bc = nullptr;
        bc = BQDBarcode_Create(const_cast<char *>(_barcode.str.data()));  //Create a barcode
        if( !bc ) return false;
        int flags = 0 ;
        if(_barcode.disPlayText){
            flags |= _barcode.type;
            flags |= BARCODE_NO_ASCII ;
        }else{
            flags |= _barcode.type;
        }

        bc->flags = flags;
        bc->height = _barcode.height;
        bc->margin = _barcode.argin;

        BQDBarcode_Encode(bc,flags);            //Create barcode data
        if(updatesizeBarCode(_barcode,bc)){

            qreal width_scale = currentwidthBarCode / bc->width ;      //Calculate the width ratio.

            currentwidthBarCode = bc->width * width_scale ;            //Recalibrate the width.
            addlog(QString("Barcode: %1, Actual width: %2 MM").arg(_barcode.str,QString::number(currentwidthBarCode / dpi.printerdpiX * 25.4)).toUtf8());

            bc->width = bc->width * width_scale;
            bc->scalef = width_scale;
            bc->height = _barcode.height;

            if(renderBarCode(_barcode,painter,bc)){
            }
        }
        BQDBarcode_Delete(bc);
    }
    return true;
}

/**
 * @brief readBarcode   Read the barcode from a specified page.
 * @param dbfile        Printer configuration file.
 * @param page          Page.
 * @return bool         Was it successful.
 */
static bool readBarcode(QString dbfile, int page){
    //Configure the database.
    QString dbname = "BQDCodeDB_" + QStringLiteral("0x%1").arg(quintptr(QThread::currentThreadId()), 0, 16, QLatin1Char('0'));
    QSqlDatabase db;
    if(QSqlDatabase::contains(dbname)){
        db = QSqlDatabase::database(dbname);
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE",dbname);
    }
    //addlog(QString("BQDLayout name is %1").arg(dbname).toUtf8(),true);
    db.setDatabaseName(dbfile);   //Set the database name.
    if(!db.open()){
        addlog(QString("The BQDLayout file failed to open due to: %1").arg(db.lastError().text()).toUtf8(),true);
        return false;
    }
    //addlog(QString("The BQDLayout file was opened successfully.%1").arg(dbfile).toUtf8());

    QSqlQuery query(db);

    QString cmd = QString("select layer,str,var,varName,posX,posY,bColor,fColor,fontName,fontSize,fontWeight,fontItalic,type,disPlayText,argin,widthScalef,height,angle "
                          "from BarCode "
                          "where page = %1 "
                          "order by layer ASC;"
                          ).arg(page);

    if(!query.exec(cmd)){
        addlog(QString("Barcode query failed due to: %1").arg(query.lastError().text()).toUtf8(),true);
        if(db.isOpen()) db.close();
        return false ;
    }else{
        getbarcode().clear();        //Clear the barcode data.
        int error = 0 ;
        while (query.next()) {
            ++error;
            QStringList bbColor = query.value(6).toString().split(",");
            QStringList ffColor = query.value(7).toString().split(",");

            QVector<QString> vbbColor , vffColor;
            if(bbColor.count() != 4){
                vbbColor.append("255");vbbColor.append("255");vbbColor.append("255");vbbColor.append("0");
            }else{
                vbbColor.append(bbColor.at(0));vbbColor.append(bbColor.at(1));vbbColor.append(bbColor.at(2));vbbColor.append(bbColor.at(3));
            }
            if(ffColor.count() != 4){
                vffColor.append("0");vffColor.append("0");vffColor.append("0");vffColor.append("255");
            }else{
                vffColor.append(ffColor.at(0));vffColor.append(ffColor.at(1));vffColor.append(ffColor.at(2));vffColor.append(ffColor.at(3));
            }
            typeBarCode tmp;
            tmp.layer = query.value(0).toInt();
            tmp.str = query.value(1).toString().toUtf8();
            tmp.var = query.value(2).toBool();
            tmp.varName = query.value(3).toString().toUtf8();
            tmp.postion = QPointF(query.value(4).toDouble() * dpi.printerdpiX / 25.4 ,query.value(5).toDouble()* dpi.printerdpiY / 25.4);
            tmp.bColor  = QColor(vbbColor.at(0).toInt(),vbbColor.at(1).toInt(),vbbColor.at(2).toInt(),vbbColor.at(3).toInt());
            tmp.fColor = QColor(vffColor.at(0).toInt(),vffColor.at(1).toInt(),vffColor.at(2).toInt(),vffColor.at(3).toInt());
            tmp.font = QFont(query.value(8).toString(),query.value(9).toInt(),query.value(10).toInt(),query.value(11).toBool());
            tmp.type = query.value(12).toInt();
            tmp.disPlayText = query.value(13).toBool();
            tmp.argin = (dpi.printerdpiX > dpi.printerdpiY) ? query.value(14).toDouble() * dpi.printerdpiX / 25.4 : query.value(14).toDouble() * dpi.printerdpiY / 25.4;
            tmp.widthScalef = query.value(15).toDouble() * dpi.printerdpiX / 25.4;
            tmp.height = query.value(16).toDouble() * dpi.printerdpiY / 25.4;
            tmp.angle = query.value(17).toDouble();
            getbarcode().append(tmp);
            //    qDebug() << tmp.layer << QString(tmp.str) << tmp.var << QString(tmp.varName) << tmp.postion << tmp.bColor << tmp.fColor
            //             << tmp.font << tmp.type << tmp.disPlayText
            //             << tmp.argin << tmp.widthScalef << tmp.height << tmp.angle;
        }
        if(error == 0){
            return false;
        }
    }
    if(db.isOpen()) db.close();
    return true ;
}

/**
 * @brief createDataMatrix      Create a DataMatrix code.
 * @param painter               Drawing object.
 * @param var                   Variable.
 * @return bool                 Was it successful.
 */
static bool createDataMatrix(QPainter &painter , const QMap<QString,QString> var){
    for (auto & _datamatrix: getdatamatrix()) {
        if(!ptest){
            if(_datamatrix.var){
                QString tmp = var.value(_datamatrix.varName);
                addlog(QString("DataMatrix variable found. Variable name: %1, Variable value: %2").arg(_datamatrix.varName,tmp).toUtf8());
                _datamatrix.str = (tmp == "")?QString("Err:%1").arg(_datamatrix.varName.data()).toUtf8():tmp.toUtf8();
            }
        }
        DmtxEncode * m_enc = nullptr;
        m_enc = BQDdmtxEncodeCreate();
        assert(m_enc != NULL);



        m_enc->sizeIdxRequest = DmtxSymbolSquareAuto;   //Default settings.
        m_enc->moduleSize = 1;
        m_enc->marginSize = _datamatrix.argin;

        BQDdmtxEncodeSetProp(m_enc, DmtxPropBytesPerPixel, 1);
    //    int ret =
        BQDdmtxEncodeDataMatrix(m_enc,_datamatrix.str.length(),(unsigned char *)(_datamatrix.str.data()));
    //    assert(ret == 1);

        widthDataMatrix = BQDdmtxImageGetProp(m_enc->image, DmtxPropWidth);      //DataMatrix width
        heightDataMatrix = BQDdmtxImageGetProp(m_enc->image, DmtxPropHeight);    //DataMatrix height

        //Calculate the ratio.
        qreal scale_x = _datamatrix.scalef / widthDataMatrix;       //Width ratio.
        qreal scale_y = _datamatrix.scalef / heightDataMatrix;      //Height ratio.

        painter.translate(_datamatrix.postion);
        painter.setBrush(_datamatrix.bColor);
        painter.setPen(Qt::NoPen);
        painter.drawRect(0, 0, widthDataMatrix,heightDataMatrix);   //Draw the background color.
        painter.setBrush(_datamatrix.fColor);                       //Set the foreground color.


        const double offset_x = 0;
        const double offset_y = 0;

        int rowSizeBytes = m_enc->image->rowSizeBytes;
        int bytesPerPixel = m_enc->image->bytesPerPixel;
        for( int y = 0; y < heightDataMatrix; y ++)
        {
            for(int x = 0; x < widthDataMatrix; x ++)
            {
                unsigned char b = m_enc->image->pxl[y * rowSizeBytes  + x * bytesPerPixel];
                if(b == 0)
                {
                    QRectF r(offset_x + x * scale_x, offset_y + y * scale_y, scale_x, scale_y);
                    painter.drawRect(r);
                }
            }
        }
        BQDdmtxEncodeDestroy(&m_enc);
        painter.translate(QPointF(0,0) - _datamatrix.postion);
    }
    return true;
}

/**
 * @brief readDataMatrix        Read DataMatrix from a specified page.
 * @param dbfile                Printer configuration file.
 * @param page                  Page.
 * @return bool                 Was it successful.
 */
static bool readDataMatrix(QString dbfile, int page){

    //Configure the database.
    QString dbname = "BQDCodeDB_" + QStringLiteral("0x%1").arg(quintptr(QThread::currentThreadId()), 0, 16, QLatin1Char('0'));
    QSqlDatabase db;
    if(QSqlDatabase::contains(dbname)){
        db = QSqlDatabase::database(dbname);
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE",dbname);
    }
    //addlog(QString("BQDLayout name is %1").arg(dbname).toUtf8(),true);
    db.setDatabaseName(dbfile);   //Set the database name.
    if(!db.open()){
        addlog(QString("The BQDLayout file failed to open due to: %1").arg(db.lastError().text()).toUtf8(),true);
        return false;
    }
    //addlog(QString("The BQDLayout file was opened successfully.").arg(dbfile).toUtf8());

    QSqlQuery query(db);
    QString cmd = QString("select layer,str,var,varName,posX,posY,bColor,fColor,argin,scalef,angle "
                          "from DataMatrix "
                          "where page = %1 "
                          "order by layer ASC;"
                          ).arg(page);

    if(!query.exec(cmd)){
        addlog(QString("DataMatrix query failed due to: %1").arg(query.lastError().text()).toUtf8(),true);
        if(db.isOpen()) db.close();
        return false ;
    }else{
        getdatamatrix().clear();        //Clear the DataMatrix data.
        int error = 0 ;
        while (query.next()) {
            ++error;
            QStringList bbColor = query.value(6).toString().split(",");
            QStringList ffColor = query.value(7).toString().split(",");

            QVector<QString> vbbColor , vffColor;
            if(bbColor.count() != 4){
                vbbColor.append("255");vbbColor.append("255");vbbColor.append("255");vbbColor.append("0");
            }else{
                vbbColor.append(bbColor.at(0));vbbColor.append(bbColor.at(1));vbbColor.append(bbColor.at(2));vbbColor.append(bbColor.at(3));
            }
            if(ffColor.count() != 4){
                vffColor.append("0");vffColor.append("0");vffColor.append("0");vffColor.append("255");
            }else{
                vffColor.append(ffColor.at(0));vffColor.append(ffColor.at(1));vffColor.append(ffColor.at(2));vffColor.append(ffColor.at(3));
            }

            typeDataMatrix tmp;
            tmp.layer = query.value(0).toInt();
            tmp.str = query.value(1).toString().toUtf8();
            tmp.var = query.value(2).toBool();
            tmp.varName = query.value(3).toString().toUtf8();
            tmp.postion = QPointF(query.value(4).toDouble() * dpi.printerdpiX / 25.4 ,query.value(5).toDouble()* dpi.printerdpiY / 25.4);
            tmp.bColor  = QColor(vbbColor.at(0).toInt(),vbbColor.at(1).toInt(),vbbColor.at(2).toInt(),vbbColor.at(3).toInt());
            tmp.fColor = QColor(vffColor.at(0).toInt(),vffColor.at(1).toInt(),vffColor.at(2).toInt(),vffColor.at(3).toInt());
            tmp.argin = (dpi.printerdpiX > dpi.printerdpiY) ? query.value(8).toDouble() * dpi.printerdpiX / 25.4 : query.value(8).toDouble() * dpi.printerdpiY / 25.4;
            tmp.scalef = (dpi.printerdpiX > dpi.printerdpiY) ? query.value(9).toDouble() * dpi.printerdpiX / 25.4 : query.value(9).toDouble() * dpi.printerdpiY / 25.4;
            tmp.angle = query.value(10).toDouble();
            getdatamatrix().append(tmp);

        }
        if(error == 0){
            return false;
        }
    }
    if(db.isOpen()) db.close();
    return true;
}

/**
 * @brief createQRCode      Create a QR code.
 * @param painter           Drawing object.
 * @param var               Variable.
 * @return bool             Was it successful.
 */
static bool createQRCode(QPainter &painter , const QMap<QString,QString> var){
    for (auto & _qrcode: getqrcode()) {
        if(!ptest){
            if(_qrcode.var){
                QString tmp = var.value(_qrcode.varName);
                addlog(QString("QR variable found. Variable name: %1, Variable value: %2").arg(_qrcode.varName,tmp).toUtf8());
                _qrcode.str = (tmp == "")?QString("Err:%1").arg(_qrcode.varName.data()).toUtf8():tmp.toUtf8();
            }
        }
        QRcode * qrcodedata = nullptr;
        qrcodedata = BQDQRcode_encodeString(_qrcode.str.data(), _qrcode.QRVersion, _qrcode.QRlevel, _qrcode.QRhint, _qrcode.CaseSensitive);

        qint32 qrcode_width = qrcodedata->width > 0 ? qrcodedata->width : 1;
        //double scale_x = (double)width2D / (double)qrcode_width;      //Scaling ratio of the QR code image.
        //double scale_y =(double) height2D /(double) qrcode_width;
        double scale_x = _qrcode.scalef / qrcode_width;
        double scale_y = _qrcode.scalef / qrcode_width;

        painter.translate(_qrcode.postion);

        painter.setBrush(_qrcode.bColor);         //Set the background color.
        painter.setPen(Qt::NoPen);
        painter.drawRect(0,0,scale_x * qrcode_width,scale_y * qrcode_width); //Draw a background color.
        painter.setBrush(_qrcode.fColor);

        unsigned char * pqrdata = qrcodedata->data;

        for(qint32 y = 0; y < qrcode_width; ++y) {
            for(qint32 x = 0; x < qrcode_width; ++x) {
                if((*pqrdata++) &0x01) {
                    QRectF r(x*scale_x, y*scale_y, scale_x, scale_y);
                    painter.drawRects(&r, 1);
                }
            }
        }

        BQDQRcode_free(qrcodedata);
        painter.translate(QPointF(0,0) - _qrcode.postion);
    }
    return true;
}

/**
 * @brief readQRCode    Read QR code from a specified page.
 * @param dbfile        Printer configuration file.
 * @param page          Page.
 * @return bool         Was it successful.
 */
static bool readQRCode(QString dbfile, int page){
    //Configure the database.
    QString dbname = "BQDCodeDB_" + QStringLiteral("0x%1").arg(quintptr(QThread::currentThreadId()), 0, 16, QLatin1Char('0'));
    QSqlDatabase db;
    if(QSqlDatabase::contains(dbname)){
        db = QSqlDatabase::database(dbname);
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE",dbname);
    }
    //addlog(QString("BQDLayout name is %1").arg(dbname).toUtf8());
    db.setDatabaseName(dbfile);   //Set the database name.
    if(!db.open()){
        addlog(QString("The BQDLayout file failed to open due to: %1").arg(db.lastError().text()).toUtf8(),true);
        return false;
    }
    //addlog(QString("The BQDLayout file opened successfully: %1").arg(dbfile).toUtf8());

    QSqlQuery query(db);
    QString cmd = QString("select layer,str,var,varName,posX,posY,bColor,fColor,QRVersion,QRlevel,QRhint,CaseSensitive,scalef,angle "
                          "from QRCode "
                          "where page = %1 "
                          "order by layer ASC;"
                          ).arg(page);

    if(!query.exec(cmd)){
        addlog(QString("QR query failed due to: %1").arg(query.lastError().text()).toUtf8(),true);
        if(db.isOpen()) db.close();
        return false ;
    }else{
        getqrcode().clear();        //Clear the QR code data.
        int error = 0 ;
        while (query.next()) {
            ++error;
            QStringList bbColor = query.value(6).toString().split(",");
            QStringList ffColor = query.value(7).toString().split(",");

            QVector<QString> vbbColor , vffColor;
            if(bbColor.count() != 4){
                vbbColor.append("255");vbbColor.append("255");vbbColor.append("255");vbbColor.append("0");
            }else{
                vbbColor.append(bbColor.at(0));vbbColor.append(bbColor.at(1));vbbColor.append(bbColor.at(2));vbbColor.append(bbColor.at(3));
            }
            if(ffColor.count() != 4){
                vffColor.append("0");vffColor.append("0");vffColor.append("0");vffColor.append("255");
            }else{
                vffColor.append(ffColor.at(0));vffColor.append(ffColor.at(1));vffColor.append(ffColor.at(2));vffColor.append(ffColor.at(3));
            }

            typeQRCode tmp;
            tmp.layer = query.value(0).toInt();
            tmp.str = query.value(1).toString().toUtf8();
            tmp.var = query.value(2).toBool();
            tmp.varName = query.value(3).toString().toUtf8();
            tmp.postion = QPointF(query.value(4).toDouble() * dpi.printerdpiX / 25.4 ,query.value(5).toDouble()* dpi.printerdpiY / 25.4);
            tmp.bColor  = QColor(vbbColor.at(0).toInt(),vbbColor.at(1).toInt(),vbbColor.at(2).toInt(),vbbColor.at(3).toInt());
            tmp.fColor = QColor(vffColor.at(0).toInt(),vffColor.at(1).toInt(),vffColor.at(2).toInt(),vffColor.at(3).toInt());
            tmp.QRVersion = query.value(8).toInt();
            tmp.QRlevel = static_cast<QRecLevel>(query.value(9).toInt());
            tmp.QRhint = static_cast<QRencodeMode>(query.value(10).toInt());
            tmp.CaseSensitive = query.value(11).toBool();
            tmp.scalef = (dpi.printerdpiX > dpi.printerdpiY) ? query.value(12).toDouble() * dpi.printerdpiX / 25.4 : query.value(12).toDouble() * dpi.printerdpiY / 25.4;
            tmp.angle = query.value(13).toDouble();
            getqrcode().append(tmp);
        }
        if(error == 0){
            return false;
        }
    }
    if(db.isOpen()) db.close();
    return true;
}

/**
 * @brief createStringText      Create a character.
 * @param painter               Drawing object.
 * @param var                   Variable.
 * @return bool                 Was it successful.
 */
static bool createStringText(QPainter &painter , const QMap<QString,QString> var){
    for (auto & _stringtext: getstringtext()) {
        if(!ptest){
            if(_stringtext.var){
                QString tmp = var.value(_stringtext.varName);
                addlog(QString("Character variable found. Variable name: %1, Variable value: %2").arg(_stringtext.varName,tmp).toUtf8());
                _stringtext.str = (tmp == "")?QString("Err:%1").arg(_stringtext.varName.data()).toUtf8():tmp.toUtf8();
            }
        }
        painter.translate(_stringtext.postion);     //Set the origin.
        painter.rotate(_stringtext.angle);          //Set the angle.
        painter.save();


        QFontMetrics metrics(_stringtext.font);    //Get the symbol width for setting coordinates.
        int mW = metrics.horizontalAdvance(_stringtext.str)  * (dpi.printerdpiX / dpi.screendpiX);  //Character width.
        int mH = metrics.capHeight() * (dpi.printerdpiY / dpi.screendpiY);                          //Character height.

        QBrush brush(_stringtext.bColor);

        painter.setBrush(brush);
        painter.setPen(Qt::NoPen);
        painter.drawRect(0,0,mW ,mH);         //Draw the background color.

        painter.setPen(_stringtext.fColor);
        painter.setFont(_stringtext.font);
        painter.drawText(0,mH ,_stringtext.str);

        painter.restore();
        painter.translate(QPointF(0,0) - _stringtext.postion);     //Return to the origin before drawing.
    }
    return true;
}

/**
 * @brief readStringText    Read character from a specified page.
 * @param dbfile            Printer configuration file.
 * @param page              Page.
 * @return bool             Was it successful.
 */
static bool readStringText(QString dbfile, int page){
    //Configure the database.
    QString dbname = "BQDCodeDB_" + QStringLiteral("0x%1").arg(quintptr(QThread::currentThreadId()), 0, 16, QLatin1Char('0'));
    QSqlDatabase db;
    if(QSqlDatabase::contains(dbname)){
        db = QSqlDatabase::database(dbname);
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE",dbname);
    }
    //addlog(QString("BQDLayout name is %1").arg(dbname).toUtf8());
    db.setDatabaseName(dbfile);   //Set the database name.
    if(!db.open()){
        addlog(QString("The BQDLayout file failed to open due to: %1").arg(db.lastError().text()).toUtf8(),true);
        return false;
    }
    //addlog(QString("The BQDLayout file opened successfully: %1").arg(dbfile).toUtf8());

    QSqlQuery query(db);
    QString cmd = QString("select layer,str,var,varName,posX,posY,bColor,fColor,fontName,fontSize,fontWeight,fontItalic,angle "
                          "from StringText "
                          "where page = %1 "
                          "order by layer ASC;"
                          ).arg(page);
    if(!query.exec(cmd)){
        addlog(QString("Character query failed due to: %1").arg(query.lastError().text()).toUtf8(),true);
        if(db.isOpen()) db.close();
        return false ;
    }else{
        getstringtext().clear();
        int error = 0 ;
        while (query.next()) {
            ++error;
            QStringList bbColor = query.value(6).toString().split(",");
            QStringList ffColor = query.value(7).toString().split(",");

            QVector<QString> vbbColor , vffColor;
            if(bbColor.count() != 4){
                vbbColor.append("255");vbbColor.append("255");vbbColor.append("255");vbbColor.append("0");
            }else{
                vbbColor.append(bbColor.at(0));vbbColor.append(bbColor.at(1));vbbColor.append(bbColor.at(2));vbbColor.append(bbColor.at(3));
            }
            if(ffColor.count() != 4){
                vffColor.append("0");vffColor.append("0");vffColor.append("0");vffColor.append("255");
            }else{
                vffColor.append(ffColor.at(0));vffColor.append(ffColor.at(1));vffColor.append(ffColor.at(2));vffColor.append(ffColor.at(3));
            }

            typeStringText tmp;
            tmp.layer      = query.value(0).toInt();
            tmp.str        = query.value(1).toString().toUtf8();
            tmp.var        = query.value(2).toBool();
            tmp.varName    = query.value(3).toString().toUtf8();
            tmp.postion    = QPointF(query.value(4).toDouble() * dpi.printerdpiX / 25.4 ,query.value(5).toDouble()* dpi.printerdpiY / 25.4);
            tmp.bColor     = QColor(vbbColor.at(0).toInt(),vbbColor.at(1).toInt(),vbbColor.at(2).toInt(),vbbColor.at(3).toInt());
            tmp.fColor     = QColor(vffColor.at(0).toInt(),vffColor.at(1).toInt(),vffColor.at(2).toInt(),vffColor.at(3).toInt());
            tmp.font       = QFont(query.value(8).toString(),query.value(9).toInt(),query.value(10).toInt(),query.value(11).toBool());
            tmp.angle      = query.value(12).toDouble();

            getstringtext().append(tmp);
        //    qDebug() << "Counter:" << error << "page:" << page ;
            //qDebug() << tmp.layer << tmp.str << tmp.var << tmp.varName << tmp.postion << tmp.bColor << tmp.fColor << tmp.font << tmp.angle;
        }
        if(error == 0){
            return false;
        }
    }
    if(db.isOpen()) db.close();
    return true;
}

/**
 * @brief createRectangle   Create a rectangle.
 * @param painter           Drawing object.
 * @return bool             Was it successful.
 */
static bool createRectangle(QPainter &painter ){
    foreach (auto const _rectangle, getrectangle()) {
        painter.translate(_rectangle.postion);
        painter.rotate(_rectangle.angle);
        painter.save();
        painter.setBrush(_rectangle.bColor);
        QPen pen(_rectangle.fColor);
        pen.setWidth(_rectangle.penWidth);
        painter.setPen(pen);
        painter.drawRect(_rectangle.rect);
        painter.restore();
        painter.translate(QPointF(0,0) - _rectangle.postion);     //Return to the origin before drawing.
    }
    return true;
}

/**
 * @brief readRectangle     Read rectangle from a specified page.
 * @param dbfile            Printer configuration file.
 * @param page              Page.
 * @return bool             Was it successful.
 */
static bool readRectangle(QString dbfile, int page){
    //Configure the database.
    QString dbname = "BQDCodeDB_" + QStringLiteral("0x%1").arg(quintptr(QThread::currentThreadId()), 0, 16, QLatin1Char('0'));
    QSqlDatabase db;
    if(QSqlDatabase::contains(dbname)){
        db = QSqlDatabase::database(dbname);
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE",dbname);
    }
    //addlog(QString("BQDLayout name is %1").arg(dbname).toUtf8());
    db.setDatabaseName(dbfile);   //Set the database name.
    if(!db.open()){
        addlog(QString("The BQDLayout file failed to open due to: %1").arg(db.lastError().text()).toUtf8(),true);
        return false;
    }
    //addlog(QString("The BQDLayout file opened successfully: %1").arg(dbfile).toUtf8());

    QSqlQuery query(db);
    QString cmd = QString("select layer,posX,posY,posWidth,posHeight,bColor,fColor,penWidth,angle "
                          "from Rectangle "
                          "where page = %1 "
                          "order by layer ASC;"
                          ).arg(page);

    if(!query.exec(cmd)){
        addlog(QString("Rectangle query failed due to: %1").arg(query.lastError().text()).toUtf8(),true);
        if(db.isOpen()) db.close();
        return false ;
    }else{
        getrectangle().clear();
        int error = 0 ;
        while (query.next()) {
            ++error ;
            QStringList bbColor = query.value(5).toString().split(",");
            QStringList ffColor = query.value(6).toString().split(",");

            QVector<QString> vbbColor , vffColor;
            if(bbColor.count() != 4){
                vbbColor.append("255");vbbColor.append("255");vbbColor.append("255");vbbColor.append("0");
            }else{
                vbbColor.append(bbColor.at(0));vbbColor.append(bbColor.at(1));vbbColor.append(bbColor.at(2));vbbColor.append(bbColor.at(3));
            }
            if(ffColor.count() != 4){
                vffColor.append("0");vffColor.append("0");vffColor.append("0");vffColor.append("255");
            }else{
                vffColor.append(ffColor.at(0));vffColor.append(ffColor.at(1));vffColor.append(ffColor.at(2));vffColor.append(ffColor.at(3));
            }

            typeRectangle tmp;
            tmp.layer = query.value(0).toInt();
            tmp.postion = QPointF(query.value(1).toDouble() * dpi.printerdpiX / 25.4 ,query.value(2).toDouble()* dpi.printerdpiY / 25.4);
            tmp.rect = QRectF(0,0,query.value(3).toDouble() * dpi.printerdpiX / 25.4 ,query.value(4).toDouble()* dpi.printerdpiY / 25.4);
            tmp.bColor = QColor(vbbColor.at(0).toInt(),vbbColor.at(1).toInt(),vbbColor.at(2).toInt(),vbbColor.at(3).toInt());
            tmp.fColor = QColor(vffColor.at(0).toInt(),vffColor.at(1).toInt(),vffColor.at(2).toInt(),vffColor.at(3).toInt());
            tmp.penWidth = query.value(7).toDouble() * dpi.printerdpiX / 25.4;
            tmp.angle = query.value(8).toDouble();
            getrectangle().append(tmp);
        }
        if(error == 0){
            return false;
        }
    }
    if(db.isOpen()) db.close();
    return true;
}

/**
 * @brief createRoundedRect     Create a rounded rectangle.
 * @param painter               Drawing object.
 * @return bool                 Was it successful.
 */
static bool createRoundedRect(QPainter &painter){
    foreach (auto const _roundedrect, getroundedrect()) {
        painter.translate(_roundedrect.postion);
        painter.rotate(_roundedrect.angle);
        painter.save();
        painter.setBrush(_roundedrect.bColor);
        QPen pen(_roundedrect.fColor);
        pen.setWidth(_roundedrect.penWidth);
        painter.setPen(pen);
        painter.drawRoundedRect(_roundedrect.rect,_roundedrect.xRadius,_roundedrect.yRadius);
        painter.restore();
        painter.translate(QPointF(0,0) - _roundedrect.postion);     //Return to the origin before drawing.
    }
    return true;
}

/**
 * @brief readRoundedRect   Read rounded rectangle from a specified page.
 * @param dbfile            Printer configuration file.
 * @param page              Page.
 * @return bool             Was it successful.
 */
static bool readRoundedRect(QString dbfile, int page){
    //Configure the database.
    QString dbname = "BQDCodeDB_" + QStringLiteral("0x%1").arg(quintptr(QThread::currentThreadId()), 0, 16, QLatin1Char('0'));
    QSqlDatabase db;
    if(QSqlDatabase::contains(dbname)){
        db = QSqlDatabase::database(dbname);
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE",dbname);
    }
    //addlog(QString("BQDLayout name is %1").arg(dbname).toUtf8());
    db.setDatabaseName(dbfile);   //Set the database name.
    if(!db.open()){
        addlog(QString("The BQDLayout file failed to open due to: %1").arg(db.lastError().text()).toUtf8(),true);
        return false;
    }
    //addlog(QString("The BQDLayout file opened successfully: %1").arg(dbfile).toUtf8());

    QSqlQuery query(db);
    QString cmd = QString("select layer,posX,posY,posWidth,posHeight,xRadius,yRadius,bColor,fColor,penWidth,angle "
                          "from RoundedRect "
                          "where page = %1 "
                          "order by layer ASC;"
                          ).arg(page);

    if(!query.exec(cmd)){
        addlog(QString("Rounded rectangle query failed due to: %1").arg(query.lastError().text()).toUtf8(),true);
        if(db.isOpen()) db.close();
        return false ;
    }else{
        getroundedrect().clear();
        int error = 0 ;
        while (query.next()) {
            ++error ;
            QStringList bbColor = query.value(7).toString().split(",");
            QStringList ffColor = query.value(8).toString().split(",");

            QVector<QString> vbbColor , vffColor;
            if(bbColor.count() != 4){
                vbbColor.append("255");vbbColor.append("255");vbbColor.append("255");vbbColor.append("0");
            }else{
                vbbColor.append(bbColor.at(0));vbbColor.append(bbColor.at(1));vbbColor.append(bbColor.at(2));vbbColor.append(bbColor.at(3));
            }
            if(ffColor.count() != 4){
                vffColor.append("0");vffColor.append("0");vffColor.append("0");vffColor.append("255");
            }else{
                vffColor.append(ffColor.at(0));vffColor.append(ffColor.at(1));vffColor.append(ffColor.at(2));vffColor.append(ffColor.at(3));
            }

            typeRoundedRect tmp;
            tmp.layer = query.value(0).toInt();
            tmp.postion = QPointF(query.value(1).toDouble() * dpi.printerdpiX / 25.4 ,query.value(2).toDouble()* dpi.printerdpiY / 25.4);
            tmp.rect = QRectF(0,0,query.value(3).toDouble() * dpi.printerdpiX / 25.4 ,query.value(4).toDouble()* dpi.printerdpiY / 25.4);
            tmp.xRadius = query.value(5).toDouble() * dpi.printerdpiX / 25.4;
            tmp.yRadius = query.value(6).toDouble() * dpi.printerdpiY / 25.4;
            tmp.bColor = QColor(vbbColor.at(0).toInt(),vbbColor.at(1).toInt(),vbbColor.at(2).toInt(),vbbColor.at(3).toInt());
            tmp.fColor = QColor(vffColor.at(0).toInt(),vffColor.at(1).toInt(),vffColor.at(2).toInt(),vffColor.at(3).toInt());
            tmp.penWidth = query.value(9).toDouble() * dpi.printerdpiX / 25.4;
            tmp.angle = query.value(10).toDouble();
            getroundedrect().append(tmp);
        }
        if(error == 0){
            return false;
        }
    }
    if(db.isOpen()) db.close();
    return true;
}

/**
 * @brief createLine        Create a line.
 * @param painter           Drawing object.
 * @return bool             Was it successful.
 */
static bool createLine(QPainter &painter){
    foreach (auto const _line, getline()) {
        painter.translate(_line.spostion);
        painter.rotate(_line.angle);
        painter.save();
        QPen pen(_line.fColor);
        pen.setWidth(_line.penWidth);
        painter.setPen(pen);
        painter.drawLine(QPointF(0,0),_line.epostion);
        painter.restore();
        painter.translate(QPointF(0,0) - _line.spostion);     //Return to the origin before drawing.
    }
    return true;
}

/**
 * @brief readLine      Read line from a specified page.
 * @param dbfile        Printer configuration file.
 * @param page          Page.
 * @return bool         Was it successful.
 */
static bool readLine(QString dbfile, int page){
    //Configure the database.
    QString dbname = "BQDCodeDB_" + QStringLiteral("0x%1").arg(quintptr(QThread::currentThreadId()), 0, 16, QLatin1Char('0'));
    QSqlDatabase db;
    if(QSqlDatabase::contains(dbname)){
        db = QSqlDatabase::database(dbname);
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE",dbname);
    }
    //addlog(QString("BQDLayout name is %1").arg(dbname).toUtf8());
    db.setDatabaseName(dbfile);   //Set the database name.
    if(!db.open()){
        addlog(QString("The BQDLayout file failed to open due to: %1").arg(db.lastError().text()).toUtf8(),true);
        return false;
    }
    //addlog(QString("The BQDLayout file opened successfully: %1").arg(dbfile).toUtf8());

    QSqlQuery query(db);
    QString cmd = QString("select layer,posX,posY,iX,iY,fColor,penWidth,angle "
                          "from Line "
                          "where page = %1 "
                          "order by layer ASC;"
                          ).arg(page);
    if(!query.exec(cmd)){
        addlog(QString("Line segment query failed due to: %1").arg(query.lastError().text()).toUtf8(),true);
        if(db.isOpen()) db.close();
        return false ;
    }else{
        getline().clear();
        int error = 0 ;
        while (query.next()) {
            ++error;
            QStringList ffColor = query.value(5).toString().split(",");

            QVector<QString> vffColor;
            if(ffColor.count() != 4){
                vffColor.append("0");vffColor.append("0");vffColor.append("0");vffColor.append("255");
            }else{
                vffColor.append(ffColor.at(0));vffColor.append(ffColor.at(1));vffColor.append(ffColor.at(2));vffColor.append(ffColor.at(3));
            }
            typeLine tmp;
            tmp.layer = query.value(0).toInt();
            tmp.spostion = QPointF(query.value(1).toDouble() * dpi.printerdpiX / 25.4 ,query.value(2).toDouble()* dpi.printerdpiY / 25.4);
            tmp.epostion = QPointF(query.value(3).toDouble() * dpi.printerdpiX / 25.4 ,query.value(4).toDouble()* dpi.printerdpiY / 25.4);
            tmp.fColor = QColor(vffColor.at(0).toInt(),vffColor.at(1).toInt(),vffColor.at(2).toInt(),vffColor.at(3).toInt());
            tmp.penWidth = query.value(6).toDouble() * dpi.printerdpiX / 25.4;
            tmp.angle = query.value(7).toDouble();
            getline().append(tmp);
        }
        if(error == 0){
            return false;
        }
    }
    if(db.isOpen()) db.close();
    return true;
}

/**
 * @brief createEllipse     Create a circle
 * @param painter           Drawing object.
 * @return bool             Was it successful.
 */
static bool createEllipse(QPainter &painter){
    foreach (auto const _ellipse, getellipse()) {
        painter.translate(_ellipse.postion);
        painter.rotate(_ellipse.angle);
        painter.save();
        painter.setBrush(_ellipse.bColor);
        QPen pen(_ellipse.fColor);
        pen.setWidth(_ellipse.penWidth);
        painter.setPen(pen);
        painter.drawEllipse(0,0,_ellipse.width,_ellipse.height);
        painter.restore();
        painter.translate(QPointF(0,0) - _ellipse.postion);     //Return to the origin before drawing.
    }
    return true;
}

/**
 * @brief readEllipse   Read circle from a specified page.
 * @param dbfile        Printer configuration file.
 * @param page          Page.
 * @return bool         Was it successful.
 */
static bool readEllipse(QString dbfile, int page){
    //Configure the database.
    QString dbname = "BQDCodeDB_" + QStringLiteral("0x%1").arg(quintptr(QThread::currentThreadId()), 0, 16, QLatin1Char('0'));
    QSqlDatabase db;
    if(QSqlDatabase::contains(dbname)){
        db = QSqlDatabase::database(dbname);
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE",dbname);
    }
    //addlog(QString("BQDLayout name is %1").arg(dbname).toUtf8());
    db.setDatabaseName(dbfile);   //Set the database name.
    if(!db.open()){
        addlog(QString("The BQDLayout file failed to open due to: %1").arg(db.lastError().text()).toUtf8(),true);
        return false;
    }
    //addlog(QString("The BQDLayout file opened successfully: %1").arg(dbfile).toUtf8());

    QSqlQuery query(db);
    QString cmd = QString("select layer,posX,posY,width,height,bColor,fColor,penWidth,angle "
                          "from Ellipse "
                          "where page = %1 "
                          "order by layer ASC;"
                          ).arg(page);
    if(!query.exec(cmd)){
        addlog(QString("Circle query failed due to: %1").arg(query.lastError().text()).toUtf8(),true);
        if(db.isOpen()) db.close();
        return false ;
    }else{
        getellipse().clear();
        int error = 0 ;
        while (query.next()) {
            ++error;
            QStringList bbColor = query.value(5).toString().split(",");
            QStringList ffColor = query.value(6).toString().split(",");

            QVector<QString> vbbColor , vffColor;
            if(bbColor.count() != 4){
                vbbColor.append("255");vbbColor.append("255");vbbColor.append("255");vbbColor.append("0");
            }else{
                vbbColor.append(bbColor.at(0));vbbColor.append(bbColor.at(1));vbbColor.append(bbColor.at(2));vbbColor.append(bbColor.at(3));
            }
            if(ffColor.count() != 4){
                vffColor.append("0");vffColor.append("0");vffColor.append("0");vffColor.append("255");
            }else{
                vffColor.append(ffColor.at(0));vffColor.append(ffColor.at(1));vffColor.append(ffColor.at(2));vffColor.append(ffColor.at(3));
            }

            typeEllipse tmp;
            tmp.layer = query.value(0).toInt();
            tmp.postion = QPointF(query.value(1).toDouble() * dpi.printerdpiX / 25.4 ,query.value(2).toDouble()* dpi.printerdpiY / 25.4);
            tmp.width = query.value(3).toDouble()  * dpi.printerdpiX / 25.4 ;
            tmp.height = query.value(4).toDouble()  * dpi.printerdpiY / 25.4 ;
            tmp.bColor = QColor(vbbColor.at(0).toInt(),vbbColor.at(1).toInt(),vbbColor.at(2).toInt(),vbbColor.at(3).toInt());
            tmp.fColor = QColor(vffColor.at(0).toInt(),vffColor.at(1).toInt(),vffColor.at(2).toInt(),vffColor.at(3).toInt());
            tmp.penWidth = query.value(7).toDouble() * dpi.printerdpiX / 25.4;
            tmp.angle = query.value(8).toDouble();

            getellipse().append(tmp);
        }
        if(error == 0){
            return false;
        }
    }
    if(db.isOpen()) db.close();
    return true;
}

/**
 * @brief addlog    Add a log.
 * @param log       Log information
 * @param err       Is it an error option.
 */
static void addlog(QByteArray log , const bool &err){
    qDebug() << QString(log);
    if(err){
        BQDlogger->error(log.data());
    }else{
        BQDlogger->info(log.data());
    }
}

/**
 * @brief createBQDLayoutFile   Create a BQD layout file.
 * @return BQDError
 */
BQDError createBQDLayoutFile(){
    if(!dllcheck()){        //The key DLL does not exist.
        addlog(QString("BQDCode.dll does not exist, and the program cannot run.").toUtf8(),true);
        return BQDDLLErr;
    }
    appnew();

    QString filename = QFileDialog::getSaveFileName(
        nullptr,
        QString("Save the file."),
        "",
        "bqd File (*.bqd);"
    );
    if(filename.trimmed().isEmpty()){
        addlog(QString("No path selected.").toUtf8());
        return BQDNFErr;
    }
    //Configure the database.
    QString dbname = "BQDCodeDB_" + QStringLiteral("0x%1").arg(quintptr(QThread::currentThreadId()), 0, 16, QLatin1Char('0'));
    QSqlDatabase db;
    if(QSqlDatabase::contains(dbname)){
        db = QSqlDatabase::database(dbname);
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE",dbname);
    }
    //addlog(QString("BQDLayout name is %1").arg(dbname).toUtf8());
    db.setDatabaseName(filename);   //Set the database name.
    if(!db.open()){
        addlog(QString("The BQDLayout file failed to open due to: %1").arg(db.lastError().text()).toUtf8(),true);
        return BQDOFErr;
    }
    //addlog(QString("The BQDLayout file opened successfully: %1").arg(filename).toUtf8());

    QSqlQuery query(db);

    //Attempt to create the config table.
    QString cmd = R"(
        create table if not exists [config] (
            id integer primary key check(id = 1) ,
            outputformat integer not null ,
            pagewidth double not null ,
            pageheight double not null,
            margleft double not null ,
            margtop double not null ,
            margright double not null ,
            margbottom double not null
        );
    )";
    if(!query.exec(cmd)){
        addlog(QString("Configuration file creation failed due to: %1").arg(query.lastError().text()).toUtf8(),true);
        if(db.isOpen()) db.close();
        return BQDCBCErr ;
    }else{
        addlog(QString("Configuration file created successfully.").toUtf8());
    }


    //Attempt to create the Barcode table.
    cmd = R"(
        create table if not exists [BarCode] (
            key_index integer not null ,
            page  integer not null ,
            layer integer not null ,
            str text not null,
            var bool not null ,
            varName text ,
            posX double not null ,
            posY double not null ,
            bColor text not null ,
            fColor text not null ,
            fontName text not null ,
            fontSize integer not null ,
            fontWeight integer not null ,
            fontItalic bool not null ,
            type integer not null ,
            disPlayText bool not null ,
            argin integer not null ,
            widthScalef double not null ,
            height double not null ,
            angle double not null ,
            primary key(key_index)
        );
    )";
    if(!query.exec(cmd)){
        addlog(QString("Barcode file creation failed due to: %1").arg(query.lastError().text()).toUtf8(),true);
        if(db.isOpen()) db.close();
        return BQDCBCErr ;
    }else{
        addlog(QString("Barcode file created successfully.").toUtf8());
    }

    //Attempt to create the StringText table.
    cmd = R"(
        create table if not exists [StringText] (
            key_index integer not null ,
            page  integer not null ,
            layer integer not null ,
            str text not null,
            var bool not null ,
            varName text ,
            posX double not null ,
            posY double not null ,
            bColor text not null ,
            fColor text not null ,
            fontName text not null ,
            fontSize integer not null ,
            fontWeight integer not null ,
            fontItalic bool not null ,
            angle double not null ,
            primary key(key_index)
        );
    )";
    if(!query.exec(cmd)){
        addlog(QString("Character file creation failed due to: %1").arg(query.lastError().text()).toUtf8(),true);
        if(db.isOpen()) db.close();
        return BQDCTErr ;
    }else{
        addlog(QString("Character file created successfully.").toUtf8());
    }

    //Attempt to create the Rectangle table.
    cmd = R"(
        create table if not exists [Rectangle] (
            key_index integer not null ,
            page  integer not null ,
            layer integer not null ,
            posX double not null ,
            posY double not null ,
            posWidth double not null ,
            posHeight double not null ,
            bColor text not null ,
            fColor text not null ,
            penWidth  double not null ,
            angle double not null ,
            primary key(key_index)
        );
    )";
    if(!query.exec(cmd)){
        addlog(QString("Rectangle file creation failed due to: %1").arg(query.lastError().text()).toUtf8(),true);
        if(db.isOpen()) db.close();
        return BQDCRTErr ;
    }else{
        addlog(QString("Rectangle file created successfully.").toUtf8());
    }


    //Attempt to create the Line table.
    cmd = R"(
        create table if not exists [Line] (
            key_index integer not null ,
            page  integer not null ,
            layer integer not null ,
            posX double not null ,
            posY double not null ,
            iX double not null ,
            iY double not null ,
            fColor text not null ,
            penWidth  double not null ,
            angle double not null ,
            primary key(key_index)
        );
    )";
    if(!query.exec(cmd)){
        addlog(QString("Line file creation failed due to: %1").arg(query.lastError().text()).toUtf8(),true);
        if(db.isOpen()) db.close();
        return BQDCLErr ;
    }else{
        addlog(QString("Line file created successfully.").toUtf8());
    }


    //Attempt to create the RoundedRect table.
    cmd = R"(
        create table if not exists [RoundedRect] (
            key_index integer not null ,
            page  integer not null ,
            layer integer not null ,
            posX double not null ,
            posY double not null ,
            posWidth double not null ,
            posHeight double not null ,
            xRadius double not null ,
            yRadius double not null ,
            bColor text not null ,
            fColor text not null ,
            penWidth  double not null ,
            angle double not null ,
            primary key(key_index)
        );
    )";
    if(!query.exec(cmd)){
        addlog(QString("Rounded rectangle file creation failed due to: %1").arg(query.lastError().text()).toUtf8(),true);
        if(db.isOpen()) db.close();
        return BQDRRErr ;
    }else{
        addlog(QString("Rounded rectangle file created successfully.").toUtf8());
    }


    //Attempt to create the DataMatrix table.
    cmd = R"(
        create table if not exists [DataMatrix] (
            key_index integer not null ,
            page  integer not null ,
            layer integer not null ,
            str text not null,
            var bool not null ,
            varName text ,
            posX double not null ,
            posY double not null ,
            bColor text not null ,
            fColor text not null ,
            argin integer not null ,
            scalef double not null ,
            angle double not null ,
            primary key(key_index)
        );
    )";
    if(!query.exec(cmd)){
        addlog(QString("DataMatrix file creation failed due to: %1").arg(query.lastError().text()).toUtf8(),true);
        if(db.isOpen()) db.close();
        return BQDDMErr ;
    }else{
        addlog(QString("DataMatrix file created successfully.").toUtf8());
    }

    //Attempt to create the QRCode table.
    cmd = R"(
        create table if not exists [QRCode] (
            key_index integer not null ,
            page  integer not null ,
            layer integer not null ,
            str text not null,
            var bool not null ,
            varName text ,
            posX double not null ,
            posY double not null ,
            bColor text not null ,
            fColor text not null ,
            QRVersion integer not null ,
            QRlevel integer not null ,
            QRhint integer not null ,
            CaseSensitive bool not null ,
            scalef double not null ,
            angle double not null ,
            primary key(key_index)
        );
    )";
    if(!query.exec(cmd)){
        addlog(QString("QRCode file creation failed due to: %1").arg(query.lastError().text()).toUtf8(),true);
        if(db.isOpen()) db.close();
        return BQDQRCErr ;
    }else{
        addlog(QString("QRCode file created successfully.").toUtf8());
    }


    //Attempt to create the Ellipse table.
    cmd = R"(
        create table if not exists [Ellipse] (
            key_index integer not null ,
            page  integer not null ,
            layer integer not null ,
            posX double not null ,
            posY double not null ,
            width double not null ,
            height double not null ,
            bColor text not null ,
            fColor text not null ,
            penWidth double not null ,
            angle double not null ,
            primary key(key_index)
        );
    )";
    if(!query.exec(cmd)){
        addlog(QString("Circle file creation failed due to: %1").arg(query.lastError().text()).toUtf8(),true);
        if(db.isOpen()) db.close();
        return BQDELPErr ;
    }else{
        addlog(QString("Circle file created successfully.").toUtf8());
    }
    appdel();
    if(db.isOpen()) db.close();
    return BQDOk;
}


/**
 * @brief printfBQDCode Print the file.
 * @param dbfile        Printer configuration file.
 * @param printername   Print the file name or printer name.
 * @param opf           Printer type
 *                      0: Standard printer
 *                      1: Generate PDF
 * @param var           Var
 *                      var1=tmp1,var2=temp2,var3=temp3
 * @return  BQDError
 */
BQDError printfBQDCode(const char * dbfile , const char *printername,int opf, const char * var )
{
    if(!dllcheck()){        //The key DLL does not exist.
        addlog(QString("BQDCode.dll does not exist, and the program cannot run.").toUtf8(),true);
        return BQDDLLErr;
    }
    appnew();
    //Read the configuration file.
    QPageSize pagesize;         //PageSize.
    QMarginsF margins;          //Margin.
    if(!getconfig(dbfile,pagesize,margins)){
        return BQDConfigErr;
    }
    QPrinter printer(QPrinter::HighResolution);     //Printer object.
    printer.setOutputFormat(static_cast<QPrinter::OutputFormat>(opf));  //Set the print format.
    printer.setPageSize(pagesize);                  //Set the paper size.
    printer.setPageMargins(margins);                //Set the margin.
    if(opf == QPrinter::PdfFormat){                 //If it's outputting to PDF.
        QFileInfo fileinfo(printername);            //Check if the output path is correct.
        QString filepath = fileinfo.path();
        QDir dir(filepath);
        if(!dir.exists()){
            if(!dir.mkpath(filepath)){
                addlog(QString("PDF output directory creation failed: %1").arg(filepath).toUtf8(),true);
                return BQDPDFPathErr;
            }
        }
        printer.setOutputFileName(printername); //Set the PDF print path.
    }else {          //Call the standard printer.
        printer.setPrinterName(printername);
    }

    //Get the printer DPI.
    dpi.printerdpiX = printer.logicalDpiX();
    dpi.printerdpiY = printer.logicalDpiY();

    auto screen = QGuiApplication::primaryScreen();   //Get the primary screen.
    // Get the DPI of the primary screen.
    dpi.screendpiX = screen->logicalDotsPerInchX();
    dpi.screendpiY = screen->logicalDotsPerInchY();

    int page = 1 ;          //Start page numbering; page 0 is the background and does not need to be printed.
    QPainter painter;       //Initialize the drawing tool.
    if(!painter.begin(&printer)){
        addlog(QString("Print failed: The print file is in use or printer configuration error.").toUtf8(),true);
        return BQDPDFOErr;
    }
    addlog(QString("Print configuration file: %1").arg(dbfile).toUtf8());
    addlog(QString("Printer name: %1").arg(printername).toUtf8());


    //Start parsing variables.
    QMap<QString,QString> mapvar;       //Variable storage.
    if(var){
        ptest = false;
        addlog(QString("Printing in progress...").toUtf8());
        QString qvar(var);
        QStringList varlist = qvar.split(",");
        foreach (const auto _var, varlist) {
            QStringList mvarlist = _var.split("=");
            if(mvarlist.count() == 2){
                QString key = mvarlist.at(0).trimmed();
                QString value = mvarlist.at(1).trimmed();
                mapvar.insert(key,value);
            }
        }
    }
    else{
        ptest = true;
        addlog(QString("Debugging the print operation, no variables will be modified.").toUtf8());
        mapvar.clear();
    }

    while(page){


        bool recterr = false , lineerr = false , texterr = false , barcodeerr = false , roundedrecterr = false , datamatrixerr = false;
        bool qrcodeerr = false , ellipseerr = false;
        if(readRectangle(dbfile,page)){
            recterr = false;
        }else{
            recterr = true;
        }

        if(readLine(dbfile,page)){
            lineerr = false;
        }else{
            lineerr = true;
        }

        if(readStringText(dbfile,page)){
            texterr = false;
        }else{
            texterr = true;
        }

        if(readBarcode(dbfile,page)){
            barcodeerr = false;
        }else{
            barcodeerr = true;
        }

        if(readRoundedRect(dbfile,page)){
            roundedrecterr = false ;
        }else{
            roundedrecterr = true;
        }

        if(readDataMatrix(dbfile,page)){
            datamatrixerr = false ;
        }else{
            datamatrixerr = true;
        }

        if(readQRCode(dbfile,page)){
            qrcodeerr = false;
        }else{
            qrcodeerr = true;
        }

        if(readEllipse(dbfile,page)){
            ellipseerr = false;
        }else{
            ellipseerr = true;
        }


        if(recterr && lineerr && texterr && barcodeerr && roundedrecterr && datamatrixerr && qrcodeerr && ellipseerr){
            break;
        }else{
            if(page > 1){
                printer.newPage();
            }
            createRectangle(painter);
            createRoundedRect(painter);
            createEllipse(painter);
            createLine(painter);
            createStringText(painter,mapvar);
            createBarCode(painter,mapvar);
            createDataMatrix(painter,mapvar);
            createQRCode(painter,mapvar);
        }

        ++page;
    }
    painter.end();
    appdel();
    addlog(QString("Print completed.").toUtf8());
    return BQDOk;
}

/**
 * @brief getVarlist    Retrieve the list of variables.
 * @param dbfile        Print the configuration file.
 * @return              Varlist: name1,name2,name3,name4
 */
const char *getVarlist(const char * dbfile)
{
    appnew();
    //Configure the database.
    QString dbname = "BQDCodeDB_" + QStringLiteral("0x%1").arg(quintptr(QThread::currentThreadId()), 0, 16, QLatin1Char('0'));
    QSqlDatabase db;

    if(QSqlDatabase::contains(dbname)){
        db = QSqlDatabase::database(dbname);
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE",dbname);
    }
    //addlog(QString("BQDLayout name is %1").arg(dbname).toUtf8());
    db.setDatabaseName(dbfile);   //Set the database name.
    if(!db.open()){
        addlog(QString("The BQDLayout file failed to open due to: %1").arg(db.lastError().text()).toUtf8(),true);
        return nullptr;
    }
    //addlog(QString("The BQD file opened successfully: %1").arg(dbfile).toUtf8());
    addlog(QString("Retrieving variable...").toUtf8());
    QSqlQuery query(db);
    //Get the barcode.
    QString cmd = QString("select varName "
                          "from BarCode "
                          "where var = 1 ;"
                          );
    getPrintVal().clear();
    if(!query.exec(cmd)){
        addlog(QString("Barcode variable query failed due to: %1").arg(query.lastError().text()).toUtf8(),true);
        if(db.isOpen()) db.close();
        return nullptr ;
    }else{
        while(query.next()){    //Get all barcode variables.
            getPrintVal().append(query.value(0).toString().toUtf8() + ",");
        }
    }

    //Get the DataMatrix.
    cmd = QString("select varName "
                  "from DataMatrix "
                  "where var = 1 ;"
                  );
    if(!query.exec(cmd)){
        addlog(QString("DataMatrix variable query failed due to: %1").arg(query.lastError().text()).toUtf8(),true);
        if(db.isOpen()) db.close();
        return nullptr ;
    }else{
        while(query.next()){    //Get all DataMatrix variables.
            getPrintVal().append(query.value(0).toString().toUtf8() + ",");
        }
    }

    //Get the QR code
    cmd = QString("select varName "
                  "from QRCode "
                  "where var = 1 ;"
                  );
    if(!query.exec(cmd)){
        addlog(QString("QRCode variable query failed due to: %1").arg(query.lastError().text()).toUtf8(),true);
        if(db.isOpen()) db.close();
        return nullptr ;
    }else{
        while(query.next()){    //Get all QR code variables.
            getPrintVal().append(query.value(0).toString().toUtf8() + ",");
        }
    }

    //Get the character.
    cmd = QString("select varName "
                  "from StringText "
                  "where var = 1 ;"
                  );
    if(!query.exec(cmd)){
        addlog(QString("Character variable query failed due to: %1").arg(query.lastError().text()).toUtf8(),true);
        if(db.isOpen()) db.close();
        return nullptr ;
    }else{
        while(query.next()){    //Get all character variables.
            getPrintVal().append(query.value(0).toString().toUtf8() + ",");
        }
    }
    if(db.isOpen()) db.close();
    if(getPrintVal().length() > 0) getPrintVal().chop(1);
    addlog(QString("Variable retrieval completed.").toUtf8());
    return getPrintVal().constData();
}

/**
 * @brief settingsBQDLayout     Adjust the layout.
 * @param dbfile                Print the configuration file.
 * @return BQDError
 */
BQDError settingsBQDLayout(const char *dbfile)
{
    //TDO
    (void)dbfile;
    return BQDSETLAYErr;
}
