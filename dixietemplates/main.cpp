#include "main.h"

#include <StringMap.h>
#include <PhoneContacts.h>
#include <Queue.h>
#include <Stack.h>
#include <RingQueue.h>

void Main::start(int argc, char **argv)
{
    test1();  // Test using: StringMap *myMap = new StringMap();
    test2();  // Test using: PhoneContacts *myPhoneContacts = new PhoneContacts();
    test3();  // Test using: LinkedList Queue Stack and RingQueue
    
    print("All Tests are successful!", TTY_RED);
    pressAnyKey();
    setTtyColor(TTY_NORMAL);
    newLine();
    return;    
}

void Main::test1()
{
    print("This is test1() using: StringMap *myMap = new StringMap();", TTY_BLUE);
    //-------------------------------------
    // Create a StringMap...
    //-------------------------------------
    StringMap *myMap = new StringMap();

    //-------------------------------------
    // See if it's empty
    //-------------------------------------
    if(myMap->isEmpty())
        print("Newly created StringMap is empty");
    else
        print("*** ERROR: Newly created StringMap WAS NOT EMPTY!", TTY_RED);
        
    //-----------------------------------------------------------
    // Create a simple dictionary  of names and their nicknames  
    //----------------------------------------------------------- 
    myMap->insert("Megan Williams", "Dixie");
    myMap->insert("Titus Williams", "Little Brother");
    myMap->insert("Alicia Elett"  , "The Awesome Girl");
    myMap->insert("Darenne Poyser", "Pookie");
    myMap->insert("Erik Simon"    , "Erik Simon");

    if(!myMap->isEmpty()) 
        print("StringMap has "+ dixieString(myMap->getSize()) +" entries");
    else
        print("*** ERROR: StringMap is empty should have count > 0", TTY_RED);

    //---------------------------------------------------------------
    // Now we get the nicknames in our dictionary based on name...
    // the last try should throw exception because it was not added
    //---------------------------------------------------------------
    try{
    string name;
    string nickname;
       
    name="Alicia Elett";
    nickname = myMap->select(name);
    print(name+ " nickname is :"+ nickname);

    name="Darenne Poyser";
    nickname = myMap->select(name);
    print(name+ " nickname is :"+ nickname);

    name="Megan Williams";
    nickname = myMap->select(name);
    print(name+ " nickname is :"+ nickname);

    name="Titus Williams";
    nickname = myMap->select(name);
    print(name+ " nickname is :"+ nickname);

    name="Erik Simon";
    nickname = myMap->select(name);
    print(name+ " also known as :"+ nickname);

    print("now we're gonna delete "+name);
    myMap->remove(name);

    print(name+" should NOT be in dictionary -- expecting exception thrown");
    nickname = myMap->select(name);
    }
    catch(std::exception &e)
    {
    print("select throw this: "+string(e.what()), TTY_RED);
    }
    //-------------------------------------------------------------
    // perform drop an recheck count...
    //-------------------------------------------------------------
    print("OK, now the count is "+dixieString(myMap->getSize()));
    print("But after calling drop()...");
    myMap->drop();
    print("The current count is "+dixieString(myMap->getSize()));
    //-------------------------------------------------------------
    // tests on alias entries
    //-------------------------------------------------------------
    try{
    string name;
    string nickname;

    name="Titus Williams";
    print("Now, I'm gonna add "+name+" 3 times");
    myMap->insert(name, "Little Brother");
    myMap->insert(name, "Ty");
    myMap->insert(name, "Mr. Fantabulous");
    print("The current count is "+dixieString(myMap->getSize()));

    print("Now, I'm gonna try select() and remove() 4 times using "+name+ "-- the last one should fail...");
    for(int i=0; i < 4; i++)
    {
        nickname = myMap->select(name);
        print(name+" also known as :"+ nickname);
        myMap->remove(name);
        print("The current count is "+dixieString(myMap->getSize()));
    }
    }	
    catch(std::exception &e)
    {
    print("getValue throw this: "+string(e.what()), TTY_RED);
    }

    delete myMap;
    print("myMap object is now deleted", TTY_BLUE);

    pressAnyKey();
    setTtyColor(TTY_NORMAL);
    newLine();
    return;
}

