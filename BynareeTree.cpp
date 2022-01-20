// BynareeTree.cpp 

#include <iostream>

using namespace std;
#define tab "   "
class Tree
{
protected:
    class Element
    {
        int Data;
        Element* pLeft;
        Element* pRight;
    public:
        Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :
            Data(Data), pLeft(pLeft), pRight(pRight)
        {
            cout << "EConstructor:\t" << this << endl;
        }
        ~Element()
        {
            cout << "EDestructor:\t" << this << endl;
        }
        bool is_leaf()const
        {
            return pLeft == pRight;
        }
        friend class Tree;
        friend class UniqueTree;
    }*Root; // Корень дерева
public:
    Element* getRoot()const
    {
        return Root;
    }
    Tree()
    {
        Root = nullptr;
        cout << "Tconstructor:\t" << this << endl;
    }
    Tree(const std::initializer_list<int>& il) :Tree()
    {
        for (int i : il)insert(i, Root);
    }
   Tree(const Tree& other):Tree()
    {
       copy(other.Root);
    }
    ~Tree()
    {
        Clear(Root);
        Root = nullptr;
        cout << "TDestructor:\t" << this << endl;
    }
    int depth()const
    {
        return depth(this->Root);
    }
    void insert(int Data)
    {
        insert(Data, this->Root);
    }
    void erase(int Data)
    {
        erase(Data, Root);
    }
    int minValue()const
    {
        return minValue(this->Root);
    }
    int maxValue()const
    {
        return maxValue(this->Root);
    }
    int Count()const
    {
        return Count(Root);
    }
    int Sum()const
    {
        return Sum(Root);
    }
    double Avg()const
    {
        return(double)Sum(Root) / Count(Root);
    }
    void Clear()
    {
        Clear(Root);
        Root = nullptr;
    }
    void copy(Element* Root)
    {
        if (Root == nullptr)return;
        insert(Root->Data, this->Root);
        copy(Root->pLeft);
        copy(Root->pRight);
    }
    void print()const
    {
        print(this->Root);
        cout << endl;
    }
    
    void print(int depth)const
    {
        print(this->Root, depth);
        cout << endl;
    }
    void tree_print(int dep)
    {
        tree_print(0);
    }
private:
    int depth(Element* Root)const
    {
        if (Root == nullptr)return 0;
        else return
            depth(Root->pLeft) + 1 > depth(Root->pRight) + 1 ?
            depth(Root->pLeft) + 1 : depth(Root->pRight) + 1;
    }
    void insert(int Data, Element* Root)
    {
        if (this->Root == nullptr)this->Root = new Element(Data);
        if (Root == nullptr)return;
        if (Data < Root->Data)
        {
            if (Root->pLeft == nullptr)// если есть место для добавления элемента, добавляем элемент прямо сюда
                Root->pLeft = new Element(Data);
            else// в противном случае идем навлево и ищем место куда добавить элемент 
                insert(Data, Root->pLeft);
        }
        else 
        {
            if (Root->pRight == nullptr)Root->pRight = new Element(Data);
            else insert(Data, Root->pRight);
        }
    }
    void erase(int Data, Element*& Root)
    {
        if (Root == nullptr)return;
        erase(Data, Root->pLeft);
        erase(Data, Root->pRight);
        if (Data == Root->Data)
        {
            if (Root->is_leaf())
            {
                delete Root;
                Root = nullptr;
            }
            else
            {
                if (Count(Root->pLeft) > Count(Root->pRight)) // если в левой ветке больше элементов чем в правой ветке то заменяем значение удаляемого элемента максимальным значением в левой ветке
                {
                    Root->Data = maxValue(Root->pLeft); // заменяем значение удаляемого элемента
                   //максимальным значением в левой ветке
                    erase(maxValue(Root->pLeft), Root->pLeft);
                }
                else
                {
                    Root->Data = minValue(Root->pRight);
                    erase(minValue(Root->pRight), Root->pRight);
                }
            }
        }
    }
    int minValue(Element* Root)const
    {
        if (Root->pLeft == nullptr)return Root->Data;
        else return minValue(Root->pLeft);
        
    }
    int maxValue(Element* Root)const
    {
       /* if (Root->pRight == nullptr)return Root->Data;
        else return maxValue(Root->pRight);*/
       // return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
        return Root->pRight ? maxValue(Root->pRight) : Root->Data;
    }
    int Count(Element* Root)const
    {
        /*if (Root == nullptr)return 0;
        return Count(Root->pLeft) + Count(Root->pRight) + 1;*/
        //return Root ? Count(Root->pLeft) + Count(Root->pRight) + 1 : 0;
        return !Root ? 0 : Count(Root->pLeft) + Count(Root->pRight) + 1;
    }
    int Sum(Element* Root)const
    {
        return Root ? Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data : 0;
    }
    void Clear(Element* Root)
    {
        if (Root == nullptr)return;
        Clear(Root->pLeft);
        Clear(Root->pRight);
        delete Root;
    }
    void copy(Element* Root)
    {
        if (Root == nullptr)return;
        insert(Root->Data, this->Root);
        copy(Root->pLeft);
        copy(Root->pRight);
    }
    void print(Element* Root)const
    {
        if (Root == nullptr)return;
        print(Root->pLeft);
        cout << Root->Data << tab;
        print(Root->pRight);
    }
    void print(Element* Root, int depth)const
    {
        if (Root == nullptr||depth == -1)return;
        if (depth == 1 && Root->pLeft == nullptr)cout << " " << tab;
        print(Root->pLeft, depth - 1);
        cout << tab;
        if (depth == 0)cout << Root->Data;
       //for (int i = 0; i < this->depth() * 4;i++)cout << tab;
        int min_distance = 8;
        cout.width(min_distance * (this->depth() - depth));
        if (depth == 1 && Root->pLeft == nullptr)cout << " " << tab;
        print(Root->pRight, depth - 1);
    }
    public:
    void tree_print(Element* Root, int depth)
    {
        if (depth == this->depth())return;
        int min_distance = 8;
        cout.width(min_distance * (this->depth() - depth));
       //for (int i = 0; i < (this->depth() - depth)*2; i++) cout << tab;
        print(depth);
        cout.width(min_distance * (this->depth() - depth));
        //for (int i = 0; i < (this->depth() - depth) *4; i++) cout << tab;
        cout << endl;
        tree_print(depth+1);
    }
};
Tree operator+(const Tree& left, const Tree& right)
{
    Tree res = left;
    res.copy(right.getRoot());
    return res;
}

