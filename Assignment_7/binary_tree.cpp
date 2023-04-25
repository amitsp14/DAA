#include <iostream>

using namespace std;

class Node
{
public:
    Node *destra;   /// prossimo nodo a destra
    Node *sinistra; /// prossimo nodo a sinistra
    int valore;
    int livello;
    Node *padre;
    Node()
    {
        destra = NULL;
        sinistra = NULL;
        padre = NULL;
        valore = 0;
        livello = 0;
    }
    Node(int valore)
    {
        this->valore = valore;
        this->livello = livello;
        this->sinistra = NULL;
        this->destra = NULL;
        this->padre = NULL;
    }
};
class alberobinario
{
    Node *head;

public:
    // Default constructor
    alberobinario() { head = NULL; }
    void cancellazione(int);
    void insertNode(int);
    void ricorsione(int, Node *, int);
    void print(Node *);
    void printe()
    {
        Node *temp = head;
        /// cout<<head<<endl;
        cout << "  (" << temp->valore << ")" << endl; ///") livello: "<<temp->livello<<"padre :"<<temp->padre;
        if (temp->sinistra != NULL)
        {
            print(temp->sinistra);
        }
        if (temp->destra != NULL)
        {
            print(temp->destra);
            cout << endl;
        }
    };
    void transplantdx(Node *root, Node *u, Node *v)
    {
        if (root == NULL)
        {
            root = v;
        }
        else if (u == u->padre->sinistra)
        {
            u->sinistra = v;
            u->padre->sinistra = v;
        }
        else
        {
            cout << "oiu" << endl;
            u->padre->destra = v;
        }
        if (v != NULL)
            v->padre = u->padre;
    }
};
void alberobinario::insertNode(int valore)
{
    int livello = 0;
    // Create the new Node.
    Node *newNode = new Node(valore);

    // Assign to head
    if (head == NULL)
    {
        head = newNode;
        head->livello = 0;
        /// cout<<head<<endl;
        return;
    }
    ricorsione(valore, head, livello);
}
void alberobinario::ricorsione(int valore, Node *head, int livello)
{
    Node *temp = head;
    Node *temp2 = temp;
    Node *newNode = new Node(valore);
    /// cout<<temp<<endl;
    // Traverse till end of list
    if (temp->valore < valore)
    { /// cout<<"wo"<<endl;
        if (temp->destra == NULL)
        { /// cout<<"ehi"<<endl;
            temp->destra = newNode;
            temp = temp->destra;
            temp->padre = temp2;
            temp->livello = livello + 1;
            /// cout<<temp->destra<<endl;
        }
        else
        {
            temp = temp->destra; /// cout<<temp<<endl;
            ricorsione(valore, temp, livello + 1);
        }
    }
    else if (temp->valore > valore)
    { /// cout<<"wa"<<endl;
        if (temp->sinistra == NULL)
        { /// cout<<"p"<<endl;done by domenico zeno
            temp->sinistra = newNode;
            temp = temp->sinistra;
            temp->padre = temp2;
            temp->livello = livello + 1;
        }
        else
        {
            temp = temp->sinistra;
            ricorsione(valore, temp, livello + 1);
        }
        // Insert at the last.
    }
}
// Function to print the
// Nodes of the linked list.
void alberobinario::print(Node *head)
{
    Node *temp = head;
    /// cout<<head<<endl;
    cout << "(" << temp->valore << ") "; ///") livello: "<<temp->livello<<"padre :"<<temp->padre;
    if (temp->sinistra != NULL)
    {
        cout << endl;
        print(temp->sinistra);
    }
    if (temp->destra != NULL)
    {
        print(temp->destra);
    }
}
void alberobinario::cancellazione(int valore)
{
    Node *temp = head;
    Node *temp2 = temp;
    Node *temp3 = temp;
    while (valore != temp->valore && temp->destra != NULL && temp->sinistra != NULL)
    {
        if (temp->valore < valore)
        {
            temp = temp->destra;
        }
        else
        {
            temp = temp->sinistra;
        }
    }
    if (temp == head)
    {
        head = temp->sinistra;
        temp3 = temp->sinistra;
        while (temp3->destra != NULL)
        {
            temp3 = temp3->destra;
        }
        temp3->destra = temp->destra;
    }
    else
    {
        temp2 = temp->padre;
        if (temp->sinistra == NULL)
        {
            transplantdx(temp2, temp, temp->destra);
        }
        else if (temp->destra == NULL)
        {
            transplantdx(temp2, temp, temp->sinistra);
        }
        else if (temp == temp2->destra)
        {
            temp2->destra = temp->sinistra;
            temp3 = temp->sinistra;
            while (temp3->destra != NULL)
            {
                temp3 = temp3->destra;
            }
            temp3->destra = temp->destra;
        }
        else
        {
            temp2->sinistra = temp->sinistra;
            temp3 = temp->sinistra;
            while (temp3->destra != NULL)
            {
                temp3 = temp3->destra;
            }
            temp3->destra = temp->destra;
        }
    }
}
int main()
{
    int valore;
    alberobinario x;
    int i = 0;
    int k = 0;
    cout << "quanti valori devi inserire?" << endl;
    cin >> k;
    while (i < k)
    {
        cout << "inserire valore" << endl;
        cin >> valore;
        x.insertNode(valore);
        i++;
    }
    x.printe();
    cout << "inserire valore da cancellare" << endl;
    cin >> k;
    x.cancellazione(k);
    x.printe();
    return 0;
}