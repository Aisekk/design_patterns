#pragma once
#include <map>
#include <iostream>
#include <memory>

/*
�������������� � ����������� ������ ��������������, ��� ������� ������, �������������� ���� ��� ���������� ��������� � ������ ������ ���������, 
�� ����� �� �������� �������. 
������������ ��� ����������� ������ � ������� ���� �������������� �������� ����������� ���������, ������� ����� ��������. 
Flyweight ������������ ��� ���������� ������ ��� ������ � ������� ����������� ������ ��������. 
��� �������������� Flyweight ���������� ��������� ��� �������� �� ������� � ����������. 
���������� �������� ������ ���������, ����� ��� ������� ����� ���������� � ����������� �� ����� � ��������� ���������� � ������ ���� �������� �� ������� ��������������.
Flyweight ��������� ������ Factory Method ����� �������, ��� ��� ��������� ������� � Factory Method ��� �������� ������ ������� �������������� 
���� ��� ��������� ������ � ������ �� �����������, ��� � � ����������, � ���������� ��� �������. ���� ������ ������� ���, �� ������� ������� �����.
*/

// "Flyweight"
class Character
{
public:
    virtual ~Character() = default;
    virtual void display() const = 0;

protected:
    char mSymbol;
    int  mWidth;
    int  mHeight;
    int  mAscent;
    int  mDescent;
    int  mPointSize;
};

// "ConcreteFlyweight"
class ConcreteCharacter : public Character
{
public:
    // Constructor
    ConcreteCharacter(char aSymbol, int aPointSize)
    {
        mSymbol = aSymbol;
        mWidth = 120;
        mHeight = 100;
        mAscent = 70;
        mDescent = 0;
        mPointSize = aPointSize;
    }

    // from Character
    virtual void display() const {
        std::cout << mSymbol << " ( PointSize " << mPointSize << " )\n";
    }
};

// "FlyweightFactory"
template < const int POINT_SIZE >
class CharacterFactory
{
public:
    const Character& getCharacter(char aKey)
    {
        // Uses "lazy initialization"
        Characters::const_iterator it = mCharacters.find(aKey);
        if (mCharacters.end() == it) 
        {
            mCharacters[aKey] = std::make_unique<const ConcreteCharacter>(aKey, POINT_SIZE);
            return *mCharacters[aKey];
        }
        else {
            return *it->second;
        }
    }

private:
    using Characters = std::map<char, std::unique_ptr<const Character>>;
    Characters mCharacters;
};

int flyweight()
{
    std::string document = "AAZZBBZB";

    CharacterFactory<12> characterFactory;

    for (auto ch : document) 
    {
        const auto& character = characterFactory.getCharacter(ch);
        character.display();
    }
    return 0;
}