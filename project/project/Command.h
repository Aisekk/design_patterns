#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
Паттерн комманда включает в себя:
 комманда (command);
 приемник комманд (receiver);
 объект, вызывающий комманды (invoker);
 клиент (client)
 */

class Document // Receiver
{
    vector<string> _data;
public:
    Document()
    {
        _data.reserve(100); // at least for 100 lines
    }

    void Insert(int line, const string& str)
    {
        if (line <= _data.size())
            _data.insert(std::next(_data.begin(), line), str);
        else
            cout << "Error!" << endl;
    }

    void Remove(int line)
    {
        if (line <= _data.size())
            _data.erase(std::next(_data.begin(), line));
        else
            cout << "Error!" << endl;
    }

    string& operator [] (int x)
    {
        return _data[x];
    }

    void Show()
    {
        for (int i = 0; i < _data.size(); ++i)
        {
            cout << i + 1 << ". " << _data[i] << endl;
        }
    }
};

class Command
{
protected:
    Document* _doc = nullptr;
public:
    virtual ~Command() {}
    virtual void Execute() = 0;
    virtual void unExecute() = 0;

    void setDocument(Document* doc)
    {
        _doc = doc;
    }
};

class InsertCommand : public Command
{
    int _line;
    string _str;
public:
    InsertCommand(int line, const string& str) : _line(line), _str(str) {}

    void Execute() override
    {
        _doc->Insert(_line, _str);
    }

    void unExecute() override
    {
        _doc->Remove(_line);
    }
};

class Invoker
{
    vector<Command*> _doneCommands;
    Document* _doc = nullptr;
    Command* _command = nullptr;
public:
    Invoker() : _doc(new Document) {}
    ~Invoker() { delete _doc; }

    void Insert(int line, string str)
    {
        auto command = new InsertCommand(line, str);
        command->setDocument(_doc);
        command->Execute();
        _doneCommands.push_back(command);
        _command = command;
    }

    void Undo()
    {
        if (_doneCommands.size() == 0)
        {
            cout << "There is nothing to undo!" << endl;
        }
        else
        {
            auto command = _doneCommands.back();
            _doneCommands.pop_back();
            command->unExecute();
            // Don't forget to delete command!!!
            delete command;
        }
    }

    void Show()
    {
        _doc->Show();
    }
};

void command() // Client
{
    cout << "=========== COMMAND ===========" << endl;
    char s = '1';
    int line = 1;
    string str;
    Invoker inv;
    while (s != 'e')
    {
        cout << "What to do: \n1.Add a line\n2.Undo last command" << endl;
        cin >> s;
        switch (s)
        {
        case '1':
            cout << "What line to insert: ";
            cin >> line;
            cout << "What to insert: ";
            cin >> str;
            inv.Insert(line, str);
            break;
        case '2':
            inv.Undo();
            break;
        }
        cout << "$$$DOCUMENT$$$" << endl;
        inv.Show();
        cout << "$$$DOCUMENT$$$" << endl;
    }
}