void Main::test2()
{
    print("This is test2() using: PhoneContacts *myPhoneContacts = new PhoneContacts();", TTY_BLUE);
    //-------------------------------------
    // Create a PhoneContacts...
    //-------------------------------------
    PhoneContacts *myPhoneContacts = new PhoneContacts();

    string name;
    try{

    PhoneContacts::PHONE_CONTACT contact;    // the contact we set into record
    PhoneContacts::PHONE_CONTACT contact2;   // the contact record we get back
    
    contact.name    ="Alicia Elett";
    contact.nickname="The Awesome Girl";
    contact.phone   ="111-111-1111";
    contact.email   ="alicia@metaqueue.net";
    myPhoneContacts->insert("Alicia"  , contact);

    contact.name    ="Megan Williams";
    contact.nickname="Dixie";
    contact.phone   ="222-222-2222";
    contact.email   ="dixie@metaqueue.net";
    myPhoneContacts->insert("Megan", contact);

    contact.name    ="Titus Williams";
    contact.nickname="Little Brother";
    contact.phone   ="333-333-3333";
    contact.email   ="ty@metaqueue.net";    
    myPhoneContacts->insert("Titus"  , contact);

    contact.name    ="Darenne Poyser";
    contact.nickname="Pookie";
    contact.phone   ="444-444-4444";
    contact.email   ="pook@metaqueue.net";    
    myPhoneContacts->insert("Dee", contact);
    
    contact.name    ="Erik Simon";
    contact.nickname="Erik Simon";
    contact.phone   ="555-555-5555";
    contact.email   ="bignothing@metaqueue.net";    
    myPhoneContacts->insert("Erik", contact);
    
    name="Alicia";
    contact2 = myPhoneContacts->select(name);
    print(name+ " fullname is :"+ contact2.name);
    print(name+ " nickname is :"+ contact2.nickname);
    print(name+ " phone    is :"+ contact2.phone);
    print(name+ " email    is :"+ contact2.email);

    name="Dee";
    contact2 = myPhoneContacts->select(name);
    print(name+ " fullname is :"+ contact2.name);
    print(name+ " nickname is :"+ contact2.nickname);
    print(name+ " phone    is :"+ contact2.phone);
    print(name+ " email    is :"+ contact2.email);

    name="Megan";
    contact2 = myPhoneContacts->select(name);
    print(name+ " fullname is :"+ contact2.name);
    print(name+ " nickname is :"+ contact2.nickname);
    print(name+ " phone    is :"+ contact2.phone);
    print(name+ " email    is :"+ contact2.email);

    name="Titus";
    contact2 = myPhoneContacts->select(name);
    print(name+ " fullname is :"+ contact2.name);
    print(name+ " nickname is :"+ contact2.nickname);
    print(name+ " phone    is :"+ contact2.phone);
    print(name+ " email    is :"+ contact2.email);

    name="Erik";
    contact2 = myPhoneContacts->select(name);
    print(name+ " fullname is :"+ contact2.name);
    print(name+ " nickname is :"+ contact2.nickname);
    print(name+ " phone    is :"+ contact2.phone);
    print(name+ " email    is :"+ contact2.email);

    pressAnyKey();
    setTtyColor(TTY_NORMAL);
    newLine();

    print("Now, creating a Queue like this: Queue<PhoneContacts::PHONE_CONTACT> *queue = new Queue<PhoneContacts::PHONE_CONTACT>; ", TTY_BLUE);
    Queue<PhoneContacts::PHONE_CONTACT> *queue = new Queue<PhoneContacts::PHONE_CONTACT>;

    print("...we're gonna dump() phone contacts and dequeue() all of Queue", TTY_BLUE);
    myPhoneContacts->dump(queue);
    while(!queue->isEmpty())
    {
	contact2 = queue->dequeue();
        print(" fullname is :"+ contact2.name);
        print(" nickname is :"+ contact2.nickname);
        print(" phone    is :"+ contact2.phone);
        print(" email    is :"+ contact2.email);
        newLine();
    }
    	
    print("now we're gonna delete "+name);
    myPhoneContacts->remove(name);
    
    print(name+" should NOT be in dictionary -- expecting exception thrown");
    contact2 = myPhoneContacts->select(name);
    }
    catch(std::exception &e)
    {
    print("select throw this: "+string(e.what()), TTY_RED);
    }

    delete myPhoneContacts;
    print("myPhoneContacts object is now deleted", TTY_BLUE);

    pressAnyKey();
    setTtyColor(TTY_NORMAL);
    newLine();
    return;
}
void Main::test3()
{
    print("This is test3() using: LinkedList<string> *myList = new LinkedList<string>;", TTY_BLUE);

    LinkedList<string> *myList = new LinkedList<string>;
    myList->add("1st");
    myList->add("2nd");
    myList->add("3rd");
    myList->add("4th");
    myList->add("5th");

    Node<string> *n=myList->getFirst();
    for(int i=0; i < 5; i++)
    {
	print(dixieString(i)+" "+n->getData());
	n = n->getNext();
    }
    myList->insert(1, "inserted");
    newLine();
    Node<string> *n1=myList->getFirst();
    for(int i=0; i < 6; i++)
    {
	print(dixieString(i)+" "+n1->getData());
	n1 = n1->getNext();
    }
    
    print("Now, lets get all these by using myList->getNode(i)->getData()", TTY_BLUE);
    for(int i=0; i < 6; i++)
    {
	print(dixieString(i)+" "+myList->getNode(i)->getData());
    }    

    pressAnyKey();
    setTtyColor(TTY_NORMAL);
    newLine();
    
    print("Now let's test a Queue -- Queue<string> *q = new Queue<string>; ", TTY_BLUE);

    Queue<string> *q = new Queue<string>;
    
    print("enqueue 1st, 2nd and 3rd...");
    q->enqueue("1st");
    q->enqueue("2nd");
    q->enqueue("3rd");

    print("dequeue 3 times...", TTY_BLUE);
    print(q->dequeue());
    print(q->dequeue());
    print(q->dequeue());
    
    print("Now let's test a Stack -- Stack<string> *t = new Stack<string>; ", TTY_BLUE);

    Stack<string> *t = new Stack<string>;

    print("push 1st, 2nd, 3rd, 4th and 5th...", TTY_BLUE);
    t->push("1st");
    t->push("2nd");
    t->push("3rd");
    t->push("4th");
    t->push("5th");

    print("now while(!t->isEmpty()) print(t->pop())", TTY_BLUE);
    while(!t->isEmpty())
        print(t->pop());

    print("Now let's test a RingQueue -- RingQueue<string> *rq = new RingQueue<string>; ", TTY_BLUE);

    RingQueue<string> *rq = new RingQueue<string>;

    print("add 1st, 2nd and 3rd...", TTY_BLUE);
    rq->add("1st");
    rq->add("2nd");
    rq->add("3rd");

    print("getnext() 10 times it will be circular...", TTY_BLUE);
    for(int i=0; i< 10;i++)
        print(rq->getNext());

    pressAnyKey();
    setTtyColor(TTY_NORMAL);
    newLine();
   
}


int main(int argc, char **argv)
{
    Main *mainApp = new Main();    // Construct this terminal app
    mainApp->setAllowColor(true);  // Set this to false if you don't want color terminal
    mainApp->start(argc, argv);    // Start app with standard arguments
    delete mainApp;                // delete app...
    return 0;                      // return to command line...
}
 
