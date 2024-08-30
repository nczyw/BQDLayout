# BQDLayout
## 用于生成pdf或者打印文件的库  
基于[BQDCode开源库](https://github.com/nczyw/BQDCode),使用Qt的GUI来生成dpf和打印文件
## Version 1.0.0.0
 * 初次发布
## 库介绍
 * 通过调用createBQDLayoutFile函数,可以轻松的创建一个bqd格式的文件,
   用于存放所有打印内容,基于SQLITE.
 * 支持把数据配置为变量,在调用打印函数时,可以传入变量的值,实现动态打印.
 * 通过调用printfBQDCode函数,可以根据bqd配置文件,生成一个pdf或者调用打印机打印.
 * 通过调用getVarlist函数,可以根据bqd配置文件,获取到哪些数据被定义为了变量,得到他们的名字.
 * 通过调用settingsBQDLayout函数,可以根据配置文件,打开一个UI窗口,进行可视化配置bqd文件
   （该功能为后续计划开发,当前调用该函数会返回一个错误）.
## 编译方法
 * 如果你也使用Qt开发,Qt打开CMakeLists.txt,选择自己想要的版本,编译生成对应的dll,这样才不会出现版本冲突.
 * 请不要使用低版本的GCC或者MinGW或者MSVC,可能会出现意想不到的错误,特别是低版本中的MinGW中的
   ```libstdc++-6.dll,libgcc_s_seh-1.dll```是无法正确调用dll的.
 * 如果你不想编译,可以联系我,提供编译好的dll以及依赖库.
 * 函数的签名以及说明,请查看```bqdlayout.h```中的注释
## bqd文件介绍
### config表格
 * ```id```:类型:```integer```;只能添加ID=1的记录,也就是只允许添加一条记录.
 * ```outputformat```:类型:```integer```;输出格式:0,标准打印机打印;1:输出一个PDF文件.
 * ```pagewidth```:类型:```double```;纸张宽度,单位MM.
 * ```pageheight```:类型:```double```;纸张高度,单位MM.
 * ```margleft```:类型:```double```;页边距左,单位MM.
 * ```margtop```:类型:```double```;页边距上,单位MM.
 * ```margright```:类型:```double```;页边距右,单位MM.
 * ```margbottom```:类型:```double```;页边距下,单位MM.
### BarCode表格
 * ```key_index```:类型:```integer```;表格的主键;条码的序号,不可重复.
 * ```page```:类型:```integer```;条码位于哪一页,0页的条码不会打印.
 * ```layer```:类型:```integer```;条码位于的图层,数字越大,图层越高,条码越最后绘制.
 * ```str```:类型:```text```;条码要显示的内容.
 * ```var```:类型:```bool```;条码是否为变量.
 * ```varName```:类型:```text```;条码的变量名字.
 * ```posX```:类型:```double```;条码的X坐标,单位MM.
 * ```posY```:类型:```double```;条码的Y坐标,单位MM.
 * ```bColor```:类型:```text```;条码的背景色,格式为:```255,255,255,0```,R,G,B,HSV.
 * ```fColor```:类型:```text```;条码的前景色,格式为:```0,0,0,255```,R,G,B,HSV.
 * ```fontName```:类型:```text```;条码的字体名字,比如```Arial```.
 * ```fontSize```:类型:```integer```;条码的字体大小.
 * ```fontWeight```:类型:```integer```;条码的字符是否加粗,参考Qt的QFont.
 * ```fontItalic```:类型:```bool```;条码的字体是否加粗.
 * ```type```:类型:```integer```;条码的类型,比如BARCODE_128,表示类型5.
 * ```disPlayText```:类型:```bool```;条码是否显示文本.
 * ```argin```:类型:```integer```;条码边缘留空距离,单位MM.
 * ```widthScalef```:类型:```double```;条码的理想宽度,单位MM,实际宽度经过计算后得到,不超过理想宽度.
 * ```height```:类型:```double```;条码的高度,单位MM.
 * ```angle```:类型:```double```;条码的旋转角度,不要超过360度.
### DataMatrix表格
 * ```key_index```:类型:```integer```;表格的主键;DataMatrix的序号,不可重复.
 * ```page```:类型:```integer```;DataMatrix位于哪一页,0页的DataMatrix不会打印.
 * ```layer```:类型:```integer```;DataMatrix位于的图层,数字越大,图层越高,DataMatrix越最后绘制.
 * ```str```:类型:```text```;DataMatrix要显示的内容.
 * ```var```:类型:```bool```;DataMatrix是否为变量.
 * ```varName```:类型:```text```;DataMatrix的变量名字.
 * ```posX```:类型:```double```;DataMatrix的X坐标,单位MM.
 * ```posY```:类型:```double```;DataMatrix的Y坐标,单位MM.
 * ```bColor```:类型:```text```;DataMatrix的背景色,格式为:```255,255,255,0```,R,G,B,HSV.
 * ```fColor```:类型:```text```;DataMatrix的前景色,格式为:```0,0,0,255```,R,G,B,HSV.
 * ```argin```:类型:```integer```;DataMatrix边缘留空距离,单位MM.
 * ```scalef```:类型:```double```;DataMatrix的宽度,单位MM.
 * ```angle```:类型:```double```;DataMatrix的旋转角度,不要超过360度.
### Ellipse表格
 * ```key_index```:类型:```integer```;表格的主键;Ellipse的序号,不可重复.
 * ```page```:类型:```integer```;Ellipse位于哪一页,0页的Ellipse不会打印.
 * ```layer```:类型:```integer```;Ellipse位于的图层,数字越大,图层越高,Ellipse越最后绘制.
 * ```str```:类型:```text```;Ellipse要显示的内容.
 * ```var```:类型:```bool```;Ellipse是否为变量.
 * ```varName```:类型:```text```;Ellipse的变量名字.
 * ```posX```:类型:```double```;Ellipse的X坐标,单位MM.
 * ```posY```:类型:```double```;Ellipse的Y坐标,单位MM.
 * ```bColor```:类型:```text```;Ellipse的背景色,格式为:```255,255,255,0```,R,G,B,HSV.
 * ```fColor```:类型:```text```;Ellipse的前景色,格式为:```0,0,0,255```,R,G,B,HSV.
 * ```penWidth```:类型:```double```;Ellipse画笔宽度,单位MM.
 * ```angle```:类型:```double```;Ellipse的旋转角度,不要超过360度.
### Line表格
 * ```key_index```:类型:```integer```;表格的主键;Line的序号,不可重复.
 * ```page```:类型:```integer```;Line位于哪一页,0页的Line不会打印.
 * ```layer```:类型:```integer```;Line位于的图层,数字越大,图层越高,Line越最后绘制.
 * ```posX```:类型:```double```;Line的X坐标,单位MM.
 * ```posY```:类型:```double```;Line的Y坐标,单位MM.
 * ```iX```:类型:```double```;Line的终点坐标X,单位MM.
 * ```iY```:类型:```double```;Line的终点坐标Y,单位MM.
 * ```fColor```:类型:```text```;Line的前景色,格式为:```0,0,0,255```,R,G,B,HSV.
 * ```penWidth```:类型:```double```;Line画笔宽度,单位MM.
 * ```angle```:类型:```double```;Line的旋转角度,不要超过360度.
### QRCode表格
 * ```key_index```:类型:```integer```;表格的主键;QRCode的序号,不可重复.
 * ```page```:类型:```integer```;QRCode位于哪一页,0页的QRCode不会打印.
 * ```layer```:类型:```integer```;QRCode位于的图层,数字越大,图层越高,QRCode越最后绘制.
 * ```str```:类型:```text```;QRCode要显示的内容.
 * ```var```:类型:```bool```;QRCode是否为变量.
 * ```varName```:类型:```text```;QRCode的变量名字.
 * ```posX```:类型:```double```;QRCode的X坐标,单位MM.
 * ```posY```:类型:```double```;QRCode的Y坐标,单位MM.
 * ```bColor```:类型:```text```;QRCode的背景色,格式为:```255,255,255,0```,R,G,B,HSV.
 * ```fColor```:类型:```text```;QRCode的前景色,格式为:```0,0,0,255```,R,G,B,HSV.
 * ```QRVersion```:类型:```integer```;QRCode的版本.
 * ```QRlevel```:类型:```integer```;QRCode的纠错等级.
 * ```QRhint```:类型:```integer```;QRCode的编码模式.
 * ```CaseSensitive```:类型:```bool```;QRCode是否区分大小写.
 * ```scalef```:类型:```double```;QRCode的宽度,单位MM.
 * ```angle```:类型:```double```;QRCode的旋转角度,不要超过360度.
### Rectangle表格
 * ```key_index```:类型:```integer```;表格的主键;Rectangle的序号,不可重复.
 * ```page```:类型:```integer```;Rectangle位于哪一页,0页的Rectangle不会打印.
 * ```layer```:类型:```integer```;Rectangle位于的图层,数字越大,图层越高,Rectangle越最后绘制.
 * ```posX```:类型:```double```;Rectangle的X坐标,单位MM.
 * ```posY```:类型:```double```;Rectangle的Y坐标,单位MM.
 * ```posWidth```:类型:```double```;Rectangle的宽度,单位MM.
 * ```posHeight```:类型:```double```;Rectangle的高度,单位MM.
 * ```bColor```:类型:```text```;Rectangle的背景色,格式为:```255,255,255,0```,R,G,B,HSV.
 * ```fColor```:类型:```text```;Rectangle的前景色,格式为:```0,0,0,255```,R,G,B,HSV.
 * ```penWidth```:类型:```double```;Rectangle画笔宽度,单位MM.
 * ```angle```:类型:```double```;Rectangle的旋转角度,不要超过360度.
### RoundedRect表格
 * ```key_index```:类型:```integer```;表格的主键;RoundedRect的序号,不可重复.
 * ```page```:类型:```integer```;RoundedRect位于哪一页,0页的RoundedRect不会打印.
 * ```layer```:类型:```integer```;RoundedRect位于的图层,数字越大,图层越高,RoundedRect越最后绘制.
 * ```posX```:类型:```double```;RoundedRect的X坐标,单位MM.
 * ```posY```:类型:```double```;RoundedRect的Y坐标,单位MM.
 * ```posWidth```:类型:```double```;RoundedRect的宽度,单位MM.
 * ```posHeight```:类型:```double```;RoundedRect的高度,单位MM.
 * ```xRadius```:类型:```double```;RoundedRect的倒角X,单位MM.
 * ```yRadius```:类型:```double```;RoundedRect的倒角Y,单位MM.
 * ```bColor```:类型:```text```;RoundedRect的背景色,格式为:```255,255,255,0```,R,G,B,HSV.
 * ```fColor```:类型:```text```;RoundedRect的前景色,格式为:```0,0,0,255```,R,G,B,HSV.
 * ```penWidth```:类型:```double```;RoundedRect画笔宽度,单位MM.
 * ```angle```:类型:```double```;RoundedRect的旋转角度,不要超过360度.
### StringText表格
 * ```key_index```:类型:```integer```;表格的主键;StringText的序号,不可重复.
 * ```page```:类型:```integer```;StringText位于哪一页,0页的StringText不会打印.
 * ```layer```:类型:```integer```;StringText位于的图层,数字越大,图层越高,StringText越最后绘制.
 * ```str```:类型:```text```;StringText要显示的内容.
 * ```var```:类型:```bool```;StringText是否为变量.
 * ```varName```:类型:```text```;StringText的变量名字.
 * ```posX```:类型:```double```;StringText的X坐标,单位MM.
 * ```posY```:类型:```double```;StringText的Y坐标,单位MM.
 * ```bColor```:类型:```text```;StringText的背景色,格式为:```255,255,255,0```,R,G,B,HSV.
 * ```fColor```:类型:```text```;StringText的前景色,格式为:```0,0,0,255```,R,G,B,HSV.
 * ```fontName```:类型:```text```;StringText的字体名字,比如```Arial```.
 * ```fontSize```:类型:```integer```;StringText的字体大小.
 * ```fontWeight```:类型:```integer```;StringText的字符是否加粗,参考Qt的QFont.
 * ```fontItalic```:类型:```bool```;StringText的字体是否加粗.
 * ```angle```:类型:```double```;StringText的旋转角度,不要超过360度.
