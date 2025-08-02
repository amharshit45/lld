#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

class DocumentElement {
public:
    virtual string render() = 0;
};

class TextElement: public DocumentElement {
    string text;
public:
    TextElement(string text) {
        this -> text = text;
    }
    string render() override {
        return text + "\n";
    }
};

class ImageElement: public DocumentElement {
    string imgPath;
public:
    ImageElement(string imgPath) {
        this -> imgPath = imgPath;
    }
    string render() override {
        return "[Image: " + imgPath + "]\n";
    }
};

class TabElement: public DocumentElement {
    public:
    string render() override {
        return "\t";
    }
};

class Document {
public: 
    vector<DocumentElement*> docElements;
    void addElement(DocumentElement* el) {
        docElements.push_back(el);
    }
    vector<DocumentElement*> getElements() {
        return docElements;
    }
};

class Persistence {
public:
    virtual void save(string data) = 0;
};

class FileStorage: public Persistence {
public:
    void save(string data) override {
        ofstream outFile("doc.txt");
        if (outFile) {
            outFile << data;
            outFile.close();
            cout << "Document saved to doc.txt\n";
        } else {
            cout << "Trouble opening file for writing. \n";
        }
    }
};

class DocumentRenderer {
    Document* doc;
    string renderedDoc;
public:
    DocumentRenderer(Document* doc) {
        this -> doc = doc;
    }
    string render() {
        if (renderedDoc.size()) return renderedDoc;
        string rDocument;
        for (auto& x: doc -> docElements) {
            rDocument += x -> render();
        }
        return rDocument;
    }
};

class DocumentEditor {
    Document* doc;
    Persistence* ps;
public:
    DocumentEditor(Document* doc, Persistence* ps) {
        this -> doc = doc;
        this -> ps = ps;
    }
    void addText(string text) {
        doc -> addElement(new TextElement(text));
    }
    void addImage(string imgPath) {
        doc -> addElement(new ImageElement(imgPath));
    }
    void addTab() {
        doc -> addElement(new TabElement());
    }
};


int main () {
    Document* doc = new Document();
    Persistence* ps = new FileStorage();
    DocumentRenderer* dr = new DocumentRenderer(doc);

    DocumentEditor* docEditor = new DocumentEditor(doc, ps);
    docEditor -> addText("Hello, I am Harshit.");
    docEditor -> addText("I am trying to learn OOPs and LLD.");
    docEditor -> addImage("img.jpg");
    docEditor -> addTab();
    docEditor -> addText("This is an image of me crying.");

    string renderedDocument = dr -> render();
    cout << renderedDocument;
    ps -> save(renderedDocument);
}