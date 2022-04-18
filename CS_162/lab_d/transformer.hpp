#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include <fstream>

class Transformer
{
public:
    virtual void doFilter (std::ifstream &in, std::ofstream & out);
    Transformer() { }
    ~Transformer() { }

protected:
    virtual char transform (char ch) = 0;
};

class Copy : public Transformer
{
public:
    Copy() : Transformer() { }
    ~Copy() { }

protected:
    virtual char transform (char ch);
};

class Encryption : public Transformer
{
public:
    Encryption(int keyToUse);
    ~Encryption() { }
private:
    int encryptionKey;

protected:
    virtual char transform (char ch);
};

class ToUpper : public Transformer
{
public:
    ToUpper() : Transformer() { }
    ~ToUpper() { }

protected:
    virtual char transform (char ch);
};

class OrderedOutput : public Transformer
{
public:
    void doFilter (std::ifstream &in, std::ofstream & out);
    OrderedOutput() : Transformer() { }
    ~OrderedOutput() { }

protected:
    virtual char transform (char ch);
};

#endif // TRANSFORMER_H