class UniqueTree : public Tree
{
    void insert(int Data, Element* Root)
    {
        if (this->Root == nullptr)this->Root = new Element(Data);
        if (Root == nullptr)return;
        if (Data < Root->Data)
        {
            if (Root->pLeft == nullptr)// если есть место для добавления элемента, добавляем элемент прямо сюда
                Root->pLeft = new Element(Data);
            else// в противном случае идем навлево и ищем место куда добавить элемент 
                insert(Data, Root->pLeft);
        }
        else if (Data > Root->Data)
        {
            if (Root->pRight == nullptr)Root->pRight = new Element(Data);
            else insert(Data, Root->pRight);
        }
    }
public:
    void insert(int Data)
    {
        insert(Data, Root);
    }

};
//#define BASE_CHECK
void main()
{
    setlocale(LC_ALL, "");
#ifdef BASE_CHECK
    int n;
    cout << " Введите количество элементов: "; cin >> n;
    Tree tree;
    for (int i = 0; i < n; i++)
    {
        tree.insert(rand() % 100);
    }
    tree.print();
    cout << endl;
    cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
    cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
    cout << "Количество элементов в дереве: " << tree.Count() << endl;
    cout << "Сумма элементов дерева: " << tree.Sum() << endl;
    cout << "Среднее арифметическое элементов дерева: " << tree.Avg() << endl;

    UniqueTree u_tree;
    for (int i = 0; i < n; i++)
    {
        u_tree.insert(rand() % 100);
    }
    u_tree.print();
    cout << endl;
    cout << "Минимальное значение в дереве: " << u_tree.minValue() << endl;
    cout << "Максимальное значение в дереве: " << u_tree.maxValue() << endl;
    cout << "Количество элементов в дереве: " << u_tree.Count() << endl;
    cout << "Сумма элементов дерева: " << u_tree.Sum() << endl;
    cout << "Среднее арифметическое элементов дерева: " << u_tree.Avg() << endl;
    u_tree.Clear();
    u_tree.print();
#endif 
    Tree tree = { 50, 25, 75, 16, 32, 64, 80, 8, 18, 48, 77, 85 };
    tree.print();
   /* int value;
    cout << " введите удаляемое значение: "; cin >> value;
    tr.erase(value);
    tr.print();*/
    cout << " Глубина дерева: " << tree.depth() << endl;

    Tree oak = { 67,37,88,22,53 };
    oak.print();
    Tree res = tree + oak;
    res.print();
}