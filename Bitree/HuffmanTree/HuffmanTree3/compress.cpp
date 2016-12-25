#include "compress.h"
#include "QDebug"

Compress::Compress(QString path, QString output)
{
    this->setFile(path);
    this->setName(path);
    this->setPath(path);
    this->outputName = output;
}

void Compress::setFile(QString path){
    QFile file(path);

    if(file.exists()){
        file.open(QIODevice::ReadOnly);
        QByteArray data = file.readAll();
        this->file = data ;
    }
    else{
        qDebug() << path;
        qDebug() << "Error: Could not open the file.";
    }
}

void Compress::setName(QString name){
    for(int i = name.length() -1; i > 0; i--)
        if(name.at(i) == '/'){
            name.remove(0, i + 1);
            break;
        }
    this->fileName = name;
}

void Compress::setPath(QString path){
    this->filePath = path;
}

void Compress::showInput(){
    if(this->file != NULL)
        qDebug() << this->file;
    else
        qDebug() << "Error: Could not find the input file.";
}

QByteArray Compress::getFile(){
    if(this->file != NULL)
        return this->file;
    else
        qDebug() << "Error: Could not find the input file.";
}

QString fill(QString bin, int n){
    int size = bin.size();
    if(size > n)
        qDebug() << "Warning: Overflow.";
    for(int i=0; i< n - size; i++)
        bin.prepend('0');
    return bin;
}

int Compress::encode(){
    QByteArray file = this->getFile();
    Frequency frequecy = Frequency(file);
    Huffman huff(frequecy);

    QByteArray array = frequecy.encondeArray();
    int arraySize = array.size();

    QString name = this->fileName;

    qDebug() << "Encoding:" << name;

    QString encoded;

    for(int i = 0; i < file.size(); i++){
            unsigned char c = file.at(i);
            encoded.append(huff.getHash()->value(c));
    }

    int garbageSize = 8 - encoded.size() % 8;

    for(int i = 0; i < garbageSize ; i++)
        encoded.append('0');

    bool convert;
    QByteArray encodedChar;
    for(int i = 0; i < encoded.length(); i+= 8){
            QString bin = encoded.mid(i,8);
            unsigned char c = bin.toInt(&convert,2);
            encodedChar.append(c);
    }

    QString garbageSizeToBit = fill(QString::number(garbageSize,10),3);
    QString arraySizeToBit = fill(QString::number(arraySize,10),13);
    QString nameSizeToBit = fill(QString::number(name.size(),10),8);

    QByteArray compressed;
    compressed.append(garbageSizeToBit);
    compressed.append(arraySizeToBit);
    compressed.append(nameSizeToBit);
    compressed.append(name);
    compressed.append(array);
    compressed.append(encodedChar);

    QFile out(this->outputName);
    out.resize(0);
    out.open(QIODevice::ReadWrite);
    out.write(compressed);
    out.close();

    double compressedSize = compressed.size();
    double fileSize = file.size();
    double compressionRate = 1 - compressedSize/fileSize;

    qDebug() << "Compression rate:" << compressionRate*100 << "%";

    return 0;
}

int Compress::decode(){
    QByteArray file = this->getFile();

    qDebug() << "Decoding:" << this->fileName;

    bool convert;
    int garbageSize = file.mid(0,3).toInt(&convert,10);
    int arraySize = file.mid(3,13).toInt(&convert,10);
    int nameSize = file.mid(16,8).toInt(&convert,10);

    QString name = file.mid(24,nameSize);
    QByteArray array = file.mid(24 + nameSize, arraySize);


    Frequency freq(0,array);
    Huffman huff(freq);
    QString contentBin;

    for(int i = 24 + nameSize + arraySize; i < file.size(); i++){
        unsigned char c = file.at(i);
        int decimal = c;
        contentBin.append(fill(QString::number(decimal,2),8));
    }

    QByteArray decoded;
    Node * n = huff.getTree()->root();

    for(int i = 0; i <= contentBin.size()-garbageSize; i++) {
        if (n->isLeaf()) {
            decoded.append(n->key());
            n = huff.getTree()->root();
            i--;
        }
        else {
            if (contentBin.at(i) == '0') {
                if(n->left() != NULL)
                    n = n->left();
                else
                     qDebug() << "Warning: File corrupted";
            }
            else if (contentBin.at(i) == '1') {
                if(n->right()!= NULL)
                    n = n->right();
                else
                     qDebug() << "Warning: File corrupted";
            }
            else {
                qDebug() << "Warning: File corrupted";
            }

        }
    }

    QFile out(this->outputName + name);
    out.resize(0);
    out.open(QIODevice::ReadWrite);
    out.write(decoded);
    out.close();

    return 0;
}
