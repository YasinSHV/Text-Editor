// YasinSHVtexteditor, Made By Yasin Shabani Varaki
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class LNode {
public:
    int l_ID;
    string data;
    LNode* next;
    LNode* prev;

    LNode() {
        l_ID = 0;
        data = "";
        next = NULL;
        prev = NULL;
    }
};

class LineList {
public:
    LNode* head, * tail;

    LineList() { head = tail = NULL; }
    bool IsEmpty() { return head == NULL; }
    void AddLine(string str, int lineNumber) {
        LNode* p, * q;
        p = new LNode;
        p->next = NULL;
        p->data = str;
        p->l_ID = lineNumber;

        if (IsEmpty()) {
            head = tail = p;
            p->prev = NULL;
        }
        else {
            q = head;
            while (q->next) {
                q = q->next;
            }
            q->next = p;
            p->prev = q;
        }
        tail = p;
    }
    void DeleteNode(LNode** head, LNode* del) {
        if (*head == NULL || del == NULL) {
            return;
        }
        if (*head == del) {
            *head = del->next;
        }
        if (del->next != NULL) {
            del->next->prev = del->prev;
        }
        if (del->prev != NULL) {
            del->prev->next = del->next;
        }
        return;
    }
};

class PNode {
public:
    int p_ID, lineCount;
    LineList lineList;
    PNode* next;
    PNode* prev;

    PNode() {
        p_ID = lineCount = 0;
        next = NULL;
        prev = NULL;
    }
};

class PageList {
public:
    PNode* head;
    PageList() { head = NULL; }
    bool IsEmpty() { return head == NULL; }
    void AddPage(int pageNumber, int lineCount, LineList lineList) {
        PNode* p, * q;
        p = new PNode;
        p->next = NULL;
        p->p_ID = pageNumber;
        p->lineCount = lineCount;
        p->lineList = lineList;

        if (IsEmpty()) {
            head = p;
            p->prev = NULL;
        }
        else {
            q = head;
            while (q->next) {
                q = q->next;
            }
            q->next = p;
            p->prev = q;
        }
    }
};

class Operations {
public:
    int opNumber, lineNumber, targetLine;
    string data, targetData;

    Operations(int _opNumber, int _lineNumber, int _targetNumber, string _data,
        string _targetData) {
        opNumber = _opNumber;
        lineNumber = _lineNumber;
        targetLine = _targetNumber;
        data = _data;
        targetData = _targetData;
    }
    Operations* next;
};

class MyTextEditor {
private:
    PageList pages;
    PNode* currentPage = new PNode;

    bool flag = false, busy = false;

    Operations* topU = NULL;
    Operations* topR = NULL;

public:
    MyTextEditor() {
        currentPage = pages.head;
        int choice = -1;
        string fileName = "";

        cout << " =========Welcome=========\n\n";

        do {
            cout << " Please enter the file name: (NOTE: exclude .txt)\n ";
            cin >> fileName;
        } while (Parse(fileName) != 1);

        Menu();

        while (choice != 0) {
            cout << " ";
            cin >> choice;

            switch (choice) {
            case 1: {  // show lines
                Show(Lines());
                break;
            }
            case 2: {  // next page
                NextPage();
                break;
            }
            case 3: {  // previous page
                PrevPage();
                break;
            }
            case 4: {  // show line count
                cout << " " << Lines() << "  Lines are in this page.\n";
                break;
            }
            case 5: {  // show currnent page number
                cout << " "
                    << "You are at page number: " << Where() << endl;
                break;
            }
            case 6: {  // remove given line
                int x;
                cout << "\nWhich line you want me to delete?\n" << endl;
                cin >> x;
                Remove(x);
                Show(Lines());
                Options();
                break;
            }
            case 7: {  // insert given string
                int n = 0;
                cout << "\n Enter Text:\n" << endl;
                string str;
                str = ReadLine();
                cout << "\n Where do you want me to insert this line: (Enter Line "
                    "Number)\n "
                    << endl;
                cin >> n;
                Insert(n, str);
                Show(Lines());
                Options();
                break;
            }
            case 8: {  // swap two lines
                int n, m;
                cout << "\n Which two lines do you want me to swap? (Example Input: "
                    "2 *Enter* 3 *Enter*)\n ";
                cin >> n >> m;
                Swap(n, m);
                Show(Lines());
                Options();
                break;
            }
            case 9: {  // find string instances
                cout << "\n Enter String:\n" << endl;
                string str;
                str = ReadLine();
                Find(str);
                break;
            }
            case 10: {  // replace given line string
                int n;
                cout
                    << "\n Which line do you want to replace? (Enter Line Number)\n ";
                cin >> n;
                cout << "\n Enter your string:\n";
                string str;
                str = ReadLine();
                Replace(n, str);
                Show(Lines());
                Options();
                break;
            }
            case 11: {  // find string and replace with given string
                string str1, str2;
                cout << "\n Enter string to find: \n";
                str1 = ReadLine();
                cout << "\n Enter string to replace: \n";
                str2 = ReadLine();
                FindAndReplace(str1, str2);
                Options();
                break;
            }
            case 12: {  // append given lines
                string str;
                cout << "\n Enter string to append"
                    << "(NOTE: use \\n as an identifier for next line) : \n";
                str = ReadLine();
                Append(str);
                Show(Lines());
                Options();
                break;
            }
            case 13: {  // save file
                string str;
                cout << "\n Enter Save File Name: \n ";
                cin >> str;
                Save(str);
                break;
            }
            case 14: {  // undo
                UndoOP();
                Show(Lines());
                break;
            }
            case 15: {  // redo
                RedoOP();
                Show(Lines());
                break;
            }
            case 16: {  // clear console
                system("CLS");
                Menu();
                break;
            }
            }
        }
    }

    void Menu() {
        cout << " What can I do for you?\n\n"
            << " 1- Show current page.\n 2- Go to next page.";
        cout << "\n 3- Go to previous page.\n 4- Page line Count.\n ";
        cout << "5- Current Page Number\n 6- Remove a line from current page.\n";
        cout << " 7- Insert a line to current page\n 8- Swap two lines in currnet "
            "page.\n";
        cout << " 9- Find a string location\n 10- Replace a line with a new "
            "string\n";
        cout << " 11- Find and Replace a line in every page.\n 12- Append to "
            "current page.\n";
        cout << " 13- Save File.\n 16. clear console.\n PRESS 0 TO EXIT.\n";
    }

    void Options() {
        cout << "\n====================================\n 14.Undo  15.Redo  "
            "16.Clear Screen\n====================================\n";
    }

    void Save(string fileName) {
        string str;
        PNode* p;
        p = pages.head;
        ofstream writer(fileName + ".txt");
        while (p) {
            LNode* q;
            q = p->lineList.head;
            while (q) {
                writer << q->data << endl;
                q = q->next;
            }
            writer << "$" << endl;
            p = p->next;
        }
        cout << "\n \aSaved Successfully.\n";
        writer.close();
    }

    int Parse(string fileName) {
        fileName += ".txt";
        ifstream f;
        f.open(fileName);

        if (!f) {
            cout << "\n Parse Failed!    Please Try Again.\n\n";
            return 0;
        }

        string s;
        int n = 0, m = 0;
        while (getline(f, s)) {
            n = 0;
            LineList lines = LineList();

            while (s != "$") {
                lines.AddLine(s, n);
                n++;
                getline(f, s);
                if (f.eof()) {
                    break;
                }
            }

            pages.AddPage(m, n, lines);
            m++;
        }
        cout << "\n Parse Was Successful!\n\n";
        f.close();
        currentPage = pages.head;
        return 1;
    }

    void UndoOP() {
        flag = true;
        popUndo();
        flag = false;
    }

    void RedoOP() { popRedo(); }

    void NextPage() {
        if (currentPage->next) {
            currentPage = currentPage->next;
            cout << "\nYou are in Page: " << Where() << endl;
        }
        else {
            cout << "\n No more pages.\n";
        }
    }

    void PrevPage() {
        if (currentPage->prev) {
            currentPage = currentPage->prev;
            cout << "\nYou are in Page: " << Where() << endl;
        }
        else
            cout << "\n You are in the first page.\n";
    }

    int Where() { return currentPage->p_ID + 1; }

    int Lines() { return currentPage->lineCount; }

    LNode* FindNode(int n) {
        LNode* p;
        p = currentPage->lineList.head;

        while (p->l_ID != n - 1) {
            p = p->next;
            if (!p) return NULL;
        }
        return p;
    }

    string ReadLine() {
        string str;
        while (getline(cin, str))
            if (str != "") break;
        return str;
    }

    string SubString(string str, int start, int end) {
        string newStr;
        for (int i = start; i <= end; i++) newStr += str[i];
        return newStr;
    }

    void Show(int n) {
        LNode* p;
        p = currentPage->lineList.head;
        cout << endl;
        while (p && p->l_ID != n) {
            cout << " " << p->data << endl;
            p = p->next;
        }
    }

    void Remove(int n) {
        LNode* p = FindNode(n);
        if (p) {
            currentPage->lineList.DeleteNode(&currentPage->lineList.head, p);
            if (!flag)
                Push(&topU, 1, n, 0, p->data, "");
            else
                Push(&topR, 1, n, 0, p->data, "");
        }
        else
            cout << "\n Operation Failed. NULL.\n";
        currentPage->lineCount--;
        ReID();
    }

    void Insert(int n, string str) {
        LNode* p, * q;
        q = currentPage->lineList.head;
        p = new LNode();
        p->data = str;

        if (Lines() <= n) {
            p->l_ID = currentPage->lineList.tail->l_ID;
            p->next = NULL;
            currentPage->lineList.tail->next = p;
            currentPage->lineList.tail = p;
        }
        else {
            p->l_ID = n - 1;
            p->prev = NULL;
            while (q->next && q->l_ID != n - 1) {
                q = q->next;
            }
            p->next = q;
            if (q->l_ID > 0) {
                q->prev->next = p;
                p->prev = q->prev;
            }
            else {
                currentPage->lineList.head = p;
            }
            q->prev = p;
            while (q) {
                q->l_ID = q->l_ID + 1;
                q = q->next;
            }
        }

        if (!flag)
            Push(&topU, 0, n, 0, "", "");
        else
            Push(&topR, 0, n, 0, "", "");
        currentPage->lineCount++;
        ReID();
    }

    void Append(string str) {
        int count = 0, start = 0;
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '\\' && str[i + 1] == 'n') {
                string resault = SubString(str, start, i - 1);
                currentPage->lineList.AddLine(resault, currentPage->lineCount);
                currentPage->lineCount++;
                count++;
                start = i + 2;
            }
        }
        string resault = SubString(str, start, str.length());
        currentPage->lineList.AddLine(resault, currentPage->lineCount);
        currentPage->lineCount++;
        count++;
        Push(&topU, 0, currentPage->lineCount - 1, count, "", "");
        ReID();
    }

    void Replace(int n, string str) {
        LNode* p;
        p = FindNode(n);
        if (p) {
            if (!flag)
                Push(&topU, 3, n, 0, p->data, "");
            else
                Push(&topR, 3, n, 0, p->data, "");
            p->data = str;
        }
        else
            cout << "\n Operation Failed. NULL.\n";
        ReID();
    }

    void Swap(int n, int m) {
        string str1, str2;
        LNode* p1 = FindNode(n);
        LNode* p2 = FindNode(m);
        if (p1 && p2) {
            str1 = p1->data;
            str2 = p2->data;
            p1->data = str2;
            p2->data = str1;
            if (!flag)
                Push(&topU, 4, m, n, "", "");
            else
                Push(&topR, 4, m, n, "", "");

        }
        else {
            cout << "\nOperation Failed. NULL.\n";
        }
        ReID();
    }

    void Find(string str) {
        PNode* p = pages.head;
        LNode* line = p->lineList.head;
        bool found = false;

        while (p) {
            while (line) {
                size_t searched = line->data.find(str);
                if (searched != string::npos) {
                    cout << "\n Page: " << (p->p_ID + 1) << ", Line: " << (line->l_ID + 1)
                        << "\n Data: " << line->data + ".\n";
                    found = true;
                }
                line = line->next;
            }
            p = p->next;
            if (p != nullptr) line = p->lineList.head;
        }
        if (!found) cout << "\n No Resault.\n";
    }

    void FindAndReplace(string str1, string str2) {
        PNode* p = pages.head;
        LNode* line = p->lineList.head;
        bool found = false;

        while (p) {
            while (line) {
                if (line->data.find(str1) != string::npos) {
                    line->data =
                        line->data.replace(line->data.find(str1),
                            line->data.find(str1) + str1.length(), str2);
                    found = true;
                }
                line = line->next;
            }
            p = p->next;
            if (p != nullptr) line = p->lineList.head;
        }
        if (!found)
            cout << "\n No Resault.\n";
        else {
            cout << "\n Operation Complete!\n";
            if (!flag)
                Push(&topU, 2, 0, 0, str2, str1);
            else
                Push(&topR, 2, 0, 0, str2, str1);
        }
        ReID();
    }

    void ReID() {
        LNode* q = currentPage->lineList.head;
        for (int i = 0; q; i++) {
            q->l_ID = i;
            q = q->next;
        }
    }

    /// Undo and Redo Stack

    bool IsEmpty(Operations* top) { return top == NULL; }

    void popUndo() {
        Operations* op = topU;
        if (!IsEmpty(topU)) {
            switch (op->opNumber) {
            case 0: {
                if (op->targetLine == 0) {
                    Remove(op->lineNumber);
                }
                else {
                    for (int i = 0; i < op->targetLine; i++) {
                        Remove(op->lineNumber + 1);
                        op->lineNumber--;
                    }
                }
                break;
            }
            case 1:
                Insert(op->lineNumber, op->data);
                break;
            case 2:
                FindAndReplace(op->data, op->targetData);
                break;
            case 3:
                Replace(op->lineNumber, op->data);
                break;
            case 4:
                Swap(op->lineNumber, op->targetLine);
                break;
            default:
                break;
            }
            topU = topU->next;
        }
        else
            cout << "\n==================\n Nothing To UNDO\n==================\n";
    }

    void popRedo() {
        Operations* op = topR;
        if (!IsEmpty(topR)) {
            switch (op->opNumber) {
            case 0:
                Remove(op->lineNumber);
                break;
            case 1:
                Insert(op->lineNumber, op->data);
                break;
            case 2:
                FindAndReplace(op->data, op->targetData);
                break;
            case 3:
                Replace(op->lineNumber, op->data);
                break;
            case 4:
                Swap(op->lineNumber, op->targetLine);
                break;
            default:
                break;
            }
            topR = topR->next;
        }
        else
            cout << "\n==================\n Nothing To REDO\n==================\n";
    }

    void Push(Operations** top, int _opNumber, int _lineNumber, int _targetNumber,
        string _data, string _targetData) {
        Operations* op = new Operations(_opNumber, _lineNumber, _targetNumber,
            _data, _targetData);

        op->next = NULL;
        if (!IsEmpty(*top)) op->next = *top;
        *top = op;
    }
};

int main() { MyTextEditor app; }